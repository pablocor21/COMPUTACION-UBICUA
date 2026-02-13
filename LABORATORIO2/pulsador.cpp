int PULSADOR = 2; 
int LED=3; 

void setup(){ 

pinMode(PULSADOR, INPUT); 
pinMode(LED, OUTPUT); 
digitalWrite(LED, LOW);

 } 

void loop (){ 

while(digitalRead(PULSADOR) == LOW){ 
 }

digitalWrite(LED, HIGH);		
delay(5000); 				 
digitalWrite(LED, LOW); 		

while(digitalRead(PULSADOR) == HIGH){ 	
 }

}