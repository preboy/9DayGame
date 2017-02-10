#pragma once

namespace Console
{
	void DisableCloseButton()
	{
		char buf[MAX_PATH];
		memset(buf, 0, sizeof(buf));
		GetConsoleTitleA(buf, sizeof(buf));
		HWND	hWnd	= FindWindowA(NULL, buf);
		HMENU	hMenu	= GetSystemMenu(hWnd, FALSE);
		RemoveMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
		DrawMenuBar(hWnd);
	}

	BOOL CtrlHandler( DWORD fdwCtrlType ) 
	{ 
		switch( fdwCtrlType ) 
		{
		case CTRL_C_EVENT: 
			Beep( 750, 300 ); 
			return TRUE;
			break;

		case CTRL_CLOSE_EVENT: 
			Beep( 600, 200 ); 
			return	TRUE; 
			break;

		case CTRL_BREAK_EVENT: 
			Beep( 900, 200 ); 
			return TRUE; 
			break;

		case CTRL_LOGOFF_EVENT: 
			Beep( 1000, 200 ); 
			return FALSE; 
			break;

		case CTRL_SHUTDOWN_EVENT: 
			Beep( 750, 500 ); 
			return FALSE; 
			break;

		default: 
			return FALSE; 
		} 
	} 
}

