// C++ code
//ultrasonic sensor2: horizontal distance
//ultrasonic sensor 1: y axis distance
//m=0: normal mode
//m=1: defense mode
//m=2: power saving mode
#include <Servo.h>
#define a 0.785398
Servo servoh;
Servo servov;
const 	int trig1= 5;
const int echo1= 6;
const int trig2= 8;
const int echo2= 9;
const int N=4;
int tot= 0; 
int i=0;
float davg=0.0;
int temp=0;
int d=0;
int dvo=0;
int dho=0;
int dvn=0;
int dhn=0;
int timing=0 ;
int m=0;
int p[2];
int cnt=0;
float theta= 0;
float phi= 0;
float x=0.0;
float y=0.0;
float z= 0.0;
float r= 0.0;
const int led1= 11;
const int buzz1= 10;
const int buzz2= 12;
const int ledr= 4;
const int ledg= 2;
const int ledb= 3;
const int pot= 0;
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int sensor(int trig, int echo)
{
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  timing = pulseIn(echo, HIGH);
  d= (timing * 0.034) / 2;
  return d;
}
float maf(float d, int trig, int echo)
{
  tot= d;
  for (i=0; i<N; i++)
  {
    temp= sensor(trig, echo);
    tot+= temp;
  }
  davg= tot/(N+1);
  return davg;
}
void alert()
{
   for(i=0; i<5; i++)
    {digitalWrite(led1, HIGH);
     digitalWrite(buzz1, HIGH);
     delay(100);
     digitalWrite(led1, LOW);
     digitalWrite(buzz1, LOW);
    }
}
void battery()
{
  temp= analogRead(0);
  temp= map(temp, 0, 1023, 0, 100);
  if (temp< 30 && temp> 10)
  {
    analogWrite(ledr, 255);
     analogWrite(ledg, 255);
     digitalWrite(buzz2, HIGH);
    m=2;
     
  }
  else if (temp< 10)
  {
    analogWrite(ledr, 255);
    m=2;
  }
}
float azimuth(int dh, int dv)
{
  x= dh;
  y= dv;
  theta= atan2((float)y, (float)x);
  return theta;
}
float elevation(int dh, int dv, int z)
{
  x= dh;
  y= dv;
  r= sqrt(x*x+ y*y);
  phi= atan2(z, r);
  return phi;
}
void setup()
{
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(buzz1, OUTPUT);
  pinMode(ledr, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(buzz2, OUTPUT);
  randomSeed(analogRead(1));
  servoh.attach(7);
  servov.attach(13);
  Serial.begin(9600);
  Serial.flush();
}

void loop()
{
  
  dvn= sensor(trig1, echo1);
  dhn= sensor(trig2, echo2);
  dvn= maf(dvn, trig1, echo1);
  dhn= maf(dhn, trig2, echo2);
  int xn= (int) dhn;
  int xo= (int)dho;
  int yn= (int) dvn;
  int yo= (int) dvo;
  if (abs(xo-xn)<2 && abs(yo-yn)<2)
   ;
  else 
 {if (cnt>1)
 {
   temp= analogRead(0);
  temp= map(temp, 0, 1023, 0, 100);
   if(temp<30)
   m=2;
   else
   {
     m=1;
     analogWrite(ledr, 0);
     analogWrite(ledg, 0);
   }
     
   
  digitalWrite(led1, HIGH);
  digitalWrite(buzz1, HIGH);
  z= random(0, 300);
  theta= azimuth(dhn, dvn);
  phi= elevation(dhn, dvn, z);
  theta= mapFloat(theta, -1.57, 1.57, 0, 180);
  phi= mapFloat(phi, -1.57, 1.57, 0, 180);
  servoh.write(theta);
  servov.write(phi);
  analogWrite(ledr, 0);
  analogWrite(ledg, 0);
  digitalWrite(buzz2, LOW);
  
 }}
  battery();
  dvo=dvn;
  dho= dhn;
  cnt++;
  //delay(500);
  //Serial.println("Sending: ");
  Serial.write(m);
 
  while(Serial.available())
  {
    if (Serial.read()==0)
    {
      m=0;
      digitalWrite(led1, 	LOW);
  digitalWrite(buzz1, LOW);
      
    }
  }
 // Serial.println(m);
  //Serial.println(m);
}
