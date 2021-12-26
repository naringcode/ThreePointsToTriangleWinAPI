#include "framework.h"
#include "Application.h"

#include "Util/Renderer.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HWND    g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_THREEPOINTSTOTRIANGLEWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THREEPOINTSTOTRIANGLEWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)
    {
       return FALSE;
    }

    RECT rt;
    GetClientRect(g_hWnd, &rt);

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT s_P1;
    static POINT s_P2;
    static POINT s_P3;

    static bool s_IsClicked = false;
    static int  s_ClickCnt  = -1;

    switch (message)
    {
        case WM_LBUTTONDOWN:
        {
            s_IsClicked = true;

            s_ClickCnt = (s_ClickCnt + 1) % 3;

            if (0 == s_ClickCnt)
            {
                s_P1.x = LOWORD(lParam);
                s_P1.y = HIWORD(lParam);
            }
            else if (1 == s_ClickCnt)
            {
                s_P2.x = LOWORD(lParam);
                s_P2.y = HIWORD(lParam);
            }
            else if (2 == s_ClickCnt)
            {
                s_P3.x = LOWORD(lParam);
                s_P3.y = HIWORD(lParam);
            }

            InvalidateRect(hWnd, nullptr, TRUE);

            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc;
            
            hdc = BeginPaint(hWnd, &ps);
            {
                if (true == s_IsClicked)
                {
                    if (0 == s_ClickCnt)
                    {
                        Ellipse(hdc, s_P1.x - 10, s_P1.y - 10, s_P1.x + 10, s_P1.y + 10);
                    }
                    else if (1 == s_ClickCnt)
                    {
                        DrawLine(hdc, s_P1.x, s_P1.y, s_P2.x, s_P2.y);

                        Ellipse(hdc, s_P1.x - 10, s_P1.y - 10, s_P1.x + 10, s_P1.y + 10);
                        Ellipse(hdc, s_P2.x - 10, s_P2.y - 10, s_P2.x + 10, s_P2.y + 10);
                    }
                    else if (2 == s_ClickCnt)
                    {
                        DrawTriangle(hdc, s_P1.x, s_P1.y, s_P2.x, s_P2.y, s_P3.x, s_P3.y);

                        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

                        Ellipse(hdc, s_P1.x - 10, s_P1.y - 10, s_P1.x + 10, s_P1.y + 10);
                        Ellipse(hdc, s_P2.x - 10, s_P2.y - 10, s_P2.x + 10, s_P2.y + 10);
                        Ellipse(hdc, s_P3.x - 10, s_P3.y - 10, s_P3.x + 10, s_P3.y + 10);

                        SelectObject(hdc, hOldBrush);
                    }
                }
            }
            EndPaint(hWnd, &ps);
            
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);

            break;
        }

        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
}
