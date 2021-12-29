//
//create by AO LI 11/17/2021
//
#pragma once

#include "Geometry.hpp"
#include "mathutil.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

#include <vector>

namespace rst{

    enum class Buffers
    {
        Color = 1,
        Depth = 2,//maybe more
        ColorMSAA = 3
    };
    
    class Rasterizer
    {
    private:

        
        std::vector<Vector3f> bufferColor;
        std::vector<Vector3f> bufferColorMSAA;
        std::vector<float> bufferDepth;
        Matrix4f model;
        Matrix4f view;
        Matrix4f projection;
        Matrix4f viewPort;

        int width;
        int height;



    public:
        Rasterizer(int w , int h):width(w),height(h) {
            bufferColor.resize( w * h );
            if(enableMSAA){
                bufferDepth.resize( MSAA*w * MSAA*h );
                bufferColorMSAA.resize( MSAA*w * MSAA*h );
                
            }else{
                bufferDepth.resize( w * h );
            }
            
            std::fill(bufferDepth.begin(), bufferDepth.end(), std::numeric_limits<float>::infinity());
        }

        void setViewPortMatrix( const Matrix4f &E );
        void setModelMatrix( const Matrix4f &M );
        void setViewMatrix( const Matrix4f &V );
        void setProjectionMatrix( const Matrix4f &P );
        Matrix4f getMVPMatrix();//P*V*M
        Matrix4f getMVP_INVERSE();//M-1*V-1*P-1
        Matrix4f getMVPEMatrix();//E*P*V*M
        Matrix4f getMVPE_INVERSE();//M-1*V-1*P-1*E-1
        Matrix4f getMVMatrix();//V*M
        void drawImagePPM( const std::vector<Vector3f> &buffer );
        void drawLine( Vector3f begin , Vector3f end );
        void drawTrangle( const Triangle &trangle );

        void setPixtel(  Vector3f &point ,  Vector3f &color );
        void setBuffer( Buffers buf_type , int &index , Vector3f &value );
        void clearBuffer( Buffers buf_type );
        void useMSAA(const bool enable);
        void drawTrangles( const Triangles &triangles );
        void drawScene(  Scene &scene );
        void interploteBefore( Triangle &trangle );
        std::vector<Vector3f> getcolorbuffer(){return bufferColor;}
        void bufMsaa2buf(Scene &scene);

        void drawSceneWithPT(Scene &scene);
        Vector3f castRay(Ray &ray , Scene &scene);


    };


}

static bool isinTrangle( const Vector3f p , const Triangle &t ){
    return inTrangle( p , t.vertexes[0] , t.vertexes[1] , t.vertexes[2] );
}

static bool isinTrangleUseCross( const Vector3f p , const Triangle &t ){
    return inTrangleUseCross( p , t.vertexes[0] , t.vertexes[1] , t.vertexes[2] );
}