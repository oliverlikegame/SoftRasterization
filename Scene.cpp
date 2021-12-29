//
//create by AO LI 11/18/2021
//
#include "Scene.hpp"

Scene::Scene( int w , int h ):width(w),height(h){
    
    
    zFar = 50;
    zNear = 0.1;
    fovY = 90.0;//dgree
    aspect = (1.0f * w) / h;
    resolution = w * h;
    projection = getProMat4(aspect , fovY , zNear ,zFar );
    view = cam.getView();
    model = getModelMat4( Vector3f( 0,1,0 ), 0 , Vector3f( 0,0,0) , Vector3f( 1 ) ); 

    viewPort.set( w/2.0f , 0 , 0 , w/2.0f,
     0 , h/2.0f , 0 , h/2.0f ,
     0 , 0 , 1 , 0 ,
     0 , 0 , 0 , 1);
    cam = Camera();
    

}

void Scene::setCamera( const Camera &_cam ){ cam = _cam ;}

void Scene::setWidth( const int _w ){ width = _w ;updateMatrix();}//viewport matirx change
void Scene::setHeight( const int _h ){ height = _h ;updateMatrix();}//viewport matirx change
void Scene::setFov( const float _fovY ){ fovY = _fovY; updateMatrix();}//projection matirx change
void Scene::setZNear( const float _znear ){ zNear = _znear ; updateMatrix();}//projection matirx change
void Scene::setZFar( const float _zfar ){ zFar = _zfar ; updateMatrix();} //projection matirx change
void Scene::setAspect( const float _aspect ){ aspect = _aspect; updateMatrix();}//projection matirx change

void Scene::updateMatrix(){ 
    projection = getProMat4(aspect , fovY , zNear ,zFar );
    viewPort.set( width/2.0f , 0 , 0 , width/2.0f,
     0 , height/2.0f , 0 , height/2.0f ,
     0 , 0 , 1 , 0 ,
     0 , 0 , 0 , 1);
}

void Scene::addMesh( ms::Mesh &mesh ){
    meshes.push_back( mesh );
}






