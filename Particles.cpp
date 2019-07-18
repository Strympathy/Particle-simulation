/*
 * Particles.cpp
 *
 *  Created on: Jul 16, 2019
 *      Author: Larnellio
 */

#include "Particles.h"
#include <math.h>
#include <stdlib.h>

namespace Fireworks {

	// put particles into the center with random values
Particles::Particles(): m_x(0), m_y(0) {

	init();

}

void Particles::init() {
	// initialize the location
	m_x = 0;
	m_y = 0;

		m_direction = (2 * M_PI * rand())/RAND_MAX;		// gives us the angle to choose from 0 to 360*
		m_speed = (0.04 * rand())/RAND_MAX;			// gives speed to choose from at random

		m_speed *= m_speed;

}

/************************************* Forget This *****************************************/
	// intitialize the x and y values
	// range of -1 to +1
	//	m_x = ((2.0 * rand()) / RAND_MAX) - 1;
	//	m_y = ((2.0 * rand()) / RAND_MAX) - 1;
	// 0.001 is speed constant multiplied by double 2 (rand)  / rand max value  - 1 )
	// multiplying it by 2 then subtracting by one satisfies the range from -1 to +1
	//	m_xspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);
	//	m_yspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);

Particles::~Particles() {
	// TODO Auto-generated destructor stub
}


void Particles::update(int interval)	{

	// make particles curl some what
	m_direction += interval * 0.0003;

	// lets see how much we can move the X and Y particle coordinates by
	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);

	m_x += xspeed * interval; // ensures amount moved is proportional to amount of time thats passed since last particle moved
	m_y += yspeed * interval;

	// check to see if particle goes of edge of the screen
	if(m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)  {
			init();
	}

	// re-initialize some of the particles to make it look weird
	if(rand() < RAND_MAX/100) {
		init();
	}
}


/************************Dismiss This*********************************
	m_x += m_xspeed;
	m_y += m_yspeed;

	// make sure particles do not move off the edge
	if (m_x <= -1.0 || m_x >= 1.0) {
			m_xspeed = -m_xspeed;	// reverse the speed
		}

		if (m_y <= -1.0 || m_y >= 1.0) {
			m_yspeed = -m_yspeed;
		} ***************************************************************/

} /* namespace caveofprogramming */
