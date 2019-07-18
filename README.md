# Particle-simulation
This project was done for the purpose of entertainment and learning more about object oriented C++. Eclipse ver 4.12.0, MinGW, &amp; SDL2 library was used to make this happen. 
***************************SETUP BELOW******************************
How to setup SimpleDirectMediaLayer Library on Eclipse using MinGW 
1. Download SDL2 Development Libraries for MinGW: http://libsdl.org/download-2.0.php
2. Extract zip file. You'll need  7Zip or WinRar.
3. If using MinGW 32 bit you'll need the i686-w64-mingw32 folders contents. For 64 bit MinGW you'll need x86_64-w64-mingw32. 
4. Copy SDL2 folder from i686-w64-mingw32/include/SDL2 to the include folder of the MinGW install.
5. Copy the entire contents of the i686-w64-mingw32/lib to the lib folder of your MinGW install.
6. Start Eclipse and select File->New->C++ Project
7. Under Project type select Hello World C++ Project and under Toolchains select MinGW GCC.
8. Click project in the Project Explorer and then selecting Properties (advanced settings).
9. expand C/C++ Build and select Settings. find Configuration and select [All Configurations] from the drop down menu.
10. Select the Tool Settings tab and expand MinGW C++ Linker
11. Under MinGW C++ Linker select Libraries and then in the top right pane (Libraries (-l)) click the Add Icon. 
    Add these to them in this order: [mingw32] [SDL2main] [SDL2]
12. Still in the Tool Settings tab. Expand GCC C++ Compiler if not already expanded. Under GCC C++ Compiler select Includes.
    In the top right pane (Include paths (-l)) click the Add Icon (looks like a piece of paper with a + on it).
    Use the dialog to add the path to the SDL2 folder where you put your header files. Add: C:\MinGW\include\SDL2
    
13. Click Finish. 
14. In the i686-w64-mingw32\bin folder find the SDL2.dll and copy this to the projects Debug and Release folders next to the exe's             created.
15. From the Eclipse menu select Project->Build Configurations->Set Active->Debug and build your Project no errors should show. 

Run this sample code for setup initialization 

#include <SDL.h>
 
int main(int argc, char* argv[]) {
    // Start SDL2
    SDL_Init(SDL_INIT_EVERYTHING);
 
    // Create a Window in the middle of the screen
    SDL_Window *window = 0;
 
    window = SDL_CreateWindow("Hello World!",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              640, 480,
                              SDL_WINDOW_SHOWN);
 
    // Delay so that we can see the window appear
    SDL_Delay(2000);
 
    // Cleanup and Quit
    SDL_DestroyWindow(window);
    SDL_Quit();
 
    return 0;
}
