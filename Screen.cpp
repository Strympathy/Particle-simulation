/*
 * Screen.cpp
 *
 *  Created on: Jul 16, 2019
 *      Author: Larnellio
 */
#include "Screen.h"

namespace Fireworks {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(
				NULL) {

}

bool Screen::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	m_window = SDL_CreateWindow("Particle Fire Explosion",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	// allocate buffer here
	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	// clear the buffer get rid of garbage memory
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	return true;
}

void Screen::boxBlur() {
	// swap pointer buffers, so pixel info is in m_buffer2 and draw to m_buffer1
	Uint32 *temp = m_buffer1;	// store info for buffer1
	m_buffer1 = m_buffer2;		// buffer 1 points to 2
	m_buffer2 = temp;		// buffer2 points to stored original value temp

	// iterate through all pixels, look at buffer2, do some blur effects, copy them to buffer1, then show on screen
	// take what's on the screen and keep blurring it
	/* 0 0 0  R   Row -1
	 * 0 1 0  G   Row 0		look at specific pixel in the middle of other pixels RGB values, add up the RGB values per pixel(8)
	 * 0 0 0  B	  Row +1	then divide by pixel count (9)  and plot it in interested pixel (the one in the middle) to generate blur
	 */

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {

			// color values to store up
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			// the loop

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col; 	// |
					int currentY = y + row;		// --

					// cover pixels on edge of screen
					if (currentX >= 0 && currentX < SCREEN_WIDTH
							&& currentY >= 0 && currentY < SCREEN_HEIGHT) {
						Uint32 color = m_buffer2[currentY * SCREEN_WIDTH
								+ currentX];// covers rows color to get index

						Uint8 red = color >> 24;// right shift red color by 24 bits
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			// plot the blur out to the screen
			setPixel(x, y, red, green, blue);

		}
	}
}

/*****************************************NO NEED **********************************
 void Screen::clear()	{
 // memset particle buffer that holds the particles,
 // set each byte to 0 (it holds 4 bytes per pixel times the 4 bytes_from sizeof Uint32) clears bits.
 // memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
 ************************************************************************************/

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	// refuse to plot a pixel off the edge of the screen by checking y>0 & y<Screen height
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	// RGB(alpha)

	m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::update() {
	SDL_UpdateTexture(m_texture, NULL, m_buffer1,
			SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);

}

bool Screen::processEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Screen::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

} /* namespace caveofprogramming */
