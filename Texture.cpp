#include "Texture.hpp"

Texture::Texture( const int &v ){ 
        t.resize( v*v ) ;
        initMipmaps(v,v);
}

Texture::Texture( const int &w , const int &h ){ 
        width = w;
        height = h;
        t.resize(w*h) ;
        //whatever use or not ,i save first one for u,in case if you want use mipmaps AFTER read texture already
        initMipmaps(w,h);
            
    }

void Texture::initMipmaps(const int &w , const int& h){
    if(checkCanUseMips(w , h)){
        int sumLevel = get2pow(width);
        if( width != height ){
            sumLevel = get2pow( width>height?height:width )+1;
            LOG("waring!!!not recommanded none squre(2^n) texture!");
        }
        mipmaps.resize(sumLevel);
        mipmaps[0].resize(w*h);
    }
}
int Texture::getMipMapMaxLevel(){
    int sumLevel = get2pow(width);
    if( width != height ){
        sumLevel = get2pow( width>height?height:width )+1;
        LOG("waring!!!not recommanded none squre(2^n) texture!");
    }
    return sumLevel;
}

Vector3f Texture::getMipMapTexColor(const float &mipmapL , Vector2f &texCoord_interplote){
    if(getMipMapMaxLevel() == int(mipmapL))
        return mipmaps[int(mipmapL)][0];
    else{
        auto p1 = Vector2f(( texCoord_interplote.x  ) * width/std::pow( 2.0 , int(mipmapL) ),( texCoord_interplote.y )*height/std::pow( 2.0 , int(mipmapL) )); 
        auto p2 = Vector2f(( texCoord_interplote.x  ) * width/std::pow( 2.0 , int(mipmapL)+1 ),( texCoord_interplote.y )*height/std::pow( 2.0 , int(mipmapL)+1 )); 
        //std::cout<<p1<<" "<<p2<<" "; 
        auto a1 = getBilinerInterpolationTex( p1.x , p1.y , int(mipmapL) );
        auto a2 = getBilinerInterpolationTex( p2.x , p2.y , int(mipmapL)+1 );
        //std::cout<<a1<<" "<<a2<<" "; 
        return Lerp(a1 , a2, mipmapL - int(mipmapL));
        //color_interplote = a2;
    }
}

Vector3f Texture::operator()( const Vector2f &v ){ 
    /*//std::cout<<int( v.x*width )<< " "<<int(  v.y*height )<<"\n";
        float u_img = v.x*width;
        float v_img = v.y*height;
        if(useBiLinerpLepForTex){
            return BilinerInterpolationTex( u_img , v_img );
            
            //if(u_img > 0 && u_img < width-1 &&
            //v_img > 0 && v_img < height-1){
            //    Vector3f LT,LB,RT,RB;
            //    //LT = Vector2f(int(u_img) , int(v_img)) ;
            //    //LB = Vector2f(int(u_img) , int(v_img)+1) ;
            //    //RT = Vector2f(int(u_img)+1 , int(v_img)) ;
            //    //RB = Vector2f(int(u_img)+1 , int(v_img)+1) ;
            //    LT = t[int(u_img) + int(v_img) * width];
            //    LB = t[int(u_img) + (int(v_img)+1) * width];
            //    RT = t[int(u_img)+1 + int(v_img) * width];
            //    RB = t[int(u_img)+1 + (int(v_img)+1) * width];
            //    return Lerp(Lerp(LT , RT , u_img - int(u_img)) ,
            //    Lerp(LB , RB , u_img - int(u_img)) ,
            //    v_img - int(v_img));
            //}
            
        }
        int a = int( u_img + int(v_img) * width);
        //if(v.x <0||v.y < 0)
        //    std::cout<<a <<" "<< v<<"\n";
        return t[a];
        */
    return (*this)( v.x , v.y );        
}

Vector3f Texture::operator()( const float &u ,const float &v ){ 
    //std::cout<<int( v.x*width )<< " "<<int(  v.y*height )<<"\n";
        float u_img = u*width;
        float v_img = v*height;
        if(useBiLinerpLepForTex){
            return getBilinerInterpolationTex( u_img , v_img );
            /*
            if(u_img > 0 && u_img < width-1 &&
            v_img > 0 && v_img < height-1){
                Vector3f LT,LB,RT,RB;
                //LT = Vector2f(int(u_img) , int(v_img)) ;
                //LB = Vector2f(int(u_img) , int(v_img)+1) ;
                //RT = Vector2f(int(u_img)+1 , int(v_img)) ;
                //RB = Vector2f(int(u_img)+1 , int(v_img)+1) ;
                LT = t[int(u_img) + int(v_img) * width];
                LB = t[int(u_img) + (int(v_img)+1) * width];
                RT = t[int(u_img)+1 + int(v_img) * width];
                RB = t[int(u_img)+1 + (int(v_img)+1) * width];
                return Lerp(Lerp(LT , RT , u_img - int(u_img)) ,
                Lerp(LB , RB , u_img - int(u_img)) ,
                v_img - int(v_img));
            }
            */
        }
        int a = int( u_img + int(v_img) * width);
        //if(v.x <0||v.y < 0)
        //    std::cout<<a <<" "<< v<<"\n";
        return t[a];
}

Vector3f Texture::getBilinerInterpolationTex(const float &u_img , const float &v_img ){
    if(!(u_img > 0 && u_img < width-1 &&
    v_img > 0 && v_img < height-1))
        return 0;
    /*
    Vector3f LT,LB,RT,RB;
    //LT = Vector2f(int(u_img) , int(v_img)) ;
    //LB = Vector2f(int(u_img) , int(v_img)+1) ;
    //RT = Vector2f(int(u_img)+1 , int(v_img)) ;
    //RB = Vector2f(int(u_img)+1 , int(v_img)+1) ;
    LT = t[int(u_img) + int(v_img) * width];
    LB = t[int(u_img) + (int(v_img)+1) * width];
    RT = t[int(u_img)+1 + int(v_img) * width];
    RB = t[int(u_img)+1 + (int(v_img)+1) * width];
    return Lerp(Lerp(LT , RT , u_img - int(u_img)) ,
    Lerp(LB , RB , u_img - int(u_img)) ,
    v_img - int(v_img));
    */
    //simplify four Vector3f -> one 
    Vector3f result = Lerp(
    Lerp(t[int(u_img) + int(v_img) * width] ,
        t[int(u_img)+1 + int(v_img) * width] ,
        u_img - int(u_img)) ,
    Lerp(t[int(u_img) + (int(v_img)+1) * width] ,
        t[int(u_img)+1 + (int(v_img)+1) * width] ,
        u_img - int(u_img)) ,
    v_img - int(v_img));
    return result;
}

Vector3f Texture::getBilinerInterpolationTex(const float &u_img , const float &v_img , const int &mipamplevel){
    int w = width/std::pow(2,mipamplevel) ;
    int h = height/std::pow(2,mipamplevel);
    if(!(u_img > 0 && u_img < w-1 &&
    v_img > 0 && v_img < h-1))
        return 0;
    if(enableMIPMAP){
        Vector3f result = Lerp(
        Lerp(mipmaps[mipamplevel][int(u_img) + int(v_img) * w] ,
            mipmaps[mipamplevel][int(u_img)+1 + int(v_img) * w] ,
            u_img - int(u_img)) ,
        Lerp(mipmaps[mipamplevel][int(u_img) + (int(v_img)+1) * w] ,
            mipmaps[mipamplevel][int(u_img)+1 + (int(v_img)+1) * w] ,
            u_img - int(u_img)) ,
        v_img - int(v_img));
        return result;
    }else{
        Vector3f result = Lerp(
        Lerp(t[int(u_img) + int(v_img) * width] ,
            t[int(u_img)+1 + int(v_img) * width] ,
            u_img - int(u_img)) ,
        Lerp(t[int(u_img) + (int(v_img)+1) * width] ,
            t[int(u_img)+1 + (int(v_img)+1) * width] ,
            u_img - int(u_img)) ,
        v_img - int(v_img));
        return result;
    }
}



void Texture::CreateMipMaps(){

    int sumLevel = get2pow(width);
    //CHECKTexture( width , height );
    if(!checkCanUseMips(width , height))
        return;
    if( width != height ){
        sumLevel = get2pow( width>height?height:width )+1;
        LOG("waring!!!not recommanded none squre(2^n) texture!");
    }
    
    int mmWidth = width , mmHeight = height;
    
    //NOTE: mipmap first one already saved when read Texture,cause i am afriad if u want use it after texture read ,it'll go wrong
    //and here i dont want copy texture to the first one mipmap ,too slow,so i do it when load texture
    for (int k = 0; k < sumLevel-1; k++)
    {   
        mipmaps[k+1].resize(mmWidth/2 * mmHeight/2);
        //Vector3f randomColor = Vector3f((rand()%255)/255.0 , (rand()%255)/255.0 , (rand()%255)/255.0 );
        //std::cout<<" "<<randomColor<<"\n";

        for (int i = 0; i < mmWidth; i+=2)
        {
            for (int j = 0; j < mmHeight; j+=2)
            {
                int ind1 = i + j * mmHeight;
                int ind2 = i/2 + j* mmHeight / 4;
                mipmaps[k+1][ind2] = 
                mipmaps[k][ind1]+
                mipmaps[k][ind1]+
                mipmaps[k][ind1]+
                mipmaps[k][ind1];
                mipmaps[k+1][ind2]*=0.25;
                //mipmaps[k+1][ind2] = randomColor;
                /*mipmap test
                if(k+1 == 1)
                    mipmaps[k+1][ind2] = Vector3f(1,1,0);
                if(k+1 == 2)
                    mipmaps[k+1][ind2] = Vector3f(1,0,0);
                if(k+1 == 3)
                    mipmaps[k+1][ind2] = Vector3f(1,0,0);
                if(k+1 == 4)
                    mipmaps[k+1][ind2] = Vector3f(0,1,0);
                if(k+1 == 5)
                    mipmaps[k+1][ind2] = Vector3f(0,1,0);
                if(k+1 == 6)
                    mipmaps[k+1][ind2] = Vector3f(0,0,1);
                if(k+1 == 7)
                    mipmaps[k+1][ind2] = Vector3f(0,0,1);
                */
            }
            
        }
        mmWidth/=2;
        mmHeight/=2;
    }
    
}

void Texture::save2ImagePPM( std::string path, const std::vector<Vector3f> &buffer , int w , int h){
     // save framebuffer to file
    FILE* fp = fopen(path.c_str(), "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", w, h);
    Vector3f buf = Vector3f(0);
    for (auto i = 0; i < w * h ; ++i) {
        buf = Clamp( buffer[i], 0, 1 );
        static unsigned char color[3];
        color[0] = (unsigned char)(255 * std::pow(buf.x, 0.6f));
        color[1] = (unsigned char)(255 * std::pow(buf.y, 0.6f));
        color[2] = (unsigned char)(255 * std::pow(buf.z, 0.6f));
        fwrite(color, 1, 3, fp);
    }
    fclose(fp);    
}

void Texture::saveMipMaps2PPM(){
    int w = width ;
    int h = width;
    
    for (int i = 0; i < mipmaps.size(); i++)
    {   
        std::cout<<mipmaps[i].size()<<" ";
        std::string str = "./mips";
        str.append(std::to_string(i));
        str.append(".ppm");
        std::cout<<str<<" "<< w << " "<< h <<" \n";
        save2ImagePPM( str.c_str(), mipmaps[i] , w , h );
        w/=2;
        h/=2;
        
    }
}



