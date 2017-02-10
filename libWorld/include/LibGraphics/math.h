#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

namespace LibGraphics
{

    // ������Ķ������꣬����2D��Ⱦ;
    struct SVertexTypeTexture
    {
        D3DXVECTOR3 position;
        D3DXVECTOR2 texture;
    };

    // ����ɫ�Ķ������꣬����ɫ�鼰�������Ⱦ;
    struct SVertexTypeColor
    {
        D3DXVECTOR3 position;
        D3DXCOLOR   color;
    };

    struct ConstantBufferType
    {
        D3DXMATRIX world;
        D3DXMATRIX view;
        D3DXMATRIX projection;
    };

    // 2D��
    class skyPoint2D
    {
    public:
        int x, y;

    public:
        skyPoint2D();
        skyPoint2D(int _x, int _y);
        ~skyPoint2D(){}
    };


    // 3D��
    class skyPoint3D
    {
    public:
        int x, y, z;

    public:
        skyPoint3D();
        skyPoint3D(int _x, int _y, int _z);
        ~skyPoint3D(){}
    };

    // ����;
    struct skyRect
    {
    public:
        int x, y;
        unsigned int w, h;

    public:
        skyRect();

        // һ����+����;
        skyRect(int _x, int _y, unsigned int _w, unsigned int _h);

        // ������������������;
        // skyRect( int px1, int py1, int px2, int py2);

        ~skyRect(){}

        skyPoint2D getLeftUp()      const;
        skyPoint2D getLeftDown()    const;
        skyPoint2D getRightUp()     const;
        skyPoint2D getRightDown()   const;

    };


    struct skyRectF
    {
    public:
        float leftUp_x, leftUp_y, rightDown_x, rightDown_y;

    public:
        skyRectF();
        skyRectF(float _leftUp_x, float _leftUp_y, float _rightDown_x, float _rightDown_y);
        ~skyRectF(){}
    };


}



