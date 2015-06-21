#!/bin/bash

CYAN="\\033[1;36m"
NORMAL="\\033[0;39m"
RED="\\033[1;31m"

mkdir -p build
cd build 
rm -rf *

echo -e "$CYAN" "Build iOS application for iOS Device or Simulator ?" "$NORMAL"
select response in "iOS Device" "iOS Simulator"
do
	case $response in
		"iOS Device") 
			IOS_PLATFORM="OS"
			CMAKE_IOS_SDK_ROOT="$(xcrun --sdk iphoneos --show-sdk-path)"
			SDK="iphoneos"
			break
			;;
		"iOS Simulator")
			IOS_PLATFORM="SIMULATOR"
			CMAKE_IOS_SDK_ROOT="$(xcrun --sdk iphonesimulator --show-sdk-path)"
			SDK="iphonesimulator"
			break
			;;
		*)
			echo -e "$RED" "Invalid option" "$NORMAL"
			;;
	esac
done

cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain/iOS.cmake \
	-DIOS_PLATFORM=$IOS_PLATFORM \
	-DCMAKE_IOS_SDK_ROOT="$CMAKE_IOS_SDK_ROOT" \
	-GXcode ..

xcodebuild -sdk $SDK

echo "Building operations done, you can run 'xcrun instruments -w \"DEVICE_NAME\"' "
echo "to start the simulator on your machine (run 'xcrun instruments -s' to list available devices)"
echo " "
echo "After running the simulator just install your app with this command :"
echo "xcrun simctl install booted build/DEBUG_OR_RELEASE_DIR/APP_NAME.app"