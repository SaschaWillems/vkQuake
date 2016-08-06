import os
import shutil
import subprocess
import sys

if subprocess.call("ndk-build", shell=True) == 0:
    print("Build successful")

    if subprocess.call("ant debug -Dout.final.file=vkQuake.apk", shell=True) == 0:
        if sys.argv[1] == "-deploy":

            if subprocess.call("adb install -r vkQuake.apk", shell=True) != 0:
                print("Could not deploy to device!")

    else:
        print("Error during build process!")

else:
    print("Error building project!")
