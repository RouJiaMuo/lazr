/*!
 * @File  DFRobot_Iraser_Sensor.ino
 * @brief  In this example, the infrared laser ranging sensor is used to measure the distance, and the sensor data is processed to obtain the measured distance
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence  The MIT License (MIT)
 * @author  [liunian](nian.liu@dfrobot.com)
 * @version  V1.0
 * @date  2020-08-13
 */
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,2);//定义软串口，3号端口为TX，2号端口为RX
char buff[4]={0x80,0x06,0x03,0x77};
unsigned char data[11]={0};
void setup()
{
 Serial.begin(115200);
 mySerial.begin(9600);
}

void loop()
{
  mySerial.print(buff);
  while(1)
  {
    if(mySerial.available()>0)//判断串口是否有数据可读
    {
      delay(50);
      for(int i=0;i<11;i++)
      {
        data[i]=mySerial.read();
      }
      unsigned char Check=0;
      for(int i=0;i<10;i++)
      {
        Check=Check+data[i];
      }
      Check=~Check+1;
      if(data[10]==Check)
      {
        if(data[3]=='E'&&data[4]=='R'&&data[5]=='R')
        {
          Serial.println("Out of range");
        }
        else
        {
          float distance=0;
          distance=(data[3]-0x30)*100+(data[4]-0x30)*10+(data[5]-0x30)*1+(data[7]-0x30)*0.1+(data[8]-0x30)*0.01+(data[9]-0x30)*0.001;
          Serial.print("Distance = ");
          Serial.print(distance,3);
          Serial.println(" M");
        }
      }
      else
      {
        Serial.println("Invalid Data!");
      }
    }
    delay(20);
  }
}
