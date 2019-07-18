/*
 * Swarm.h
 *
 *  Created on: Jul 16, 2019
 *      Author: Larnellio
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particles.h"

namespace Fireworks {

class Swarm {
public:
	const static int NPARTICLES = 5000;

private:
	// particles pointer
	Particles *  m_pParticles;
	int lastTime;	// past time since update ran -- behind elapsed time --

public:
	Swarm();
	virtual ~Swarm();
	void update(int elapsed );	// take the time since the program started -- current time --
	// get particles from swarm particle cannot be changed once its returned
	const Particles *const getParticles() {return m_pParticles; };
};

} /* namespace caveofprogramming */

#endif /* SWARM_H_ */
