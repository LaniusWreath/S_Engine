/*
1. wWinMain은 프로그램 진입점입니다. 프로그램이 시작되면 애플리케이션 창의 동작에 대한 일부 정보를 등록합니다. 
   가장 중요한 항목 중 하나는 이 예제에서 이름이 WindowProc인 함수의 주소입니다. 
   이 함수는 창의 모양, 사용자와 상호 작용하는 방식 등 창의 동작을 정의합니다.
2. 다음으로 프로그램은 창을 만들고 창을 고유하게 식별하는 핸들을 받습니다.
3. 창이 성공적으로 만들어지면 프로그램은 while 루프를 입력합니다. 
   프로그램은 사용자가 창을 닫고 애플리케이션을 종료할 때까지 이 루프에 남아 있습니다.

*/



// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "iostream";
#include "framework.h"
#include "Editor_Window.h"
#include "CommonInclude.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다. 2Byte
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다. 


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// 윈도우 진입점 : 표준 함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 인스턴스 핸들 : 메모리에서 실행파일 정의 유도, 타겟 메모리 제한
                     _In_opt_ HINSTANCE hPrevInstance,  // 의미 없음
                     _In_ LPWSTR    lpCmdLine,  // 명령행으로 입력된 프로그램 인수, 문자열
                     _In_ int       nCmdShow)   // 프로그램이 실행될 형태, 최대,최소 정상 표시 여부 플래그
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); // 윈도우 클래스 정보 정의

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;    // 메시지 구조체 생성

    // 기본 메시지 루프입니다:
    // 끌 때 까지 무한 반복 메시지 루프, 사용자 입력 대기 -> 메세지 함수 실행 : 메세지 하나 씩 입력 받아 처리
    // 창 프로시저가 실행되는 동안 동일한 스레드에서 만든 창에 대한 다른 모든 메시지를 차단합니다
     
    /*while (GetMessage(&msg, nullptr, 0, 0))   // 메시지 객체에 데이터 채움
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/

    /*
    * 운영 체제는 메시지 큐에 WM_LBUTTONDOWN 메시지를 배치합니다.
        프로그램에서 GetMessage 함수를 호출합니다 .
        GetMessage는 큐에서 WM_LBUTTONDOWN 메시지를 끌어와 MSG 구조체를 채웁니다.
        프로그램에서 TranslateMessage 및 DispatchMessage 함수를 호출합니다.
        DispatchMessage 내에서 운영 체제는 창 프로시저를 호출합니다.
        창 프로시저는 메시지에 응답하거나 무시할 수 있습니다.

        기본 구조는 GetMessage() or PeekMessage() -> TranslateMessage -> DispatchMessage
        "메시지 게시" : 메시지가 메시지 큐로 이동 -> 메시지 루프 및 dispatch
        "메시지 보내기" : 메시지가 메시지 큐를 건너 뛰고, os가 창 프로시저 직접 호출
    */

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg); // 키 입력 문자로 변환, DispatchMessage 이전에 쌍으로 호출
                DispatchMessage(&msg);  // 운영 체제에 메시지의 대상인 창의 창 프로시저를 호출하도록 지시
            }
        }
        
        else
        {
            // 로직 실행
        }
        
        if (msg.message == WM_QUIT)
        {
            break;
        }
    }

    return (int) msg.wParam;
}



// 윈도우 클래스 구조체
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    wcex.lpszClassName  = szWindowClass;    // 메모리에 윈도우 이름 등록
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // 운영체제에 창 클래스를 전달. 이대로 메모리에 등록할꺼야
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에(메모리에) 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 새 창 인스턴스 만들기
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,   // 클래스 이름, 창 제목 텍스트, 윈도우 종류, 시작 위치xy, 해상도xy
      CW_USEDEFAULT, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);   

   HWND hWnd1 = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,   
       CW_USEDEFAULT, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)   // 윈도우 객체 이상 있을 시 리턴
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);  // 윈도우 화면에 호출
   UpdateWindow(hWnd);  // 윈도우 초기화

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
// 윈도우 메세지에 함수 할당, 윈도우 프로시저
void OnSize(HWND hwnd, UINT flag, int width, int height)
{
    bool isStoped = true;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // 윈도우 핸들, 메시지, 창 크기 조정 확인 플래그, 새 창 규격
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            //DC 객체
            HDC hdc = BeginPaint(hWnd, &ps);
            // 브러쉬 객체 
            HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
            // SelectObject : 객체에 brush 적용, 적용 이전 사용하던 브러쉬 객체 리턴 가능
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
            
            // 사각형 그리기
            Rectangle(hdc, 100, 100, 200, 200);

            // 객체에 Brush 적용
            SelectObject(hdc, oldBrush);
            // 브러쉬 다 썼으면 객체 삭제. 메세지 함수가 계속 반복되기 때문에 Brush 객체 적용 함수가 힙에 계속 남아있음
            DeleteObject(brush);

            // 선 객체 생성 및 적용
            HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
            HPEN OldPen = (HPEN)SelectObject(hdc, redPen);

            // 원 그리기
            Ellipse(hdc, 200, 200, 300, 300);
            
            // 다 썼다면 삭제
            SelectObject(hdc, OldPen);
            DeleteObject(redPen);

            HBRUSH grayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
            oldBrush = (HBRUSH)SelectObject(hdc, grayBrush);
            Rectangle(hdc, 400, 400, 500, 500);
            DeleteObject(grayBrush);


            // DC : 화면 출력에 필요한 모든 정보를 가지는 데이터 구조체
            // GDI 모듈에 의해서 관리됨
            // 어떤 폰트? 어떤 선의 굵기? 어떤 색상으로 그려줌?
            // 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행
            //
            //

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_MOVE:
    {
        int a = 0;
    }
        break;

    case WM_SIZE:
    {
        int width = LOWORD(lParam); // low-order word get 매크로
        int height = HIWORD(lParam); // high-order word get 매크로

        // 메시지 Respond
        OnSize(hWnd, int(wParam), width, height);
    }
    case WM_CLOSE:
        if (MessageBox(hWnd, L"Really quit?", L"My application",
            MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hWnd);
        }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
