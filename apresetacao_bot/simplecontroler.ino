#include <Servo.h>

const int dedaoButton = 2;
const int apontadorButton = 3;
const int meioButton = 4;
const int dedinhoButton = 5;
  
int dedaoState = 0;
int apontadorState = 0;
int meioState = 0;
int dedinhoState = 0;

const int dedaoLed = 7;
const int apontadorLed = 8;
const int meioLed = 12;
const int dedinhoLed = 13;

int potValue;
int mapPotValue;

Servo dedao;
Servo apontador;
Servo meio;
Servo dedinho;

  
void setup()
{
  Serial.begin(9600);

  pinMode(dedaoButton, INPUT);
  pinMode(apontadorButton, INPUT);
  pinMode(meioButton, INPUT);
  pinMode(dedinhoButton, INPUT);
  
  pinMode(dedaoLed, OUTPUT);
  pinMode(apontadorLed, OUTPUT);
  pinMode(meioLed, OUTPUT);
  pinMode(dedinhoLed, OUTPUT);
  
  dedao.attach(6);
  apontador.attach(9);
  meio.attach(10);
  dedinho.attach(11);
}

void loop()
{   
  int potValue = analogRead(A0);
  mapPotValue = map(potValue,0,1023,0,180);
  
  dedaoState = digitalRead(dedaoButton);
  apontadorState = digitalRead(apontadorButton);
  meioState = digitalRead(meioButton);
  dedinhoState = digitalRead(dedinhoButton);
  
  if (dedaoState == HIGH) {
    digitalWrite(dedaoLed, HIGH);
    dedao.write(mapPotValue);
  } else {
    digitalWrite(dedaoLed, LOW);
    dedao.write(0);
  }
  
  if (apontadorState == HIGH) {
    digitalWrite(apontadorLed, HIGH);
    apontador.write(mapPotValue);
  } else {
    digitalWrite(apontadorLed, LOW);
    apontador.write(0);
  }
  
    
  if (meioState == HIGH) {
    digitalWrite(meioLed, HIGH);
    meio.write(mapPotValue);
  } else {
    digitalWrite(meioLed, LOW);
    meio.write(0);
  }
  
    
  if (dedinhoState == HIGH) {
    digitalWrite(dedinhoLed, HIGH);
    dedinho.write(mapPotValue);
  } else {
    digitalWrite(dedinhoLed, LOW);
    dedinho.write(0);
  }
}
