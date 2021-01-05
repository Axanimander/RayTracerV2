#include "sdl_canvas.h"
#include <cassert>
#include <iostream>

using std::cerr;

SDLCanvas::SDLCanvas(int width, int height) : width(width), height(height) {

  pixelsin = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    
  }
  //SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
  window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
  surface = SDL_GetWindowSurface(window);
}

void SDLCanvas::addPixelToSurface(int x, int y, int R, int G, int B){
  
  unsigned char* pixels = (unsigned char*)surface -> pixels;
  pixels[4 * (y * surface -> w + x) + 0] = B;
  pixels[4 * (y * surface -> w + x) + 1] = G;
  pixels[4 * (y * surface -> w + x) + 2] = R;       
}


void SDLCanvas::putPixel(int x, int y, int R, int G, int B){
    
    //SDL_SetRenderDrawColor(renderer, colors[0], colors[1], colors[2],255);
   // int screen_x = width/2 + x;
  //  int screen_y = height/2 - y;
    addPixelToSurface(x, y, R,G,B);
    //SDL_RenderDrawPoint(renderer, screen_x, screen_y);
    //SDL_RenderPresent(renderer);
}
void SDLCanvas::putPixel(int x, int y, Color c){
  int R = static_cast<int>(255.999 * c.x());
  int G = static_cast<int>(255.999 * c.y());
  int B = static_cast<int>(255.999 * c.z());

  if(x > width || y > height){
    assert(false);
  }
  putPixel(x, y, R,G,B);
}

void SDLCanvas::appendPixel(Color c){
  int x = pixelsin % width;
  int y = (pixelsin / width) % height;
  putPixel(x, y, c);
  pixelsin++;
}

void SDLCanvas::resetScan(){
  pixelsin = 0;
}
void SDLCanvas::updateCanvas(){
  SDL_UpdateWindowSurface(window);
}
int SDLCanvas::getHeight(){
    return height;
}

int SDLCanvas::getWidth(){
    return width;
}

double SDLCanvas::left(){
  return -width/2;
}

double SDLCanvas::right(){
  return width/2;
}

double SDLCanvas::top(){
  return -height/2;
}

double SDLCanvas::bottom(){
  return height/2;
}