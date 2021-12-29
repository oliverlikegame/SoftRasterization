//
//create by AO LI 11/16/2021
//
#include "Geometry.hpp"
#include "Rasterizer.hpp"
#include <vector>
#include <cstring>
#include "Scene.hpp"
#include "Loader.hpp"
#include "Global.hpp"

void rasterizationTest();
void pathTracingTest();

int main(){

    rasterizationTest();
    //pathTracingTest();
    std::cout<<"done \n";

}


void rasterizationTest(){
    //rasterizer.useMSAA(false);
    enableMSAA = true;
    MSAA = 2;
    useBiLinerpLepForTex = true;
    enableMIPMAP = true;

    //float a = 0.249999999999999999;
    //float b = a * 4;
    //std::cout<<b <<" "<< int(b)<<"\n";

    Scene scene = Scene( 1280 , 900 );
    //Scene scene = Scene( 800 , 800 );

    int width = scene.width, height = scene.height;
    
    rst::Rasterizer rasterizer = rst::Rasterizer( width , height );
    objl::Loader Loader;

    ms::Mesh obj,floor;

    std::vector<ms::Mesh> objs;
    objs.push_back(obj);
    //objs.push_back(floor);
    
    std::vector<std::string> objloadPath;
    objloadPath.push_back("../models/spot/spot_triangulated_good.obj");
    objloadPath.push_back("../models/cube/cube.obj");
   
    //bool loadout = Loader.LoadFile("../models/floor/floor.obj");
    //bool loadout = Loader.LoadFile("../models/spot/spot_triangulated_good.obj");
    std::vector<std::string> texLoadPath;

    texLoadPath.push_back("../models/spot/spot_texture2048.bmp");
    texLoadPath.push_back("../models/floor/cube.bmp");
    /*
    auto buffer = readBmp(str1.c_str() );
    //str1 = "../111.bmp";
    //saveBmp(str1.c_str(),buffer,1024,1024,24,nullptr);
    Texture texture = Texture(1024) ;
    
    texture.loadTexture( buffer );
    */
    //std::string str1 = "../models/spot/random3_.bmp";
    //auto buffer = readBmp(str1.c_str() );
    //std::string str3 = "../222.bmp";
    //saveBmp(str3.c_str(),buffer,597,813,24,nullptr);
    
    //std::cout<< obj.baseColor.t[ 475.484 + 586.948*1024 ]*255 <<"\n" ;
    //for (int i = 0; i < obj.baseColor.t.size(); i++)
    //{
    //    std::cout<<obj.baseColor.t[i]<<"  ";
   // }
    
    //bool loadout = Loader.LoadFile("../models/bunny/bunny.obj");
    //bool loadout = Loader.LoadFile("../models/cube/cube.obj");
    for (int index = 0; index < objs.size(); index++)
    {
        bool loadout = Loader.LoadFile(objloadPath[index]);
        if(!loadout)
            LOG("model loading went wrong\n");
        Texture texture = loadTextureFromBMP(texLoadPath[index].c_str());
        objs[index].setTexture( texture );

        #pragma omp parallel for
        for(auto mesh:Loader.LoadedMeshes)
        {    
            for(int i=0;i<mesh.Vertices.size();i+=3)
            {
                Triangle t ;
                for(int j=0;j<3;j++)
                {
                    t.setVertex(j,Vector4f(mesh.Vertices[i+j].Position.X,mesh.Vertices[i+j].Position.Y,mesh.Vertices[i+j].Position.Z,1.0));
                    t.setVertexNormal(j,Vector3f(mesh.Vertices[i+j].Normal.X,mesh.Vertices[i+j].Normal.Y,mesh.Vertices[i+j].Normal.Z));
                    t.setTexCoord(j,Vector2f(mesh.Vertices[i+j].TextureCoordinate.X, mesh.Vertices[i+j].TextureCoordinate.Y));
                }
                objs[index].tset.push_back(t);
            }
        }
        scene.addMesh( objs[index] );
        /*mipmap test
        scene.addMesh( objs[index] );
        scene.addMesh( objs[index] );
        scene.addMesh( objs[index] );
        scene.addMesh( objs[index] );
        scene.addMesh( objs[index] );
        */
    }
    
    /*
    rasterizer.clearBuffer(rst::Buffers::Color);

    for (int i = 0; i < _msize(buffer) -3; i+=3)
    {
        Vector3f temp2 = Vector3f( float(buffer[i+2]), float(buffer[i+1]),float(buffer[i])  );
        temp2/=255;
        // std::cout<<temp2<<"\n";
        int index = i / 3;
        int y = index /width;//index = y*width + x;
        int x = index % width;
        int ind2 = index + (height-1) * width - 2*y*width;//  inverse y axis of texture, buffer[ind1]-->buffer[ind2] ind2 = ind1 + (h-1) * w - 2*y*w;
        rasterizer.setBuffer( rst::Buffers::Color , ind2 , temp2 );
        //std::cout<< index << " " << ind2 << " "<< x << " "<< y  <<" \n";
    }
    
    auto bbb = rasterizer.getcolorbuffer();

    for (int i = bbb.size()-1024*10; i < bbb.size(); i++)
    {
        bbb[i] = Vector3f(1,0,0);
    }
    
  
    rasterizer.drawImagePPM( bbb );
    */
    //rasterizer.drawImagePPM( texture.t );
    
/*
    Triangle trangle = Triangle();
    Triangle trangle1 = Triangle();
    Vector3f a = Vector3f( 3 ,30 ,45 );
    Vector3f b = Vector3f( 30 ,3 ,45 );
    Vector3f c = Vector3f( 3 ,3 ,45 );
    Vector3f d = Vector3f( 20-3 ,30 ,50 );
    Vector3f e = Vector3f( 20-30 ,3 ,50 );
    Vector3f f = Vector3f( 20-3 ,3 ,50 ) ;

    Triangles ts ;
    ts.addTriangle( trangle );
    ts.addTriangle( trangle1 );
    //Box box;
    ms::Mesh mesh , mesh2;
    //mesh.setTriangles(box);
    mesh2.setTriangles(ts);
    scene.addMesh(mesh);
    //scene.addMesh(mesh2);
    */
  
    //scene.addMesh( floor );
    rasterizer.drawScene(scene);
}

void pathTracingTest(){
    Scene scene = Scene( 1280 , 900 );
    //Scene scene = Scene( 800 , 800 );

    int width = scene.width, height = scene.height;
    
    rst::Rasterizer rasterizer = rst::Rasterizer( width , height );

    rasterizer.drawSceneWithPT(scene);
}

