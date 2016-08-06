import os
import subprocess

subprocess.call("ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk TARGET_OUT=../../staticlibs/$(TARGET_ARCH_ABI)", shell=True)