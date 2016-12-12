/*
 * Copyright (c) 2015-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// spimidikeyboard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
using namespace std;

#include "spiutility.h"

/*
/////////////////////////////////////
//include all headers related to midi
/////////////////////////////////////
#include "portmidi.h"
#include "porttime.h"
#include "spimidi.h"
*/

string global_begin = "begin.ahk";
string global_end = "end.ahk";


#include <iostream>
#include <windows.h>
#include <stdio.h>

HHOOK hKeyboardHook;

bool alreadydown_AtoZ = false;
bool alreadydown_0to9 = false;
bool alreadydown_lshift = false;
bool alreadydown_capslock = false;
bool alreadydown_tab = false;
bool alreadydown_ascii96 = false; //`
bool alreadydown_backspace = false;
bool alreadydown_minus = false;
bool alreadydown_equals = false;
bool alreadydown_leftbrace = false;
bool alreadydown_rightbrace = false;
bool alreadydown_backslash = false;
bool alreadydown_semicolon = false;
bool alreadydown_apostrophe = false;
bool alreadydown_return = false;
bool alreadydown_comma = false;
bool alreadydown_period = false;
bool alreadydown_slash = false;
bool alreadydown_rshift = false;

__declspec(dllexport) LRESULT CALLBACK KeyboardEvent (int nCode, WPARAM wParam, LPARAM lParam)
{
    DWORD SHIFT_key=0;
    DWORD CTRL_key=0;
    DWORD ALT_key=0;
    DWORD LSHIFT_key=0;
    DWORD LCTRL_key=0;
    DWORD LALT_key=0;
    DWORD RSHIFT_key=0;
    DWORD RCTRL_key=0;
    DWORD RALT_key=0;

    DWORD LWIN_key=0;
    DWORD RWIN_key=0;
    DWORD APPS_key=0;


    if  ( (nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYUP) || (wParam == WM_KEYUP)) )      
    {
        KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);

        //spi, begin
		/*
		DWORD dwMsg = 1;
        dwMsg += hooked_key.scanCode << 16;
        dwMsg += hooked_key.flags << 24;
        char lpszKeyName[1024] = {0};

        int i = GetKeyNameTextA(dwMsg,   (lpszKeyName+1),0xFF) + 1;
		*/
		//spi, end

        int key = hooked_key.vkCode;
		DWORD extendedflag = hooked_key.flags & LLKHF_EXTENDED;
		DWORD upflag = hooked_key.flags & LLKHF_UP;

        SHIFT_key = GetAsyncKeyState(VK_SHIFT);
        CTRL_key = GetAsyncKeyState(VK_CONTROL);
        ALT_key = GetAsyncKeyState(VK_MENU);
        LSHIFT_key = GetAsyncKeyState(VK_LSHIFT);
        LCTRL_key = GetAsyncKeyState(VK_LCONTROL);
        LALT_key = GetAsyncKeyState(VK_LMENU);
        RSHIFT_key = GetAsyncKeyState(VK_RSHIFT);
        RCTRL_key = GetAsyncKeyState(VK_RCONTROL);
        RALT_key = GetAsyncKeyState(VK_RMENU);

		LWIN_key = GetAsyncKeyState(VK_LWIN);
		RWIN_key = GetAsyncKeyState(VK_RWIN);
		APPS_key = GetAsyncKeyState(VK_APPS);
        //printf("Keycode = %c\n",key);
		//spi, begin
		/*
		int bit4 = hooked_key.flags & 16;
		printf("bit4 = %d\n", bit4);
		int bit7 = hooked_key.flags & 128;
		printf("bit7 = %d\n", bit7);
		int bit30 = HIWORD(lParam) & KF_REPEAT;
		printf("bit30 = %d\n", bit30);
		*/
		//spi, end
        if (wParam == WM_SYSKEYDOWN)   
        {
			return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
		}
        else if ( (wParam == WM_KEYDOWN) && (key==VK_LSHIFT) )  //lshift
		{
			if(alreadydown_lshift) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_lshift=true;

			printf("Keydown = lshift\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==VK_CAPITAL) )  //caps lock 
		{
			if(alreadydown_capslock) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_capslock=true;

			printf("Keydown = capslock\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==VK_TAB) )  //tab 
		{
			if(alreadydown_tab) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_tab=true;

			printf("Keydown = tab\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==192) )  //` 
		{
			if(alreadydown_ascii96) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_ascii96=true;

			printf("Keydown = `\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key >= '0' && key <= '9') )   
        {
			if(alreadydown_0to9) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_0to9=true;

			printf("Keydown = %c\n",key);
			return 1;
		}
		else if ( (wParam == WM_KEYDOWN) && (key >= 'A' && key <= 'Z') )   
        {
			if(alreadydown_AtoZ) return 1; //CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_AtoZ=true;


            //if  (GetAsyncKeyState(VK_SHIFT)>= 0) key +=32;

            if (CTRL_key !=0 && key == 'Y' )
            {
               MessageBoxA(NULL, "CTRL-y was pressed\nLaunch your app here", "H O T K E Y", MB_OK); 
               //CTRL_key=0;

               //do stuff here

			   return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
            }

            if (CTRL_key !=0 && key == 'Q' )
            {
                //MessageBoxA(NULL, "Shutting down", "H O T K E Y", MB_OK); 
				//ShellExecuteA(NULL, "open", global_end.c_str(), "", NULL, 0);
               PostQuitMessage(0);
            }


			printf("Keydown = %c\n",key);
			return 1;
			/*
            SHIFT_key = 0;
            CTRL_key = 0;
            ALT_key = 0;
			LSHIFT_key=0;
			LCTRL_key=0;
			LALT_key=0;
			RSHIFT_key=0;
			RCTRL_key=0;
			RALT_key=0;
			*/
        }
        else if ( (wParam == WM_KEYDOWN) && (key==189) )  //minus with underscore 
		{
			if(alreadydown_minus) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_minus=true;

			printf("Keydown = minus\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==187) )  //equals with plus 
		{
			if(alreadydown_equals) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_equals=true;

			printf("Keydown = equal\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==VK_BACK) )  //backspace 
		{
			if(alreadydown_backspace) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_backspace=true;

			printf("Keydown = backspace\n");
			return 1;
		}

        else if ( (wParam == WM_KEYDOWN) && (key==219) )  //left brace 
		{
			if(alreadydown_leftbrace) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_leftbrace=true;

			printf("Keydown = leftbrace\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==221) )  //right brace 
		{
			if(alreadydown_rightbrace) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_rightbrace=true;

			printf("Keydown = rightbrace\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==220) )  //backslash 
		{
			if(alreadydown_backslash) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_backslash=true;

			printf("Keydown = backslash\n");
			return 1;
		}

        else if ( (wParam == WM_KEYDOWN) && (key==186) )  //semicolon 
		{
			if(alreadydown_semicolon) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_semicolon=true;

			printf("Keydown = semicolon\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==222) )  //apostrophe 
		{
			if(alreadydown_apostrophe) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_apostrophe=true;

			printf("Keydown = apostrophe\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==VK_RETURN) && (extendedflag==0) )  //return 
		{
			if(alreadydown_return) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_return=true;

			printf("Keydown = return\n");
			return 1;
		}

        else if ( (wParam == WM_KEYDOWN) && (key==188) )  //comma 
		{
			if(alreadydown_comma) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_comma=true;

			printf("Keydown = comma\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==190) )  //period 
		{
			if(alreadydown_period) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_period=true;

			printf("Keydown = period\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==191) )  //slash (forward slash) 
		{
			if(alreadydown_slash) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_slash=true;

			printf("Keydown = slash\n");
			return 1;
		}
        else if ( (wParam == WM_KEYDOWN) && (key==VK_RSHIFT) )  //rshift 
		{
			if(alreadydown_rshift) return 1;//CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
			  else alreadydown_rshift=true;

			printf("Keydown = rshift\n");
			return 1;
		}

        else if (wParam == WM_SYSKEYUP)   
        {
			return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
		}
        else if ( (wParam == WM_KEYUP) && (key==VK_LSHIFT) )  //lshift
		{
			alreadydown_lshift=true;

			printf("Keyup = lshift\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==VK_CAPITAL) )  //caps lock 
		{
			alreadydown_capslock=false;

			printf("Keyup = capslock\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==VK_TAB) )  //tab 
		{
			alreadydown_tab=false;

			printf("Keyup = tab\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==192) )  //` 
		{
			alreadydown_ascii96=false;

			printf("Keyup = `\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key >= '0' && key <= '9') )   
        {
			alreadydown_0to9= false;
			printf("Keyup = %c\n",key);
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key >= 'A' && key <= 'Z') )   
        {
			alreadydown_AtoZ= false;
			printf("Keyup = %c\n",key);
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==189) )  //minus with underscore 
		{
			alreadydown_minus=false;

			printf("Keyup = minus\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==187) )  //equals with plus 
		{
			alreadydown_equals=false;

			printf("Keyup = equal\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==VK_BACK) )  //backspace 
		{
			alreadydown_backspace=false;

			printf("Keyup = backspace\n");
			return 1;
		}

        else if ( (wParam == WM_KEYUP) && (key==219) )  //left brace 
		{
			alreadydown_leftbrace=false;

			printf("Keyup = leftbrace\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==221) )  //right brace 
		{
			alreadydown_rightbrace=false;

			printf("Keyup = rightbrace\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==220) )  //backslash 
		{
			alreadydown_backslash=false;

			printf("Keyup = backslash\n");
			return 1;
		}

        else if ( (wParam == WM_KEYUP) && (key==186) )  //semicolon 
		{
			alreadydown_semicolon=false;

			printf("Keyup = semicolon\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==222) )  //apostrophe 
		{
			alreadydown_apostrophe=false;

			printf("Keyup = apostrophe\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==VK_RETURN) && (extendedflag==0) )  //return 
		{
			alreadydown_return=false;

			printf("Keyup = return\n");
			return 1;
		}

        else if ( (wParam == WM_KEYUP) && (key==188) )  //comma 
		{
			alreadydown_comma=false;

			printf("Keyup = comma\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==190) )  //period 
		{
			alreadydown_period=false;

			printf("Keyup = period\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==191) )  //slash (forward slash) 
		{
			alreadydown_slash=false;

			printf("Keyup = slash\n");
			return 1;
		}
        else if ( (wParam == WM_KEYUP) && (key==VK_RSHIFT) )  //rshift 
		{
			alreadydown_rshift=false;

			printf("Keyup = rshift\n");
			return 1;
		}

	}
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void MessageLoop()
{
    MSG message;
    while (GetMessage(&message,NULL,0,0)) 
    {
        TranslateMessage( &message );
        DispatchMessage( &message );
    }
}

DWORD WINAPI my_HotKey(LPVOID lpParm)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    if (!hInstance) hInstance = LoadLibraryA((LPCSTR) lpParm); 
    if (!hInstance) return 1;

    hKeyboardHook = SetWindowsHookEx (  WH_KEYBOARD_LL, (HOOKPROC) KeyboardEvent,   hInstance,  NULL    );
    MessageLoop();
    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}



int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread;
    DWORD dwThread;

    printf("CTRL-y  for  H O T K E Y  \n");
    printf("CTRL-q  to quit  \n");

    hThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)   my_HotKey, (LPVOID) argv[0], NULL, &dwThread);

       /* uncomment to hide console window */
    //ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);

    if (hThread) 
	{
		DWORD dwReturn;

		int nShowCmd = false;
		//ShellExecuteA(NULL, "open", "begin.bat", "", NULL, nShowCmd);
		ShellExecuteA(NULL, "open", global_begin.c_str(), "", NULL, nShowCmd);

		//////////////////////////
		//initialize random number
		//////////////////////////
		//srand((unsigned)time(0));
		srand((unsigned int)GetTickCount());

		dwReturn = WaitForSingleObject(hThread,INFINITE);

		ShellExecuteA(NULL, "open", global_end.c_str(), "", NULL, nShowCmd);

		return dwReturn;
	}
    else return 1;




	//ShellExecuteA(NULL, "open", global_end.c_str(), "", NULL, nShowCmd);
	return 0;
}

