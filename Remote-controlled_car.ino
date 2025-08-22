int trig1 = A0;
int echo1 = A1;
int trig2 = A2;
int echo2 = A3;
int trig3 = A4;
int echo3 = A5;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int ENA = 3;
int ENB = 11;
int LeftSpeed = 110;
int RightSpeed = 110;                                                                                       ;
long khoang_cach_trai = 0, khoang_cach_giua = 0, khoang_cach_phai = 0;
long pingTime, distance;
float speedSound = 0.0343;
int DIS = 18;
int led = 13;
int loa = 12;


long line_trai() {
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  pingTime = pulseIn(echo1, HIGH);
  distance = (pingTime / 2) * speedSound;
  return (distance);
}

long line_giua() {
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  pingTime = pulseIn(echo2, HIGH);
  distance = (pingTime / 2) * speedSound;
  return (distance);
}

long line_phai() {
  digitalWrite(trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  pingTime = pulseIn(echo3, HIGH);
  distance = (pingTime / 2) * speedSound;
  return (distance);
}

void setup() {
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(loa, OUTPUT);

  moveStop();
}

void loop() {

  // digitalWrite(led, HIGH);
  // tone(loa, 1000);
  // noTone(loa);

  khoang_cach_trai = line_trai();
  delay(10);
  khoang_cach_giua = line_giua();
  delay(10);
  khoang_cach_phai = line_phai();
  delay(10);
  Serial.print("khoang_cach_trai = ");
  Serial.print(khoang_cach_trai);
  Serial.print("cm /");
  Serial.print("khoang_cach_giua = ");
  Serial.print(khoang_cach_giua);
  Serial.print("cm /");
  Serial.print("khoang_cach_phai = ");
  Serial.print(khoang_cach_phai);
  Serial.println("cm");

  //  Obstacle on left side
  if (khoang_cach_trai < DIS && khoang_cach_giua > DIS && khoang_cach_phai > DIS) {
    DenCoi();
    turnRight();
    delay(25);  //  turn lightly right
  }
  //  Obstacle on front
  else if (khoang_cach_trai > DIS && khoang_cach_giua < DIS && khoang_cach_phai > DIS) {
    if (khoang_cach_trai > khoang_cach_phai) {
      DenCoi();
      turnLeft();
      delay(400);  //  turn 90 degree left
    }
    if (khoang_cach_trai < khoang_cach_phai) {
      DenCoi();
      turnRight();
      delay(400);  //  turn 90 degree right
    }
  }
  //  Obstacle on right side
  else if (khoang_cach_trai > DIS && khoang_cach_giua > DIS && khoang_cach_phai < DIS) {
    DenCoi();
    turnLeft();
    delay(25);  //turn lightly left
  }
  //  Obstacle on front & left side
  else if (khoang_cach_trai < DIS && khoang_cach_giua < DIS && khoang_cach_phai > DIS) {
    DenCoi();
    turnRight();
    delay(400);  //  turnRight 90 degree
  }
  //  Obstacle on front & right side
  else if (khoang_cach_trai > DIS && khoang_cach_giua < DIS && khoang_cach_phai < DIS) {
    DenCoi();
    turnLeft();
    delay(400);  //  turnLeft 90 degree
  }
  //  Obstacle on left & right side
  else if (khoang_cach_trai < DIS && khoang_cach_giua > DIS && khoang_cach_phai < DIS) {
    if (khoang_cach_trai > khoang_cach_phai) {
      DenCoi();
      turnLeft();
      delay(50);  //  shift left
    }
    if (khoang_cach_trai < khoang_cach_phai) {
      DenCoi();
      turnRight();
      delay(50);  //  shift right
    }
  }
  //  Obstacle on all 3 side
  else if (khoang_cach_trai < DIS && khoang_cach_giua < DIS && khoang_cach_phai < DIS) {
    moveStop();
    delay(1000);
    moveBackward();
    delay(1000);
    DenCoi();
    turnLeft();
    delay(800);  //turn 180 degrees
  } else {
    moveForward();
  }
}

void moveForward() {
  Serial.println("Move Forward");
  analogWrite(ENA, LeftSpeed);
  analogWrite(ENB, RightSpeed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  Serial.println("Move Backward");
  analogWrite(ENA, LeftSpeed);
  analogWrite(ENB, RightSpeed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  Serial.println("Turn Right");
  analogWrite(ENA, LeftSpeed);
  analogWrite(ENB, RightSpeed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  Serial.println("Turn Left");
  analogWrite(ENA, LeftSpeed);
  analogWrite(ENB, RightSpeed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveStop() {
  Serial.println("Move Stop");
  analogWrite(ENA, LOW);
  analogWrite(ENB, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void DenCoi() {
  digitalWrite(led, HIGH);
  tone(loa, 1000);
  delay(40);
  digitalWrite(led, LOW);
  noTone(loa);
}
