//
//create by AO LI 11/16/2021
//
#pragma once

#include <cmath>
#include <cstring>
#include "common.hpp"
#include <windows.h>
#include "Global.hpp"




inline float Sqr(const float &v) { return v * v; }
inline float SafeSqrt(const float &v) { return std::sqrt(std::max(v, 0.f)); }
inline float SafeAcos(const float &v) {
    return std::acos(std::min(std::max(v, 0.f), 1.f));
}

class Vector2f
{
private:
    /* data */
public:
    Vector2f( const float &v = 0 ): x( v ) ,y( v )  {}
    Vector2f(const float &_x ,const float &_y ) : x( _x ) ,y( _y )  {}

    Vector2f operator+( const Vector2f &v )const{ return Vector2f( x + v.x ,y + v.y ) ;}
    Vector2f operator-( const Vector2f &v )const{ return Vector2f( x - v.x ,y - v.y ) ;}
    Vector2f operator*( const Vector2f &v )const{ return Vector2f( x * v.x ,y * v.y  ) ;}
    Vector2f operator*( const float &v )const{ return Vector2f( x * v ,y * v  ) ;}
    Vector2f operator/( const float &v )const{
        CHECK( v != 0 );
        float inv = 1.0/v;
        return Vector2f( x * inv , y * inv );
    }
    Vector2f operator/( const Vector2f &v )const{
        CHECK( v.x != 0.0);
        CHECK( v.y != 0.0);
       
        float invX = 1.0/v.x;
        float invY = 1.0/v.y;
        
        return Vector2f( x * invX , y * invY  );
    }
    Vector2f &operator+=( const Vector2f &v ){ 
        x += v.x ; 
        y += v.y ;
       
        return *this;
    }
    Vector2f &operator-=( const Vector2f &v ){ 
        x -= v.x ; 
        y -= v.y ;
        
        return *this;
    }
    Vector2f &operator*=( const float &v ){ 
        x *= v ; 
        y *= v ;
        
        return *this;
    }
    Vector2f &operator*=( const Vector2f &v ){ 
        x *= v.x ; 
        y *= v.y ;
        
        return *this;
    }
    Vector2f &operator/=( const float &v ){ 
        CHECK( v != 0.0);
        x /= v ; 
        y /= v ;
        
        return *this;
    }
    Vector2f &operator/=( const Vector2f &v ){ 
        CHECK( v.x != 0.0);
        CHECK( v.y != 0.0);
        
        x /= v.x ; 
        y /= v.y ;
        
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os, const Vector2f &v) {
        os << "[ " << v.x << ", " << v.y << " ]";
        return os;
    }

    float x ,y ;
};

inline float Length(const float x ,const float y ){
    return std::sqrt( x*x + y*y );
}
inline float Length(const Vector2f v ){
    return std::sqrt( v.x*v.x + v.y*v.y );
}
inline float Distance(const float x1 ,const float y1 , const float x2 ,const float y2){
    return Length( x1-x2,y1-y2 );
}
inline float Distance(const Vector2f v1 , const Vector2f v2){
    return Length( v1 - v2 );
}


class Vector3f
{
private:
    /* data */
public:
    
    Vector3f( const float &v = 0 ): x( v ) ,y( v ) ,z( v ) {}
    Vector3f(const float &_x ,const float &_y ,const float &_z):x( _x ) ,y( _y ) ,z( _z ) {}

    Vector3f operator+( const Vector3f &v )const{ return Vector3f( x + v.x ,y + v.y ,z + v.z ) ;}
    Vector3f operator-( const Vector3f &v )const{ return Vector3f( x - v.x ,y - v.y ,z - v.z ) ;}
    Vector3f operator*( const Vector3f &v )const{ return Vector3f( x * v.x ,y * v.y ,z * v.z ) ;}
    Vector3f operator*( const float &v )const{ return Vector3f( x * v ,y * v ,z * v ) ;}
    Vector3f operator/( const float &v )const{
        CHECK( v != 0 );
        float inv = 1.0/v;
        return Vector3f( x * inv , y * inv , z * inv );
    }
    Vector3f operator/( const Vector3f &v )const{
        CHECK( v.x != 0.0);
        CHECK( v.y != 0.0);
        CHECK( v.z != 0.0);
        float invX = 1.0/v.x;
        float invY = 1.0/v.y;
        float invZ = 1.0/v.z;
        return Vector3f( x * invX , y * invY , z * invZ );
    }
    Vector3f &operator+=( const Vector3f &v ){ 
        x += v.x ; 
        y += v.y ;
        z += v.z ;
        return *this;
    }
    Vector3f &operator-=( const Vector3f &v ){ 
        x -= v.x ; 
        y -= v.y ;
        z -= v.z ;
        return *this;
    }
    Vector3f &operator*=( const float &v ){ 
        x *= v ; 
        y *= v ;
        z *= v ;
        return *this;
    }
    Vector3f &operator*=( const Vector3f &v ){ 
        x *= v.x ; 
        y *= v.y ;
        z *= v.z ;
        return *this;
    }
    Vector3f &operator/=( const float &v ){ 
        CHECK( v != 0.0);
        x /= v ; 
        y /= v ;
        z /= v ;
        return *this;
    }
    Vector3f &operator/=( const Vector3f &v ){ 
        CHECK( v.x != 0.0);
        CHECK( v.y != 0.0);
        CHECK( v.z != 0.0);
        x /= v.x ; 
        y /= v.y ;
        z /= v.z ;
        return *this;
    }
    bool operator==( const Vector3f &v ){return v.x==x && v.y == y && v.z == z;}
    bool operator==( const float &v ){return v==x && v == y && v == z;}
    bool operator>(const float &v){ return x>v && y>v && z>v ;}
    bool operator>(const Vector3f &v){ return x>v.x && y>v.y && z>v.z ;}
    bool operator>=(const float &v){ return x>=v && y>=v && z>=v ;}
    bool operator>=(const Vector3f &v){ return x>=v.x && y>=v.y && z>=v.z ;}

    float x ,y ,z;
};

inline Vector3f Min(const Vector3f &a, const Vector3f &b) {
    return Vector3f(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

inline Vector3f Max(const Vector3f &a, const Vector3f &b) {
    return Vector3f(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

inline float Dot(const Vector3f &a, const Vector3f &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline Vector3f Cross(const Vector3f &a, const Vector3f &b){
    return Vector3f( b.y*b.z-b.y*a.z ,a.z*b.x-a.x*b.z ,a.x*b.y-a.y*b.x );
}


inline Vector3f Abs(const Vector3f &a) {
    return Vector3f(std::fabs(a.x), std::fabs(a.y), std::fabs(a.z));
}
inline Vector3f Sqr(const Vector3f &a) { return Vector3f(Sqr(a.x), Sqr(a.y), Sqr(a.z)); }
inline Vector3f SafeSqrt(const Vector3f &a) {
    return Vector3f(SafeSqrt(a.x), SafeSqrt(a.y), SafeSqrt(a.z));
}

// (1 - s) * u + s * v
inline Vector3f Lerp(const Vector3f &u, const Vector3f &v, const float &s) {
    return u + (v - u) * s;
}
inline Vector3f Clamp(const Vector3f &v, const Vector3f &l, const Vector3f &r) {
    return Min(Max(v, l), r);
}

inline float SqrLength(const Vector3f &a) { return Sqr(a.x) + Sqr(a.y) + Sqr(a.z); }
inline float Length(const Vector3f &a) { return std::sqrt(Sqr(a.x) + Sqr(a.y) + Sqr(a.z)); }
inline Vector3f normalized(const Vector3f &a) { return a / Length(a); }

inline float SqrDistance(const Vector3f &a, const Vector3f &b) { return SqrLength(a - b); }
inline float Distance(const Vector3f &a, const Vector3f &b) { return Length(a - b); }

inline std::ostream &operator<<(std::ostream &os, const Vector3f &v) {
    os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
    return os;
}

class Vector3b
{
private:
    /* data */
public:
    
    Vector3b( const BYTE &v = 0 ): x( v ) ,y( v ) ,z( v ) {}
    Vector3b(const BYTE &_x ,const BYTE &_y ,const BYTE &_z):x( _x ) ,y( _y ) ,z( _z ) {}

    Vector3b operator+( const Vector3b &v )const{ return Vector3b( x + v.x ,y + v.y ,z + v.z ) ;}
    Vector3b operator-( const Vector3b &v )const{ return Vector3b( x - v.x ,y - v.y ,z - v.z ) ;}
    Vector3b operator*( const Vector3b &v )const{ return Vector3b( x * v.x ,y * v.y ,z * v.z ) ;}
    Vector3b operator*( const BYTE &v )const{ return Vector3b( x * v ,y * v ,z * v ) ;}
    Vector3b operator/( const BYTE &v )const{
        CHECK( v != 0 );
        BYTE inv = 1.0/v;
        return Vector3b( x * inv , y * inv , z * inv );
    }
    Vector3b operator/( const Vector3b &v )const{
        CHECK( v.x != 0.0);
        CHECK( v.y != 0.0);
        CHECK( v.z != 0.0);
        float invX = 1.0/v.x;
        float invY = 1.0/v.y;
        float invZ = 1.0/v.z;
        return Vector3b( x * invX , y * invY , z * invZ );
    }
    Vector3b &operator+=( const Vector3b &v ){ 
        x += v.x ; 
        y += v.y ;
        z += v.z ;
        return *this;
    }
    Vector3b &operator-=( const Vector3b &v ){ 
        x -= v.x ; 
        y -= v.y ;
        z -= v.z ;
        return *this;
    }
    Vector3b &operator*=( const float &v ){ 
        x *= v ; 
        y *= v ;
        z *= v ;
        return *this;
    }
    Vector3b &operator*=( const Vector3b &v ){ 
        x *= v.x ; 
        y *= v.y ;
        z *= v.z ;
        return *this;
    }
    Vector3b &operator/=( const BYTE &v ){ 
        CHECK( v != 0.0);
        x /= v ; 
        y /= v ;
        z /= v ;
        return *this;
    }
    Vector3b &operator/=( const Vector3b &v ){ 
        CHECK( v.x != 0.0);
        CHECK( v.y != 0.0);
        CHECK( v.z != 0.0);
        x /= v.x ; 
        y /= v.y ;
        z /= v.z ;
        return *this;
    }
    bool operator==( const Vector3b &v ){return v.x==x && v.y == y && v.z == z;}
    bool operator==( const BYTE &v ){return v==x && v == y && v == z;}
    
    operator Vector3f(){ return( Vector3f( x , y , z ) ) ;}

    BYTE x ,y ,z;
};


class Vector4f
{
private:
    /* data */
public:
    
    Vector4f( const float &v = 0 ): x( v ) ,y( v ) ,z( v ) ,w(1) {}
    Vector4f( const Vector3f &v , const float &w ): x( v.x ) ,y(v.y) ,z(v.z) ,w(w) {}
    Vector4f(const float &_x ,const float &_y ,const float &_z ,const float &_w):x( _x ) ,y( _y ) ,z( _z ) , w(_w) {}

    Vector4f operator+( const Vector4f &v )const{ return Vector4f( x + v.x ,y + v.y ,z + v.z , w + v.w) ;}
    Vector4f operator-( const Vector4f &v )const{ return Vector4f( x - v.x ,y - v.y ,z - v.z , w - v.w) ;}
    Vector4f operator*( const Vector4f &v )const{ return Vector4f( x * v.x ,y * v.y ,z * v.z ,w * v.w ) ;}
    Vector4f operator*( const float &v )const{ return Vector4f( x * v ,y * v ,z * v , w * v) ;}
    Vector4f operator/( const float &v )const{
        CHECK( v != 0 );
        float inv = 1.0/v;
        return Vector4f( x * inv , y * inv , z * inv ,w * inv);
    }
    Vector4f operator/( const Vector4f &v )const{
        CHECK( v.x != 0.0);
        CHECK( v.y != 0.0);
        CHECK( v.z != 0.0);
        CHECK( v.w != 0.0);
        float invX = 1.0/v.x;
        float invY = 1.0/v.y;
        float invZ = 1.0/v.z;
        float invW = 1.0/v.w;
        return Vector4f( x * invX , y * invY , z * invZ , w * invW );
    }
    Vector4f &operator+=( const Vector4f &v ){ 
        x += v.x ; 
        y += v.y ;
        z += v.z ;
        w += v.w ;
        return *this;
    }
    Vector4f &operator-=( const Vector4f &v ){ 
        x -= v.x ; 
        y -= v.y ;
        z -= v.z ;
        w -= v.w ;
        return *this;
    }
    Vector4f &operator*=( const float &v ){ 
        x *= v ; 
        y *= v ;
        z *= v ;
        w *= v ;
        return *this;
    }
    Vector4f &operator*=( const Vector4f &v ){ 
        x *= v.x ; 
        y *= v.y ;
        z *= v.z ;
        w *= v.w ;
        return *this;
    }
    Vector4f &operator/=( const float &v ){ 
        CHECK( v != 0.0);
        x /= v ; 
        y /= v ;
        z /= v ;
        w /= w ;
        return *this;
    }
    Vector4f &operator/=( const Vector4f &v ){ 
        CHECK( v.x != 0.0);
        CHECK( v.y != 0.0);
        CHECK( v.z != 0.0);
        CHECK( v.w != 0.0);
        x /= v.x ; 
        y /= v.y ;
        z /= v.z ;
        w /= v.w ;
        return *this;
    }
    
    //default if w!= 0 , w->1
    //转换函数 Vector4f -> Vector3f
    operator Vector3f(){
        if(w == 0){
            return Vector3f( x , y , z );
        }else{
            float inv = 1.0 / w;
            return Vector3f( x * inv , y * inv ,z * inv );
        }
    }
    Vector3f toVec3f(){
        if(w == 0){
            return Vector3f( x , y , z );
        }else{
            float inv = 1.0 / w;
            return Vector3f( x * inv , y * inv ,z * inv );
        }
    }
    float x ,y ,z ,w ;
};

inline std::ostream &operator<<(std::ostream &os, const Vector4f &v) {
    os << "[ " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << " ]";
    return os;
}

class Matrix4f
{
private:
    /* data */
public:
    Matrix4f(/* args */){
        memset(m, 0, sizeof(float) * 16);
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
    }

    Matrix4f(const float _m[4][4]) { memcpy(m, _m, sizeof(float) * 16); }

    Matrix4f(const float _m[16]) { memcpy(m, _m, sizeof(float) * 16); }

    Matrix4f &operator+(const Matrix4f mat){
        m[0][0]  += mat.m[0][0]; m[0][1]  += mat.m[0][1]; m[0][2]  += mat.m[0][2]; m[0][3]  += mat.m[0][3];
        m[1][0]  += mat.m[1][0]; m[1][1]  += mat.m[1][1]; m[1][2]  += mat.m[1][2]; m[1][3]  += mat.m[1][3];
        m[2][0]  += mat.m[2][0]; m[2][1]  += mat.m[2][1]; m[2][2]  += mat.m[2][2]; m[2][3]  += mat.m[2][3];
        m[3][0]  += mat.m[3][0]; m[3][1]  += mat.m[3][1]; m[3][2]  += mat.m[3][2]; m[3][3]  += mat.m[3][3];
        return *this;
    }

    Matrix4f operator*( const float &n )const{
        Matrix4f ret;
        for (uint32_t i = 0; i < 4; i++) {
            for (uint32_t j = 0; j < 4; j++) {
                ret.m[i][j] = m[i][j] * n;
            }
        }
        return ret;
    }

    Matrix4f operator/(const float &v) const {
        CHECK(v != 0);
        float inv = 1.f / v;
        return *this * inv;
    }

    Matrix4f operator*(const Matrix4f mat) const {
        Matrix4f ret;
        for (uint32_t i = 0; i < 4; i++) {
            for (uint32_t j = 0; j < 4; j++) {
                ret.m[i][j] = 0;
                for (uint32_t k = 0; k < 4; k++) {
                    ret.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }
        return ret;
    }
    
    float operator()( const int i , const int j ){return m[i][j] ;}

    Vector4f operator()(const Vector4f &p ) const;

    void set( const Matrix4f mat4 );

    void set(float,float, float,float,float,float,float,float,float,float,float,float,float,float,float,float);

    
    float m[4][4];

    public:
    friend std::ostream &operator<<(std::ostream &os, const Matrix4f &mat) {
        os << mat.m[0][0] << "\t" << mat.m[0][1] << "\t" << mat.m[0][2] << "\t"
           << mat.m[0][3] << "\n"
           << mat.m[1][0] << "\t" << mat.m[1][1] << "\t" << mat.m[1][2] << "\t"
           << mat.m[1][3] << "\n"
           << mat.m[2][0] << "\t" << mat.m[2][1] << "\t" << mat.m[2][2] << "\t"
           << mat.m[2][3] << "\n"
           << mat.m[3][0] << "\t" << mat.m[3][1] << "\t" << mat.m[3][2] << "\t"
           << mat.m[3][3];
        return os;
    }

    friend Matrix4f Inverse(const Matrix4f &mat);
    friend Matrix4f Transpose(const Matrix4f &mat);
};

static void setMaxMin( float a , float b , float c , float &min , float &max ){
    min = a < b ? a : b;
    min = min < c ? min : c;
    max = a > b ? a : b;
    max = max > c ? max : c;
    
}
static void setMaxMin( const Vector3f &va ,const Vector3f &vb ,const Vector3f &vc , Vector3f &min , Vector3f &max ){
    setMaxMin( va.x , vb.x , vc.x , min.x , max.x);
    setMaxMin( va.y , vb.y , vc.y , min.y , max.y);
    setMaxMin( va.z , vb.z , vc.z , min.z , max.z);
}
static Vector3f barycentricCoord( const Vector3f p , const Vector3f va , const Vector3f vb , const Vector3f vc ){
    float num = (p.y - vb.y) * ( vc.x - vb.x ) - ( p.x - vb.x ) * ( vc.y - vb.y );
    float deno =1 /( ( va.y - vb.y ) * ( vc.x - vb.x ) - ( va.x - vb.x ) * ( vc.y - vb.y ) );
    float alphe = num * deno;
    num = (p.y - vc.y) * ( va.x - vc.x ) - ( p.x - vc.x ) * ( va.y - vc.y );
    deno =1 /( ( vb.y - vc.y ) * ( va.x - vc.x ) - ( vb.x - vc.x ) * ( va.y - vc.y ) );
    float beta = num * deno;
    float gama = 1 - alphe - beta;
    return Vector3f( alphe , beta , gama );
}

static bool inTrangle(const Vector3f p , const Vector3f va , const Vector3f vb , const Vector3f vc ){
    Vector3f barycoord = barycentricCoord( p , va , vb , vc );
    
    if(barycoord.x > 0 && barycoord.y > 0 && barycoord.z >0)       
        return true; 
    else
        return false;
}

static bool inTrangleUseCross( const Vector3f p , const Vector3f va , const Vector3f vb , const Vector3f vc ){
    auto cross1 = Cross(( p - va ) , ( vb - va ) );
    auto cross2 = Cross(( p - vb ) , ( vc - vb ) );
    auto cross3 = Cross(( p - vc ) , ( va - vc ) );
    return bool( ( Dot( cross1 , cross2 )>=0 && Dot( cross2 , cross3 )>=0 && Dot( cross3 , cross1 )>=0 )||
    ( Dot( cross1 , cross2 )<=0 && Dot( cross2 , cross3 )<=0 && Dot( cross3 , cross1 )<=0 ) );
}

Matrix4f getModelMat4(Vector3f axis ,float rotation_angle , float _translate , float _scale);

Matrix4f getModelMat4(Vector3f axis ,float rotation_angle , Vector3f _translate , Vector3f _scale);

Matrix4f getViewMat4(Vector3f pos ,Vector3f lookAtDir , Vector3f upDir);

Matrix4f getProMat4( float aspect , float fovY , float zNear , float zFar );


static unsigned char *readBmp(const char *bmpName)
{
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
	
	return pBmpBuf;
}


static bool saveBmp(const char *bmpName, unsigned char *imgBuf, int width, int height, 
			 int biBitCount, RGBQUAD *pColorTable)
{//https://blog.csdn.net/yuupengsun/article/details/105983528?spm=1001.2101.3001.6661.1&depth_1-
	//如果位图数据指针为0,则没有数据传入,函数返回
	if(!imgBuf)
		return 0;
	
	//颜色表大小,以字节为单位,灰度图像颜色表为1024字节,彩色图像颜色表大小为0
	int colorTablesize=0;
	if(biBitCount==8)
		colorTablesize=1024;
 
	//待存储图像数据每行字节数为4的倍数
	int lineByte=(width * biBitCount/8+3)/4*4;
	
	//以二进制写的方式打开文件
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0) return 0;
	
	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型
	
	//bfSize是图像文件4个组成部分之和
	fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
		+ colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	
	//bfOffBits是图像文件前三个部分所需空间之和
	fileHead.bfOffBits=54+colorTablesize;
	
	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
	
	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head; 
	head.biBitCount=biBitCount;
	head.biClrImportant=0;
	head.biClrUsed=0;
	head.biCompression=0;
	head.biHeight=height;
	head.biPlanes=1;
	head.biSize=40;
	head.biSizeImage=lineByte*height;
	head.biWidth=width;
	head.biXPelsPerMeter=0;
	head.biYPelsPerMeter=0;
	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
	
	//如果灰度图像,有颜色表,写入文件 
	if(biBitCount==8)
		fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
	
	//写位图数据进文件
	fwrite(imgBuf, height*lineByte, 1, fp);
	
	//关闭文件
	fclose(fp);
	
	return 1;
}

static Vector2f interpolate(float alpha, float beta, float gamma, const Vector2f& vert1, const Vector2f& vert2, const Vector2f& vert3, float weight)
{
    auto u = (alpha * vert1.x + beta * vert2.x + gamma * vert3.x);
    auto v = (alpha * vert1.y + beta * vert2.y + gamma * vert3.y);

    u /= weight;
    v /= weight;

    return Vector2f(u, v);
}

static Vector3f interpolate(float alpha, float beta, float gamma, const Vector3f& vert1, const Vector3f& vert2, const Vector3f& vert3, float weight)
{
    return (vert1 *alpha +  vert2 * beta + vert3 * gamma ) / weight;
}

static Vector3f interpolate( Vector3f baryCoord , const Vector3f& vert1, const Vector3f& vert2, const Vector3f& vert3, float weight)
{
    return (vert1 *baryCoord.x +  vert2 * baryCoord.y + vert3 * baryCoord.z ) / weight;
}
static Vector3f interpolate( Vector3f baryCoord , const Vector3f verts[3],  float weight)
{
    return (verts[0] *baryCoord.x +  verts[1] * baryCoord.y + verts[2] * baryCoord.z ) / weight;
}

static int wiseInt( float v){ 
    if(v > 0)
        return v - int(v) > 0.5 ? int(v) + 1 : int(v) ;
    else
        return 0;
}

static int get2pow( unsigned x ){
    switch (x)
    {
    case 1: return 0;
    case 2: return 1;  
    case 4: return 2;
    case 8: return 3;
    case 16: return 4;
    case 32: return 5;
    case 64: return 6;
    case 128: return 7;
    case 256: return 8;
    case 512: return 9;
    case 1024: return 10;
    case 2048: return 11;
    case 4096: return 12;
    case 8192: return 13;
    case 16384:return 14;
    case 32768: return 15;
    case 65536: return 16;
    case 131072: return 17;
    case 262144: return 18;
    case 524288: return 19;
    case 1048576: return 20;
    default:
        LOG("Texture too big! or illegal width height...");
        return -1;
    }

}

static bool checkCanUseMips(const int &width ,const int &height){
    if ( width < 0 || height < 0) {                                                           
        LOG("Runtime Error.Texture's height or weight illegal!");
        enableMIPMAP = false;
        return false;                                                                                      
    }                                                                            
    if ( !(width & (width-1))==0 || !(height & (height-1))==0 ) {
        enableMIPMAP = false;                                     
        LOG("Runtime Error.Texture's height or weight not 2^n!");
        return false;                                                                                  
    }
    return true;
}

static float CaculateMipMapLeve(int &w , int &h , Vector3f &point ,Vector2f tex_coords[3],Vector4f v[3] ){
    float onestep= 0.5;
    if(enableMSAA)
        onestep = 1/MSAA;
    auto c1 = barycentricCoord(Vector3f(point.x - onestep , point.y - onestep,1.0),v[0].toVec3f(),v[1].toVec3f(),v[2].toVec3f());
    auto c2 = barycentricCoord(Vector3f(point.x + onestep , point.y - onestep,1.0),v[0].toVec3f(),v[1].toVec3f(),v[2].toVec3f());
    auto c3 = barycentricCoord(Vector3f(point.x + onestep , point.y + onestep,1.0),v[0].toVec3f(),v[1].toVec3f(),v[2].toVec3f());
    auto t1 = tex_coords[0] * c1.x + tex_coords[1] * c1.y + tex_coords[2] * c1.z;
    auto t2 = tex_coords[0] * c2.x + tex_coords[1] * c2.y + tex_coords[2] * c2.z;
    auto t3 = tex_coords[0] * c3.x + tex_coords[1] * c3.y + tex_coords[2] * c3.z;
    //std::cout<<"["<<t1.x*w << " "<<t1.y*h<<"]["<<" "<<t2.x*w << " "<<t2.y*h<<"]["<<t3.x*w << " "<<t3.y*h<<"][";  
    float what = std::max(Distance( t1 , t2 )*w , Distance(t2,t3)*h);
    return  std::log2(std::max(what,1.0f));//mipmap use for big texture , if its small .its go wrong!
}