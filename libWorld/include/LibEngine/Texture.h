#pragma once

namespace LibEngine
{
    // ����ӿ�;
    struct ITexture
    {
        virtual ~ITexture(){};
        virtual void    Release() = 0;
        
        virtual UINT    GetWidth()  const = 0;
        virtual UINT    GetHeight() const = 0;
    };

}


