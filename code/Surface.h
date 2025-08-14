#ifndef SURFACEH
#define SURFACEH

#include "glm/vec3.hpp"
#include "Ray.h"
#include "Material.h"
struct hit_record {
    glm::vec3 p;
    glm::vec3 norm;
    float t;
    glm::vec3 color_hit;
    Material material;
};

class Surface{
public:
    virtual ~Surface() = default;
    virtual bool hit(Ray& r, float t_min, float t_max, hit_record &rec) const = 0;
    

};

#endif