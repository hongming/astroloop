//配置DEC步进电机的EasyDriver驱动板

#define DEC_dir_pin 3//步进电机方向
#define DEC_step_pin 4  //驱动板的步进
#define DEC_MS2 5 //MS2
#define DEC_MS1 6 //MS1
#define Mount_SLEEP 7 //驱动板SLEEP，共用

//配置RA步进电机的EasyDriver驱动板

#define RA_dir_pin 8 //步进电机方向
#define RA_step_pin 9 //驱动板的步进
#define RA_MS2 10 //MS2
#define RA_MS1 11 //MS1



//配置中断
#define Goto_speed_interrupt 2 //SW键,控制速度,使用中断

//配置状态切换按钮
#define RA_dir_forward 22 //RA前进
#define RA_dir_back 24 //RA后退
#define DEC_dir_forward 18 //RA前进
#define DEC_dir_back 2 //RA后退

//配置步进电机速度,步进暂停时间
int stepper_speed = 100;
int stepper_speed_tracing = 15150;

//配置陀螺仪参数

//配置显示屏幕参数


void setup() {
  pinMode(DEC_MS1, OUTPUT);
  pinMode(DEC_MS2, OUTPUT);
  pinMode(DEC_step_pin, OUTPUT);
  pinMode(DEC_dir_pin, OUTPUT);
  pinMode(RA_MS1, OUTPUT);
  pinMode(RA_MS2, OUTPUT);
  pinMode(RA_step_pin, OUTPUT);
  pinMode(RA_dir_pin, OUTPUT);
  pinMode(Mount_SLEEP, OUTPUT);
  //RA和DEC的前进方向
  pinMode(RA_dir_forward, INPUT);
  pinMode(RA_dir_back, INPUT);
  pinMode(DEC_dir_forward, INPUT);
  pinMode(DEC_dir_back, INPUT);
  //RA和DEC的前进速度
  pinMode(Goto_speed_interrupt, INPUT);
  //唤醒步进电机
  digitalWrite(Mount_SLEEP, HIGH);
  //暂停时间
  delay(1000);
  //配置步进电机类型MS1,MS2 00 FULL, 10 HALF,01 QUARTER,11 Eighth
  digitalWrite(RA_MS1, HIGH);
  digitalWrite(RA_MS2, HIGH);
  digitalWrite(DEC_MS1, HIGH);
  digitalWrite(DEC_MS2, HIGH);
  //定义中断
 // attachInterrupt(digitalPinToInterrupt(Goto_speed_interrupt), Step_Speed_Control, CHANGE);
  //陀螺仪启动

  //显示屏启动

}

void loop() {

  //DEC前进
  if (digitalRead(DEC_dir_forward) == LOW) {
    DEC_forward();
  }
  //DEC后退
  else if (digitalRead(DEC_dir_back) == LOW) {
    DEC_back();
  }
  //RA前进
   if (digitalRead(RA_dir_forward) == LOW) {
    RA_forward();
  }
  //RA后退
  else if (digitalRead(RA_dir_back) == LOW) {
    RA_back();
  }
   //判断，如果没有按下开关，就按照电跟的速度进行
  else if  (digitalRead(RA_dir_forward)==HIGH && digitalRead(RA_dir_back)==HIGH && digitalRead(DEC_dir_forward)==HIGH && digitalRead(DEC_dir_back)==HIGH){
      digitalWrite(RA_MS1, HIGH);
      digitalWrite(RA_MS2, HIGH);
      //RA步进电机速度
      digitalWrite(RA_dir_pin, HIGH);
      digitalWrite(RA_step_pin, HIGH);
      delayMicroseconds(stepper_speed_tracing);
      digitalWrite(RA_step_pin, LOW);
      delayMicroseconds(stepper_speed_tracing);
  }

//输出两个角度

//显示显示屏幕上

}

void Step_Speed_Control() {
  // if(!(digitalRead(Joy_switch))){
  //delayMicroseconds(5000); //delay for deboucing
  switch (stepper_speed) {
    case 200:
      stepper_speed = 8000;
      break;
    case 100:
      stepper_speed = 200;
      break;
    case 8000:
      stepper_speed = 100;
      break;
  }
}

void DEC_forward() {
  digitalWrite(DEC_MS1, LOW);
  digitalWrite(DEC_MS2, LOW);
  //DEC步进电机速度
  digitalWrite(DEC_dir_pin, HIGH);
  digitalWrite(DEC_step_pin, HIGH);
  delayMicroseconds(stepper_speed);
  digitalWrite(DEC_step_pin, LOW);
  delayMicroseconds(stepper_speed);
}

void DEC_back() {
  digitalWrite(DEC_MS1, LOW);
  digitalWrite(DEC_MS2, LOW);
  //DEC步进电机速度
  digitalWrite(DEC_dir_pin, LOW);
  digitalWrite(DEC_step_pin, HIGH);
  delayMicroseconds(stepper_speed);
  digitalWrite(DEC_step_pin, LOW);
  delayMicroseconds(stepper_speed);
}

void RA_forward() {
  digitalWrite(RA_MS1, LOW);
  digitalWrite(RA_MS2, LOW);
  //DEC步进电机速度
  digitalWrite(RA_dir_pin, HIGH);
  digitalWrite(RA_step_pin, HIGH);
  delayMicroseconds(stepper_speed);
  digitalWrite(RA_step_pin, LOW);
  delayMicroseconds(stepper_speed);
}

void RA_back() {
  digitalWrite(RA_MS1, LOW);
  digitalWrite(RA_MS2, LOW);
  //DEC步进电机速度
  digitalWrite(RA_dir_pin, LOW);
  digitalWrite(RA_step_pin, HIGH);
  delayMicroseconds(stepper_speed);
  digitalWrite(RA_step_pin, LOW);
  delayMicroseconds(stepper_speed);
}
