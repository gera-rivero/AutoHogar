/*
  Porton.cpp - Libraria para manejar un servo que simula un porton electrico.
  Created by Gerardo Rivero, Resistencia Chaco 19/12/2016.
  Released into the public domain.
*/
#include "Porton.h"

Porton::Porton(){
	abierto=false;
	angulo=90;
	previousMillis=0;
	intervaloMovimiento=90;
    p.write(angulo);        
}

void Porton::inicializar(int pinServo){
	p.attach(pinServo);
}

bool Porton::getAbierto(){
	return(abierto);
}
		
void Porton::abrir(){
	unsigned long currentMillis = millis();
	// retardar el movimiento del porton durante el intervalo
    if (currentMillis - previousMillis >= intervaloMovimiento){
        previousMillis = currentMillis;
              
        if (angulo>0){
            angulo-=1;
        } 
  
        p.write(angulo);        
    }
    abierto== true;
}

void Porton::cerrar(){
    unsigned long currentMillis = millis();
    // retardar el movimiento del porton durante el intervalo
    if (currentMillis - previousMillis >= intervaloMovimiento) {
        previousMillis = currentMillis;
               
        if (angulo<90){
            angulo+=1;
        } 
        p.write(angulo);        
    }
    if (angulo==90){
      	abierto=false;
  	}
}