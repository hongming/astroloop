//Julian 儒略日的计算方法 http://aa.usno.navy.mil/faq/docs/JD_Formula.php

#include "RTClib.h"

//变量声明
float longitude,latitude
int year,month,day,hour,minute,second
long JD,LST
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
//计算本地恒星时
  LST = 100.46+0.985647*(JD-2451545.0)+longitude+15*((hour-8)+minute/60+second/(60*60));
  While LST<0 LST+=360.0;
  While LST>360 LST-=360.0;
  LST = LST/15;
//计算特定星体的时角
  t=LST-A
}

void jd(year,month,day){
  JD= day-32075+1461*(year+4800+(month-14)/12)/4+367*(month-2-(month-14)/12*12)/12-3*((year+4900+(month-14)/12)/100)/4;
  return JD
}
