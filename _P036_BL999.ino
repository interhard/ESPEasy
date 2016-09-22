//############################################################################################################################
//#################################### Plugin 036: 433Mhz Temp. & Humidity sensor BL999 by Ea2 ###############################
//############################################################################################################################
//#############################  This plugin is designed for low-cost weather BL999 sensor from Ea2  #########################
//##############################  Library for this plugin - https://github.com/sprilukin/lib_BL999 ###########################


#include <lib_bl999.h>
static BL999Info info;

#define PLUGIN_036
#define PLUGIN_ID_036         36
#define PLUGIN_NAME_036       "433Mhz Temp. & Humidity sensor BL999 by Ea2"
#define PLUGIN_VALUENAME1_036 "Channel"
#define PLUGIN_VALUENAME2_036 "Battery"
#define PLUGIN_VALUENAME3_036 "Temperature"
#define PLUGIN_VALUENAME4_036 "Humidity"
byte Plugin_036_BL999_Pin;

boolean Plugin_036(byte function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {
    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_036;
        Device[deviceCount].Type = DEVICE_TYPE_SINGLE;
        Device[deviceCount].VType = SENSOR_TYPE_QUAD;
        Device[deviceCount].Ports = 0;
        Device[deviceCount].PullUpOption = false;
        Device[deviceCount].InverseLogicOption = false;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 4;
        Device[deviceCount].SendDataOption = true;
        Device[deviceCount].TimerOption = true;
        Device[deviceCount].GlobalSyncOption = true;
        break;
      }

    case PLUGIN_GET_DEVICENAME:
      {
        string = F(PLUGIN_NAME_036);
        break;
      }

    case PLUGIN_GET_DEVICEVALUENAMES:
      {
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_036));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[1], PSTR(PLUGIN_VALUENAME2_036));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[2], PSTR(PLUGIN_VALUENAME3_036));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[3], PSTR(PLUGIN_VALUENAME4_036));
        break;
      }

     
       case PLUGIN_INIT:
        {
        
        Plugin_036_BL999_Pin = Settings.TaskDevicePin1[event->TaskIndex];

        bl999_set_rx_pin(Plugin_036_BL999_Pin);
        bl999_rx_start();  
        success = true;
        break;
       
      }


      case PLUGIN_TEN_PER_SECOND:
      {
          
        if (bl999_have_message() && bl999_get_message(info))
        {
          
          UserVar[event->BaseVarIndex] = info.channel;
          
          UserVar[event->BaseVarIndex + 1] = (info.battery == 0 ? 1 : 0);
         
          UserVar[event->BaseVarIndex + 2] = (info.temperature / 10.0);
          
          UserVar[event->BaseVarIndex + 3] = info.humidity;
        
         /* 
          String log = F("Ok.");
          log = F("Channel");
          log += UserVar[event->BaseVarIndex];
          addLog(LOG_LEVEL_INFO, log);
          log = F("Battery");
          log += UserVar[event->BaseVarIndex + 1];
          addLog(LOG_LEVEL_INFO, log);
          log = F("Temperature");
          log += UserVar[event->BaseVarIndex + 2];
          addLog(LOG_LEVEL_INFO, log);
          log = F("Humidity");
          log += UserVar[event->BaseVarIndex + 3];
          addLog(LOG_LEVEL_INFO, log);  
          */
          sendData(event);         
        }
     
        success = true;
        
        break;
      }
  }
  return success;
}

      
   

