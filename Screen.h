/*
 * Screen.h
 *
 *  Created on: Jul 16, 2019
 *      Author: Larnellio
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL.h>

namespace Fireworks {

class Screen {
public:
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer1;	// look at this buffer for pixels to plot
	Uint32 *m_buffer2;	// put calculated results for pixel blur in different buffer then draw it



public:
	Screen();
	bool init();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	bool processEvents();
	void close();

	void boxBlur();
};

} /* namespace caveofprogramming */

#endif /* SCREEN_H_ */
