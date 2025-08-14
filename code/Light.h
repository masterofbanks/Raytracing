#ifndef LIGHTH
#define LIGHTH

#include "Surface.h"


class Light{
public:
    virtual ~Light() = default;
    virtual glm::vec3 illuminate(Ray& ray, hit_record& rec, hit_record& srec) = 0;
    virtual glm::vec3 get_location() = 0;
};


#endif