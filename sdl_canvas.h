#ifndef SDL_CANVAS_H
#define SDL_CANVAS_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>

#include "rayt.h"




//An interface for us to put pixels on. That's it.
class SDLCanvas {
    private:
        int     width; //Height and width may be adjustable later
        int     height;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Surface * surface;
        int pixelsin;
        void    addPixelToSurface(int x, int y, int R, int G, int B);
    public:
                SDLCanvas(int width, int height);
        void    putPixel(int x, int y, int R, int G, int B); 
        void    putPixel(int x, int y, Color c);
        void    appendPixel(Color c); //Scanline style pixel placement
        void    resetScan(); //Restart scanline style
        void    updateCanvas();
        int getWidth();
        int getHeight();
        double left();
        double right();
        double top();
        double bottom();
};

#endif
