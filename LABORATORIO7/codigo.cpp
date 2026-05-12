// -------- PINES DEL RECEPTOR RF --------
// Nota: Conecta D0 al 4, D1 al 2, D2 al 8 y D3 al 7
const int pinA = 4; // Boton A
const int pinB = 2; // Boton B
const int pinC = 8; // Boton C
const int pinD = 7; // Boton D

// -------- MOTORES (Shield L298P) --------
const int dirA = 12;   // Motor izquierdo
const int pwmA = 10;
const int dirB = 13;   // Motor derecho
const int pwmB = 11;

// Velocidad de giro (0 a 255)
const int velocidad = 200; 

void setup() {
  pinMode(dirA, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmB, OUTPUT);

  // Los pines del RF deben ser entradas
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);
  pinMode(pinD, INPUT);

  Serial.begin(9600);
  Serial.println("Robot listo. Esperando señal RF...");
}

void loop() {
  // Leer el estado de los botones
  int valA = digitalRead(pinA);
  int valB = digitalRead(pinB);
  int valC = digitalRead(pinC);
  int valD = digitalRead(pinD);

  // -------- CONTROL DE MOVIMIENTO --------
  // He corregido el orden para que coincida con las letras del control
  if (valA == HIGH) {         
    adelante(velocidad, velocidad);
    Serial.println("Boton A: Adelante");
  } 
  else if (valB == HIGH) {    
    atras(velocidad, velocidad);
    Serial.println("Boton B: Atras");
  } 
  else if (valC == HIGH) {    
    izquierda(velocidad, velocidad);
    Serial.println("Boton C: Izquierda");
  } 
  else if (valD == HIGH) {    
    derecha(velocidad, velocidad);
    Serial.println("Boton D: Derecha");
  } 
  else {
    parar();
  }
  
  delay(10); // Pequeña pausa para estabilidad
}

// -------- FUNCIONES DE MOVIMIENTO --------

void adelante(int velIzq, int velDer) {
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, HIGH);
  analogWrite(pwmA, velIzq);
  analogWrite(pwmB, velDer);
}

void atras(int velIzq, int velDer) {
  digitalWrite(dirA, LOW);
  digitalWrite(dirB, LOW);
  analogWrite(pwmA, velIzq);
  analogWrite(pwmB, velDer);
}

void izquierda(int velIzq, int velDer) {
  digitalWrite(dirA, LOW);  // Motor A atrás
  digitalWrite(dirB, HIGH); // Motor B adelante
  analogWrite(pwmA, velIzq);
  analogWrite(pwmB, velDer);
}

void derecha(int velIzq, int velDer) {
  digitalWrite(dirA, HIGH); // Motor A adelante
  digitalWrite(dirB, LOW);  // Motor B atrás
  analogWrite(pwmA, velIzq);
  analogWrite(pwmB, velDer);
}

void parar() {
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
}
