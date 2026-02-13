int pinLED = 3;

int pinPOT = A0;


void setup(){
  
 pinMode(pinLED, OUTPUT);
}

void loop(){
  int valor = analogRead(pinPOT);
  
  int PWM = map(valor, 0, 1020, 0, 255);
  
  analogWrite(pinLED, PWM);
  
  delay(10);
}