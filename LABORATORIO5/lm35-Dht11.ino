#include <LiquidCrystal.h> // Librería para controlar la pantalla LCD
#include <DHT.h>           // Librería para los sensores de temperatura y humedad DHT

// Configuración de pines para la LCD: RS, Enable, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Definición de parámetros para el DHT11
#define DHTPIN 12          // Pin digital donde está conectado el pin de datos del sensor
#define DHTTYPE DHT11      // Definimos el modelo específico (azul)
DHT dht(DHTPIN, DHTTYPE);  // Inicialización del objeto dht

// Pin analógico donde conectamos la pata central del LM35
const int pinLM35 = A0;

void setup() {
  Serial.begin(9600);      // Inicia la comunicación con la PC para ver datos en el monitor serie
  lcd.begin(16, 2);        // Configura la pantalla LCD (16 columnas y 2 filas)
  dht.begin();             // Arranca el sensor DHT11
  
  // Mensaje de bienvenida inicial en la pantalla
  lcd.print("Iniciando...");
  delay(2000);             // Espera 2 segundos
  lcd.clear();             // Limpia la pantalla para empezar a mostrar datos
}

void loop() {
  // --- LECTURA DEL LM35 ---
  // analogRead nos da un valor entre 0 y 1023 basado en el voltaje (0-5V)
  int lecturaLM35 = analogRead(pinLM35);
  
  // Convertimos el valor analógico a grados Celsius:
  // (Lectura * 5000mV / 1023 niveles) / 10mV por cada grado Celsius
  float tempLM35 = (lecturaLM35 * 5000.0 / 1023.0) / 10.0;

  // --- LECTURA DEL DHT11 ---
  float tempDHT = dht.readTemperature(); // Lee la temperatura en grados Celsius
  float humDHT = dht.readHumidity();    // Lee el porcentaje de humedad relativa

  // --- MOSTRAR DATOS EN PANTALLA LCD ---
  
  // Ubicamos el cursor al inicio de la primera fila
  lcd.setCursor(0, 0);
  lcd.print("LM35: ");
  lcd.print(tempLM35, 1);    // Mostramos la temperatura con 1 decimal
  lcd.print("C   ");         // Espacios al final para evitar basura visual

  // Ubicamos el cursor al inicio de la segunda fila
  lcd.setCursor(0, 1);
  
  // Verificamos si la lectura del DHT falló (isnan = is not a number)
  if (isnan(tempDHT)) {
    lcd.print("DHT: Error    ");
  } else {
    // Si la lectura es correcta, mostramos Temp y Humedad
    lcd.print("DHT11:");
    lcd.print((int)tempDHT); // El DHT11 no tiene precisión decimal, usamos entero
    lcd.print("C ");
    lcd.print("H:");
    lcd.print((int)humDHT);
    lcd.print("%    ");
  }

  // --- IMPRIMIR DATOS EN EL MONITOR SERIAL (PC) ---
  
  Serial.print("LM35: ");
  Serial.print(tempLM35, 1);
  Serial.print(" C | ");
  
  // Segunda validación para el monitor serie
  if (!isnan(tempDHT)) {
    Serial.print("DHT11 Temp: ");
    Serial.print(tempDHT, 0); // Mostramos sin decimales
    Serial.print(" C | Humedad: ");
    Serial.print(humDHT, 0);
    Serial.println(" %");      // println hace un salto de línea al final
  } else {
    Serial.println("Error en lectura de DHT11");
  }

  // Espera de 2 segundos. Es vital para que el DHT11 no se sature.
  delay(2000); 
}