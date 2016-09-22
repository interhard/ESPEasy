//#######################################################################################################
//######################## Plugin 037 BMP0685 I2C Barometric Pressure Sensor  ###########################
//#######################################################################################################

#define PLUGIN_037
#define PLUGIN_ID_037        37
#define PLUGIN_NAME_037       "Temperature & Pressure - MPL3115A2"
#define PLUGIN_VALUENAME1_037 "Temperature"
#define PLUGIN_VALUENAME2_037 "Pressure"
#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();


boolean Plugin_037_init = false;

boolean Plugin_037(byte function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {
    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_037;
        Device[deviceCount].Type = DEVICE_TYPE_I2C;
        Device[deviceCount].VType = SENSOR_TYPE_TEMP_BARO;
        Device[deviceCount].Ports = 0;
        Device[deviceCount].PullUpOption = false;
        Device[deviceCount].InverseLogicOption = false;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 2;
        Device[deviceCount].SendDataOption = true;
        Device[deviceCount].TimerOption = true;
        Device[deviceCount].GlobalSyncOption = true;
        break;
      }

    case PLUGIN_GET_DEVICENAME:
      {
        string = F(PLUGIN_NAME_037);
        break;
      }

    case PLUGIN_GET_DEVICEVALUENAMES:
      {
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_037));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[1], PSTR(PLUGIN_VALUENAME2_037));
        break;
      }

    case PLUGIN_READ:
      {
        if (baro.begin()) 
        {
          float pascals = baro.getPressure();
          
          UserVar[event->BaseVarIndex] = (pascals/3377);
          
          float tempC = baro.getTemperature();
          
          UserVar[event->BaseVarIndex + 1] = tempC;

          delay(250);
          
          String log = F("Pressure: ");
          log += UserVar[event->BaseVarIndex];
          addLog(LOG_LEVEL_INFO, log);
          log = F("Temperature: ");
          log += UserVar[event->BaseVarIndex + 1];
          addLog(LOG_LEVEL_INFO, log);
          success = true;
        }
        break;
      }

  }
  return success;
}


