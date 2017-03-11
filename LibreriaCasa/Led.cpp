#include "Led.h"

Led::Led(){                                        // Constructor                  
	setPin(13);
      pinMode(pin , OUTPUT);
      apagar();
      setIntervaloParpadeo(0);
}   

Led::~Led(){}

Led::Led(int pin, int estado, int intervalo){      // Constructor
      setPin(pin);
      setEstado(estado);
      setIntervaloParpadeo(intervalo);

      pinMode(pin , OUTPUT);
                  
      if (getEstado()==HIGH){
      	prender();
      }
      if (getEstado()==LOW){
            apagar();
      };
}

void Led::setPin( int p){
      pin= p;
}

void Led::setEstado(int e){
      estado=e;
}

void Led::setIntervaloParpadeo(int t){
      intervalo=t;
}

int Led::getEstado(){
      return(estado);
}
    
void Led::prender(){
      setEstado(HIGH);
	digitalWrite(pin, estado);
}      

void Led::apagar(){
      setEstado(LOW);
      digitalWrite(pin, estado);
}      
       
void Led::parpadear(){
	unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= intervalo) {
        	// save the last time you blinked the LED
      	previousMillis = currentMillis;
        	// if the LED is off turn it on and vice-versa:
        	if (getEstado() == LOW){
            	setEstado(HIGH);
        	} 
        	else {
          		setEstado(LOW);
        	}

        	digitalWrite(pin, getEstado());
      }
}

void Led::ajustarBrillo(int valor){
	analogWrite(pin, valor);
}