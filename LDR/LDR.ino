const int ldr_pin = 7;
const int led_pin = 13;
void setup() {
  // put your setup code here, to run once:
    pinMode(ldr_pin,INPUT);
    pinMode(led_pin,OUTPUT);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   if( analogRead( ldr_pin ) > 290){
      digitalWrite( led_pin,HIGH);
   }
   else{
      digitalWrite( led_pin , LOW);
   }
   
   Serial.println( analogRead( ldr_pin ));
   delay(100);
}