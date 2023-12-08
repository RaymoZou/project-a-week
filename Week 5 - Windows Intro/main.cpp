#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_LBUTTONDOWN:
            OutputDebugStringW(L"What up");
            break;
        case WM_TIMER:
            OutputDebugStringW(L"Timer has expired....");
            // SetWindowPos(hwnd, 0, 100, 100, 300, 300, 0);
            RECT dimensions;
            GetWindowRect(hwnd, &dimensions);
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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PWSTR pCmdLine,
                    int nCmdShow) {
    WNDCLASSW wc = {};
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Testing";

    // RegisterClassW will return 0 if function call fails
    if (!RegisterClassW(&wc)) {
        MessageBoxW(NULL, L"Window Registration Failed!", L"ERROR",
                    MB_ICONEXCLAMATION | MB_OK);
        return 0;
    };

    // Create Window (CreateWindowW)
    HWND hwnd = CreateWindowW(wc.lpszClassName, L"Cool Window Name",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 800,
                              0, 0, hInstance, 0);

    if (hwnd == NULL) {
        MessageBoxW(NULL, L"Window Creation Failed", L"ERROR",
                    MB_ICONEXCLAMATION | MB_OK);
        return -1;
    };

    // Create a 3 second timer
    SetTimer(hwnd, 0, 1000, 0);

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessageW(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };

    return 0;
};
