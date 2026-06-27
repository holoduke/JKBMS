#  Auto-versioning: derive FW_VERSION from git at build time so every commit
#  produces a fresh, unique version with no manual edits.
#
#  Version = "<BASE>.<patch>" where patch = total commit count on HEAD. If the
#  working tree is dirty (uncommitted changes — i.e. you're about to commit),
#  patch is bumped by one so the firmware you build now is already labelled with
#  the version it will have once committed. That keeps the flashed build and the
#  commit that contains it in sync in the usual edit -> build -> flash -> commit flow.
#
#  Bump BASE (e.g. to "1.1" or "2.0") when you want a new minor/major line.
import subprocess

Import("env")  # noqa: F821  (injected by PlatformIO/SCons)

BASE = "1.0"


def git(args, default=""):
    try:
        return subprocess.check_output(["git"] + args, stderr=subprocess.DEVNULL).decode().strip()
    except Exception:
        return default


count = git(["rev-list", "--count", "HEAD"], "0")
dirty = git(["status", "--porcelain"]) != ""
try:
    patch = int(count) + (1 if dirty else 0)
except ValueError:
    patch = 0

version = "%s.%d" % (BASE, patch)
print("Firmware version: %s%s" % (version, "  (uncommitted changes)" if dirty else ""))

env.Append(CPPDEFINES=[("FW_VERSION", env.StringifyMacro(version))])  # noqa: F821
