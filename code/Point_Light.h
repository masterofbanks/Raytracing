#ifndef POINT_LIGHTH
#define POINT_LIGHTH

#include "glm/geometric.hpp"
#include "Light.h" 
#include <iostream>

class Point_Light : public Light{
private:
    glm::vec3 I;
    glm::vec3 p;
public:
    Point_Light(){
        I = glm::vec3(1,1,1);
        p = glm::vec3(0,0,0);
    }

    Point_Light(glm::vec3 color, glm::vec3 position){
        I = color;
        p = position;
    }

    glm::vec3 illuminate(Ray& ray, hit_record& rec, hit_record& srec) override{
        glm::vec3 answer;
        
        if(srec.t < MAXFLOAT){
            glm::vec3 x = ray.at_t(rec.t);
            //auto r = glm::length(p - x);
            glm::vec3 l = glm::normalize(p - x);
            glm::vec3 n = rec.norm;
            //glm::vec3 E = (std::max(0.0f,glm::dot(n,l)) / (r*r)) * I;
            glm::vec3 diffuse_light = rec.material.get_diffuse_k() * I * std::max(0.0f,glm::dot(n,l));
            
            //glm::vec3 h = (1/glm::length(l+x)) * (l + x);
            glm::vec3 h = 2*glm::dot(n,l)*n - l;
            glm::vec3 spec_light = rec.material.get_spec_k() * I * float(pow(std::max(0.0f,glm::dot(n,h)), 16));

            answer = diffuse_light + spec_light;
        }

        else{
            answer = glm::vec3(0,0,0);
        }
        

        
        return answer;
    }

    glm::vec3 get_location() override {
        return p;
    }

};





#endif