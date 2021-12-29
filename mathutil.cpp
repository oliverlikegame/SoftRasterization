//
//create by AO LI 11/16/2021
//
#include "mathutil.hpp"


Matrix4f Inverse(const Matrix4f &mat) {
    float inv[4][4];
    inv[0][0] = +mat.m[1][1] * mat.m[2][2] * mat.m[3][3] +
                mat.m[1][2] * mat.m[2][3] * mat.m[3][1] +
                mat.m[1][3] * mat.m[2][1] * mat.m[3][2] -
                mat.m[1][1] * mat.m[2][3] * mat.m[3][2] -
                mat.m[1][2] * mat.m[2][1] * mat.m[3][3] -
                mat.m[1][3] * mat.m[2][2] * mat.m[3][1];
    inv[1][0] = -mat.m[1][0] * mat.m[2][2] * mat.m[3][3] -
                mat.m[1][2] * mat.m[2][3] * mat.m[3][0] -
                mat.m[1][3] * mat.m[2][0] * mat.m[3][2] +
                mat.m[1][0] * mat.m[2][3] * mat.m[3][2] +
                mat.m[1][2] * mat.m[2][0] * mat.m[3][3] +
                mat.m[1][3] * mat.m[2][2] * mat.m[3][0];
    inv[2][0] = +mat.m[1][0] * mat.m[2][1] * mat.m[3][3] +
                mat.m[1][1] * mat.m[2][3] * mat.m[3][0] +
                mat.m[1][3] * mat.m[2][0] * mat.m[3][1] -
                mat.m[1][0] * mat.m[2][3] * mat.m[3][1] -
                mat.m[1][1] * mat.m[2][0] * mat.m[3][3] -
                mat.m[1][3] * mat.m[2][1] * mat.m[3][0];
    inv[3][0] = -mat.m[1][0] * mat.m[2][1] * mat.m[3][2] -
                mat.m[1][1] * mat.m[2][2] * mat.m[3][0] -
                mat.m[1][2] * mat.m[2][0] * mat.m[3][1] +
                mat.m[1][0] * mat.m[2][2] * mat.m[3][1] +
                mat.m[1][1] * mat.m[2][0] * mat.m[3][2] +
                mat.m[1][2] * mat.m[2][1] * mat.m[3][0];
    inv[0][1] = -mat.m[0][1] * mat.m[2][2] * mat.m[3][3] -
                mat.m[0][2] * mat.m[2][3] * mat.m[3][1] -
                mat.m[0][3] * mat.m[2][1] * mat.m[3][2] +
                mat.m[0][1] * mat.m[2][3] * mat.m[3][2] +
                mat.m[0][2] * mat.m[2][1] * mat.m[3][3] +
                mat.m[0][3] * mat.m[2][2] * mat.m[3][1];
    inv[1][1] = +mat.m[0][0] * mat.m[2][2] * mat.m[3][3] +
                mat.m[0][2] * mat.m[2][3] * mat.m[3][0] +
                mat.m[0][3] * mat.m[2][0] * mat.m[3][2] -
                mat.m[0][0] * mat.m[2][3] * mat.m[3][2] -
                mat.m[0][2] * mat.m[2][0] * mat.m[3][3] -
                mat.m[0][3] * mat.m[2][2] * mat.m[3][0];
    inv[2][1] = -mat.m[0][0] * mat.m[2][1] * mat.m[3][3] -
                mat.m[0][1] * mat.m[2][3] * mat.m[3][0] -
                mat.m[0][3] * mat.m[2][0] * mat.m[3][1] +
                mat.m[0][0] * mat.m[2][3] * mat.m[3][1] +
                mat.m[0][1] * mat.m[2][0] * mat.m[3][3] +
                mat.m[0][3] * mat.m[2][1] * mat.m[3][0];
    inv[3][1] = +mat.m[0][0] * mat.m[2][1] * mat.m[3][2] +
                mat.m[0][1] * mat.m[2][2] * mat.m[3][0] +
                mat.m[0][2] * mat.m[2][0] * mat.m[3][1] -
                mat.m[0][0] * mat.m[2][2] * mat.m[3][1] -
                mat.m[0][1] * mat.m[2][0] * mat.m[3][2] -
                mat.m[0][2] * mat.m[2][1] * mat.m[3][0];
    inv[0][2] = +mat.m[0][1] * mat.m[1][2] * mat.m[3][3] +
                mat.m[0][2] * mat.m[1][3] * mat.m[3][1] +
                mat.m[0][3] * mat.m[1][1] * mat.m[3][2] -
                mat.m[0][1] * mat.m[1][3] * mat.m[3][2] -
                mat.m[0][2] * mat.m[1][1] * mat.m[3][3] -
                mat.m[0][3] * mat.m[1][2] * mat.m[3][1];
    inv[1][2] = -mat.m[0][0] * mat.m[1][2] * mat.m[3][3] -
                mat.m[0][2] * mat.m[1][3] * mat.m[3][0] -
                mat.m[0][3] * mat.m[1][0] * mat.m[3][2] +
                mat.m[0][0] * mat.m[1][3] * mat.m[3][2] +
                mat.m[0][2] * mat.m[1][0] * mat.m[3][3] +
                mat.m[0][3] * mat.m[1][2] * mat.m[3][0];
    inv[2][2] = +mat.m[0][0] * mat.m[1][1] * mat.m[3][3] +
                mat.m[0][1] * mat.m[1][3] * mat.m[3][0] +
                mat.m[0][3] * mat.m[1][0] * mat.m[3][1] -
                mat.m[0][0] * mat.m[1][3] * mat.m[3][1] -
                mat.m[0][1] * mat.m[1][0] * mat.m[3][3] -
                mat.m[0][3] * mat.m[1][1] * mat.m[3][0];
    inv[3][2] = -mat.m[0][0] * mat.m[1][1] * mat.m[3][2] -
                mat.m[0][1] * mat.m[1][2] * mat.m[3][0] -
                mat.m[0][2] * mat.m[1][0] * mat.m[3][1] +
                mat.m[0][0] * mat.m[1][2] * mat.m[3][1] +
                mat.m[0][1] * mat.m[1][0] * mat.m[3][2] +
                mat.m[0][2] * mat.m[1][1] * mat.m[3][0];
    inv[0][3] = -mat.m[0][1] * mat.m[1][2] * mat.m[2][3] -
                mat.m[0][2] * mat.m[1][3] * mat.m[2][1] -
                mat.m[0][3] * mat.m[1][1] * mat.m[2][2] +
                mat.m[0][1] * mat.m[1][3] * mat.m[2][2] +
                mat.m[0][2] * mat.m[1][1] * mat.m[2][3] +
                mat.m[0][3] * mat.m[1][2] * mat.m[2][1];
    inv[1][3] = +mat.m[0][0] * mat.m[1][2] * mat.m[2][3] +
                mat.m[0][2] * mat.m[1][3] * mat.m[2][0] +
                mat.m[0][3] * mat.m[1][0] * mat.m[2][2] -
                mat.m[0][0] * mat.m[1][3] * mat.m[2][2] -
                mat.m[0][2] * mat.m[1][0] * mat.m[2][3] -
                mat.m[0][3] * mat.m[1][2] * mat.m[2][0];
    inv[2][3] = -mat.m[0][0] * mat.m[1][1] * mat.m[2][3] -
                mat.m[0][1] * mat.m[1][3] * mat.m[2][0] -
                mat.m[0][3] * mat.m[1][0] * mat.m[2][1] +
                mat.m[0][0] * mat.m[1][3] * mat.m[2][1] +
                mat.m[0][1] * mat.m[1][0] * mat.m[2][3] +
                mat.m[0][3] * mat.m[1][1] * mat.m[2][0];
    inv[3][3] = +mat.m[0][0] * mat.m[1][1] * mat.m[2][2] +
                mat.m[0][1] * mat.m[1][2] * mat.m[2][0] +
                mat.m[0][2] * mat.m[1][0] * mat.m[2][1] -
                mat.m[0][0] * mat.m[1][2] * mat.m[2][1] -
                mat.m[0][1] * mat.m[1][0] * mat.m[2][2] -
                mat.m[0][2] * mat.m[1][1] * mat.m[2][0];
    float det = mat.m[0][0] * inv[0][0] + mat.m[0][1] * inv[1][0] +
                mat.m[0][2] * inv[2][0] + mat.m[0][3] * inv[3][0];
    return Matrix4f(inv) / det;
}

Matrix4f Transpose(const Matrix4f &mat) {
    float m[4][4];
    for (uint32_t i = 0; i < 4; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            m[i][j] = mat.m[j][i];
        }
    }
    return Matrix4f(m);
}

Vector4f Matrix4f::operator()(const Vector4f &p) const {
    Vector4f ret;
    float x = m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3] * p.w;
    float y = m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3] * p.w;
    float z = m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3] * p.w;
    float w = m[3][0] * p.x + m[3][1] * p.y + m[3][2] * p.z + m[3][3] * p.w;
    //std::cout<<x<<" "<<y << " " << z << " w =  " << w <<"\n"; 
    ret = Vector4f(x, y, z , w ) ;
    //if( w != 0 )
    //    ret = Vector4f(x/w, y/w, z/w , 1.0 ) ;
    return ret;
}

void Matrix4f::set( const Matrix4f mat4 ){
    m[0][0] = mat4.m[0][0]; m[0][1] = mat4.m[0][1]; m[0][2] = mat4.m[0][2]; m[0][3] = mat4.m[0][3];
    m[1][0] = mat4.m[1][0]; m[1][1] = mat4.m[1][1]; m[1][2] = mat4.m[1][2]; m[1][3] = mat4.m[1][3];
    m[2][0] = mat4.m[2][0]; m[2][1] = mat4.m[2][1]; m[2][2] = mat4.m[2][2]; m[2][3] = mat4.m[2][3];
    m[3][0] = mat4.m[3][0]; m[3][1] = mat4.m[3][1]; m[3][2] = mat4.m[3][2]; m[3][3] = mat4.m[3][3];
}

void Matrix4f::set(float m00, float m01, float m02, float m03,
float m10, float m11, float m12, float m13,
float m20, float m21, float m22, float m23,
float m30, float m31, float m32, float m33 ){
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

Matrix4f getProMat4( float aspect , float fovY , float zNear , float zFar ){

    Matrix4f projection , orthoScale , orthoTrans;
    auto t = fabs(zNear)*tan(acos(-1)*(fovY/360));//(fovY/2)/180
    
    auto b = -t; 
    auto r = aspect*t;
    auto l = -r;
    
    orthoScale.set(projection);
    orthoScale.set( 2/(r-l),0,0,0,
    0,-1.0f*2/(t-b),0,0,// y toward to down side ,so i muiltiple -1 to let y toward to up
    0,0,-2/(zNear-zFar),0,
    0,0,0,1);

    orthoTrans.set(1,0,0,-(r+l)/2.0,
    0,1,0,-(t+b)/2.0,
    0,0,1,-(zNear+zFar)/2.0,
    0,0,0,1);

    projection.set( zNear,0,0,0,
    0,zNear,0,0,
    0,0,zNear+zFar,-zNear*zFar,
    0,0,1,0 );

    Matrix4f a;
    //a.set(2*zNear/(r-l) , 0 , (l+r) / (l - r), 0,
    //0 , 2*zNear /(t-b) , (b+t) / (b-t) , 0,
    //0 , 0 , (zNear + zFar) / (zFar - zNear) , 2*zNear * zFar / ( zNear - zFar ),
    //0,0,1,0
    
    //return a;
    return orthoScale*orthoTrans*projection;
}

Matrix4f getModelMat4(Vector3f axis ,float rotation_angle , float _translate , float _scale){
    Matrix4f model ;
    Matrix4f model2 ;
    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    float rosin = std::sin(acos(-1)*rotation_angle/180.0);
    float rocos = std::cos(acos(-1)*rotation_angle/180.0);
    model.set(rocos,-rosin,0,0,
    rosin,rocos,0,0,
    0,0,1,0,
    0,0,0,1);
    float cosangle = cos(acos(-1)*rotation_angle/180.0),sinangle = sin(acos(-1)*rotation_angle/180.0);
    Matrix4f N;
    N.set( 0,-axis.z,axis.y,0 ,
    axis.z,0,-axis.x,0 ,
    -axis.y,axis.x,0 , 0 ,
    0 , 0 , 0 , 0  
    );
    Matrix4f axis_axistranspose;
    axis_axistranspose.set(
        axis.x * axis.x , axis.x * axis.y , axis.x * axis.z , 0,
        axis.y * axis.x , axis.y * axis.y , axis.y * axis.z , 0 ,
        axis.z * axis.x , axis.z * axis.y , axis.z * axis.z , 0 , 
        0 , 0 , 0 , 0
    );
    model2 = model2 * cosangle + axis_axistranspose * (1-cosangle) + N * sinangle;
    Matrix4f Rotation;
    Rotation.set( model2(0,0),model2(0,1),model2(0,2),0,model2(1,0),model2(1,1),model2(1,2),0,model2(2,0),model2(2,1),model2(2,2),0,0,0,0,1 );
    
    Matrix4f scale;
    scale.set( _scale, 0, 0, 0,
              0, _scale, 0, 0,
              0, 0, _scale, 0,
              0, 0, 0, 1);

    Matrix4f translate;
    translate.set( 1, 0, 0, _translate,
            0, 1, 0, _translate,
            0, 0, 1, _translate,
            0, 0, 0, 1);
    
    return translate * Rotation * scale;
    //return model; //rotation axis :z
}

Matrix4f getModelMat4(Vector3f axis ,float rotation_angle , Vector3f _translate , Vector3f _scale){
    Matrix4f model ;
    Matrix4f model2 ;
    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    float rosin = std::sin(acos(-1)*rotation_angle/180.0);
    float rocos = std::cos(acos(-1)*rotation_angle/180.0);
    model.set(rocos,-rosin,0,0,
    rosin,rocos,0,0,
    0,0,1,0,
    0,0,0,1);
    float cosangle = cos(acos(-1)*rotation_angle/180.0),sinangle = sin(acos(-1)*rotation_angle/180.0);
    Matrix4f N;
    N.set( 0,-axis.z,axis.y,0 ,
    axis.z,0,-axis.x,0 ,
    -axis.y,axis.x,0 , 0 ,
    0 , 0 , 0 , 0  
    );
    Matrix4f axis_axistranspose;
    axis_axistranspose.set(
        axis.x * axis.x , axis.x * axis.y , axis.x * axis.z , 0,
        axis.y * axis.x , axis.y * axis.y , axis.y * axis.z , 0 ,
        axis.z * axis.x , axis.z * axis.y , axis.z * axis.z , 0 , 
        0 , 0 , 0 , 0
    );
    model2 = model2 * cosangle + axis_axistranspose * (1-cosangle) + N * sinangle;
    Matrix4f Rotation;
    Rotation.set( model2(0,0),model2(0,1),model2(0,2),0,model2(1,0),model2(1,1),model2(1,2),0,model2(2,0),model2(2,1),model2(2,2),0,0,0,0,1 );
    
    Matrix4f scale;
    scale.set( _scale.x, 0, 0, 0,
              0, _scale.y, 0, 0,
              0, 0, _scale.z, 0,
              0, 0, 0, 1);

    Matrix4f translate;
    translate.set( 1, 0, 0, _translate.x,
            0, 1, 0, _translate.y,
            0, 0, 1, _translate.z,
            0, 0, 0, 1);
    
    return translate * Rotation * scale;
    //return model; //rotation axis :z
}


Matrix4f getViewMat4(Vector3f pos ,Vector3f lookAtDir , Vector3f upDir){
        Vector3f thirdAxis = Cross( lookAtDir , upDir );
        Matrix4f rotation , trans;
        rotation.set( thirdAxis.x , thirdAxis.y , thirdAxis.z , 0,
        upDir.x , upDir.y , upDir.z , 0 ,
        -lookAtDir.x , -lookAtDir.y , -lookAtDir.z , 0, 
        0,0,0,1.0f);
        trans.set(1.0f , 0 , 0 , -pos.x ,
        0 , 1.0f , 0 , -pos.y ,
        0 , 0 , 1.0f , -pos.z ,
        0 , 0 , 0 , 1.0f
        );
        return rotation * trans;
}



