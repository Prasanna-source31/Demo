#include<windows.h>
HWND staticW = NULL;
int posX = 0;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    

    switch (uMsg) {
        case WM_CREATE: {
            SCROLLINFO si;
            si.cbSize = sizeof(si);
            si.nPos = 0;
            si.nMax = 800;
            si.nPage = 400;
            si.fMask = SIF_ALL;
            si.nMin = 0;
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
        }break;
        case WM_HSCROLL: {
            SCROLLINFO si;
            si.cbSize = sizeof(si);
            GetScrollInfo(hwnd, SB_HORZ, &si);
            switch (LOWORD(wParam)) {
                case SB_LINELEFT: {
                    si.nPos -= 5;
                }break;
                case SB_LINERIGHT: {
                    si.nPos += 5;
                }break;
                case SB_THUMBTRACK: {
                    si.nPos = HIWORD(wParam);
                }break;
            };
            SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
            posX = -si.nPos;
            MoveWindow(
                staticW,
                posX,
                0,
                800,
                50,
                TRUE
            );
        }break;
                     
    };
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	
	const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Sample Window Class";
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(0,
        wc.lpszClassName,                     // Window class
        "Algolancer Tutorial",    // Window text
        WS_OVERLAPPED,            // Window style

        // Size and position
        100, 100, 400, 200,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );
    staticW = CreateWindowEx(0,
        "STATIC",                     // Window class
        "text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text ",    // Window text
        WS_CHILD|WS_VISIBLE,            // Window style

        // Size and position
        posX, 0, 800, 50,

        hwnd,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );
    
    ShowWindow(hwnd, nCmdShow);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}