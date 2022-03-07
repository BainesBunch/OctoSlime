#include <Arduino.h>
#include "globals.h"
#include <GyverOLED.h>

namespace UI
{

    void Setup();
     void DrawSplash();
     void MainUIFrame();
     void SetIMUStatus(uint8 imuID, bool Status);
     void DrawFrame(void);
     void SetImuCount(uint8 IMUs);
     void SetMessage(uint8 MessageID);

}