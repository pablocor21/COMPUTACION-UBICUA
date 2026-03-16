#include <LiquidCrystal.h> // Importa la librería para controlar pantallas LCD

// Configura los pines de la pantalla: (RS, Enable, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int SENSOR;          // Variable para almacenar el valor crudo del ADC (0 a 1023)
float TEMPERATURA;   // Variable para el cálculo de la temperatura actual
float SUMA;          // Variable acumuladora para sacar el promedio

void setup() {
  lcd.begin(16, 2);  // Inicializa la pantalla (16 columnas y 2 filas)
}

void loop() {
  SUMA = 0;          // Reiniciamos el acumulador en cada ciclo
  
  // Ciclo para tomar 5 muestras y suavizar la lectura
  for (int i = 0; i < 5; i++) {
    SENSOR = analogRead(A0); // Lee el voltaje en el pin analógico A0
    
    // Convierte el valor digital (0-1023) a grados Celsius
    // 5000.0 es el voltaje de referencia en mV (5V)
    // Se divide por 10 porque el sensor LM35 entrega 10mV por cada grado
    TEMPERATURA = ((SENSOR * 5000.0) / 1023) / 10;
    
    SUMA = TEMPERATURA + SUMA; // Suma la lectura actual al total
    delay(500);                // Espera medio segundo entre lecturas
  }

  // Visualización de resultados
  lcd.setCursor(0, 0);       // Ubica el cursor en la primera fila
  lcd.print("Temp:");        // Escribe el texto "Temp:"
  
  // Calcula el promedio (SUMA / 5) y lo muestra con 1 decimal
  lcd.print(SUMA / 5.0, 1);  
  
  lcd.print(" C");           // Añade la unidad de medida
}