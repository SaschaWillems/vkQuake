import os
import shutil
import subprocess
import sys
import glob

if subprocess.call("ndk-build", shell=True) == 0:
    print("Build successful")

    VALIDATION = False

    for arg in sys.argv[1:]:
        print(arg)
        if arg == "-validation":
            VALIDATION = True
            break

    # Copy validation layers
    if VALIDATION:
        print("Validation enabled, copying validation layers...")
        os.makedirs("./libs/armeabi-v7a", exist_ok=True)
        for file in glob.glob("layers/armeabi-v7a/*.so"):
            print(file + "\n")
            shutil.copy(file, "./libs/armeabi-v7a")

    if subprocess.call("ant debug -Dout.final.file=vkQuake.apk", shell=True) == 0:
        for arg in sys.argv[1:]:
            if arg == "-deploy":
                if subprocess.call("adb install -r vkQuake.apk", shell=True) != 0:
                    print("Could not deploy to device!")

    else:
        print("Error during build process!")

else:
    print("Error building project!")
