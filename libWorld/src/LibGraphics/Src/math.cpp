#include "stdafx.h"
#include "LibGraphics/math.h"

#include <algorithm>
using namespace std;

namespace LibGraphics
{

    skyPoint2D::skyPoint2D()
    {
        x = y = 0;
    }

    skyPoint2D::skyPoint2D(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    skyPoint3D::skyPoint3D()
    {
        x = y = z = 0;
    }

    skyPoint3D::skyPoint3D(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    skyRect::skyRect()
    {
        x = y = w = h = 0;
    }

    skyRect::skyRect(int _x, int _y, unsigned int _w, unsigned int _h)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    //skyRect::skyRect( int px1, int py1, int px2, int py2)
    //{
    //    x = std::min<int>(px1, px2);
    //    y = std::min<int>(py1, py2);
    //    w = std::max<int>(px1, px2) - x;
    //    h = std::max<int>(py1, py2) - y;
    //}

    skyPoint2D skyRect::getLeftUp() const
    {
        skyPoint2D pt(x, y);
        return pt;
    }

    skyPoint2D skyRect::getLeftDown() const
    {
        skyPoint2D pt(x, y+h);
        return pt;
    }

    skyPoint2D skyRect::getRightUp() const
    {
        skyPoint2D pt(x+w, y);
        return pt;
    }

    skyPoint2D skyRect::getRightDown() const
    {
        skyPoint2D pt(x+w, y+h);
        return pt;
    }


    skyRectF::skyRectF()
    {
        leftUp_x = leftUp_y = rightDown_x = rightDown_y = .0f;
    }

    skyRectF::skyRectF(float _leftUp_x, float _leftUp_y, float _rightDown_x, float _rightDown_y)
    {
        leftUp_x = _leftUp_x;   rightDown_x = _rightDown_x;
        leftUp_y = _leftUp_y;   rightDown_y = _rightDown_y;
    }
    
}