//
//create by AO LI 11/21/2021
//
#pragma once

#include <vector>
#include "mathutil.hpp"
#include "Global.hpp"
#include "common.hpp"

class Texture
{
private:
    /* data */
public:
    Texture():width(1),height(1){t.resize(1);};
    Texture( const int &v );
    Texture( const int &w , const int &h );
    
    //contain three channel values
    std::vector<Vector3f> t;
    int width;
    int height;
    //NOTE int(v*height) ,v(0~1),v*height(0,height),int(v*height)'s width,it must be integer's row !
    Vector3f operator()( const float &u ,const float &v );
    Vector3f operator()( const Vector2f &v );
    std::vector< std::vector<Vector3f> > mipmaps;

    //abort
    //load texture data from bmp image , save to itself
    //void loadTexture( unsigned char *originData );
    Vector3f getBilinerInterpolationTex(const float &u_img , const float &v_img);
    Vector3f getBilinerInterpolationTex(const float &u_img , const float &v_img , const int &w , const  int &h );
    Vector3f getBilinerInterpolationTex(const float &u_img , const float &v_img , const int &mipamplevel);
    void CreateMipMaps();
    void initMipmaps(const int &w , const int& h);
    void save2ImagePPM( std::string path, const std::vector<Vector3f> &buffer , int w , int h);
    void saveMipMaps2PPM();
    Vector3f getMipMapTexColor(const float &mipamplevel,Vector2f &texCoord_interplote);
    int getMipMapMaxLevel();

};

static Texture loadTextureFromBMP( const char *bmpName ){
    //二进制读方式打开指定的图像文件
    FILE *fp=fopen(bmpName,"rb");
	if(fp==0) return 0;
	
	RGBQUAD *pColorTable;
	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER),0);
	
	
	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head;  
	fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); 
	
	//获取图像宽、高、每像素所占位数等信息
	auto bmpWidth = head.biWidth;
	auto bmpHeight = head.biHeight;
	auto biBitCount = head.biBitCount;
	
	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	
	//灰度图像有颜色表，且颜色表表项为256
	if(biBitCount==8){
		//申请颜色表所需要的空间，读颜色表进内存
		pColorTable=new RGBQUAD[256];
		fread(pColorTable,sizeof(RGBQUAD),256,fp);
	}

	//申请位图数据所需要的空间，读位图数据进内存
	unsigned char *pBmpBuf=new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf,1,lineByte * bmpHeight,fp);
    
	//关闭文件
	fclose(fp);
    
    Texture texture = Texture( bmpWidth , bmpHeight );
    //std::cout<<bmpWidth<<" " <<bmpHeight << " "<< texture.t.size() <<"\n";
    int length = _msize(pBmpBuf) > bmpWidth*bmpHeight*3 ? bmpWidth*bmpHeight*3 :_msize(pBmpBuf);
    //std::cout<<length<<"\n";
    Vector3f rgb;
    int index;
    bool mips = checkCanUseMips(texture.width , texture.height);
    //std::cout<<texture.mipmaps[0].size()<<" ";
    for (int i = 0; i < length - 2; i+=3)
    {
        index = i/3;
        //int y = index /texture.width;//index = y*width + x; CAPTIAL int!
        //inverse y axis of texture, buffer[ind1]-->buffer[ind2] ind2 = ind1 + (h-1) * w - 2*y*w;
        //int ind2 = index + (texture.height-1) * texture.width - 2*y*texture.width;
        
        rgb = Vector3f( float(pBmpBuf[i+2]), float(pBmpBuf[i+1]),float(pBmpBuf[i])  );
        rgb/=255;
        //if(mips)
        //    texture.mipmaps[0][ind2] = rgb;
        //texture.t[ind2] = rgb;
        //if(index >= texture.t.size())
        //    std::cout<<index<<" error!\n";
        
        //whatever use or not ,i save first one for u,in case if you want use mipmaps AFTER read texture already
        if(mips)
            texture.mipmaps[0][index] = rgb;
        texture.t[index] = rgb;
    }
    
    if(enableMIPMAP&&checkCanUseMips( texture.width, texture.height ))
        texture.CreateMipMaps();
    return texture;
}

