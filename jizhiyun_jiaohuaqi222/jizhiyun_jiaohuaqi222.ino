#include <Gizwits.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>        //寄存器库
SoftwareSerial mySerial(A4, A5);
Gizwits myGizwits;
#define   KEY1              2
#define   KEY2              3
#define   KEY1_SHORT_PRESS  1
#define   KEY1_LONG_PRESS   2
#define   KEY2_SHORT_PRESS  4
#define   KEY2_LONG_PRESS   8
#define   NO_KEY            0
#define   KEY_LONG_TIMER    3
unsigned long varR_HT_FZ;
unsigned long t = 5000;
unsigned long now_time;
unsigned long last_time;
//////////////////////////////////////////////
#define h1 A0
#define h2 A1
#define h3 A2
int i = 0;
unsigned char *dpointer;//寄存器文件-结构体存储浮点型数据
union data {
  double v;
  unsigned char dchar[8];
} dvalue;
double ht;
///////////////////////////////////////////////

int flag = 0;
unsigned long Last_KeyTime = 0;
unsigned long gokit_time_s(void)
{
  return millis() / 1000;
}
char gokit_key1down(void)//按键函数，不用管
{
  unsigned long keep_time = 0;
  if (digitalRead(KEY1) == LOW)
  {
    delay(100);
    if (digitalRead(KEY1) == LOW)
    {
      keep_time = gokit_time_s();
      while (digitalRead(KEY1) == LOW)
      {
        if ((gokit_time_s() - keep_time) > KEY_LONG_TIMER)
        {
          Last_KeyTime = gokit_time_s();
          return KEY1_LONG_PRESS;
        }
      } //until open the key
      if ((gokit_time_s() - Last_KeyTime) > KEY_LONG_TIMER)
      {
        return KEY1_SHORT_PRESS;
      }
      return 0;
    }
    return 0;
  }
  return 0;
}
char gokit_key2down(void)//按键函数不用管。
{
  int unsigned long keep_time = 0;
  if (digitalRead(KEY2) == LOW)
  {
    delay(100);
    if (digitalRead(KEY2) == LOW)
    {
      keep_time = gokit_time_s();
      while (digitalRead(KEY2) == LOW) //until open the key
      {
        if ((gokit_time_s() - keep_time) > KEY_LONG_TIMER)
        {
          Last_KeyTime = gokit_time_s();
          return KEY2_LONG_PRESS;
        }
      }
      if ((gokit_time_s() - Last_KeyTime) > KEY_LONG_TIMER)
      {
        return KEY2_SHORT_PRESS;
      }
      return 0;
    }
    return 0;
  }
  return 0;
}
char gokit_keydown(void)
{
  char ret = 0;
  ret |= gokit_key2down();
  ret |= gokit_key1down();
  return ret;
}
void KEY_Handle(void)//这里是检测按键的函数，不用管
{
  switch (gokit_keydown())
  {
    case KEY1_SHORT_PRESS:
      myGizwits.setBindMode(WIFI_PRODUCTION_TEST);
      break;
    case KEY1_LONG_PRESS:
      myGizwits.setBindMode(WIFI_RESET_MODE);
      break;
    case KEY2_SHORT_PRESS:
      myGizwits.setBindMode(WIFI_SOFTAP_MODE);
      break;
    case KEY2_LONG_PRESS:
      myGizwits.setBindMode(WIFI_AIRLINK_MODE);//这里我自己加了一个如果开启了配网功能，蜂鸣器就响一秒。很好用哦
      digitalWrite(12, HIGH);
      delay(1000);
      digitalWrite(12, LOW);
      break;
    default:
      break;
  }
}
//////////////////////////////////////////////
double jiance(int pin)
{
  ht = 1024 - analogRead(pin);
  ht = ht / 7.3;
  if (ht > 100) ht = 100;
  return ht ;
}
/////////////////////////////////////////////
void panduan() {
  ////////////////////////////读取数据
  for (i = 0; i < 8; i++) dvalue.dchar[i] = EEPROM.read(i);
  if (jiance(h1) < dvalue.v && dvalue.v != 0 )  jiaohua();
  if (jiance(h2) < dvalue.v && dvalue.v != 0 )  jiaohua();
  if (jiance(h3) < dvalue.v && dvalue.v != 0 )  jiaohua();

}
void jiaohua() {
  now_time = millis();
  if (now_time > last_time) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(200);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    last_time = millis() + t;
  }
}
/////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
  pinMode(h1, INPUT);//A0
  pinMode(h2, INPUT);//A1
  pinMode(h3, INPUT);//A2
  pinMode(KEY1, INPUT_PULLUP);//2
  pinMode(KEY2, INPUT_PULLUP);//3
  pinMode(4, OUTPUT); digitalWrite(4, HIGH); //1
  pinMode(5, OUTPUT); digitalWrite(5, HIGH); //2
  pinMode(6, OUTPUT); digitalWrite(6, HIGH); //3
  pinMode(7, OUTPUT); digitalWrite(7, HIGH); //4
  pinMode(8, OUTPUT); digitalWrite(8, HIGH); //5
  pinMode(9, OUTPUT); digitalWrite(9, HIGH); //6
  pinMode(10, OUTPUT); digitalWrite(10, HIGH); //7
  pinMode(11, OUTPUT); digitalWrite(11, HIGH); //8
  pinMode(12, OUTPUT); digitalWrite(12, LOW); //beeWIFI_AIRLINK成功报警提示这里是配网提示
  myGizwits.begin();
}
void loop() {
  KEY_Handle();//key handle , network configure网络配置
  //////////////////////////////////////////////////////////////////////控制区
  unsigned long varW_H1_ht = jiance(h1);
  myGizwits.write(VALUE_H1_ht, varW_H1_ht);
  unsigned long varW_H2_ht = jiance(h2);
  myGizwits.write(VALUE_H2_ht, varW_H2_ht);
  unsigned long varW_H3_ht = jiance(h3);
  myGizwits.write(VALUE_H3_ht, varW_H3_ht);
  ////////////////////////////读取数据
  for (i = 0; i < 8; i++) dvalue.dchar[i] = EEPROM.read(i);
  unsigned long varW_MR_FZ = dvalue.v ;
  myGizwits.write(VALUE_MR_FZ, varW_MR_FZ);
  bool varR_H_1 = 0;
  if (myGizwits.hasBeenSet(EVENT_H_1))
  {
    myGizwits.read(EVENT_H_1, &varR_H_1); //Address for storing data
    if (varR_H_1 == 1)
    {
      digitalWrite(4, LOW);
    }
    else
      digitalWrite(4, HIGH);
  }
  bool varR_H_2 = 0;
  if (myGizwits.hasBeenSet(EVENT_H_2))
  {
    myGizwits.read(EVENT_H_2, &varR_H_2); //Address for storing data
    if (varR_H_2 == 1)
    {
      digitalWrite(5, LOW);
    }
    else
      digitalWrite(5, HIGH);
  }
  bool varR_H_3 = 0;
  if (myGizwits.hasBeenSet(EVENT_H_3))
  {
    myGizwits.read(EVENT_H_3, &varR_H_3); //Address for storing data
    if (varR_H_3 == 1)
    {
      digitalWrite(6, LOW);
    }
    else
      digitalWrite(6, HIGH);
  }
  bool varR_KG_1 = 0;
  if (myGizwits.hasBeenSet(EVENT_KG_1))
  {
    myGizwits.read(EVENT_KG_1, &varR_KG_1); //Address for storing data
    if (varR_KG_1 == 1)
    {
      digitalWrite(7, LOW);
    }
    else
      digitalWrite(7, HIGH);
  }
  bool varR_KG_2 = 0;
  if (myGizwits.hasBeenSet(EVENT_KG_2))
  {
    myGizwits.read(EVENT_KG_2, &varR_KG_2); //Address for storing data
    if (varR_KG_2 == 1)
    {
      digitalWrite(8, LOW);
    }
    else
      digitalWrite(8, HIGH);
  }
  bool varR_KG_3 = 0;
  if (myGizwits.hasBeenSet(EVENT_KG_3))
  {
    myGizwits.read(EVENT_KG_3, &varR_KG_3); //Address for storing data
    if (varR_KG_3 == 1)
    {
      digitalWrite(9, LOW);
    }
    else
      digitalWrite(9, HIGH);
  }
  bool varR_KG_4 = 0;
  if (myGizwits.hasBeenSet(EVENT_KG_4))
  {
    myGizwits.read(EVENT_KG_4, &varR_KG_4); //Address for storing data
    if (varR_KG_4 == 1)
    {
      digitalWrite(10, LOW);
    }
    else
      digitalWrite(10, HIGH);
  }
  bool varR_KG_5 = 0;
  if (myGizwits.hasBeenSet(EVENT_KG_5))
  {
    myGizwits.read(EVENT_KG_5, &varR_KG_5); //Address for storing data
    if (varR_KG_5 == 1)
    {
      digitalWrite(11, LOW);
    }
    else
      digitalWrite(11, HIGH);
  }
  if (myGizwits.hasBeenSet(EVENT_HT_FZ))
  {
    myGizwits.read(EVENT_HT_FZ, &varR_HT_FZ); //Address for storing data
    //////////////////////////////存储数据
    dvalue.v = varR_HT_FZ;
    dpointer = dvalue.dchar ;
    for (i = 0; i < 8; i++) {
      EEPROM.write(i, *dpointer);
      dpointer++;
    }
  }
  myGizwits.process();
  panduan();
}
