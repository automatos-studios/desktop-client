/*
* ---------------------------------------------------------
* Copyright 2018-present (c) Automatos Studios. All Rights Reserved.
* ---------------------------------------------------------
*/

/**
* @file			softStudio.cpp : Defines the entry point for the application (FOR NOW WINDOWS ONLY).
* @author		cosmoplankton < cosmoplankton@automatos.studio >
*/



#include "../source/devicemanager/Idevice.h"
#include "../source/devicemanager/IgraphicsAppManager.h"
#include "../source/devicemanager/IcomputeAppManager.h"

#include "../source/appManager.h"


#ifdef _WIN32


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    int error = FALSE;
    
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MyRegisterClass(hInstance);

    // Perform application initialization:
    // if (app::Manager< app::WinApp >().initializeApplication(hInstance))
    if (app::APPLICATION< app::WinApp >::get().initializeApplication(hInstance))
    {
        return error;
    }

    int height = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER);
    app::APPLICATION< app::WinApp >::get().setTitleBarHeight(height);


    // Start application event-loop
    try
    {
        error = app::APPLICATION< app::WinApp >::get().startEventLoop();
    }
    catch (const std::exception& e)
    {
        // app::APPLICATION< app::WinApp >::EXCEPTION(e); // #improvement - handle and try to recover.
        app::APPLICATION< app::WinApp >::destroy();
        error = FALSE;
    }
    
    return error;
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
    LoadStringW(hInstance, IDC_WINDOWSAPP, szWindowClass, MAX_LOADSTRING);

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSAPP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSAPP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int height = app::APPLICATION< app::WinApp >::get().getTitleBarHeight();

    POINT mousePos;
    GetCursorPos(&mousePos);
    ux::UxEventInfo eventInfo;
    eventInfo.mouseX = mousePos.x;
    eventInfo.mouseY = mousePos.y;
    
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        app::APPLICATION< app::WinApp >::get().setUxEventInfo(eventInfo);
    }
    break;
    case WM_SIZE:
        app::APPLICATION< app::WinApp >::get().setUxEventInfo(eventInfo);
        if (wParam != SIZE_MINIMIZED)
        {
            app::APPLICATION< app::WinApp >::get().setAppWidth(LOWORD(lParam));
            app::APPLICATION< app::WinApp >::get().setAppHeight(HIWORD(lParam));
            app::APPLICATION< app::WinApp >::get().appResize();
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        app::APPLICATION< app::WinApp >::destroy();
        break;
    case WM_LBUTTONDOWN:
        eventInfo.event = ux::UxEventType::UX_EVENT_MOUSE_L_DOWN;
        eventInfo.mouseX = GET_X_LPARAM(lParam);
        eventInfo.mouseY = GET_Y_LPARAM(lParam);
        app::APPLICATION< app::WinApp >::get().setUxEventInfo(eventInfo);
        break;
    case WM_RBUTTONDOWN:
        eventInfo.event = ux::UxEventType::UX_EVENT_MOUSE_R_DOWN;
        eventInfo.mouseX = GET_X_LPARAM(lParam);
        eventInfo.mouseY = GET_Y_LPARAM(lParam);
        app::APPLICATION< app::WinApp >::get().setUxEventInfo(eventInfo);
        break;
    case WM_MOUSEMOVE:
        eventInfo.event = ux::UxEventType::UX_EVENT_MOUSE_MOVE;
        eventInfo.mouseX = GET_X_LPARAM(lParam);
        eventInfo.mouseY = GET_Y_LPARAM(lParam);
        app::APPLICATION< app::WinApp >::get().setUxEventInfo(eventInfo);
        break;
    case WM_LBUTTONDBLCLK:
        eventInfo.event = ux::UxEventType::UX_EVENT_MOUSE_L_DBLCLICK;
        eventInfo.mouseX = GET_X_LPARAM(lParam);
        eventInfo.mouseY = GET_Y_LPARAM(lParam);
        app::APPLICATION< app::WinApp >::get().setUxEventInfo(eventInfo);
        break;
    default:
        app::APPLICATION< app::WinApp >::get().setUxEventInfo(eventInfo);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



#endif // !_WIN32