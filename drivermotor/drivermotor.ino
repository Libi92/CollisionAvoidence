const int trigPin1 = 12;
const int echoPin1 = 11;
int motor1 = 3;
int motor2 = 5;
int motor3 = 7;
int motor4 = 9;
long starttime = 0;
long endtime = 0;
bool turnflag = false;
bool selfMode = false;

String data;

void setup() {

  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
}

void loop() {

  if(selfMode){
    driveInSelfMode();
  }

}

void driveInSelfMode(){
  long duration1, cm1;
  pinMode(trigPin1, OUTPUT);

  digitalWrite(trigPin1, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin1, LOW);

  pinMode(echoPin1, INPUT);

  duration1 = pulseIn(echoPin1, HIGH);
  //  Serial.println(duration1);
  cm1 = microsecondsToCentimeters(duration1);

  Serial.print(cm1);
  Serial.print(",");
  Serial.println(cm1);

  if (cm1 < 15) {
    if (!turnflag) {
      turnflag = true;
      starttime = millis();
    }
    goRight();
  } else {
    if (turnflag) {
      goRight();
      delay(6000);      

      if(cm1 < 15){
        return;
      }
      turnflag = false;
      
      endtime = millis();
      int d = endtime - starttime;
      goStraight();
      delay(4000);
      goLeft();
      delay(d);
    } else {
      goStraight();
    }

  }
}

void serialEvent() {


  Serial.println("Please eneter data");
  while (Serial.available() == 0) {
    
  }

  data = Serial.readString();

  if(data == "USERMODE"){
    selfMode = false;
    mStop();
  }
  else if(data == "SELFMODE"){
    selfMode = true;
  }
  else if(data == "STRAIGHT"){
    if(!selfMode){
      goStraight();
    }
  }
  else if(data == "LEFT"){
    if(!selfMode){
      goLeft();
    }
  }
  else if(data == "RIGHT"){
    if(!selfMode){
      goRight();
    }
  }
  else if(data == "STOP"){
    if(!selfMode){
      mStop();
    }
  }
  
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 74 / 2;
}
void goStraight() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, HIGH);
}
void goLeft() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, HIGH);

}
void goRight() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);

}
void mStop() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);

}
