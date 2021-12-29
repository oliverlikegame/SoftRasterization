//
//create by AO LI 11/21/2021
//
#pragma once

#include "Geometry.hpp"
#include "Texture.hpp"


namespace ms{
    
    class Mesh
    {
    private:
        /* data */
    public:
        Mesh(/* args */){};
        
        Texture baseColor ;
        
        std::vector<Triangle> tset;
        
        void setTriangles( const Triangles t ){ tset = t.tset; }
        
        void setTexture( Texture &texture ){ baseColor = texture ;};

    };




}


