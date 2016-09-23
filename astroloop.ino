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



//配置JoyStick
#define Joy_RA_pin A0 // X轴
#define Joy_DEC_pin A1  //  Y轴
#define Joy_switch 2 //SW键,控制速度,使用中断

//配置状态切换按钮
#define Mount_Stop 12

//配置步进电机速度,步进暂停时间
int stepper_speed = 100;
int stepper_speed_tracing = 641000;

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
  pinMode(Mount_Stop, OUTPUT);
  pinMode(Joy_RA_pin, INPUT);
  pinMode(Joy_DEC_pin, INPUT);
  pinMode(Joy_switch, INPUT);
  //唤醒步进电机
  digitalWrite(Mount_SLEEP, HIGH);
  //暂停时间
  delayMicroseconds(100000);
  //配置步进电机类型MS1,MS2 11 FULL, 10 HALF,01 QUARTER,00,Eighth
  digitalWrite(RA_MS1, HIGH);
  digitalWrite(RA_MS2, HIGH);
  digitalWrite(DEC_MS1, HIGH);
  digitalWrite(DEC_MS2, HIGH);
  //定义中断
  attachInterrupt(digitalPinToInterrupt(Joy_switch), Step_Speed_Control, CHANGE);
}

void loop() {

  //判断，如果没有按下开关，就按照电跟的速度进行
  if ((digitalRead(Mount_Stop))) {
    digitalWrite(RA_MS1, LOW);
    digitalWrite(RA_MS2, LOW);
    //RA步进电机速度
    digitalWrite(RA_dir_pin, LOW);
    digitalWrite(RA_step_pin, HIGH);
    delayMicroseconds(stepper_speed_tracing);
    digitalWrite(RA_step_pin, LOW);
    delayMicroseconds(stepper_speed_tracing);
  }
  //RA轴变化
  else if (analogRead(RA_step_pin >= 700))
  {

    digitalWrite(RA_dir_pin, LOW);
    digitalWrite(RA_step_pin, HIGH);
    delayMicroseconds(stepper_speed);
    digitalWrite(RA_step_pin, LOW);
    delayMicroseconds(stepper_speed);
  }
  else if (analogRead(RA_step_pin <= 300))
  {

    digitalWrite(RA_dir_pin, HIGH);
    digitalWrite(RA_step_pin, HIGH);
    delayMicroseconds(stepper_speed);
    digitalWrite(RA_step_pin, LOW);
    delayMicroseconds(stepper_speed);
  }

  //DEC轴变化
  else if (analogRead(DEC_step_pin >= 700))
  {

    digitalWrite(DEC_dir_pin, LOW);
    digitalWrite(DEC_step_pin, HIGH);
    delayMicroseconds(stepper_speed);
    digitalWrite(DEC_step_pin, LOW);
    delayMicroseconds(stepper_speed);
  }
}

void Step_Speed_Control() {
  // if(!(digitalRead(Joy_switch))){
  //delayMicroseconds(5000); //delay for deboucing
  switch (stepper_speed) {
    case 100:
      stepper_speed = 1000;
      break;
    case 300:
      stepper_speed = 100;
      break;
    case 1000:
      stepper_speed = 300;
      break;
  }
}
