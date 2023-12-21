#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_TIMER:
            OutputDebugStringW(L"Testing");
    };
    return DefWindowProcW(hwnd, msg, wparam, lparam);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
    WNDCLASSW wc = {0};
    wc.lpfnWndProc = &WindowProc;
    wc.lpszClassName = L"Testing";

    RegisterClassW(&wc);
    HWND hwnd = CreateWindowW(wc.lpszClassName, L"Cool Window Name",
                              WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 800,
                              0, 0, hInstance, 0);
    if (!hwnd) return -1;

    // SetTimer(hwnd, 0, 1000, 0);

    MSG msg = {};
    while (GetMessageW(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };
    return 0;
};