/**
************************************************************
* @file         Gizwits + ArduinoUnoR3 Library 
* @brief        Datapoints handle , Gizwits Process
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
#include <Gizwits.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A2, A3); // A2 -> RX, A3 -> TX

Gizwits myGizwits;

/**
* Serial Init , Gizwits Init  
* @param none
* @return none
*/
void setup() {
  // put your setup code here, to run once:

  mySerial.begin(115200);

  myGizwits.begin();

  mySerial.println("GoKit init  OK \n");

}

/**
* Arduino loop 
* @param none
* @return none
*/
void loop() {  
  
  //Configure network
  //if(XXX) //Trigger Condition
  //myGizwits.setBindMode(0x02);  //0x01:Enter AP Mode;0x02:Enter Airlink Mode
    /*
  unsigned long varW_H1_ht = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_H1_ht, varW_H1_ht);
  unsigned long varW_H2_ht = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_H2_ht, varW_H2_ht);
  unsigned long varW_H3_ht = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_H3_ht, varW_H3_ht);
  unsigned long varW_MR_FZ = 0;//Add Sensor Data Collection
  myGizwits.write(VALUE_MR_FZ, varW_MR_FZ);


  bool varR_H_1 = 0;
  if(myGizwits.hasBeenSet(EVENT_H_1))
  {
    myGizwits.read(EVENT_H_1,&varR_H_1);//Address for storing data
    mySerial.println(F("EVENT_H_1"));
    mySerial.println(varR_H_1,DEC);

  }
  bool varR_H_2 = 0;
  if(myGizwits.hasBeenSet(EVENT_H_2))
  {
    myGizwits.read(EVENT_H_2,&varR_H_2);//Address for storing data
    mySerial.println(F("EVENT_H_2"));
    mySerial.println(varR_H_2,DEC);

  }
  bool varR_H_3 = 0;
  if(myGizwits.hasBeenSet(EVENT_H_3))
  {
    myGizwits.read(EVENT_H_3,&varR_H_3);//Address for storing data
    mySerial.println(F("EVENT_H_3"));
    mySerial.println(varR_H_3,DEC);

  }
  bool varR_KG_1 = 0;
  if(myGizwits.hasBeenSet(EVENT_KG_1))
  {
    myGizwits.read(EVENT_KG_1,&varR_KG_1);//Address for storing data
    mySerial.println(F("EVENT_KG_1"));
    mySerial.println(varR_KG_1,DEC);

  }
  bool varR_KG_2 = 0;
  if(myGizwits.hasBeenSet(EVENT_KG_2))
  {
    myGizwits.read(EVENT_KG_2,&varR_KG_2);//Address for storing data
    mySerial.println(F("EVENT_KG_2"));
    mySerial.println(varR_KG_2,DEC);

  }
  bool varR_KG_3 = 0;
  if(myGizwits.hasBeenSet(EVENT_KG_3))
  {
    myGizwits.read(EVENT_KG_3,&varR_KG_3);//Address for storing data
    mySerial.println(F("EVENT_KG_3"));
    mySerial.println(varR_KG_3,DEC);

  }
  bool varR_KG_4 = 0;
  if(myGizwits.hasBeenSet(EVENT_KG_4))
  {
    myGizwits.read(EVENT_KG_4,&varR_KG_4);//Address for storing data
    mySerial.println(F("EVENT_KG_4"));
    mySerial.println(varR_KG_4,DEC);

  }
  bool varR_KG_5 = 0;
  if(myGizwits.hasBeenSet(EVENT_KG_5))
  {
    myGizwits.read(EVENT_KG_5,&varR_KG_5);//Address for storing data
    mySerial.println(F("EVENT_KG_5"));
    mySerial.println(varR_KG_5,DEC);

  }
  unsigned long varR_HT_FZ = 0;
  if(myGizwits.hasBeenSet(EVENT_HT_FZ))
  {
    myGizwits.read(EVENT_HT_FZ,&varR_HT_FZ);//Address for storing data
    mySerial.println(F("EVENT_HT_FZ"));
    mySerial.println(varR_HT_FZ,DEC);

  }


  //binary datapoint handle
  */

  myGizwits.process();
}