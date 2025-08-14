#ifndef PLANEH
#define PLANEH

#include "Surface.h"
#include "Material.h"
#include "glm/geometric.hpp"
//#include ""
#include <cmath>

class Plane : public Surface{
private:
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;
    glm::vec3 color;
    Material mat;
    
public:
    Plane(){
        a = glm::vec3(0,0,3);
        b = glm::vec3(0,1,3);
        c = glm::vec3(1,0,3);
        color = glm::vec3(1,0,0);
        mat = Material();
    }

    Plane(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, glm::vec3 col, float amb, float f, float sp, float mir){
        a = vert1;
        b = vert2;
        c = vert3;
        color = col;
        mat = Material(amb,f,sp,mir);
    }

    bool hit(Ray& r, float t_min, float t_max, hit_record &rec) const override{
        glm::vec3 e = r.get_origin();
        glm::vec3 d = r.get_direction();

        float _a = a.x - b.x;
        float _b = a.y - b.y;
        float _c = a.z - b.z;

        float _d = a.x - c.x;
        float _e = a.y - c.y;
        float _f = a.z - c.z;

        float _g = d.x;
        float _h = d.y;
        float _i = d.z;

        float _j = a.x - e.x;
        float _k = a.y - e.y;
        float _l = a.z - e.z;

        float M = _a * (_e*_i-_h*_f) + _b*(_g*_f-_d*_i) + _c*(_d*_h-_e*_g);

        float t = (-1.0f * (_f * (_a*_k-_j*_b) + _e*(_j*_c-_a*_l) + _d*(_b*_l-_k*_c))) / M;

        if(t < t_min){
            return false;
        }

        float gamma = (_i * (_a*_k-_j*_b) + _h*(_j*_c-_a*_l) + _g*(_b*_l-_k*_c)) / M;

        if(gamma < 0 || gamma > 1){
            return false;
        }

        float beta = (_j * (_e*_i-_h*_f) + _k*(_g*_f-_d*_i) + _l*(_d*_h-_e*_g)) / M;

        if(beta < 0 || beta > (1-gamma)){
            return false;
        }

        rec.t = t;
        rec.p = r.at_t(t);
        rec.norm = glm::normalize(glm::cross(b,c));
        rec.color_hit = color;
        rec.material = mat;


        return true;
    }

    
};

#endif