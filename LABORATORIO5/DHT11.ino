#include <DHT.h>

int pinDatos = 12; // Variable tradicional para el pin
DHT dht(pinDatos, DHT11); 

void setup(){
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  // Leemos y guardamos en variables cortas para limpiar el código
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Si la lectura es correcta, imprimimos
  if (!isnan(t) && !isnan(h)) {
    Serial.print("Temp: "); Serial.print(t, 1);
    Serial.print(" C | Hum: "); Serial.print(h, 0);
    Serial.println(" %");
  } else {
    Serial.println("Error: Sensor desconectado");
  }

  delay(2000); 
}