#!/bin/bash
SDK_ROOT=/opt/android-sdk-linux
APP_NAME=SDLActivity
PACKAGE_NAME=org.libsdl.app

ant debug -Dsdk.dir=$SDK_ROOT

adb -d install -r bin/$APP_NAME-debug.apk

adb shell am start -n $PACKAGE_NAME/$PACKAGE_NAME.$APP_NAME
