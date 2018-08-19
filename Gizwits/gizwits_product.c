/**
************************************************************
* @file         gizwits_product.c
* @brief        Control protocol processing and platform related hardware initialization
* @author       Gizwits
* @date         2017-08-01
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "gizwits_protocol.h"

/**@name Gizwits Interface
* @{
*/

extern dataPoint_t currentDataPoint;
attrFlags_t attrFlags;
extern wifiStatueFlags_t wifiStatueFlags;

/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *data, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)data;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)data;
  protocolTime_t *ptime = (protocolTime_t *)data;

  if((NULL == info) || (NULL == data))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_H_1:
        currentDataPoint.valueH_1 = dataPointPtr->valueH_1;
        attrFlags.flagH_1 = 1;
        break;
      case EVENT_H_2:
        currentDataPoint.valueH_2 = dataPointPtr->valueH_2;
        attrFlags.flagH_2 = 1;
        break;
      case EVENT_H_3:
        currentDataPoint.valueH_3 = dataPointPtr->valueH_3;
        attrFlags.flagH_3 = 1;
        break;
      case EVENT_KG_1:
        currentDataPoint.valueKG_1 = dataPointPtr->valueKG_1;
        attrFlags.flagKG_1 = 1;
        break;
      case EVENT_KG_2:
        currentDataPoint.valueKG_2 = dataPointPtr->valueKG_2;
        attrFlags.flagKG_2 = 1;
        break;
      case EVENT_KG_3:
        currentDataPoint.valueKG_3 = dataPointPtr->valueKG_3;
        attrFlags.flagKG_3 = 1;
        break;
      case EVENT_KG_4:
        currentDataPoint.valueKG_4 = dataPointPtr->valueKG_4;
        attrFlags.flagKG_4 = 1;
        break;
      case EVENT_KG_5:
        currentDataPoint.valueKG_5 = dataPointPtr->valueKG_5;
        attrFlags.flagKG_5 = 1;
        break;


      case EVENT_HT_FZ:
        currentDataPoint.valueHT_FZ = dataPointPtr->valueHT_FZ;
        attrFlags.flagHT_FZ = 1;
        //user handle
        break;


      case WIFI_SOFTAP:
        wifiStatueFlags.flagWifi_softap = 1;
        break;
      case WIFI_AIRLINK:
        wifiStatueFlags.flagWifi_airlink = 1;
        break;
      case WIFI_STATION:
        wifiStatueFlags.flagWifi_station = 1;
        break;
      case WIFI_CON_ROUTER:
        wifiStatueFlags.flagWifi_con_router = 1;
        break;
      case WIFI_DISCON_ROUTER:
        wifiStatueFlags.flagWifi_discon_router = 1;
        break;
      case WIFI_CON_M2M:
        wifiStatueFlags.flagWifi_con_m2m = 1;
        break;
      case WIFI_DISCON_M2M:
        wifiStatueFlags.flagWifi_discon_m2m = 1;
        break;
      case WIFI_RSSI:
        break;
      case TRANSPARENT_DATA:
        break;
      case WIFI_NTP:

        //GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);

        break;
      default:
        break;
    }
  }

  return 0;
}




/**
* @brief MCU Restart

* @param none
* @return none
*/
void mcuRestart(void)
{

}
