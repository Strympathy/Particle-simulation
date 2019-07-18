/*
 * Particles.h
 *
 *  Created on: Jul 16, 2019
 *      Author: Larnellio
 */

#ifndef PARTICLES_H_
#define PARTICLES_H_

namespace Fireworks {

// everythings public by default.. i think with a struct
struct Particles {
	// give particle x and y position
	double m_x;
	double m_y;

private:
	double m_speed;			// how fast particle is moving in a direction
	double m_direction; 	// angle from 0-360 degrees

	/***************************** Forget This ************************************/
	// 0.001 is speed constant multiplied by double 2 (rand)  / rand max value  - 1 )
	// multiplying it by 2 then subtracting by one satisfies the range from -1 to +1
	// double m_xspeed;
	// double m_yspeed;

private:
	void init();

public:
	Particles();
	virtual ~Particles();
	void update(int interval);		// update position of particle
};

} /* namespace caveofprogramming */

#endif /* PARTICLES_H_ */
