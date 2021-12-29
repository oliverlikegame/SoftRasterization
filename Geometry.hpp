//
//create by AO LI 11/16/2021
//
#pragma once

#include <cmath>
#include "common.hpp"
#include "mathutil.hpp"
#include <vector>
//SHOULD DEFINE IN MATERIAL CLASS
#define RED Vector3f( 255 ,0 ,0 )
#define GREEN Vector3f( 0 ,255 ,0 )
#define BLUE Vector3f( 0 ,0 ,255 )

class Triangle
{
private:
    /* data */
public:
    
    Vector3f vertexes[3];/*the original coordinates of the triangle, v0, v1, v2 in
    counter clockwise order*/
    Vector3f normals[3]; // normal for each vertex
    Vector3f colors[3]; // color for each vertex
    Vector2f tex_coords[3]; //texture coordinate for each vertex
    Vector3f normalTriangle;
    Vector3f a()const{ return vertexes[0] ;}
    Vector3f b()const{ return vertexes[1] ;}
    Vector3f c()const{ return vertexes[2] ;}

    Triangle();

    void setVertex(int ind, Vector3f ver); // set i-th vertex coordinate
    void setVertex( Vector3f &a , Vector3f &b , Vector3f &c );
    void setVertexNormal(int ind, Vector3f n);   // set i-th vertex normals vector
    void setNormal(Vector3f n);
    void setColor(int ind, float r, float g, float b); // set i-th vertex color
    void setColor(int ind, Vector3f color);
    void setColor( Vector3f color );
    void setTexCoord(int ind, float u , float v); // ser i-th texture coordinate
    void setTexCoord(int ind, Vector2f coord);

};

inline std::ostream &operator<<(std::ostream &os, const Triangle &t) {
    os << "[ " << " vertex position : " << t.vertexes[0] << ", " << t.vertexes[1] << ", " << t.vertexes[2] <<
     "colors : " <<t.colors[0] << ", " << t.colors[1] << ", " << t.colors[2]<<
     " normals : " << t.normals[0] << ", " << t.normals[1] << ", " << t.normals[2]
    << " ]";
    return os;
}

class Triangles
{
private:
    /* data */
public:

    std::vector<Triangle> tset;

    Triangles(){ tset.resize(0) ;}
    
    void addTriangle( const Triangle &t );


};

class Box : public Triangles
{
private:
    /* data */
public:
    Box(/* args */);

};






