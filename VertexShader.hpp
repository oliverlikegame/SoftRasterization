//
//create by AO LI 12/5/2021
//
#pragma once

#include "mathutil.hpp"
#include "Geometry.hpp"
#include "Texture.hpp"
#include "Global.hpp"


class VertexShader
{
private:
    /* data */
public:

    VertexShader( Vector3f point,Vector3f barycood, Vector4f v[3],Vector3f screenSpacePos[3] ,
    Vector3f normals[3],Vector2f tex_coords[3],Texture *tex ){
        p = point;
        
        auto Z = 1.0 / (barycood.x / v[0].w + barycood.y / v[1].w + barycood.z / v[2].w);
        depth = barycood.x * v[0].z / v[0].w + barycood.y * v[1].z / v[1].w + barycood.z * v[2].z / v[2].w;
        depth *= Z/3;

        normal_interplote = normals[0]*barycood.x + normals[1]*barycood.y + normals[2]*barycood.z;
        if(!(normal_interplote == 0) )
            normal_interplote= normalized(normal_interplote); 
        //color_interplote = (normal_interplote + 1.0) * 0.5 ;//normal [-1,1] to color[0,1]||[0,255]
        shadingPos_interplote = screenSpacePos[0]*barycood.x + screenSpacePos[1]*barycood.y + screenSpacePos[2]*barycood.z;        
        
        texCoord_interplote = tex_coords[0] * barycood.x + tex_coords[1] * barycood.y + tex_coords[2] * barycood.z;
        //std::cout<<"["<<texCoord_interplote.x*tex->width << " " << texCoord_interplote.x*tex->height <<"] ";
        color_interplote = (*tex)( texCoord_interplote );
        if(enableMIPMAP){
            
            /*
            float onestep= 0.5;
            int w = tex->width;
            int h = tex->height;
            if(enableMSAA){
                onestep = 1/MSAA;
            }
                
            auto c1 = barycentricCoord(Vector3f(point.x - onestep , point.y - onestep,1.0),v[0].toVec3f(),v[1].toVec3f(),v[2].toVec3f());
            auto c2 = barycentricCoord(Vector3f(point.x + onestep , point.y - onestep,1.0),v[0].toVec3f(),v[1].toVec3f(),v[2].toVec3f());
            auto c3 = barycentricCoord(Vector3f(point.x + onestep , point.y + onestep,1.0),v[0].toVec3f(),v[1].toVec3f(),v[2].toVec3f());
            auto t1 = tex_coords[0] * c1.x + tex_coords[1] * c1.y + tex_coords[2] * c1.z;
            auto t2 = tex_coords[0] * c2.x + tex_coords[1] * c2.y + tex_coords[2] * c2.z;
            auto t3 = tex_coords[0] * c3.x + tex_coords[1] * c3.y + tex_coords[2] * c3.z;
            //std::cout<<"["<<t1.x*w << " "<<t1.y*h<<"]["<<" "<<t2.x*w << " "<<t2.y*h<<"]["<<t3.x*w << " "<<t3.y*h<<"][";  
            float what = std::max(Distance( t1 , t2 )*w , Distance(t2,t3)*h);
            float mipmapL =  std::log2(std::max(what,1.0f));//mipmap use for big texture , if its small .its go wrong!
            //std::cout<<"["<<t1.x*w<<" "<<t1.y*h<<"] ";
            //std::cout<<"trouble!\n";
            //std::cout<<std::max(Distance( t1 , t2 )*w , Distance(t2,t3)*h)<<" \n";
            //if(std::max(Distance( t1 , t2 )*w , Distance(t2,t3)*h) < 1)
            //std::cout<<mipmapL<<" ";
            */
            float mipmapL =CaculateMipMapLeve(tex->width,tex->height,point,tex_coords,v);

            tex->getMipMapTexColor( mipmapL , texCoord_interplote );
            /*
            int w = tex->width;
            int h = tex->height;
            if(tex->getMipMapMaxLevel() == int(mipmapL))
                color_interplote = tex->mipmaps[int(mipmapL)][0];
            else{
                auto p1 = Vector2f(( texCoord_interplote.x  ) * w/std::pow( 2.0 , int(mipmapL) ),( texCoord_interplote.y )*h/std::pow( 2.0 , int(mipmapL) )); 
                auto p2 = Vector2f(( texCoord_interplote.x  ) * w/std::pow( 2.0 , int(mipmapL)+1 ),( texCoord_interplote.y )*h/std::pow( 2.0 , int(mipmapL)+1 )); 
                //std::cout<<p1<<" "<<p2<<" "; 
                auto a1 = tex->getBilinerInterpolationTex( p1.x , p1.y , int(mipmapL) );
                auto a2 = tex->getBilinerInterpolationTex( p2.x , p2.y , int(mipmapL)+1 );
                //std::cout<<a1<<" "<<a2<<" "; 
                color_interplote = Lerp(a1 , a2, mipmapL - int(mipmapL));
                //color_interplote = a2;
            }
            */
        }


        
    }

    Vector3f color_interplote,normal_interplote,shadingPos_interplote , p;
    Vector2f texCoord_interplote;
    float depth;
    
};

