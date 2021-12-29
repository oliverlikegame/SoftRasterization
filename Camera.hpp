#pragma once

#include "mathutil.hpp"

class Camera
{
private:
    /* data */
public:

    Vector3f pos;
    Vector3f upDir;
    Vector3f lookAtDir;
    Matrix4f viewMat4;

    Camera(/* args */){
        pos = 0 ; 
        upDir = Vector3f( 0 , 1.0f , 0 ) ; 
        lookAtDir = Vector3f( 0 , 0 , -1.0f );
        viewMat4 = getViewMat4( pos , lookAtDir , upDir );
    }
    void setPos( const Vector3f &_pos ){ pos = _pos ;upDateViewMat4() ;}
    void setUpdir( const Vector3f &_upDir ){ upDir = _upDir ;upDateViewMat4() ;}
    void setLookAtDir( const Vector3f &_lookAtDir ){ lookAtDir = _lookAtDir ;upDateViewMat4() ;}
    Matrix4f getView(){
        return viewMat4;
    }
    void upDateViewMat4(){viewMat4 = getViewMat4( pos , lookAtDir , upDir ) ;}
};

