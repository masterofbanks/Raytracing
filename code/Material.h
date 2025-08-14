#ifndef MATERIALH
#define MATERIALH

class Material{
private:
    float ambient_k;
    float diffuse_k;
    float specular_k;
    float mirror_k;
public:
    
    Material(){
        ambient_k = 0.0f;
        diffuse_k = 0.0f;
        specular_k = 0.0f;
        mirror_k = 0.0f;
    }

    Material(float a, float d, float spec, float mir){
        ambient_k = a;
        diffuse_k = d;
        specular_k = spec;
        mirror_k = mir;
    }
    float get_ambient_k(){
        return ambient_k;
    }

    float get_diffuse_k(){
        return diffuse_k;
    }

    float get_spec_k(){
        return specular_k;
    }

    float get_mirror_k(){
        return mirror_k;
    }

};


#endif