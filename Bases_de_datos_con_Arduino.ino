#include <SD.h>
#define pot_text "Pot.txt"
#define pot_grafica "Pot.csv"
#define luz_text "Luz.txt"
#define luz_grafica "Luz.csv"
#define chipSelect 10
#define potPin A1
#define LDR A0
#define intervalo 1000

File escritor;
byte medicion;

void setup() {
  Serial.begin(9600);
  
if(!SD.begin(chipSelect)){
  Serial.println("Tarjeta no funcional o no presente");
  //cuando salga este error debemos revisr la tarjeta, las conexiones y reiniciar el Arduino
  while(1);//se detiene el programa por completo
}
  Serial.println("Tarjeta inicializada correctamente");

  if(SD.exists(pot_text))SD.remove(pot_text);
  if(SD.exists(pot_grafica))SD.remove(pot_grafica);
  if(SD.exists(luz_text))SD.remove(luz_text);
  if(SD.exists(luz_grafica))SD.remove(luz_grafica);
  
  escritor = SD.open(pot_grafica, FILE_WRITE);
  escritor.println("Muestra,Medicion");
  escritor.close(); 

  escritor = SD.open(luz_grafica, FILE_WRITE);
  escritor.println("Muestra,Medicion");
  escritor.close();
  
}

void loop() {
  for(medicion = 1;medicion <= 10; medicion++){
    int potenciometro = analogRead(potPin);
    int ldr = analogRead(LDR);
  
    escritor = SD.open(pot_grafica, FILE_WRITE);
    escritor.print(medicion);
    escritor.print(',');
    escritor.println(potenciometro);
    escritor.close();
  
    escritor = SD.open(luz_grafica, FILE_WRITE);
    escritor.print(medicion);
    escritor.print(',');
    escritor.println(ldr);
    escritor.close();
  
    escritor = SD.open(pot_text, FILE_WRITE);
    escritor.print("En la muestra numero ");
    escritor.print(medicion);
    escritor.print(" se tiene una medida con valor de ");
    escritor.println(potenciometro);
    escritor.close();
  
    escritor = SD.open(luz_text, FILE_WRITE);
    escritor.print("En la muestra numero ");
    escritor.print(medicion);
    escritor.print(" se tiene una medida con valor de ");
    escritor.println(potenciometro);
    escritor.close();

    Serial.println("Escritura lista");
    delay(intervalo);
  }
  Serial.println("Todos los archivos correctamente escritos");
  while(1);//con esto detenemos completamente el programa
}
