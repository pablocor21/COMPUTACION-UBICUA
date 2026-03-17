#include <DHT.h>

#define DHTPIN 12      // Usamos 'define' para ahorrar memoria
DHT dht(DHTPIN, DHT11); 

void setup(){
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  // Leemos directamente en las variables
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Verificación rápida
  if (isnan(t) || isnan(h)) {
    Serial.println("Error de lectura");
  } else {
    // Imprimimos todo de forma más compacta
    Serial.print("T: "); Serial.print(t, 1);
    Serial.print("C | H: "); Serial.print(h, 0);
    Serial.println("%");
  }

  delay(2000); 
}