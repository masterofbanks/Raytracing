#ifndef MULTIPLE_SURFACESH
#define MULTIPLE_SURFACESH

#include "Surface.h"
#include <vector>
#include <iostream>
#include "Point_Light.h"
#include "Ambient_Light.h"

class Multiple_Surfaces : public Surface{
public:
    
    Surface ** list;
    unsigned int size;
    Light ** lights;
    unsigned int light_num;
    Multiple_Surfaces(Surface** l, int s, Light** li, int ln){
        list = l;
        size = s;
        lights = li;
        light_num = ln;
    }

    bool hit(Ray& r, float t_min, float t_max, hit_record &rec) const override{
        hit_record temp_rec;
        bool any_hits = false;
        float closest_so_far = t_max;

        for(unsigned int i = 0; i < size; i++){
            if(list[i]->hit(r,t_min,closest_so_far,temp_rec)){
                any_hits = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
            
        }
        
        return any_hits;
    }


    
};

#endif