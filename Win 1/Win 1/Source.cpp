#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
int winWidth = 400, winHeight = 400;

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = CreateSolidBrush(RGB(150, 75, 0)); 	// ���������� ���� 


	// ����������� ������ ����
	if (!RegisterClass(&wc))
		return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
		_T("������ Windows-����������"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 ������� ���� 
		winWidth, 				// width 
		winHeight, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 

	ShowWindow(hWnd, mode); 				// �������� ����

	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	}

	WM_RBUTTONDOWN;
	return 0;
}

// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������
//bool firstRightClick = true;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static COLORREF colors[] = { RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 255, 255) };

	static bool firstRightClick = true;	// ��������������� ������ ��� ������ ������ �-���
	static int disabledCircleIndex = -1;
	HDC hdc; //������ �������� ����������
	PAINTSTRUCT ps; //������ ��������� ��������� ������������ ������
	LOGFONT lf;
	HFONT hFont;
	RECT r;
	HBRUSH hBrush;
	HPEN hPen;

	
	switch (message)		 // ���������� ���������
	{

	//��������� ���������
	case WM_PAINT:
	hdc = BeginPaint(hWnd, &ps);



	for (int i = 0; i < 3; ++i) {
		if (disabledCircleIndex != i) {
			hBrush = CreateSolidBrush(colors[i]);
			SelectObject(hdc, hBrush);
			Ellipse(hdc, 20, 20 + i*100, 120, 120 + i*100); // top = 20 120 220, bottom = 120 220 320
		}
	}

	/*if (disabledCircleIndex != 0) {
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, 20, 20, 120, 120);
	}
	
	if (disabledCircleIndex != 1) {
		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, 20, 120, 120, 220);
	}

	if (disabledCircleIndex != 2) {
		hBrush = CreateSolidBrush(RGB(0, 200, 0));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, 20, 220, 120, 320);
	}*/

	ValidateRect(hWnd, NULL);
	EndPaint(hWnd, &ps);
	break;

	case WM_LBUTTONDOWN:
		disabledCircleIndex = (disabledCircleIndex + 1) % 3;

		InvalidateRect(hWnd, NULL, true);

	break;

	case WM_RBUTTONDOWN:
		if (firstRightClick == true) {
			ShowWindow(hWnd, SW_MINIMIZE);
			firstRightClick = false;
		}
		else
		{
			MoveWindow(hWnd, rand() % 500, rand() % 500, winWidth, winHeight, false);
			firstRightClick = true;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// ���������� ��������� 
	default: 			// ��������� ��������� �� ��������� 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//POINT poly[3];
//BYTE polytype[3];

//poly[0].x = 375; //���������� ������ �������
//poly[0].y = 375;

//poly[1].x = 400; //���������� ������ �������
//poly[1].y = 400;

//poly[2].x = 500; //���������� ������� �������
//poly[2].y = 500;

//polytype[0] = PT_LINETO;
//polytype[1] = PT_LINETO;
//polytype[2] = PT_LINETO;
//PolyDraw(hdc, poly, polytype, 3); //��������� ��������������


		/*if (disabledCircleIndex == 0) {
			disabledCircleIndex = 1;
		}
		if (disabledCircleIndex == 1) {
			disabledCircleIndex = 2;
		}
		if (disabledCircleIndex == 2) {
			disabledCircleIndex = 0;
		}*/