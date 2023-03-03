int LED1 = 13;
int LED2 = 12;
int LED3 = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1, HIGH);    // turn on LED1 
  delay(1000);                  // wait for 200ms
  digitalWrite(LED2, HIGH);    // turn on LED2
  delay(1000);                  // wait for 200ms       
  digitalWrite(LED3, HIGH);    // turn on LED3 
  delay(1000);                  // wait for 200ms
  digitalWrite(LED1, LOW);     // turn off LED1
  delay(100);                  // wait for 300ms
  digitalWrite(LED2, LOW);     // turn off LED2
  delay(100);                  // wait for 300ms
  digitalWrite(LED3, LOW);     // turn off LED3
  delay(100);                  // wait for 300ms before running program all over again

}
