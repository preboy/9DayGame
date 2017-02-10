#include "stdafx.h"
#include "LibEngine/GuiManager.h"

#include "LibEngine/button.h"
#include "LibEngine/Static.h"
#include "LibEngine/EditBox.h"
#include "LibEngine/ListCtrl.h"
#include "LibEngine/CheckBox.h"
#include "LibEngine/Slider.h"
#include "LibEngine/form.h"

using namespace LibEngine;

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



