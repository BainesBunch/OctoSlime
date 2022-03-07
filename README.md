# Octo Slime Tracker firmware for ESP

Firmware for ESP8266 / ESP32 microcontrollers and the MPU-6050 IMU sensors to use them as a vive-like trackers in VR.

Requires [SlimeVR Server](https://github.com/SlimeVR/SlimeVR-Server) to work with SteamVR and resolve pose. Should be compatible with [owoTrack](https://github.com/abb128/owo-track-driver), but is not guaranteed.

## Configuration

Firmware configuration is located in the `defines.h` file. For more information on how to configure your firmware, refer to the [Configuring the firmware project section of SlimeVR documentation](https://docs.slimevr.dev/firmware/configuring-project.html).

## Compatibility

The following IMUs are supported by the firmware:

* MPU-6500 (IMU_MPU6500) & MPU-6050 (IMU_MPU6050)
  * Using internal DMP to fuse Gyroscope and Accelerometer. Can drift substantially.
  * NOTE: Currently the MPU will auto calibrate when powered on. You *must* place it on the ground and *DO NOT* move it until calibration is complete (for a few seconds). **LED on the ESP will blink 5 times after calibration is over.**

Firmware can work with both ESP8266 and ESP32. Please edit defines.h and set your pinout properly according to how you connected the IMU.

#Uploading On Linux

Follow the instructions in this link [Platformio](https://docs.platformio.org/en/latest//faq.html#platformio-udev-rules), this should solve any permission denied errors

## Contributions

By contributing to this project you are placing all your code under MIT or less restricting licenses, and you certify that the code you have used is compatible with those licenses or is authored by you. If you're doing so on your work time, you certify that your employer is okay with this.
