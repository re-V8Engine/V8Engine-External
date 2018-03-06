#include "stdafx.h"

LRESULT CALLBACK tOverlayWindow::tOverlayWindowFunctions::WndProc(HWND Handle, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
        {
        case WM_PAINT:
        {
            pESP.Functions.Tick();
        }
		case WM_ERASEBKGND:
		{
			return 0;
		}
        default:
        {
            return DefWindowProc(Handle, Message, wParam, lParam);
        }
        }
}

int tOverlayWindow::tOverlayWindowFunctions::GetRandomInt()
{
    std::random_device Random;
    std::mt19937 RandomGenerator(Random());
    std::uniform_int<int> RandomDistribute(0, 1000);
    return RandomDistribute(RandomGenerator);
}

bool tOverlayWindow::tOverlayWindowFunctions::Setup()
{
    ZeroMemory(&pOverlayWindow.Class, sizeof(pOverlayWindow.Class));
    pOverlayWindow.Class.cbSize = sizeof(pOverlayWindow.Class);
    pOverlayWindow.Class.hInstance = GetModuleHandle(NULL);
    pOverlayWindow.Class.lpfnWndProc = pOverlayWindow.Functions.WndProc;
	std::wstring WindowName = pGlobalVars.OverlayWindowSettings.OverlayWindowName.append(L" - ").append(std::to_wstring(GetRandomInt()));
	pOverlayWindow.Class.lpszClassName = WindowName.c_str();
    pOverlayWindow.Class.style = CS_HREDRAW | CS_VREDRAW;
    pOverlayWindow.Class.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    if (RegisterClassEx(&pOverlayWindow.Class))
        {
            pOverlayWindow.Handle = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, pOverlayWindow.Class.lpszClassName, pOverlayWindow.Class.lpszClassName, WS_POPUP, pOverlayWindow.X, pOverlayWindow.Y, pOverlayWindow.Width, pOverlayWindow.Height, NULL, NULL, pOverlayWindow.Class.hInstance, NULL);
            if (pOverlayWindow.Handle)
                {
                    SetLayeredWindowAttributes(pOverlayWindow.Handle, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);
                    ShowWindow(pOverlayWindow.Handle, 1);
                    MARGINS Margin = { -1, -1, -1, -1 };
                    DwmExtendFrameIntoClientArea(pOverlayWindow.Handle, &Margin);
                    HWND WinHandle = FindWindow(NULL, pGlobalVars.OverlayWindowSettings.ReferenceWindowName.c_str());
                    if (WinHandle)
                        {
                            if (IsWindowVisible(WinHandle))
                                {
                                    GetClientRect(WinHandle, &pOverlayWindow.Bounds);
                                    pOverlayWindow.Width = pOverlayWindow.Bounds.right - pOverlayWindow.Bounds.left;
                                    pOverlayWindow.Height = pOverlayWindow.Bounds.bottom - pOverlayWindow.Bounds.top;
                                    ZeroMemory(&pOverlayWindow.Bounds, sizeof(pOverlayWindow.Bounds));
                                    GetWindowRect(WinHandle, &pOverlayWindow.Bounds);
                                    pOverlayWindow.X = pOverlayWindow.Bounds.left;
                                    pOverlayWindow.Y = pOverlayWindow.Bounds.top;
                                    SetWindowPos(pOverlayWindow.Handle, HWND_TOPMOST, pOverlayWindow.X, pOverlayWindow.Y, pOverlayWindow.Width, pOverlayWindow.Height, NULL);
                                    return true;
                                }
                        }
                }
        }
    return false;
}

void tOverlayWindow::tOverlayWindowFunctions::Refresh()
{
    if (pOverlayWindow.Handle)
        {
            InvalidateRect(pOverlayWindow.Handle, NULL, false);
			if (PeekMessage(&pOverlayWindow.Message, pOverlayWindow.Handle, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&pOverlayWindow.Message);
                    DispatchMessage(&pOverlayWindow.Message);
                }
        }
    else
        {
            if (pOverlayWindow.Functions.Setup())
                {
                    if (!pD3D.Functions.Setup())
                        {
                            MessageBox(NULL, L"Failed to setup D3D.", L"Error", MB_OK);
                        }
                }
            else
                {
                    MessageBox(NULL, L"Failed to setup overlay window.", L"Error", MB_OK);
                }
        }
}

void tOverlayWindow::tOverlayWindowFunctions::Destruct()
{
    DestroyWindow(pOverlayWindow.Handle);
    UnregisterClass(pOverlayWindow.Class.lpszClassName, pOverlayWindow.Class.hInstance);
}