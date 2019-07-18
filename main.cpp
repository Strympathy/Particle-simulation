//============================================================================
// Name        : SDL.cpp
// Author      : Kent King 
// Version     :
// Copyright   : Your copyright notice
/* Description : This is a particle  project done for the purpose of entertainment
				 and learning more about object oriented C++. I got really bored at work
				 since I was not advancing my knowledge on engineering fundementals/ anything
				 related to computer engineering/ programming so here take a look. I used SDL2
				 an open source cross-platform development library designed to provide
				 low level access to audio, keyboard, mouse, joystick,
				 and graphics hardware via OpenGL and Direct3D. This project took a little over a month btw
				 do not mind the actual dates in the header section of each file  */

//============================================================================

#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
#include "Swarm.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace Fireworks;



int main(int argc, char *argv[]) {
	// seeds random # generator with different sequence of #'s every time
	srand(time(NULL));

	Screen screen;

	if (screen.init() == false) {
		cout << "Error initializing SDL." << endl;
	}

	Swarm swarm;

// ****This Loop determines the speed of the particles moving based on how fast it iterates ****/
	while (true) {
		// Update particles
		// Draw particles

		int elapsed = SDL_GetTicks();

		// clear the screen
		// screen.clear(); ***** this holds position of particles if commented out , look below at bluring the screen  for a natural look *********
		// update position of all particles
		swarm.update(elapsed);	// gives time since program started and update each particle in Swarm.h

		unsigned char green =(unsigned char) ((1 + sin(elapsed * 0.0001)) * 128);
		unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);

		// loop through all the particles
		const Particles *const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particles particle = pParticles[i];

		/*************************** This is Optimized ******************************/
			// this makes an oval if i use SCREEN_HEIGHT for Y direction
			// map particle space to screen space to get a plot of particles (-1 to +1) on screen
			// int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;	 add one so its not negative (0 to 2) then multiply by 1/2 to get screen width
			// int y = (particle.m_y + 1) * Screen::SCREEN_WIDTH / 2;	 add one so its not negative (0 to 2) then multiply by 1/2 to get screen height


			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y  * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT/2;	// we wont plot stuff off edge of screen on top and bottom but we want it at the center

			screen.setPixel(x, y, red, green, blue);
		}

		// blur the screen (blurring algorithm)
		screen.boxBlur();

		// Draw the screen
		screen.update();

		// Check for messages/events
		if (screen.processEvents() == false) {
			break;
		}
	}

	screen.close();

	return 0;
}
