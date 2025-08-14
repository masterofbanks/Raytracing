#ifndef AMBIENT_LIGHTH
#define AMBIENT_LIGHTH

#include "glm/geometric.hpp"
#include "Light.h" 
#include <iostream>

class Ambient_light : public Light{
private:
    glm::vec3 I;
    
public:
    Ambient_light(){
        I = glm::vec3(1,1,1);
        
    }

    Ambient_light(glm::vec3 color){
        I = color;
        
    }

   glm::vec3 illuminate(Ray& ray, hit_record& rec, hit_record& srec) override{
        return rec.material.get_ambient_k()*I;
    }

    glm::vec3 get_location() override{
        return glm::vec3(0,0,0);
    }

};


//


#endif