/*
    SlimeVR Code is placed under the MIT license
    Copyright (c) 2021 Eiren Rain & SlimeVR contributors

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/
#include <i2cscan.h>
#include "sensorfactory.h"

#include "bno055sensor.h"
#include "bno080sensor.h"
#include "mpu9250sensor.h"
#include "mpu6050sensor.h"

SensorFactory::SensorFactory()
{
}

SensorFactory::~SensorFactory()
{
    for (int SensorCount = 0; SensorCount < IMUCount; SensorCount++)
    {
        delete IMUs[SensorCount];
    }
}

void SensorFactory::SetIMU(uint8_t bus)
{
    Wire.beginTransmission(0x70); // TCA9548A address is 0x70
    Wire.write(1 << bus);         // send byte to select bus
    Wire.endTransmission();
    // Serial.printf("Setting MUX ID : %d\n",bus);
}

void SensorFactory::create()
{
    for (int SensorCount = 0; SensorCount < IMUCount; SensorCount++)
    {
        this->SetIMU(SensorCount);
        uint8_t first_addr = I2CSCAN::pickDevice(0x68, 0x69, false);
        if (first_addr == 0)
        {
            this->IMUs[SensorCount] = new EmptySensor();
        }
        else
        {
            this->IMUs[SensorCount] = new MPU6050Sensor();
            Serial.print("IMU Address  : 0x");
            Serial.print(first_addr, HEX);
            ;
            Serial.print(" Found on MUX Channel : ");
            Serial.println(SensorCount);
        }
        this->IMUs[SensorCount]->setupSensor(IMU, SensorCount, first_addr, PIN_IMU_INT);
    }
}

void SensorFactory::motionSetup()
{
    for (int SensorCount = 0; SensorCount < IMUCount; SensorCount++)
    {
        if (IMUs[SensorCount]->Connected)
        {
            this->SetIMU(SensorCount);
            IMUs[SensorCount]->motionSetup();
            UI::SetIMUStatus(SensorCount, IMUs[SensorCount]->isWorking() ? true : false);
        }
        else
        {
            UI::SetIMUStatus(SensorCount, false);
        }
    }
}

void SensorFactory::motionLoop()
{
    for (int SensorCount = 0; SensorCount < IMUCount; SensorCount++)
    {
        this->SetIMU(SensorCount);
        IMUs[SensorCount]->motionLoop();
    }
}

void SensorFactory::sendData()
{
    for (int SensorCount = 0; SensorCount < IMUCount; SensorCount++)
    {

        this->SetIMU(SensorCount);
        IMUs[SensorCount]->sendData();
    }
}

void SensorFactory::startCalibration(int sensorId, int calibrationType)
{
    this->SetIMU(sensorId);
    IMUs[sensorId]->startCalibration(calibrationType);
}
