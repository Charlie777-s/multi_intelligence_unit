// C++ code
//
void forward();
void back();
void right();
void left();
void reset();
const int in1= 9;
const int in2= 10;
const int en1= 11;
const int in3= 5;
const int in4= 6;
const int en2= 3;
const int b1= 13;
const int b2= 12;
const int b3= 8;
const int b4= 7;
const int ledPin = 4;
const int interruptPin= 2;
int bp1=0;
int bp2= 0;
int bp3= 0;
int bp4=0;
int p[2];
int m=0;
volatile int state= 0;
void setup()
{
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  attachInterrupt(digitalPinToInterrupt(interruptPin), reset, CHANGE);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(ledPin, LOW);
  if (digitalRead(b1)==1)
    forward();
    else if (digitalRead(b2)==1)
    back();
    else if (digitalRead(b3)==1)
    right();
    else if (digitalRead(b4)==1)
    left();
    else
  {
    digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in3, LOW);
    }
   delay(100);
  digitalWrite(ledPin, state);
  while(Serial.available())
  {
    m=Serial.read();
  }
  Serial.write(m);
  
}
void forward()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  
}
void back()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void right()
{
 digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}
void left()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
}
void reset()
{
  if (m==1)
  {
    m=0;
    digitalWrite(ledPin, HIGH);
  }
}
