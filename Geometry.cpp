//
//create by AO LI 11/16/2021
//

#include"Geometry.hpp"


Triangle::Triangle(){
    vertexes[0] = 0;
    vertexes[1] = 0;
    vertexes[2] = 0;

    colors[0] = 0;
    colors[1] = 0;
    colors[2] = 0;

    tex_coords[0] = 0;
    tex_coords[1] = 0;
    tex_coords[2] = 0;

    normalTriangle = 0;
}
void Triangle::setVertex(int ind, Vector3f ver) { vertexes[ind] = ver; }

void Triangle::setVertex( Vector3f &a , Vector3f &b , Vector3f &c ){ vertexes[0] = a , vertexes[1] = b , vertexes[2] = c;  }

void Triangle::setVertexNormal(int ind, Vector3f n) { normals[ind] = n; }

void Triangle::setNormal( Vector3f N){ normalTriangle = N; }

void Triangle::setColor(int ind, float r, float g, float b)
{
    if ((r < 0.0) || (r > 255.) || (g < 0.0) || (g > 255.) || (b < 0.0) ||
        (b > 255.)) {
        throw std::runtime_error("Invalid color values");
    }

    colors[ind] = Vector3f((float)r / 255., (float)g / 255., (float)b / 255.);
    return;
}

void Triangle::setColor(int ind, Vector3f color)
{
    float r = color.x , g = color.y , b = color.z;
    if ((r < 0.0) || (r > 255.) || (g < 0.0) || (g > 255.) || (b < 0.0) ||
        (b > 255.)) {
        throw std::runtime_error("Invalid color values");
    }

    colors[ind] = Vector3f((float)r / 255., (float)g / 255., (float)b / 255.);
    return;
}
void Triangle::setColor( Vector3f color ){
    float r = color.x , g = color.y , b = color.z;
    if ((r < 0.0) || (r > 255.) || (g < 0.0) || (g > 255.) || (b < 0.0) ||
        (b > 255.)) {
        throw std::runtime_error("Invalid color values");
    }

    colors[0] = Vector3f((float)r / 255., (float)g / 255., (float)b / 255.);
    colors[1] = colors[0];
    colors[2] = colors[1];
    return;
}


void Triangle::setTexCoord(int ind, float s, float t)
{
    tex_coords[ind] = Vector2f(s, t);
}

void Triangle::setTexCoord(int ind, Vector2f coord)
{
    tex_coords[ind] = coord;
}

void Triangles::addTriangle( const Triangle &t ){ tset.push_back(t); }


Box::Box(){
    
    Triangle u1 ,u2 ,
    d1 , d2 ,
    l1 , l2 ,
    r1 , r2 ,
    f1 , f2 ,
    b1 , b2;
    
    Vector3f a = Vector3f( -5,-5,10 );
    Vector3f b = Vector3f( -5,-5,20 );
    Vector3f c = Vector3f( 5,-5,20 );
    Vector3f d = Vector3f( 5,-5,10 );
    Vector3f e = Vector3f( -5,5,10 );
    Vector3f f = Vector3f( -5,5,20 );
    Vector3f g = Vector3f( 5,5,20 );
    Vector3f h = Vector3f( 5,5,10 );

    u1.setVertex( e , f , g );
    u2.setVertex( g , h , e );
    d1.setVertex( a , b , c );
    d2.setVertex( c , d , a );
    l1.setVertex( a , b , f );
    l2.setVertex( f , e , a );
    r1.setVertex( d , c , g );
    r2.setVertex( g , h , d );
    f1.setVertex( a , d , h );
    f2.setVertex( h , e , a );
    b1.setVertex( b , c , g );
    b2.setVertex( g , f , b );

    u1.setColor( 0 , Vector3f( 10 , 200 ,100 ) );
    u2.setColor( 2 , Vector3f( 10 , 200 ,100 ) );
    l2.setColor( 1 , Vector3f( 10 , 200 ,100 ) );
    f1.setColor( 1 , Vector3f( 10 , 200 ,100 ) );

    u1.setColor( 1 , Vector3f( 100 , 200 ,100 ) );
    l1.setColor( 2 , Vector3f( 100 , 200 ,100 ) );
    l2.setColor( 1 , Vector3f( 100 , 200 ,100 ) );
    b2.setColor( 1 , Vector3f( 100 , 200 ,100 ) );

    u2.setColor( 0 , Vector3f( 10 , 20 ,100 ) );
    u1.setColor( 2 , Vector3f( 10 , 20 ,100 ) );
    r1.setColor( 2 , Vector3f( 10 , 20 ,100 ) );
    r2.setColor( 0 , Vector3f( 10 , 20 ,100 ) );
    
    u2.setColor( 1 , Vector3f( 100 , 100 ,0 ) );
    d1.setColor( 0 , Vector3f( 255 , 10 ,255 ) );
    d1.setColor( 1 , Vector3f( 10 , 200 ,155 ) );
    d2.setColor( 0 , Vector3f( 10 , 255 ,100 ) );
    d2.setColor( 1 , Vector3f( 255 , 255 ,100 ) );

    u1.setColor( RED ); 
    u2.setColor( RED ); 
    d1.setColor( RED ); 
    d2.setColor( RED );
    l1.setColor( BLUE ); 
    l2.setColor( BLUE );
    r1.setColor( BLUE ); 
    r2.setColor( BLUE );
    f1.setColor( Vector3f( 255 ,255 ,0 ) ); 
    f2.setColor( Vector3f( 255 ,255 ,0 ) );
    b1.setColor( GREEN ); 
    b2.setColor( GREEN );

    tset.push_back(u1);
    tset.push_back(u2);
    tset.push_back(d1);
    tset.push_back(d2);
    tset.push_back(l1);
    tset.push_back(l2);
    tset.push_back(r1);
    tset.push_back(r2);
    //tset.push_back(f1);
    //tset.push_back(f2);
    tset.push_back(b1);
    tset.push_back(b2);
}