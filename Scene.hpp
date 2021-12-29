//
//create by AO LI 11/18/2021
//
#pragma once

#include "mathutil.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include <vector>

class Scene
{
private:
    
public:
    Scene( int w , int h );
    int width;
    int height;
    float fovY;
    float zNear;
    float zFar;
    float aspect;
    int resolution ;
    float rotation_angle;
    Camera cam;
    std::vector<ms::Mesh> meshes;
    Matrix4f projection;
    Matrix4f view;
    Matrix4f model;
    Matrix4f viewPort;

    Matrix4f getProjection(){return projection ;}
    Matrix4f getView(){ return view; }
    Matrix4f getModel(){ return model ;}//round  0，1，0 axis rotation 0 degree
    Matrix4f getViewPort(){ return viewPort; }
    Matrix4f getMVP(){ return projection * viewPort * model; }
    void setProjection(Matrix4f pro){ projection = pro;  }//set projection matrix 
    void setView(Matrix4f _view){ view = _view; }//set view matrix 
    void setModel(Matrix4f _model){ model = _model;  }//set model matrix 
    void setViewPort(Matrix4f pro){ projection = pro; }

    void setCamera( const Camera &_cam );
    void setWidth( const int _w );
    void setHeight( const int _h );
    void setFov( const float _fovY );
    void setZNear( const float _znear ); 
    void setZFar( const float _zfar ); 
    void setAspect( const float _aspect );
    void updateMatrix();
    void addMesh( ms::Mesh &mesh );

    
};





