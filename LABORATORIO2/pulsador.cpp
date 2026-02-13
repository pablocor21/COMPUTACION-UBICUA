int PULSADOR = 2;
int LED = 3;

int estadoLED = LOW;
int estadoBotonAnterior = HIGH;   

void setup() {
  pinMode(PULSADOR, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  int estadoBotonActual = digitalRead(PULSADOR);

 
  if (estadoBotonActual == LOW && estadoBotonAnterior == HIGH) {
    estadoLED = !estadoLED;
    digitalWrite(LED, estadoLED);
    delay(5000); 
  }

  estadoBotonAnterior = estadoBotonActual;
}