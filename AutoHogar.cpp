#include <Led.h>
#include <Porton.h>


int servo=5;
String entrada;
String actuarPorton;
String actuarLuz;
unsigned long previousMillis=0; // para la espera de la luz del garage;
int tiempoEsperaGarage= 10000;

int temp_ingresada=100;
int ventilador= 4;
bool vent_prendido= false;

// Crear Objetos Led luz; ejemplo sin ()
Porton p;

Led luzPorton(2,LOW,200); //luz de afuera que indica que el porton está abierto
Led luzGarage(8,LOW,0); // va a estar prendida mientras se abra o cierra el portón

Led luzCocina2(3,LOW,0);
Led luzPieza2(7,LOW,0);
Led luzPieza(6,LOW,0); //puede cambiar la intensidad del brillo
Led luzHall(11,LOW,0);

int cocina2=0; //esta luz es ficticia para ocupar un lugar en el arreglo noma
int pieza=1;
int pieza2=2;
int garage=3;
int porton=4; //esta luz no puede manejar el cliente
int hall= 5;

Led luces[]={luzCocina2,luzPieza,luzPieza2,luzGarage,luzPorton,luzHall};

int tempPin = 0; //Analog pin connected to LM35
float referenceVoltage;

void setup()
{ 
  p.inicializar(servo);
  pinMode(ventilador, OUTPUT);

  Serial.begin(9600);

  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  analogReference(INTERNAL);
  referenceVoltage = 1.1; //Set to 5, 3.3, 2.56 or 1.1 depending on analogReference Setting
}



void loop(){
  
  if(Serial.available()>0){
    entrada = Serial.readString();
  };
  
  if (entrada=="a"||entrada=="c"){
    actuarPorton=entrada;
  }; 

  moverPorton(actuarPorton);
  luz(entrada);
  
  if (entrada=="t"){
    int temp=updateTemparature();
    Serial.println(temp);
    entrada="o";
  }

  venti(entrada);

}



void moverPorton(String accion)
{
  unsigned long currentMillis = millis();

  if (accion=="a")
  {
    p.abrir();
  };

  if (accion=="c")
  {
    p.cerrar();
  };

  if (p.getAbierto() && (accion=="a"||accion=="c") )
  {
    luces[porton].parpadear();
    luces[garage].prender();
    previousMillis= currentMillis;
  }
  
  if (!p.getAbierto()&& (accion=="a"||accion=="c"))
  {
    luces[porton].apagar();
    if (currentMillis - previousMillis >= tiempoEsperaGarage) //cuando se cerró el garage espera 2 segundos luego apago la luz del garage 
    {
      luces[garage].apagar();
      actuarPorton="o";
    }
  }
};

void luz(String accion)
{
  if (accion=="1a")
  {
    luces[pieza].apagar();
    luces[pieza2].apagar();
  }

  if (accion=="3a")
  {
    luces[garage].apagar();
  }
  
  if (accion=="5a")
  {
    luces[hall].apagar();
  }


  if (accion=="1p")
  {
    luces[pieza].prender();
    luces[pieza2].prender();
  }

  if (accion=="3p")
  {
    luces[garage].prender();
  }

  if (accion=="5p")
  {
    luces[hall].prender();
  }
}

int updateTemparature(){
  float tempC;
    float reading = 0;
    int i=0;
    int leoTemperatura= 500;
    unsigned long previousMillis=0;

    while(i < 10) 
    { // Average 10 readings for accurate reading
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= leoTemperatura) 
      {
        // save the last time you blinked the LED
          previousMillis = currentMillis;
      
          reading += analogRead(tempPin);

          ++i;
      }
    }
    // A lot of examples divide the sensor reading by 1024. This is incorrect and should be 1023. There are 1024 values including 0 so this should be 1023.
  tempC =  (referenceVoltage * reading * 10) / 1023; 
    
  int temperatura= round(tempC);
  
  return(temperatura);  
}

void venti(String accion){

  if(accion=="st"){
    while (Serial.available() == 0);
    if((Serial.available()>0)){
      temp_ingresada = Serial.parseInt(); //read int or parseFloat for ..float...
    }
  };
  
  if (updateTemparature()>temp_ingresada && vent_prendido==false) {
      digitalWrite(ventilador, HIGH);
      vent_prendido= true;
  }

  if(updateTemparature()<temp_ingresada && vent_prendido==true){
    digitalWrite(ventilador, LOW);
    vent_prendido= false;
  }
  
  if (accion=="vp") {
      digitalWrite(ventilador, HIGH);
      vent_prendido= true;
      temp_ingresada=-10;
  }
  if (accion=="vo") {
    digitalWrite(ventilador, LOW);
    vent_prendido=false;
    temp_ingresada=100;
  }
  entrada="o";
}