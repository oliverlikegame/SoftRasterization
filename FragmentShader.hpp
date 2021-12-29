//
//create by AO LI 12/4/2021
//
#pragma once


#include "mathutil.hpp"
#include "Texture.hpp"

struct light
{
    Vector3f position;
    Vector3f intensity;
};


class FragmentShader
{
private:
    /* data */
public:
    enum shaderType { Blinn_Feng };
    FragmentShader();
    FragmentShader(const Vector3f &color,const Vector3f &normal,const Vector2f &tex_coords, Texture * tex );

    void init(const Vector3f &color,const Vector3f &normal,const Vector2f &tex_coords, Texture * tex );
    Vector3f shade(shaderType shadertype);

    Vector3f view_pos;//view space shading point's postion
    Vector3f color;
    Vector3f normal;
    Vector2f tex_coords;
    Texture* texture;
    
};

