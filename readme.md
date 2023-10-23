# DynDebloater Installation Guide

This guide will walk you through the process of downloading, customizing, compiling, and flashing the DynDebloater onto your Android device.
It consists of a customized AOSP and a management app.

## Summary of Steps

1. [Download the Source Code of AOSP](#step-1-download-the-source-code-of-aosp)
2. [Customize Your AOSP Repository](#step-2-customize-your-aosp-repository)
3. [Download Device Drivers](#step-3-download-device-drivers)
4. [Compile AOSP](#step-4-compile-aosp)
5. [Flash AOSP to Your Device](#step-5-flash-aosp-to-your-device)

## Step 1: Download the Source Code of AOSP

Begin by downloading the AOSP source code to your computer.

```shell
mkdir aosp && cd aosp
repo init -u https://android.googlesource.com/platform/manifest -b android-13.0.0_r11   # For Android 13
repo sync -c -j$(nproc --all)     # Sync the current branch using all available processing units in the system
``````



## Step 2: Customize Your AOSP Repository
Download our custom repository containing the necessary code modifications and merge it with the original AOSP source code, overwriting existing files.

For example, if you are using a device other than Pixel 7 Pro (Cheetah), follow these steps:

1. Download our custom repository containing the modifications.

2. Merge the contents of this repository with the downloaded AOSP source code, overwriting existing files. Ensure that your custom code is correctly integrated.

   ```shell
   cp -r path-to-downloaded-custom-repo/* path-to-downloaded-original-aosp/
    ```



  Depending on your target device, you may need to add specific code to the device configuration files. For instance, if you are using Pixel 4a (Sunfish), add the following code to <b>AOSP/device/google/sunfish/device-sunfish.mk:</b>
  ```shell
  PRODUCT_PACKAGES += MINIMAManager
```
This code is for adding the management app into the pre-installed app list.


If your target device is <b>Cheetah (Pixel 7 Pro)</b>, no additional customizations are required. We have already configured the necessary settings for this device in our custom repository. <br>Simply download our custom repository containing the modifications and merge it with the original AOSP source code, overwriting existing files.



## Step 3: Download Device Drivers
Visit the [Google Android drivers page](https://developers.google.com/android/drivers )
 to download the device drivers required for your target device. Extract the downloaded driver package into the AOSP root directory.
  We implemented DynDebloater on Pixel 7 pro with Android 13(TD1A.220804.031), and the download link is https://dl.google.com/dl/android/aosp/google_devices-cheetah-td1a.220804.031-d59f7f42.tgz
  
  Decompress the downloaded .tgz files and put the two .sh files into the AOSP folder.
	Execute the two .sh files which will download the drivers into the folder vender/
  You can choose your own device's driver with Android 13, but we have not tested other devices yet.

## Step 4: Compile AOSP
Set up the build environment and compile AOSP. Make sure to replace \<your-device-code\> with the appropriate device code. 
(You can use command 'lunch' to list out all the device code). Here the device code of Pixel 13 pro is 20.

``` shell
source build/envsetup.sh
lunch <your-device-code>
make -j8 # it will compile the AOSP using 8 threads
```

## Step 5: Flash AOSP to Your Device
After successfully compiling AOSP, follow these steps to flash the custom ROM to your device. Ensure that your device's bootloader is unlocked.
(https://source.android.com/docs/core/architecture/bootloader/locking_unlocking)

``` shell
adb reboot bootloader  # Make sure your device's bootloader is unlocked before proceeding.
fastboot -w flashall

```

To use the DynDebloater, please refer to this video (https://youtu.be/zEzBMxf1Vf8).
The example app and corresponding debloating schema are included in /example