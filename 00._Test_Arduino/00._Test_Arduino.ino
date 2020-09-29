#define yellowLed1 6
#define yellowLed2 5
#define yellowLed3 4

void setup() {
  pinMode(yellowLed1, OUTPUT);
  pinMode(yellowLed2, OUTPUT);
  pinMode(yellowLed3, OUTPUT);
  
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(yellowLed1, HIGH); 
  delay(500);
  digitalWrite(yellowLed1, LOW); 
  delay(500);

  digitalWrite(yellowLed2, HIGH); 
  delay(500);
  digitalWrite(yellowLed2, LOW); 
  delay(500);

  digitalWrite(yellowLed3, HIGH); 
  delay(500);
  digitalWrite(yellowLed3, LOW); 
  delay(500);
}
