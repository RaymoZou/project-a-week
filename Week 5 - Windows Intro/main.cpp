#include <d2d1.h>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM laparam);

const int UPDATE_TIME = 1;
const int WINDOW_LENGTH = 200;
const int WINDOW_HEIGHT = 200;
const int X_MAX = GetSystemMetrics(SM_CXSCREEN);
const int X_MIN = 0;
const int Y_MAX = GetSystemMetrics(SM_CYSCREEN);
const int Y_MIN = 0;
int X_VELOCITY = 10;
int Y_VELOCITY = 10;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PWSTR pCmdLine,
                    int nCmdShow) {
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Testing";
    if (!RegisterClassW(&wc)) return -1;

    HWND hwnd = CreateWindowW(wc.lpszClassName, L"Cool Window Name",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0,
                              WINDOW_LENGTH, WINDOW_HEIGHT, 0, 0, hInstance, 0);
    if (!hwnd) return -1;

    SetTimer(hwnd, 0, UPDATE_TIME, 0);

    MSG msg = {};
    while (GetMessageW(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };

    return 0;
};

int MoveWindow(HWND hwnd) {
    RECT currPos = {};
    if (GetWindowRect(hwnd, &currPos) == 0) return -1;
    if (currPos.bottom + Y_VELOCITY > Y_MAX | currPos.top + Y_VELOCITY < Y_MIN) {
        Y_VELOCITY = -Y_VELOCITY;
    };
    if (currPos.right + X_VELOCITY > X_MAX | currPos.left + X_VELOCITY < X_MIN) {
        X_VELOCITY = -X_VELOCITY;
    }

    int newY = currPos.top + Y_VELOCITY;
    int newX = currPos.left + X_VELOCITY;

    // bottom boundary
    SetWindowPos(hwnd, 0, newX, newY, WINDOW_LENGTH, WINDOW_HEIGHT, 0);

    return 0;
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_TIMER: {
            MoveWindow(hwnd);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT: {
            // create PAINTSTRUCT
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            LOGBRUSH logBrush;
            logBrush.lbStyle = BS_SOLID;
            logBrush.lbColor = 0x00AF8558;
            logBrush.lbHatch = 0;  // what is this
            HBRUSH hbr = CreateBrushIndirect(&logBrush);
            FillRect(hdc, &ps.rcPaint, hbr);

            EndPaint(hwnd, &ps);
            OutputDebugStringW(L"W_PAINT\n");
            break;
        }
        default:
            return DefWindowProcW(hwnd, msg, wparam, lparam);
            break;
    };
    return 0;
};
