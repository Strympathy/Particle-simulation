/*
 * Swarm.cpp
 *
 *  Created on: Jul 16, 2019
 *      Author: Larnellio
 */

#include "Swarm.h"

namespace Fireworks {

Swarm::Swarm(): lastTime(0){
	// initialize pointer array of particles
	m_pParticles = new Particles[NPARTICLES];

}

Swarm::~Swarm() {
	// de-allocate memory of pointer since its an array
	delete [] m_pParticles;
}

void Swarm::update(int elapsed) {

	int interval = elapsed - lastTime;	// get difference in time of particles updating (design pattern??)

	// loop through all particles and update them
	for (int i = 0; i < Swarm::NPARTICLES; i++) {
		m_pParticles[i].update(interval);
	}

	lastTime = elapsed;	// stored time since last updated time
}

} /* namespace caveofprogramming */
