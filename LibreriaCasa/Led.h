#ifndef Led_H
#define Led_H

#include <Arduino.h>

class Led
{
	private:
		int pin;
        int estado;
        bool prendido;
        // Generally, you should use "unsigned long" for variables that hold time
        // The value will quickly become too large for an int to store
        unsigned long previousMillis;        // will store last time LED was updated
        int intervalo;
	public:
		Led();
		~Led();
		Led(int pin, int estado, int intervalo);
		void setPin( int p);
		void setEstado(int e);
		void setIntervaloParpadeo(int t);
		int getEstado();
		void prender();
		void apagar();
		void parpadear();
		void ajustarBrillo(int valor);
};

#endif