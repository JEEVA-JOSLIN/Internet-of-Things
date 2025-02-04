const int led=13;
const int sound=10;
const int threshold=300;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(sound,INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  int s=analogRead(sound);
  
  if(s>threshold)
  {
    digitalWrite(led,HIGH);
    Serial.print(s);
    Serial.print("\n");
  }
  else
  {
    digitalWrite(led,LOW);
  }

}
