#include "stdafx.h"
#include "LibGraphics/GuiManager.h"

#include "LibGraphics/GUI/button.h"
#include "LibGraphics/GUI/Static.h"
#include "LibGraphics/GUI/EditBox.h"
#include "LibGraphics/GUI/ListCtrl.h"
#include "LibGraphics/GUI/CheckBox.h"
#include "LibGraphics/GUI/Slider.h"
#include "LibGraphics/GUI/form.h"

using namespace LibGraphics;

//#ifdef _DEBUG
//#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#endif


GuiManager::GuiManager()
{
    
}

GuiManager::~GuiManager()
{

}

bool GuiManager::Init()
{
    return true;
}

void GuiManager::Release()
{
}

Control* GuiManager::CreateControl(const char* pName)
{
    if(!pName) return nullptr;

    Control* pControl = nullptr;
    if(strcmp("Button", pName) == 0)
    {
        pControl = new Button();
    }
    else if (strcmp("Static", pName) == 0)
    {
        pControl = new Static();
    }
    else if (strcmp("EditBox", pName) == 0)
    {
        pControl = new EditBox();
    }
    else if(strcmp("ListCtrl", pName) == 0)
    {
        pControl = new ListCtrl();
    }
    else if(strcmp("CheckBox", pName) == 0)
    {
        pControl = new CheckBox();
    }
    else if(strcmp("RadioBox", pName) == 0)
    {
        pControl = new RadioBox;
    }
    else if(strcmp("Slider", pName) == 0)
    {
        pControl = new Slider;
    }

    return pControl;
}



