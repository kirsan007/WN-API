#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
int winWidth = 400, winHeight = 400;

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = CreateSolidBrush(RGB(150, 75, 0)); 	// Заполнение окна 


	// Регистрация класса окна
	if (!RegisterClass(&wc))
		return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Каркас Windows-приложения"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		winWidth, 				// width 
		winHeight, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}

	WM_RBUTTONDOWN;
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения
//bool firstRightClick = true;



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static COLORREF colors[] = { RGB(255, 0, 0), RGB(0, 0, 0), RGB(255, 255, 255) };

	static bool firstRightClick = true;	// инициализируетя только при первом вызове ф-ции
	static int disabledCircleIndex = -1;
	HDC hdc; //создаём контекст устройства
	PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
	LOGFONT lf;
	HFONT hFont;
	RECT r;
	HBRUSH hBrush;
	HPEN hPen;

	
	switch (message)		 // Обработчик сообщений
	{

	//сообщение рисования
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
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


//POINT poly[3];
//BYTE polytype[3];

//poly[0].x = 375; //координаты первой вершины
//poly[0].y = 375;

//poly[1].x = 400; //координаты второй вершины
//poly[1].y = 400;

//poly[2].x = 500; //координаты третиий вершины
//poly[2].y = 500;

//polytype[0] = PT_LINETO;
//polytype[1] = PT_LINETO;
//polytype[2] = PT_LINETO;
//PolyDraw(hdc, poly, polytype, 3); //рисование многоугольника


		/*if (disabledCircleIndex == 0) {
			disabledCircleIndex = 1;
		}
		if (disabledCircleIndex == 1) {
			disabledCircleIndex = 2;
		}
		if (disabledCircleIndex == 2) {
			disabledCircleIndex = 0;
		}*/