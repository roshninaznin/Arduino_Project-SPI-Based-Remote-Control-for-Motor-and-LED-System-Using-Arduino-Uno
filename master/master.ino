
#include<SPI.h> 
#define LED 7
#define ipbutton 2
int buttonvalue;
int x;
void setup (void){
 Serial.begin(115200); 
 pinMode(ipbutton,INPUT); 
 pinMode(LED,OUTPUT); 
 SPI.begin(); 
 SPI.setClockDivider(SPI_CLOCK_DIV8); 

 digitalWrite(SS,HIGH); 
}
void loop(void){
 byte Mastersend, Mastereceive;
 buttonvalue = digitalRead(ipbutton); 
 if(buttonvalue == HIGH)
 {
 x = 1;
 }
 else
 {
 x = 0;
 }
 digitalWrite(SS, LOW);
 Mastersend = x;
 Mastereceive = SPI.transfer(Mastersend); 

if(Mastereceive == 1) 
 {
 digitalWrite(LED,HIGH); 
 Serial.println("Master LED is ON");
 }
 else
 {
 digitalWrite(LED,LOW); 
 Serial.println("Master LED is OFF");
 }
 delay(1000);
}