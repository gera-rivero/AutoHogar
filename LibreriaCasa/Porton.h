/*
  Porton.h - Libraria para manejar un servo que simula un porton electrico.
  Created by Gerardo Rivero, Resistencia Chaco 19/12/2016.
  Released into the public domain.
*/
#ifndef Porton_h
#define Porton_h

#include "Arduino.h"
#include "Servo.h"
class Porton
{
  private:
		Servo p;
		bool abierto; // false es cerrado y verdadero abierto
		int angulo;
		unsigned long previousMillis;        // will store last time LED was updated
		// constants won't change :
		int intervaloMovimiento;

	public:
		Porton();
		void inicializar(int pinServo);
		bool getAbierto();
		void abrir();
		void cerrar();
};

#endif