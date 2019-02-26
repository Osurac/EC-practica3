#include "44b.h"
#include "gpio.h"

/* Port B interface implementation */

int portB_conf(int pin, enum port_mode mode)
{
	int ret = 0;
	volatile unsigned int x = 0;

	if (pin < 0 || pin > 10)
		return -1; // indica error

	if (mode == SIGOUT){
		// COMPLETAR: poner en rPCONB el bit indicado por pin a 1 para que por
		// dicho pin en el puerto B salga la señal correspondiente del
		// controlador de memoria

		//rPCONB |= (0x1 << pin);
		// controlador de memoria
				x = rPCONB;
				x = x | (1<<pin);
				rPCONB = x;


	}else if (mode == OUTPUT){
		// COMPLETAR: poner en rPCONB el bit indicado por pin a 0 para que dicho
		// pin sea un pin de salida
		//rPCONB &= ~(0x1 << pin);

		x = rPCONB;
		x = x | ~(1<<pin);
		rPCONB = x;


	}else{
		ret = -1; // indica error
	}
	return ret;
}

int portB_write(int pin, enum digital val)
{
	volatile unsigned int x = 0;

	if (pin < 0 || pin > 10)
		return -1; // indica error

	if (val < 0 || val > 1)
		return -1; // indica error

	if (val){
		// COMPLETAR: poner en rPDATB el bit indicado por pin a 1
		//rPDATB |= (0x1 << pin);
		x = rPDATB;
		x = x | (1<<pin);
		rPDATB = x;

	}else{
		// COMPLETAR: poner en rPDATB el bit indicado por pin a 0
		//rPDATB |= ~(0x1 << pin);
		x = rPDATB;
		x = x & ~(1<<pin);
		rPDATB = x;

	}
	return 0;
}

/* Port G interface implementation */

int portG_conf(int pin, enum port_mode mode)
{
	int pos = pin*2;
	volatile unsigned int x = 0;


	if (pin < 0 || pin > 7)
		return -1; // indica error

	switch (mode) {
		case INPUT:
			// COMPLETAR: poner en rPCONG 00 a partir de la posición pos para
			// configurar como pin de entrada el pin indicado por el parámetro pin
			//Osu dice: rPCONG 00

//			rPCONG &= ~(0x1 << pos);
	//		rPCONG &= ~(0x1 << (pos + 1));

			x = rPCONG;
			x = x & ~(3<<pos);
			x = x | (0<<pos);
			rPCONG = x;

			break;
		case OUTPUT:
			// COMPLETAR: poner en rPCONG 01 a partir de la posición pos para
			// configurar como pin de salida el pin indicado por el parámetro pin
			//Osu dice: rPCONG 01
			//rPCONG |= ~(0x1 << pos);
			//rPCONG &= ~(0x1 << (pos + 1));

			x = rPCONG;
			x = x & ~(3<<pos);
			x = x | (1<<pos);
			rPCONG = x;

			break;
		case SIGOUT:
			// COMPLETAR: poner en rPCONG 10 a partir de la posición pos para
			// que salga la señal interna correspondiente por el pin indicado
			// por el parámetro pin
			//Osu dice: rPCONG 10
		//	rPCONG &= ~(0x1 << pos);
			//rPCONG |= ~(0x1 << (pos + 1));

			x = rPCONG;
			x = x | (1<<pos);
			x = x & ~(3<<pos);
			rPCONG = x;

			break;
		case EINT:
			// COMPLETAR: poner en rPCONG 11 a partir de la posición pos para
			// habilitar la generación de interrupciones externas por el pin
			// indicado por el parámetro pin
			//Osu dice: rPCONG 11
			//rPCONG |= ~(0x1 << pos);
		//	rPCONG |= ~(0x1 << (pos + 1));

			x = rPCONG;
			x = x | (1<<pos);
			x = x | (1<<pos);
		    rPCONG = x;

			break;
		default:
			return -1;
	}

	return 0;
}

int portG_eint_trig(int pin, enum trigger trig)
{
	// A COMPLETAR EN LA SEGUNDA PARTE DE LA PRÁCTICA
	return 0;
}

int portG_write(int pin, enum digital val)
{
	int pos = pin*2;
	volatile unsigned int x = 0;

	if (pin < 0 || pin > 7)
		return -1; // indica error

	if (val < 0 || val > 1)
		return -1; // indica error

	if ((rPCONG & (0x3 << pos)) != (0x1 << pos))
		return -1; // indica error

	if (val){
		// COMPLETAR: poner en rPDATG el bit indicado por pin a 1
		//rPDATG |= (0x1 << pin);
		x = rPCONB;
		x = x | (1<<pin);
	    rPCONB = x;

	}else{
		// COMPLETAR: poner en rPDATG el bit indicado por pin a 0
		//rPDATG &= (0x1 << pin);
		x = rPCONB;
		x = x | (1<<pin);
		rPCONB = x;
	}
	return 0;
}

int portG_read(int pin, enum digital* val)
{
	int pos = pin*2;

	if (pin < 0 || pin > 7)
		return -1; // indica error

	if (rPCONG & (0x3 << pos))
		return -1; // indica error
	/*COMPLETAR: true si está a 1 en rPDATG el pin indicado por el parámetro pin*/

	if(rPDATG & (0x1 << pos)){
		*val = HIGH;
	}else{
		*val = LOW;
	}
	return 0;
}

int portG_conf_pup(int pin, enum enable st)
{
	 volatile unsigned int x = 0;

	if (pin < 0 || pin > 7)
		return -1; // indica error

	if (st != ENABLE && st != DISABLE)
		return -1; // indica error
	if(st == ENABLE){
		// COMPLETAR: poner el pin de rPUPG indicado por el parametro pin al valor adecuado,
		// para activar la resistencia de pull-up
		x = rPUPG;
		x = x | (1<<pin);
		rPUPG = x;
	}else{
		// COMPLETAR: poner el pin de rPUPG indicado por el parametro pin al valor adecuado,
		// para desactivar la resistencia de pull-up
		x = rPUPG;
		x = x & ~(1<<pin);
		rPUPG = x;
	}
	return 0;

}

