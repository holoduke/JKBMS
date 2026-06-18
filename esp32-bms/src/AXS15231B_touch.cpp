#include "AXS15231B_touch.h"

AXS15231B_Touch* AXS15231B_Touch::instance = nullptr;

bool AXS15231B_Touch::begin() {
    instance = this;
    attachInterrupt(digitalPinToInterrupt(int_pin), isrTouched, FALLING);
    return (Wire.begin(sda, scl));
}

ISR_PREFIX
void AXS15231B_Touch::isrTouched() {
    if (instance) instance->touch_int = true;
}

void AXS15231B_Touch::setRotation(uint8_t rot) { rotation = rot; }

bool AXS15231B_Touch::touched() { return update(); }

void AXS15231B_Touch::readData(uint16_t *x, uint16_t *y) { *x = point_X; *y = point_Y; }

void AXS15231B_Touch::enOffsetCorrection(bool en) { en_offset_correction = en; }

void AXS15231B_Touch::setOffsets(uint16_t x_real_min, uint16_t x_real_max, uint16_t x_ideal_max,
                                 uint16_t y_real_min, uint16_t y_real_max, uint16_t y_ideal_max) {
    this->x_real_min = x_real_min; this->x_real_max = x_real_max;
    this->y_real_min = y_real_min; this->y_real_max = y_real_max;
    this->x_ideal_max = x_ideal_max; this->y_ideal_max = y_ideal_max;
}

void AXS15231B_Touch::correctOffset(uint16_t *x, uint16_t *y) {
    *x = map(*x, x_real_min, x_real_max, 0, x_ideal_max);
    *y = map(*y, y_real_min, y_real_max, 0, y_ideal_max);
}

bool AXS15231B_Touch::update() {
    if (!touch_int) return false;
    touch_int = false;

    uint8_t tmp_buf[8] = {0};
    static const uint8_t read_touchpad_cmd[8] = {0xB5, 0xAB, 0xA5, 0x5A, 0x00, 0x00, 0x00, 0x08};

    Wire.beginTransmission(addr);
    Wire.write(read_touchpad_cmd, sizeof(read_touchpad_cmd));
    Wire.endTransmission();

    Wire.requestFrom(addr, sizeof(tmp_buf));
    for (int i = 0; i < (int)sizeof(tmp_buf) && Wire.available(); i++) tmp_buf[i] = Wire.read();

    uint16_t raw_X = AXS_GET_POINT_X(tmp_buf);
    uint16_t raw_Y = AXS_GET_POINT_Y(tmp_buf);

    if (point_X || point_Y) {
        if (raw_X > x_real_max) raw_X = x_real_max;
        if (raw_X < x_real_min) raw_X = x_real_min;
        if (raw_Y > y_real_max) raw_Y = y_real_max;
        if (raw_Y < y_real_min) raw_Y = y_real_min;
    }

    uint16_t x_max, y_max;
    if (en_offset_correction) {
        correctOffset(&raw_X, &raw_Y);
        x_max = x_ideal_max; y_max = y_ideal_max;
    } else {
        x_max = x_real_max; y_max = y_real_max;
    }

    switch (rotation) {
        case 0: point_X = raw_X;         point_Y = raw_Y;         break;
        case 1: point_X = raw_Y;         point_Y = x_max - raw_X; break;
        case 2: point_X = x_max - raw_X; point_Y = y_max - raw_Y; break;
        case 3: point_X = y_max - raw_Y; point_Y = raw_X;         break;
        default: break;
    }
    return true;
}
