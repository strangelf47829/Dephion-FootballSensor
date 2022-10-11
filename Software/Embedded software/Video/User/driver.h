/*
 * object.h
 *
 *  Created on: Oct 11, 2022
 *      Author: Rafael de Bie
 */

#ifndef DRIVER_H_
#define DRIVER_H_

typedef unsigned int uint;
typedef unsigned short ushort;


struct timing
{
	uint sync;
	uint frontPorch;
	uint backPorch;
	uint lines;
	bool edge;
};

class driver {
	public:
		driver();
		driver(ushort mode, struct timing horizontal, struct timing vertical);

		void setPixel();
	private:
		struct timing x;
		struct timing y;
		ushort mode;
};

#endif /* POLY_H_ */