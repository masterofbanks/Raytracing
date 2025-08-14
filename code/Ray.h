#ifndef RAYH
#define RAYH


#include <iostream>
#include "glm/vec3.hpp"
class Ray{
private:
    glm::vec3 origin;
    glm::vec3 direction;
public:
    Ray(){
        origin    = glm::vec3(0, 0, 0);
        direction = glm::vec3(1, 0, 0);
    }

    Ray(glm::vec3 o, glm::vec3 d){
        origin    = o;
        direction = d;
    }
    
    glm::vec3 at_t(float t){
        return origin + t * direction;
    }
    glm::vec3 get_origin(){
        return origin;
    }
    glm::vec3 get_direction(){
        return direction;
    }

};

#endif