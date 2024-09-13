// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 인스턴스 핸들 : 타겟 메모리 제한
                     _In_opt_ HINSTANCE hPrevInstance,  // 이전 실행된 프로그램의 인스턴스 핸들, NULL
                     _In_ LPWSTR    lpCmdLine,  // 명령행으로 입력된 프로그램 인수
                     _In_ int       nCmdShow)   // 프로그램이 실행될 형태, 모양정보
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

    MSG msg;

    // 기본 메시지 루프입니다:
    // 끌 때 까지 무한 반복 메시지 루프, 사용자 입력 대기 -> 메세지 함수 실행
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
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

    return RegisterClassExW(&wcex);
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

   // 윈도우 인스턴스 핸들
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,   // 클래스 이름, 창 제목 텍스트, 윈도우 종류, 시작 위치xy, 해상도xy
      CW_USEDEFAULT, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);   

   HWND hWnd1 = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,   
       CW_USEDEFAULT, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)   // 윈도우 객체 이상 있을 시 리턴
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);  // 윈도우 호출
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
// 윈도우 메세지에 함수 할당
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
            //DC 객체 : GDI 모아놓은 클래스
            HDC hdc = BeginPaint(hWnd, &ps);

            // 브러쉬 객체 생성 및 색 정하기
            HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));  // RGB 매크로 사용 색 정하기
            HBRUSH grayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);  // 스톡오브젝트에서 색 불러오기 (검정, 흰색, 투명밖에 없음)
            HBRUSH patternBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 255));   // 무늬 브러쉬
            HBRUSH oldBrush; // 원래 쓰던 브러쉬 저장해둘 브러쉬

            // SelectObject : 객체에 brush 적용, 적용 이전 사용하던 브러쉬 객체 리턴 가능
            oldBrush = (HBRUSH)SelectObject(hdc, brush);
            
            // 사각형 그리기
            Rectangle(hdc, 100, 100, 200, 200);

            // dc 객체 Brush 원래대로 돌려놓기 -> dc에 할당되어있는 브러쉬는 삭제 못하기 때문
            SelectObject(hdc, oldBrush);
            // 브러쉬 다 썼으면 메모리 해제. 메세지 함수가 계속 반복되기 때문에 Brush 객체 적용 함수가 힙에 계속 남아있음
            DeleteObject(brush);

            // 선 객체 생성 및 적용
            HPEN translucentPen = CreatePen(PS_DASHDOT, 1, DKGRAY_BRUSH);
            HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
            HPEN oldPen = (HPEN)SelectObject(hdc, redPen);
            
            // 원 그리기
            Ellipse(hdc, 200, 200, 300, 300);
            
            // 다 썼다면 메모리 해제
            SelectObject(hdc, oldPen);
            DeleteObject(redPen);

            oldBrush = (HBRUSH)SelectObject(hdc, grayBrush);
            Rectangle(hdc, 10, 10, 800, 600);
            SelectObject(hdc, oldBrush);
            DeleteObject(grayBrush);

            // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ패턴, 펜 브러쉬로 도형쓰기 종합ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
            
            PAINTSTRUCT ps1;
            HDC dc1;
            HBRUSH patternBrush1;
            HPEN pen1;
            HBRUSH oldBrush1;
            HPEN oldPen1;


            dc1 = BeginPaint(hWnd, &ps);
            patternBrush1 = CreateHatchBrush( 0,RGB(255, 0, 0));
            oldBrush1 = (HBRUSH)SelectObject(hdc, patternBrush1);
            pen1 = CreatePen(0, 0, RGB(0, 0, 255));
            oldPen1 = (HPEN)SelectObject(hdc, pen1);

            Rectangle(hdc, 0, 0, 900, 700);
            
            SelectObject(hdc, oldBrush1);
            SelectObject(hdc, oldPen1);

            DeleteObject(patternBrush1);
            DeleteObject(pen1);
            // 


            // DC : 화면 출력에 필요한 모든 정보를 가지는 데이터 구조체
            // GDI 모듈에 의해서 관리됨
            // 어떤 폰트? 어떤 선의 굵기? 어떤 색상으로 그려줌?
            // 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행
            //
            // 순서 : 
            // 1. paint dc 객체 생성
            // 2. brush 객체 생성 (스톡오브젝트에서 불러다 써도 됨)
            // 3. 새 브러쉬 dc에 적용 및 기존 브러쉬 저장
            // 4. 그리기 
            // 5. dc 기존 브러쉬로 되돌리기
            // 6. 새 브러쉬 객체 삭제

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
