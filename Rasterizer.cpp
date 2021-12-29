//
//create by AO LI 11/17/2021
//
#include "Rasterizer.hpp"
#include "mathutil.hpp"
#include "cstring"
#include <stdexcept>
#include <limits>
#include "FragmentShader.hpp"
#include "VertexShader.hpp"
#include "Global.hpp"
#include "Ray.hpp"


void rst::Rasterizer::setViewPortMatrix( const Matrix4f &E ){
    viewPort = E;
}

void rst::Rasterizer::setModelMatrix( const Matrix4f &M ){
    model = M;
}

void rst::Rasterizer::setViewMatrix( const Matrix4f &V ){
    view = V;
}

void rst::Rasterizer::setProjectionMatrix( const Matrix4f &P ){
    projection = P;
}

Matrix4f rst::Rasterizer::getMVPMatrix(){ return projection * view * model ; }//P*V*M

Matrix4f rst::Rasterizer::getMVPEMatrix(){ return viewPort * getMVPMatrix() ; }//E*P*V*M

Matrix4f rst::Rasterizer::getMVP_INVERSE(){ return Inverse(projection * view * model) ; }//M-1*V-1*P-1

Matrix4f rst::Rasterizer::getMVPE_INVERSE(){ return  getMVP_INVERSE()*Inverse( viewPort )  ; }//M-1*V-1*P-1*E-1

Matrix4f rst::Rasterizer::getMVMatrix(){ return view * model ; }

void rst::Rasterizer::drawImagePPM( const std::vector<Vector3f> &buffer ){
     // save framebuffer to file
    FILE* fp = fopen("./binary.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", width, height);
    Vector3f buf = Vector3f(0);
    for (auto i = 0; i < height * width ; ++i) {
        buf = Clamp( buffer[i], 0, 1 );
        static unsigned char color[3];
        color[0] = (unsigned char)(255 * std::pow(buf.x, 0.6f));
        color[1] = (unsigned char)(255 * std::pow(buf.y, 0.6f));
        color[2] = (unsigned char)(255 * std::pow(buf.z, 0.6f));
        fwrite(color, 1, 3, fp);
    }
    fclose(fp);    
}

void rst::Rasterizer::drawLine(  Vector3f begin ,  Vector3f end ){
    auto x1 = begin.x;
    auto y1 = begin.y;
    auto x2 = end.x;
    auto y2 = end.y;

    Vector3f line_color = {255, 255, 255};

    int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;

    dx=x2-x1;
    dy=y2-y1;
    dx1=fabs(dx);
    dy1=fabs(dy);
    px=2*dy1-dx1;
    py=2*dx1-dy1;

    if(dy1<=dx1)
    {
        if(dx>=0)
        {
            x=x1;
            y=y1;
            xe=x2;
        }
        else
        {
            x=x2;
            y=y2;
            xe=x1;
        }
        Vector3f point = Vector3f(x, y, 1.0f);
        setPixtel(point,line_color);
        for(i=0;x<xe;i++)
        {
            x=x+1;
            if(px<0)
            {
                px=px+2*dy1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    y=y+1;
                }
                else
                {
                    y=y-1;
                }
                px=px+2*(dy1-dx1);
            }
//            delay(0);
            Vector3f point = Vector3f(x, y, 1.0f);
            setPixtel(point,line_color);
        }
    }
    else
    {
        if(dy>=0)
        {
            x=x1;
            y=y1;
            ye=y2;
        }
        else
        {
            x=x2;
            y=y2;
            ye=y1;
        }
        Vector3f point = Vector3f(x, y, 1.0f);
        setPixtel(point,line_color);
        for(i=0;y<ye;i++)
        {
            y=y+1;
            if(py<=0)
            {
                py=py+2*dx1;
            }
            else
            {
                if((dx<0 && dy<0) || (dx>0 && dy>0))
                {
                    x=x+1;
                }
                else
                {
                    x=x-1;
                }
                py=py+2*(dx1-dy1);
            }
//            delay(0);
            Vector3f point = Vector3f(x, y, 1.0f);
            setPixtel(point,line_color);
        }
    }
    drawImagePPM( bufferColor );
}

//abort
void rst::Rasterizer::drawTrangle( const Triangle &trangle ){
    //drawLine(trangle.b() , trangle.c() );

    Vector3f v0 = trangle.a() , v1 = trangle.b(), v2 = trangle.c();
    Vector3f pmin , pmax;
    setMaxMin( v0 , v1 ,v2 , pmin , pmax );
    //if its after mvp clamp ,remove what is not in screen 
    pmin.x = pmin.x<0 ? 0.0f :( pmin.x< width ? pmin.x : width );
    pmin.y = pmin.y<0 ? 0.0f :( pmin.y< width ? pmin.y : height );
    pmax.x = pmax.x<0 ? 0.0f :( pmax.x< width ? pmax.x : width );
    pmax.y = pmax.y<0 ? 0.0f :( pmax.y< width ? pmax.y : height );

    Vector3f p;
    Vector3f color_interplote = Vector3f( 255 , 255 , 255);
    Vector3f normal_interplote = Vector3f( 255 , 255 , 255);
    if(!enableMSAA){
        for (int i = pmin.x; i < pmax.x; i++)
        {
            for (int j = pmin.y; j < pmax.y; j++)
            {
                p = Vector3f( i + 0.5 , j + 0.5 , 1.0 );
                
                //for this ,M-1*V-1*P-1*E-1 作用与p，只能得到原世界坐标中的x y ，得不到z，因为z是深度值经过逆变换才会是正确的世界坐标z，所以用矫正算法吧
                Vector3f coord = barycentricCoord( p , trangle.a() , trangle.b() , trangle.c() );
                
                if(coord.x >= 0 && coord.y >= 0 && coord.z >=0){// if in trangle
                    //depth 需要矫正
                    p.z = trangle.vertexes[0].z * coord.x  + trangle.vertexes[1].z * coord.y + trangle.vertexes[2].z * coord.z;
                    
                    color_interplote = trangle.colors[0]*coord.x + trangle.colors[1]*coord.y + trangle.colors[2]*coord.z;
                    normal_interplote = trangle.normals[0]*coord.x + trangle.normals[1]*coord.y + trangle.normals[2]*coord.z;
                    if(!(normal_interplote == 0) )
                        normal_interplote= normalized(normal_interplote); 
                    //std::cout<<color<<std::endl;
                    color_interplote = (normal_interplote + 1.0) * 0.5 ;//normal [-1,1] to color[0,1]||[0,255]

                    setPixtel( p , color_interplote );
                }
                    
            }
            
        }
    }else{//MSAA
        for (int i = pmin.x; i < pmax.x; i++)
        {
            for (int j = pmin.y; j < pmax.y; j++)
            {//each pixtel center coordinate p , add four sample
                Vector3f p = Vector3f( i + 0.5 , j + 0.5, 1.0 );
                //Vector3f p1 = Vector3f( i + 0.25, j + 0.25, 1.0 );
                //Vector3f p2 = Vector3f( i + 0.75, j + 0.25, 1.0 );
                //Vector3f p3 = Vector3f( i + 0.25, j + 0.75, 1.0 );
               // Vector3f p4 = Vector3f( i + 0.75, j + 0.75, 1.0 );
                Vector3f coord = barycentricCoord( p , trangle.a() , trangle.b() , trangle.c() );
                //Vector3f coord1 = barycentricCoord( p1 , trangle.a() , trangle.b() , trangle.c() );
                //Vector3f coord2 = barycentricCoord( p2 , trangle.a() , trangle.b() , trangle.c() );
               //Vector3f coord3 = barycentricCoord( p3 , trangle.a() , trangle.b() , trangle.c() );
                //Vector3f coord4 = barycentricCoord( p4 , trangle.a() , trangle.b() , trangle.c() );
                //bool in = coord.x > 0 && coord.y > 0 && coord.z >0 ;
                //bool in1 = coord1.x > 0 && coord1.y > 0 && coord1.z >0 ;
               // bool in2 = coord2.x > 0 && coord2.y > 0 && coord2.z >0 ;
               // bool in3 = coord3.x > 0 && coord3.y > 0 && coord3.z >0 ;
               // bool in4 = coord4.x > 0 && coord4.y > 0 && coord4.z >0 ;
               
                float weight = 0.2 *  (isinTrangleUseCross(Vector3f( i + 0.5 , j + 0.5, 1.0 ),trangle) +
                isinTrangleUseCross(Vector3f( i + 0.25 , j + 0.25, 1.0 ),trangle)+
                isinTrangleUseCross(Vector3f( i + 0.25 , j + 0.75, 1.0 ),trangle)+
                isinTrangleUseCross(Vector3f( i + 0.75 , j + 0.25, 1.0 ),trangle)+
                isinTrangleUseCross(Vector3f( i + 0.75 , j + 0.75, 1.0 ),trangle)
                 );
    
                if(weight > 0){// if in trangle
                //depth 需要矫正
                    p.z = trangle.vertexes[0].z * coord.x  + trangle.vertexes[1].z * coord.y + trangle.vertexes[2].z * coord.z;
                    color_interplote = trangle.colors[0]*coord.x + trangle.colors[1]*coord.y + trangle.colors[2]*coord.z;
                    normal_interplote = trangle.normals[0]*coord.x + trangle.normals[1]*coord.y + trangle.normals[2]*coord.z;
                    if(!(normal_interplote == 0) )
                        normal_interplote= normalized(normal_interplote); 
                    //std::cout<<color<<std::endl;
                    //color_interplote = trangle.colors[0]*coord.x + trangle.colors[1]*coord.y + trangle.colors[2]*coord.z;
                    color_interplote = (normal_interplote + 1.0) * 0.5;//normal [-1,1] to color[0,1]||[0,255]
                    color_interplote *= weight;
                    
                    setPixtel( p , color_interplote );
                }
                
               
                    
            }
            
        }
    }
    

}





void rst::Rasterizer::setBuffer( rst::Buffers buf_type , int &index , Vector3f &value ){
    if( buf_type == rst::Buffers::Color )
        bufferColor[index] = value;
    else if(buf_type == rst::Buffers::ColorMSAA)
        bufferColorMSAA[index] = value;
    
}

void rst::Rasterizer::setPixtel( Vector3f &point , Vector3f &color ){
    /*
    int index = int(point.x) + int(point.y) * width;
    //color/=255;
        if( point.z < bufferDepth[index] ){
            bufferDepth[index] = point.z;
            setBuffer( rst::Buffers::Color , index , color );
  
        } 
    */
    
    int index = int(point.x) + int(point.y) * width;
    auto type = rst::Buffers::Color;
    if(enableMSAA){//(point - step/2)*MSAA step = 1/MSAA  //NOTE THIS MSAA, POINT IS MIDDLE POINT IN EACH SAME AREA'S ARER
        index = int(point.x * MSAA - 0.5) + int(point.y * MSAA - 0.5) * width * MSAA;
        type = rst::Buffers::ColorMSAA;
    }//if use msaa , depth buffer will increase!so the index is different
    if(point.z < bufferDepth[index]){
        bufferDepth[index] = point.z;
        setBuffer( type , index , color );
    }
    
}



void rst::Rasterizer::clearBuffer(rst::Buffers buff)
{
    if ( buff == rst::Buffers::Color)
    {
        std::fill(bufferColor.begin(), bufferColor.end(), Vector3f(0.0));
    }
    if ( buff == rst::Buffers::Depth)
    {
        std::fill(bufferDepth.begin(), bufferDepth.end(), std::numeric_limits<float>::infinity());
    }
}

void rst::Rasterizer::useMSAA(const bool enable){
    if(enable)
        enableMSAA = true;
    else
        enableMSAA = false;
}

void rst::Rasterizer::drawTrangles( const Triangles &triangles ){
    for (int i = 0; i < triangles.tset.size(); i++)
    {
        rst::Rasterizer::drawTrangle(triangles.tset[i]);
    }
    
}

void rst::Rasterizer::drawScene(  Scene &scene ){

    //Rasterizeration pipeline

    //scene.model = translate * rotation * scale;

    //std::cout<<scene.model<<"\n";
    
    auto shadeMode = FragmentShader::shaderType::Blinn_Feng;
    for (int i = 0; i < scene.meshes.size(); i++)
    {   auto obj = scene.meshes[i];
        scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 0 , Vector3f( 0,0,2) , Vector3f( 1 ) ));//move model to appropriate position
        if(i==0)
            scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 45 , Vector3f( 0,0,2) , Vector3f( 1 ) ));//move model to appropriate position
        if(i==1){
            scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 45 , Vector3f( 1,0,4) , Vector3f( 1 ) ));//move model to appropriate position  
        }
/*         mipmap test
        if(i==0)
            scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 45 , Vector3f( 1.5,0,2) , Vector3f( 1 ) ));//move model to appropriate position
        if(i==1){
            scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 45 , Vector3f( 1,0,4) , Vector3f( 1 ) ));//move model to appropriate position  
        }
        if(i==2)
            scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 45 , Vector3f( -1,0,5) , Vector3f( 1 ) ));//move model to appropriate position
        if(i==3)
            scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 45 , Vector3f( -5,0,8) , Vector3f( 1 ) ));//move model to appropriate position
        if(i==4)
            scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 45 , Vector3f( -10,0,10) , Vector3f( 1 ) ));//move model to appropriate position
        if(i==5)
            scene.setModel(getModelMat4( Vector3f( 0,1,0 ), 45 , Vector3f( -20.0,0,16) , Vector3f( 1 ) ));//move model to appropriate position

*/
        setModelMatrix( scene.getModel() );
        setViewMatrix(scene.getView());
        setProjectionMatrix(scene.getProjection());
        setViewPortMatrix( scene.getViewPort());
        //#pragma omp parallel for
        //for (int j = scene.meshes[i].tset.size()-863; j < scene.meshes[i].tset.size()-862; j++)
        for (int j = 0; j < scene.meshes[i].tset.size(); j++)
        {//each triangle in single mesh
            //Vector3f edgeAC =scene.meshes[i].tset[j].vertexes[2] - scene.meshes[i].tset[j].vertexes[0];
            //Vector3f edgeAB =scene.meshes[i].tset[j].vertexes[1] - scene.meshes[i].tset[j].vertexes[0];
            //auto tmp = Cross( edgeAB , edgeAC );
            auto tmp = Cross( scene.meshes[i].tset[j].vertexes[1] - scene.meshes[i].tset[j].vertexes[0] ,
            scene.meshes[i].tset[j].vertexes[2] - scene.meshes[i].tset[j].vertexes[0] );

            //MV matrix -> camera in (0,0,0) 's triangle position
            Vector3f screenSpacePos[3];
            screenSpacePos[0] = getMVMatrix()(Vector4f( scene.meshes[i].tset[j].vertexes[0] , 1.0f ));
            screenSpacePos[1] = getMVMatrix()(Vector4f( scene.meshes[i].tset[j].vertexes[1] , 1.0f ));
            screenSpacePos[2] = getMVMatrix()(Vector4f( scene.meshes[i].tset[j].vertexes[2] , 1.0f ));
            
            //v-vertex
            //MVPE matrix to triangle three vertex,
            Vector4f v[3];
            v[0] = getMVPEMatrix()(Vector4f( scene.meshes[i].tset[j].vertexes[0] , 1.0f ));
            v[1] = getMVPEMatrix()(Vector4f( scene.meshes[i].tset[j].vertexes[1] , 1.0f ));
            v[2] = getMVPEMatrix()(Vector4f( scene.meshes[i].tset[j].vertexes[2] , 1.0f ));
            
            scene.meshes[i].tset[j].setNormal(  tmp==0?0:normalized( tmp ) );
            //keep the origine coordinates
            //use v[0].toVec3f()v[1].toVec3f()v[2].toVec3f() represent 3  vertex after MVPE in triangle 
            //scene.meshes[i].tset[j].setVertex( 0 , v[0].toVec3f() );
            //scene.meshes[i].tset[j].setVertex( 1 , v[1].toVec3f() );
            //scene.meshes[i].tset[j].setVertex( 2 , v[2].toVec3f() );
            
            //scene.meshes[i].tset[j].setColor( Vector3f( rand()%255 , rand()%255 , rand()%255 ) );
            
            Triangle triangle = scene.meshes[i].tset[j];
            //std::cout<<scene.meshes[i].baseColor(0,0)<<"\n";
            Vector3f v0 = v[0].toVec3f() , v1 = v[1].toVec3f(), v2 = v[2].toVec3f();
            Vector3f pmin , pmax;
            setMaxMin( v0 , v1 ,v2 , pmin , pmax );
            //if its after mvp clamp ,remove what is not in screen 
            pmin.x = pmin.x<0 ? 0.0f :( pmin.x< width ? pmin.x : width );
            pmin.y = pmin.y<0 ? 0.0f :( pmin.y< width ? pmin.y : height );
            pmax.x = pmax.x<0 ? 0.0f :( pmax.x< width ? pmax.x : width );
            pmax.y = pmax.y<0 ? 0.0f :( pmax.y< width ? pmax.y : height );
            //std::cout<<pmin<<" "<<pmax<<"\n";
            //std::cout<<v0<<" "<<v1<<" "<<v2<<" ";
            for (int k1 = pmin.x; k1 < pmax.x; k1++)
            {//std::cout<< k1<< "\n";
                for (int k2 = pmin.y; k2 < pmax.y; k2++)
                {   //std::cout<<k1<<" "<<k2<<"\n";       
                    std::vector<Vector3f>points;
                    std::vector<Vector3f>coords;
                    bool isinT = false;
                    //每个子采样点都是有自己的颜色和深度存储的，并且每个子采样点都会做深度测试。
                    if(enableMSAA){
                        float step = 1.0/MSAA;
                        for (int m1 = 0; m1 < MSAA; m1++)
                        {
                            for (int m2 = 0; m2 < MSAA; m2++)
                            {   
                                Vector3f tmp = Vector3f( k1 + 0.5*step + m1 * step ,k2 + 0.5*step + m2 * step , 1.0 );
                                points.push_back(tmp);
                                Vector3f tmp2 = barycentricCoord(tmp , v0 ,v1 , v2);                            
                                coords.push_back(tmp2);
                                if(tmp2 > 0 )
                                    isinT = true;      
                                //std::cout<<tmp<<" " << int(tmp.x * MSAA - 0.5) + int(tmp.y * MSAA - 0.5) * width<<" ";
                                //std::cout<<tmp<<" "; 
                            }
                        }
                    }else{
                        Vector3f p = Vector3f( k1 + 0.5 , k2 + 0.5 , 1.0 );
                        //std::cout<< p<< "\n";
                        //for this ,M-1*V-1*P-1*E-1 作用与p，只能得到原世界坐标中的x y ，得不到z，因为z是深度值经过逆变换才会是正确的世界坐标z，所以用矫正算法吧
                        Vector3f coord = barycentricCoord( p , v[0].toVec3f() , v[1].toVec3f() , v[2].toVec3f() );
                        if(coord>0)
                            isinT = true;
                        points.push_back(p);
                        coords.push_back(coord);
                    }
        
                    //std::cout<<"\n======\n";

                    for (int n = 0; n < points.size(); n++)
                    {   //in triangle , need give this pixtel a color
                        if(coords[n].x >= 0 && coords[n].y >= 0 && coords[n].z >= 0){

                            
                            //Distance( points[i].x - onestep , points[i].y - onestep , points[i].x + onestep , points[i].y - onestep);
                            //Distance( points[i].x + onestep , points[i].y + onestep , points[i].x + onestep , points[i].y - onestep);
                            //Distance( points[i].x - onestep , points[i].y + onestep , points[i].x + onestep , points[i].y + onestep);
                            //Distance( points[i].x - onestep , points[i].y + onestep , points[i].x - onestep , points[i].y - onestep);

                            VertexShader vertexshader = VertexShader(points[i], coords[n] , v , screenSpacePos,triangle.normals,triangle.tex_coords,&obj.baseColor);
                            points[n].z = vertexshader.depth;
                            FragmentShader shader = FragmentShader( vertexshader.color_interplote , vertexshader.normal_interplote , vertexshader.texCoord_interplote , &obj.baseColor);
                            shader.view_pos = vertexshader.shadingPos_interplote;
                            int index1 = int(points[n].x * MSAA - 0.5) + int(points[n].y * MSAA - 0.5) * width * MSAA;
                            auto color = shader.shade( shadeMode );
                            setPixtel( points[n] , color );
                            //if(points[n].z < bufferDepth[index1]){
                            //    bufferDepth[index1] = points[n].z;
                            //    Vector3f color = shader.shade( shadeMode );
                            //    bufferColorMSAA[index1] = shader.shade( shadeMode );
                            // }
                        }
                    }
                    //std::cout<<"\n============\n";
         
//                        Vector3f p = Vector3f( k1 + 0.5 , k2 + 0.5 , 1.0 );
//                    
//                        //std::cout<< p<< "\n";
//                        //for this ,M-1*V-1*P-1*E-1 作用与p，只能得到原世界坐标中的x y ，得不到z，因为z是深度值经过逆变换才会是正确的世界坐标z，所以用矫正算法吧
//                        Vector3f coord = barycentricCoord( p , v[0].toVec3f() , v[1].toVec3f() , v[2].toVec3f() );
//                        
//                        if(coord.x >= 0 && coord.y >= 0 && coord.z >=0){// if in triangle
//                            
//                            //depth 需要矫正
//                            //p.z = triangle.vertexes[0].z * coord.x  + triangle.vertexes[1].z * coord.y + triangle.vertexes[2].z * coord.z;
//                            //    * v[i].w is the vertex view space depth value z.
//                            //    * Z is interpolated view space depth for the current pixel
//                            //    * p.z is depth between zNear and zFar, used for z-buffer
//                            /*
//                            Vector3f color_interplote = Vector3f( 255 , 255 , 255);
//                            Vector3f normal_interplote = 0;
//                            Vector2f texCoord_interplote = 0;  
//                            Vector3f shadingPos_interplote = 0;
//                            auto Z = 1.0 / (coord.x / v[0].w + coord.y / v[1].w + coord.z / v[2].w);
//                            p.z = coord.x * v[0].z / v[0].w + coord.y * v[1].z / v[1].w + coord.z * v[2].z / v[2].w;
//                            p.z *= Z;
//                            
//                            //color_interplote = triangle.colors[0]*coord.x + triangle.colors[1]*coord.y + triangle.colors[2]*coord.z;
//                            normal_interplote = interpolate( coord.x , coord.y , coord.z , triangle.normals[0] , triangle.normals[1],triangle.normals[2] , 1.0 );
//                            //normal_interplote = triangle.normals[0]*coord.x + triangle.normals[1]*coord.y + triangle.normals[2]*coord.z;
//                            if(!(normal_interplote == 0) )
//                                normal_interplote= normalized(normal_interplote); 
//                            //color_interplote = (normal_interplote + 1.0) * 0.5 ;//normal [-1,1] to color[0,1]||[0,255]
//                            shadingPos_interplote = interpolate(coord.x , coord.y , coord.z , screenSpacePos[0] , screenSpacePos[1] , screenSpacePos[2] , 1.0 );
//                            //shadingPos_interplote = screenSpacePos[0]*coord.x + screenSpacePos[1]*coord.y + screenSpacePos[2]*coord.z;;
//                            texCoord_interplote = interpolate(coord.x , coord.y , coord.z , triangle.tex_coords[0] , triangle.tex_coords[1] , triangle.tex_coords[2] , 1.0 );
//                            //texCoord_interplote = triangle.tex_coords[0] * coord.x + 
//                            //triangle.tex_coords[1] * coord.y+
//                            //triangle.tex_coords[2] * coord.z;
//                            color_interplote = obj.baseColor( texCoord_interplote );
//
//
//                            //FragmentShader shader = FragmentShader( color_interplote , normal_interplote , texCoord_interplote , &obj.baseColor);
//                            //shader.view_pos = shadingPos_interplote;
//                            
//                            //color_interplote = shader.shade( FragmentShader::shaderType::Blinn_Feng );
 //                           */
 //                           VertexShader vertexshader = VertexShader( coord , v , screenSpacePos,triangle.normals,triangle.tex_coords,&obj.baseColor);
 //                           p.z = vertexshader.depth;
 //                           //if(vertexshader.texCoord_interplote.x != texCoord_interplote.x)
 //                           //    std::cout<<" not equal ! ";
 //                           FragmentShader shader = FragmentShader( vertexshader.color_interplote , vertexshader.normal_interplote , vertexshader.texCoord_interplote , &obj.baseColor);
 //                           shader.view_pos = vertexshader.shadingPos_interplote;
 //                           //auto color_interplote = (vertexshader.normal_interplote + 1.0) * 0.5 ;//normal [-1,1] to color[0,1]||[0,255]
 //                           auto color_interplote = shader.shade( shadeMode );
 //                           
 //                           
 //                           setPixtel( p , color_interplote );
 //
 //                       }
                           
                }
                
            }
            
        }
        
    }
    //if use msaa ,need make buffer1[width *msaa x height * msaa]=>
    //buffer[weight x height] 
    //weight:screen weight , height : screen height , screen :final image plane u want draw/show 
    if(enableMSAA){
        /*
        #pragma omp parallel for
        for (int i = 0; i < scene.width*MSAA; i+=MSAA)
        {
            for (int j = 0; j < scene.height*MSAA; j+=MSAA)
            {
                Vector3f color;
                float weight = 0;
                for (int k1 = 0; k1 < MSAA; k1++)
                {
                    for (int k2 = 0; k2 < MSAA; k2++)
                    {
                        int index = i+k1 + (j+k2) * (width *MSAA);
                        if(bufferColorMSAA[index].x>0)
                        color += Vector3f(bufferColorMSAA[index].x,bufferColorMSAA[index].y,bufferColorMSAA[index].z);
                    }
                    
                }
                color /= MSAA * MSAA;
                int index = (i/MSAA) + (j/MSAA) * (width);
                setBuffer(rst::Buffers::Color ,index , color );
            }
        }*/
        bufMsaa2buf(scene);
    }
    //color draw to image
    //drawImagePPM( scene.meshes[0].baseColor.t );
    drawImagePPM( bufferColor );
    //drawImagePPM( bufferColorMSAA );
    //depth-buffer draw to image
    //std::vector<Vector3f> depth3f ;
    //depth3f.assign(bufferDepth.begin(),bufferDepth.end());
    //drawImagePPM( depth3f );
}

void rst::Rasterizer::bufMsaa2buf(Scene &scene){
    #pragma omp parallel for
    for (int i = 0; i < scene.width*MSAA; i+=MSAA)
    {
        for (int j = 0; j < scene.height*MSAA; j+=MSAA)
        {
            Vector3f color;
            float weight = 0;
            for (int k1 = 0; k1 < MSAA; k1++)
            {
                for (int k2 = 0; k2 < MSAA; k2++)
                {
                    int index = i+k1 + (j+k2) * (width *MSAA);
                    if(bufferColorMSAA[index].x>0)
                    color += Vector3f(bufferColorMSAA[index].x,bufferColorMSAA[index].y,bufferColorMSAA[index].z);
                }
                
            }
            color /= MSAA * MSAA;
            int index = (i/MSAA) + (j/MSAA) * (width);
            setBuffer(rst::Buffers::Color ,index , color );
        }
    }
}

void rst::Rasterizer::interploteBefore(  Triangle &t ){

    Vector3f edgeAC =t.vertexes[2] - t.vertexes[0];
    Vector3f edgeAB =t.vertexes[1] - t.vertexes[0];
    auto tmp = Cross( edgeAB , edgeAC );
    

    t.setNormal(  tmp==0?0:normalized( tmp ) );
    t.setVertex( 0 , getMVPEMatrix()(Vector4f( t.a() , 1.0f )) );
    t.setVertex( 1 , getMVPEMatrix()(Vector4f( t.b() , 1.0f )) );
    t.setVertex( 2 , getMVPEMatrix()(Vector4f( t.c() , 1.0f )) );
    
    t.setColor( Vector3f( rand()%255 , rand()%255 , rand()%255 ) );
}

void rst::Rasterizer::drawSceneWithPT(Scene &scene){
    //path tracing pipeline
    int height = scene.height;
    int weight = scene.width;
    float imagePlaneH = 2.0*tan(acos(-1)*(scene.fovY/360));
    float imagePlaneW = imagePlaneH*scene.aspect;
    std::cout<<imagePlaneH<<" "<<imagePlaneW<<"\n";
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < weight; x++)
        {
            //each fragment/pixtel
            int ind1 = x + y*width;
            float step = imagePlaneH / height;
            //let assume the image plane set in plane z = -1 , middle in (0,0,-1) NOTE Camera Coordinate
            //so the array,aka screen ,map the screen coord to word position (x,y,-1) NOTE Camera Coordinate
            //so (0,0)=>(-w/2,h/2)  (0,height)=>(-w/2,h/2) (width,0)=>(w/2,h/2) (weight,height)=>(w/2,-h/2)
            //u = x - w/2 , v = -(y - h/2) 
            float u = (x*1.0/width)*imagePlaneW - imagePlaneW/2.0;
            float v = -1.0*((y*1.0/height)*imagePlaneH - imagePlaneH/2.0);
            Vector3f p = Vector3f(u+step/2 , v+step/2 , 1.0);//image plane every fragent middle
            Vector3f dir = normalized( p - Vector3f(0) );
            Ray ray = Ray( p , dir );
            //std::cout<<"[" <<x << " "<<y<<"] ["<<u<<" "<<v<<"]\n";
            int spp = 1 ;
            Vector3f color = Vector3f(0);
            for (int i = 0; i < spp; i++)
            {
                color = castRay( ray , scene );
            }
            color/=spp;
            setBuffer(rst::Buffers::Color , ind1 , color);
        }   
    }
}

Vector3f rst::Rasterizer::castRay(Ray&ray , Scene &scene){
    return Vector3f(0);
}
