//Julian 儒略日的计算方法 http://aa.usno.navy.mil/faq/docs/JD_Formula.php

#include "RTClib.h"

//变量声明
int year,month,day,hour,minute,second
long JD

RTC_DS1307 rtc;

void setup(){
  Serial.begin(9600);
  rtc.begin();

    if(! rtc.isrunning()){
      Serial.println("RTC is not running!");
      rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
    }
}

void loop(){

//计算当前时间
  DateTime now =rtc.now();
  year = now.year();
  month = now.month();
  day  = now.day();
  hour= now.hour();
  minute = now.minute();
  second = now.second();
  JD =jd(year,month,day);
}

void jd(year,month,day){
  JD= K-32075+1461*(I+4800+(J-14)/12)/4+367*(J-2-(J-14)/12*12)/12-3*((I+4900+(J-14)/12)/100)/4;
  return JD
}
