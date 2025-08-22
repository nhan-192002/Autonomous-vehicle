// cảm biến giữa
int trig2 = A2;
int echo2 = A3;

// cảm biến phải
int trig3 = A4;
int echo3 = A5;

//bánh bên trái
int in1 = 4;
int ENA = 3;
//bánh bên phải
int in3 = 6;
int ENB = 11;

int LeftSpeed = 130;
int RightSpeed = 130;

long khoang_cach_trai = 0, khoang_cach_giua = 0, khoang_cach_phai = 0;
long pingTime, distance;
float speedSound = 0.0343;

int topDIS = 25;

//3 khoản cách 
int DIS = 25;
int DISR = 20;
int DISL = 10;

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
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  khoang_cach_giua = line_giua();
  delay(10);
  khoang_cach_phai = line_phai();
  delay(10);

  if (khoang_cach_giua < topDIS) {
    turnLeft();
    delay(250);

  } else if (khoang_cach_phai < DIS) {

    if (khoang_cach_phai < DISL) {
      analogWrite(ENA, RightSpeed);
      analogWrite(ENB, LeftSpeed - 70);
      digitalWrite(in1, HIGH);
      digitalWrite(in3, HIGH);
      delay(250);

    } else if (khoang_cach_phai > DISR) {
      Serial.println("Move Forward");
      analogWrite(ENA, RightSpeed - 70);
      analogWrite(ENB, LeftSpeed);
      digitalWrite(in1, HIGH);
      digitalWrite(in3, HIGH);
      delay(50);

    } else if (khoang_cach_phai > DIS) {
      Serial.println("Move Forward");
      analogWrite(ENA, RightSpeed - 70);
      analogWrite(ENB, LeftSpeed);
      digitalWrite(in1, HIGH);
      digitalWrite(in3, HIGH);

    } else if (khoang_cach_giua < DISR && khoang_cach_phai < DISR) {
      analogWrite(ENA, RightSpeed);
      analogWrite(ENB, LeftSpeed - 70);
      digitalWrite(in1, HIGH);
      digitalWrite(in3, HIGH);

    } else {
      moveForward();
    }

  } else {
    moveForward();
  }
}

// đi thẳng
void moveForward() {
  Serial.println("Move Forward");
  analogWrite(ENA, RightSpeed);
  analogWrite(ENB, LeftSpeed);
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
}

// rẽ trái
void turnLeft() {
  Serial.println("Turn Left");
  analogWrite(ENA, RightSpeed);
  analogWrite(ENB, LeftSpeed);
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
}