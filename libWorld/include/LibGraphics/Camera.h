#pragma once

#include <d3dx10math.h>

namespace LibGraphics
{
    class Camera
    {
    public:
        Camera();
        Camera(const Camera&);
        ~Camera();

        void SetPosition(float, float, float);
        void SetRotation(float, float, float);

        void Render();
        void GetViewMatrix(D3DXMATRIX&);

    private:
        D3DXMATRIX m_viewMatrix;
        float m_positionX, m_positionY, m_positionZ;
        float m_rotationX, m_rotationY, m_rotationZ;
    };

}
