#ifndef SPHEREH
#define SPHEREH

#include "Surface.h"
#include "Material.h"
#include "glm/geometric.hpp"
#include <cmath>

class Sphere : public Surface{
private:
    glm::vec3 center;
    float radius;
    glm::vec3 color;
    Material mat;
public:
    Sphere(){
        center = glm::vec3(0.0,0.0,0.0);
        radius = 1.0f;
        color = glm::vec3(1.0,0.0,0.0);
        mat = Material();
    }

    Sphere(glm::vec3 c, float r, glm::vec3 col, float a, float f, float sp, float mir){
        center = c;
        radius = r;
        color = col;
        mat = Material(a,f, sp, mir);
    }

    bool hit(Ray& r, float t_min, float t_max, hit_record &rec) const override{
        glm::vec3 offset = r.get_origin() - center;
        auto a = glm::dot(r.get_direction(), r.get_direction());
        auto b = glm::dot(2.0f * r.get_direction(), offset);
        auto c = glm::dot(offset,offset) - radius*radius;
        float discriminant = b*b - 4*a*c;

        if(discriminant < 0)
            return false;
        float t = (float)(-b-sqrt(discriminant)) / (2.0 * a);
        if(t <= t_min || t > t_max){
            t = (float)(-b+sqrt(discriminant)) / (2.0 * a);
            if(t <= t_min || t > t_max){
                return false;
            }
        }


        rec.t = t;
        rec.p = r.at_t(t);
        rec.norm = (rec.p -  center)/radius;
        rec.color_hit = color;
        rec.material = mat;
        //std::cout << rec.color_hit.x << rec.color_hit.y << rec.color_hit.z << std::endl;
        // std::cout << rec.norm.x << rec.norm.y << rec.norm.z << std::endl;

        return true;
    }

    
};

#endif