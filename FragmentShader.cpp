#include "FragmentShader.hpp"

FragmentShader::FragmentShader(){
    texture = nullptr;
}

FragmentShader::FragmentShader(const Vector3f &_color,const Vector3f &_normal,const Vector2f &_tex_coords, Texture * _tex ){
    color = _color;
    normal = _normal;
    tex_coords = _tex_coords;
    texture = _tex;
}

void FragmentShader::init(const Vector3f &_color,const Vector3f &_normal,const Vector2f &_tex_coords, Texture * _tex ){
    color = _color;
    normal = _normal;
    tex_coords = _tex_coords;
    texture = _tex;
}

Vector3f FragmentShader::shade( FragmentShader::shaderType shadertype ){
    if( shadertype == FragmentShader::shaderType::Blinn_Feng ){
        Vector3f ka = Vector3f(0.005, 0.005, 0.005);
        Vector3f kd = this->color;
        //Vector3f kd = Vector3f(0.1,0.1,0.1);
        Vector3f ks = Vector3f(0.7937, 0.7937, 0.7937);

        auto l1 = light{{0, 0, 20}, {255, 255, 255}};
        auto l2 = light{{-0, 0, -20}, {255, 255, 255}};
        
        std::vector<light> lights = {l1, l2};
        Vector3f amb_light_intensity{10, 10, 10};

        float p = 150;

        Vector3f color = this->color;
        Vector3f point = this->view_pos;
        Vector3f normal = this->normal;
        Vector3f La{0,0,0},Ls{0,0,0},Ld{0,0,0};
        
        Vector3f result_color = {0, 0, 0};
        for (auto& light : lights)
        {
            // For each light source in the code, calculate what the *ambient*, *diffuse*, and *specular* 
            // compnents are. Then, accumulate that result on the *result_color* object.
            auto l2p = Length((light.position - point)) ;
            l2p *=l2p;
            auto deno = Dot( normal ,normalized(normalized(light.position - point)  ));
            Ld += kd*(light.intensity/l2p)*Max(0,Dot( normal,normalized(light.position-point) ));
            Ls += ks*(light.intensity/l2p)*pow( (deno < 0? 0 : deno) ,p);
            La += ka*(amb_light_intensity);
        }
        result_color = Ld + Ls + La;
        //return color ;
        return result_color  ;
    }else{
        return Vector3f(0);
    }
}

