#include <SDL2/SDL.h>

#include <iostream>
#include <cassert>

#include "sdl_canvas.h"
#include "rayt.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "scenes.h"



using std::cout;
using std::endl;
using std::cerr;






Color ray_color(const Ray& r, const hittable& world, int depth){
    hit_record rec;
    if(depth <= 0){
        return Color(0,0,0);
    }
    if(world.hit(r, 0.001, infinity, rec)){
        Ray scattered;
        Color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation * ray_color(scattered, world, depth-1);
        }
       return Color(0,0,0);
    }
    Vec3 unit_dir = unit_vector(r.direction());
    auto t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * Color(1.0,1.0,1.0) + t * Color(0.5, 0.7, 1.0);
}
int main(){

    //Canvas
    const auto aspect_ratio = 3.0/2.0;
    const int image_width = 1200;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 6;
    SDLCanvas Canvas(image_width, image_height);

    //World
  
    auto world = random_scene();


    Point3 lookfrom(13,2,3);
    Point3 lookat(0,0,0);
    Vec3 vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
    

    //Render
    Canvas.putPixel(0, 0, 255,255,255);
    for (int j = image_height-1; j >= 0; --j) {
        cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0,0,0);
            for(int s = 0; s < samples_per_pixel; ++s){
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.get_ray(u,v);
                pixel_color += ray_color(r, world, max_depth);
        }
            Color final_color = write_color(pixel_color, samples_per_pixel);
            Canvas.appendPixel(final_color);
        }
    }
    Canvas.updateCanvas();
    SDL_Delay(10000);
}