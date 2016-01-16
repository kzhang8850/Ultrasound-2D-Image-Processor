int POTpin = 3;
int Ultrainput = 5;
int Ultraoutput2 = 6;
int Ultraoutput = 4;
int MotorPin = 8;
int MotorPin2 = 9;
int res = 0;
unsigned long duration = 0;
unsigned long threshold = 0;
unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long endTime2 = 0;
unsigned long duration2 = 0;
boolean notstarted = true;
boolean ended = false;
boolean ran = false;
boolean ran2 = false;
boolean run1 = false;
boolean measure2 = false;
boolean ended2 = false;
boolean forward = true;
boolean middle = true;
int pot = 40;
//int count1 = 0;
//int count2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MotorPin, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(Ultrainput, INPUT);
  pinMode(Ultraoutput2, INPUT);
  pinMode(Ultraoutput, INPUT);

}

void motor(int pot){

  if (pot < 10 && forward && middle){
    forward = false;
    middle = false;
  }else if(pot >340 && !forward && middle){
    forward = true;
    middle = false;
  }
  if(pot <120 && pot > 90){
    middle = true;
  }
  
}

void loop() {
  unsigned int currentmicros = micros();
/*    int pot = analogRead(POTpin) *((float)360 / 1023)

  //Serial.println(potentiometer());
    if (pot < 10 && forward && middle){
    forward = false;
    middle = false;
  }else if(pot >340 && !forward && middle){
    forward = true;
    middle = false;
  }
  if(pot <120 && pot > 90){
    middle = true;
  }*/
  if(forward){
    digitalWrite(MotorPin2, LOW);
    digitalWrite(MotorPin, HIGH);
  }else{
    digitalWrite(MotorPin, LOW);
    digitalWrite(MotorPin2, HIGH);    
  }

  
if((digitalRead(Ultrainput)== HIGH) && notstarted){
  startTime = currentmicros;
  notstarted = false;
  ended=false;
  ended2 = false;
  ran = false;
  ran2 = false;
  run1 = false;
  measure2 = false;
}
  //Serial.println("NOT HERE");
if ((digitalRead(Ultraoutput)== HIGH) && !ended){
  endTime = currentmicros;
  ended = true;
  ran = true;
}
//////////////////////////////////////
  //THIS PART IS FOR THE LONGER READING
  ///////////////////////////////////////
  /*
if(digitalRead(Ultraoutput2) == HIGH && !run1 && !ended2){
  run1 = true;
}
if(digitalRead(Ultraoutput2) == LOW && run1 && !ended2){
  measure2 = true;
}
if(digitalRead(Ultraoutput2) == HIGH && measure2 && !ended2){
  endTime2 = currentmicros;
  ran2 = true;
  ended2 = true;
}
*/
// END OF LONGER READING PART
////////////////////////////

//threshold = currentmicros - startTime;
if(currentmicros - startTime > 2500){
  notstarted = true;
}
//Serial.println(currentmicros - startTime);
duration = endTime - startTime;
duration2 = endTime2 - startTime;
if(ran || ran2){
  if(ran){
    Serial.print(duration);
    Serial.print('t');
    pot = analogRead(POTpin) *((float)360 / 1023);
    Serial.println(pot);
    motor(pot);
    //Serial.println("ONE");
    //Serial.println(micros());
  }
  if(ran2 && !ran){
    Serial.print(duration2);
    Serial.print('t');
    pot = analogRead(POTpin) *((float)360 / 1023);
    Serial.println(pot);
    motor(pot);
  }
  
  ran = false;
  ran2 = false;
}
}
