
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include "Ray.h"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include <iostream>
#include <cmath>
#include "Multiple_Surfaces.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include <string> 
#include "stb_image_write.h"



glm::vec3 color(Ray r, Multiple_Surfaces* scene, int depth){
    hit_record rec;
    //glm::vec3 background_color = glm::vec3(25.0f/255, 25.0f/255, 113.0f/255);
    if(scene->hit(r,0.0,MAXFLOAT,rec)){
        
       
        
        glm::vec3 c = rec.color_hit;

        for(unsigned int i = 0; i < scene->light_num; i++){
            hit_record srec;
            if(scene->lights[i]->get_location() != glm::vec3(0,0,0)){
                glm::vec3 x = r.at_t(rec.t);
                glm::vec3 l = glm::normalize(scene->lights[i]->get_location() - x);
                Ray new_ray = Ray(x,l);
                if(scene->hit(new_ray,0.001,MAXFLOAT,srec)){
                    continue;
                    
                }
            }
            c = c + scene->lights[i]->illuminate(r,rec, srec);
        }

        
        
        return c;
    }

    else{
        return glm::vec3(0.0,0.0,0.0);
    }

    //return glm::vec3(0.0,0.0,0.0);


}

int main(){
    
    int width = 800;
    int height = 800;

    //camera position
    //glm::vec3 lower_left_corner  = glm::vec3(-2.0, -1.0, -1.0);
    //glm::vec3 look_at_vector = glm::vec3(-2.0,-1.0,1.0);
    glm::vec3 look_at_vector = glm::vec3(0,0,1);
    glm::vec3 horizontal = glm::vec3(8.0, 0.0, 0.0);
    glm::vec3 vertical = glm::vec3(0.0, 8.0, 0.0);
    //glm::vec3 origin = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 lower_left_corner = glm::vec3(-4.0, -4.0, 0.0);

    std::cout << "render movie? enter yes to do so or anything else render only one picture: " << std::endl;
    std::string input = "";
    std::cin >> input; 

    

    bool make_movie_frames = (input == "yes");
    if(make_movie_frames){
        float r = 3;
        float theta = 0;
        const float PI = 3.14159;
        int photo_num = 1;
        std::cout << "Enter the number of frames for the movies. Movie will be rendered at 60fps: " << ::std::endl;
        float num_frames = 0;
        std::cin >> num_frames;
        float incrament = PI/num_frames;

        while(theta < 2 * PI){
            Surface *list[6];   
        
            
            list[0] = new Sphere(glm::vec3(r * cos (theta),r * sin (theta), 10), 0.5, glm::vec3(0.3,0.3,0.3), 0.2, 0.4, 0.4, 0);
            list[1] = new Sphere(glm::vec3(r * cos (theta + PI/2),r * sin (theta + PI/2), 10), 0.5, glm::vec3(0,0,0.3), 0.2, 0.4, 0.4, 0);
            list[2] = new Sphere(glm::vec3(r * cos (theta + PI),r * sin (theta + PI), 10), 0.5, glm::vec3(0.3,0,0), 0.2, 0.4, 0.4, 0);
            list[3] = new Sphere(glm::vec3(r * cos (theta + 3 * PI/2),r * sin (theta + 3 * PI/2), 10), 0.5, glm::vec3(0.3,0,0.3), 0.2, 0.4, 0.4, 0);
            list[4] = new Sphere(glm::vec3(0,1,3), 0.5, glm::vec3(0.3,0.3,0.3), 0.2, 0.4, 0.4, 0);
            list[5] = new Sphere(glm::vec3(0,0,3), 0.15, glm::vec3(1,1,0.0), 0.0, 0.0, 0.0, 0);
            
            Light *light_list[2];
            light_list[0] = new Point_Light(glm::vec3(1,1,1),glm::vec3(0,0,1));
            light_list[1] = new Ambient_light(glm::vec3(1,1,1));

            Multiple_Surfaces *scene = new Multiple_Surfaces(list,6, light_list, 2);


            
            
            
            








            //DO STUFF WITH PIXELS HERE
            unsigned char* data = new unsigned char[width*height*3];
            for(int y = 0; y < height; ++y){
                for(int x  = 0; x < width; ++x){
                    float u = float(x) / float(width);
                    float v = float(y) / float(height);
                    
                    Ray r = Ray(lower_left_corner + u * horizontal + v* vertical, look_at_vector); //ortho camera
                    //Ray r = Ray(origin, look_at_vector + u * horizontal + v* vertical); // perspective

                    glm::vec3 col = color(r, scene, 5);
                    int red = int(255 * col.x);
                    int g = int(255 * col.y);
                    int b = int(255 * col.z);

                    if(red > 255){
                        red = 255;
                    }

                    if(g > 255){
                        g = 255;
                    }

                    if(b > 255){
                        b = 255;
                    }
                    data[y * height * 3 + x * 3    ] = red; // r
                    data[y * height * 3 + x * 3 + 1] = g; // g 
                    data[y * height * 3 + x * 3 + 2] = b; // b
                }
            }


            glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
            int nrChannels = 3;
            int stride =  nrChannels * width;
            stride += (stride % 4) ? (4 - stride % 4) : 0;
            stbi_flip_vertically_on_write(true);
            std::string filename = "photo" + std::to_string(photo_num) + ".png";
            char* c = new char[filename.size()];
            for(unsigned int i = 0; i < filename.size(); i++){
                c[i] = filename[i];
            }
            stbi_write_png(c, width, height, nrChannels, data, stride);
            delete data;
            photo_num++;
            std::cout << theta * 100 / (2 * PI) << "%" << std::endl;

            theta += incrament;
        }

        std::cout << "done rendering" << std::endl;
    }

    else{
        GLFWwindow* window;
        if(!glfwInit()){
            std::cout << "Couldn't init GLFWW\n";
            return 1;
        }
        window = glfwCreateWindow(width, height, "raytracer", NULL, NULL);
        if(!window){
            std::cout << "Could not open window" << std::endl;
            return 1;
        }
    


        //make the scene


        // glm::vec3 top = glm::vec3(0,2,4);
        // glm::vec3 bot1 = glm::vec3(0,1,3);
        // glm::vec3 bot2 = glm::vec3(1,1,5);
        // glm::vec3 bot3 = glm::vec3(-1,1,5);

        Surface *list[1];   
        
            
        list[0] = new Sphere(glm::vec3(0,0,3), 0.5, glm::vec3(0.3,0.3,0.3), 0.2, 0.4, 0.4, 0);

        Light *light_list[2];
        light_list[0] = new Point_Light(glm::vec3(1,1,1),glm::vec3(5,5,-10));
        light_list[1] = new Ambient_light(glm::vec3(1,1,1));

        Multiple_Surfaces *scene = new Multiple_Surfaces(list,1, light_list, 2);


    
        //DO STUFF WITH PIXELS HERE
            unsigned char* data = new unsigned char[width*height*3];
            for(int y = 0; y < height; ++y){
                for(int x  = 0; x < width; ++x){
                    float u = float(x) / float(width);
                    float v = float(y) / float(height);
                    
                    Ray r = Ray(lower_left_corner + u * horizontal + v* vertical, look_at_vector); //ortho camera
                    //Ray r = Ray(origin, look_at_vector + u * horizontal + v* vertical); // perspective

                    glm::vec3 col = color(r, scene, 5);
                    int red = int(255 * col.x);
                    int g = int(255 * col.y);
                    int b = int(255 * col.z);

                    if(red > 255){
                        red = 255;
                    }

                    if(g > 255){
                        g = 255;
                    }

                    if(b > 255){
                        b = 255;
                    }
                    data[y * height * 3 + x * 3    ] = red; // r
                    data[y * height * 3 + x * 3 + 1] = g; // g 
                    data[y * height * 3 + x * 3 + 2] = b; // b
                }
            }
        

        //VERY IMPORTANT THIS IS BEFORE U MAKE THE TEXTURE
        glfwMakeContextCurrent(window);


        GLuint tex_handle;
        glGenTextures(1, &tex_handle);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        


        while(!glfwWindowShouldClose(window)){

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //SET UP ORPHOGRAPHIC PROJECTION
            int window_width, window_height;
            glfwGetFramebufferSize(window, &window_width, &window_height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, window_width, 0, window_height, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            //render here

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, tex_handle);
            glBegin(GL_QUADS); 
                glTexCoord2d(0,0); glVertex2i(0,0);
                glTexCoord2d(1,0); glVertex2i(width,0);
                glTexCoord2d(1,1); glVertex2i(width,height);
                glTexCoord2d(0,1); glVertex2i(0,height);
            glEnd();
            glDisable(GL_TEXTURE_2D);

                
            glfwSwapBuffers(window);
            glfwWaitEvents();
        }
    }
 
    
    return 0;

}