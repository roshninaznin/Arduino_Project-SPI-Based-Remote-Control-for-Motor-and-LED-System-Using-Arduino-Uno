#include <SPI.h>
#define in3 7    
#define in4 6   
#define ConA 5   
#define buttonPin 2  

volatile boolean received;
volatile byte Slavereceived, Slavesend;
int buttonValue;
int analogValue;
int x;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);   
  pinMode(in3, OUTPUT);       
  pinMode(in4, OUTPUT);       
  pinMode(ConA, OUTPUT);     
  pinMode(MISO, OUTPUT);    
  SPCR |= _BV(SPE);        
  
  received = false;
  SPI.attachInterrupt();     
}

ISR(SPI_STC_vect) {
  Slavereceived = SPDR; 
  received = true;    
}

void TurnMotorA1() {

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
 
  analogValue = analogRead(A0); 
  int PWMvalue = map(analogValue, 0, 1023, 0, 255)*1.2;  
 
  analogWrite(ConA, PWMvalue);   
}

void TurnMotorA2() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
  analogValue = analogRead(A0);   
  int PWMvalue = map(analogValue, 0, 1023, 0, 255);  
 
  analogWrite(ConA, PWMvalue); 
}

void loop() {
  if (received) {
    if (Slavereceived == 1) { 
      TurnMotorA1();
      Serial.println("Motor Running in Direction 1");
    } else {  
      TurnMotorA2();
      Serial.println("Motor Running in Direction 2");
    }

    buttonValue = digitalRead(buttonPin);  

    if (buttonValue == HIGH) {
      x = 1;  
    } else {
      x = 0;  
    }

    Slavesend = x;     
    SPDR = Slavesend;  
    received = false;

    delay(1000);
  }
}
