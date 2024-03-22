#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <string>

//переменные, которые будем использовать
std::string a = "", b = "", strResult; //первое число, второе, итог (строкой)
double first, second, result;//первое число, второе, итог (числом)
char sign, buffer[32]; //знак (/*-+), массив для вывода итога
bool condition = true, term = false; //условие (введен ли знак), выводили ли уже результат
int points = 0; //количество точек в числе

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Калькулятор");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop"), NULL);
        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        215, 330,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        MessageBox(NULL, _T("Call to CreateWindow failed!"),
            _T("Windows Desktop"), NULL);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, Windows desktop!");
    static HWND hStatic;

    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_CREATE:
        //все кнопки
        HWND hButton0;
        hButton0 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("C"), WS_CHILD,
            10, 10, 40, 40,
            hWnd, reinterpret_cast<HMENU>(1),
            NULL, NULL
        );
        ShowWindow(hButton0, SW_SHOW);
        UpdateWindow(hButton0);

        HWND hButton1;
        hButton1 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("<-"), WS_CHILD,
            100, 10, 40, 40,
            hWnd, reinterpret_cast<HMENU>(2),
            NULL, NULL
        );
        ShowWindow(hButton1, SW_SHOW);
        UpdateWindow(hButton1);

        HWND hButton2;
        hButton2 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("/"), WS_CHILD,
            145, 10, 40, 40,
            hWnd, reinterpret_cast<HMENU>(3),
            NULL, NULL
        );
        ShowWindow(hButton2, SW_SHOW);
        UpdateWindow(hButton2);

        HWND hButton3;
        hButton3 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("7"), WS_CHILD,
            10, 55, 40, 40,
            hWnd, reinterpret_cast<HMENU>(4),
            NULL, NULL
        );
        ShowWindow(hButton3, SW_SHOW);
        UpdateWindow(hButton3);

        HWND hButton4;
        hButton4 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("8"), WS_CHILD,
            55, 55, 40, 40,
            hWnd, reinterpret_cast<HMENU>(5),
            NULL, NULL
        );
        ShowWindow(hButton4, SW_SHOW);
        UpdateWindow(hButton4);

        HWND hButton5;
        hButton5 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("9"), WS_CHILD,
            100, 55, 40, 40,
            hWnd, reinterpret_cast<HMENU>(6),
            NULL, NULL
        );
        ShowWindow(hButton5, SW_SHOW);
        UpdateWindow(hButton5);

        HWND hButton6;
        hButton6 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("*"), WS_CHILD,
            145, 55, 40, 40,
            hWnd, reinterpret_cast<HMENU>(7),
            NULL, NULL
        );
        ShowWindow(hButton6, SW_SHOW);
        UpdateWindow(hButton6);

        HWND hButton7;
        hButton7 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("4"), WS_CHILD,
            10, 100, 40, 40,
            hWnd, reinterpret_cast<HMENU>(8),
            NULL, NULL
        );
        ShowWindow(hButton7, SW_SHOW);
        UpdateWindow(hButton7);

        HWND hButton8;
        hButton8 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("5"), WS_CHILD,
            55, 100, 40, 40,
            hWnd, reinterpret_cast<HMENU>(9),
            NULL, NULL
        );
        ShowWindow(hButton8, SW_SHOW);
        UpdateWindow(hButton8);

        HWND hButton9;
        hButton9 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("6"), WS_CHILD,
            100, 100, 40, 40,
            hWnd, reinterpret_cast<HMENU>(10),
            NULL, NULL
        );
        ShowWindow(hButton9, SW_SHOW);
        UpdateWindow(hButton9);

        HWND hButton10;
        hButton10 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("-"), WS_CHILD,
            145, 100, 40, 40,
            hWnd, reinterpret_cast<HMENU>(11),
            NULL, NULL
        );
        ShowWindow(hButton10, SW_SHOW);
        UpdateWindow(hButton10);

        HWND hButton11;
        hButton11 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("1"), WS_CHILD,
            10, 145, 40, 40,
            hWnd, reinterpret_cast<HMENU>(12),
            NULL, NULL
        );
        ShowWindow(hButton11, SW_SHOW);
        UpdateWindow(hButton11);

        HWND hButton12;
        hButton12 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("2"), WS_CHILD,
            55, 145, 40, 40,
            hWnd, reinterpret_cast<HMENU>(13),
            NULL, NULL
        );
        ShowWindow(hButton12, SW_SHOW);
        UpdateWindow(hButton12);

        HWND hButton13;
        hButton13 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("3"), WS_CHILD,
            100, 145, 40, 40,
            hWnd, reinterpret_cast<HMENU>(14),
            NULL, NULL
        );
        ShowWindow(hButton13, SW_SHOW);
        UpdateWindow(hButton13);

        HWND hButton14;
        hButton14 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("+"), WS_CHILD,
            145, 145, 40, 40,
            hWnd, reinterpret_cast<HMENU>(15),
            NULL, NULL
        );
        ShowWindow(hButton14, SW_SHOW);
        UpdateWindow(hButton14);

        HWND hButton15;
        hButton15 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("0"), WS_CHILD,
            55, 190, 40, 40,
            hWnd, reinterpret_cast<HMENU>(16),
            NULL, NULL
        );
        ShowWindow(hButton15, SW_SHOW);
        UpdateWindow(hButton15);

        HWND hButton16;
        hButton16 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT(","), WS_CHILD,
            100, 190, 40, 40,
            hWnd, reinterpret_cast<HMENU>(17),
            NULL, NULL
        );
        ShowWindow(hButton16, SW_SHOW);
        UpdateWindow(hButton16);

        HWND hButton17;
        hButton17 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("="), WS_CHILD,
            145, 190, 40, 40,
            hWnd, reinterpret_cast<HMENU>(18),
            NULL, NULL
        );
        ShowWindow(hButton17, SW_SHOW);
        UpdateWindow(hButton17);

        //поле для вывода ответа
        hStatic = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Static"),
            TEXT(""), WS_CHILD | SS_CENTERIMAGE,
            10, 235, 175, 40,
            hWnd, NULL,
            hInst, NULL
        );
        ShowWindow(hStatic, SW_SHOW);
        UpdateWindow(hStatic);
        break;

    case WM_COMMAND: {
        //ввод первого и второго чисел строкой посимвольно
        switch (LOWORD(wParam))
        {
        case 4:
            if (condition == true)
            {
                if (term == false)
                    a += "7";
                else
                {
                    a.clear();
                    a += "7";
                    term = false;
                }
            }
            else
                b += "7";
            break;
        case 5:
            if (condition == true)
            {
                if (term == false)
                    a += "8";
                else
                {
                    a.clear();
                    a += "8";
                    term = false;
                }
            }
            else
                b += "8";
            break;
        case 6:
            if (condition == true)
            {
                if (term == false)
                    a += "9";
                else
                {
                    a.clear();
                    a += "9";
                    term = false;
                }
            }
            else
                b += "9";
            break;
        case 8:
            if (condition == true)
            {
                if (term == false)
                    a += "4";
                else
                {
                    a.clear();
                    a += "4";
                    term = false;
                }
            }
            else
                b += "4";
            break;
        case 9:
            if (condition == true)
            {
                if (term == false)
                    a += "5";
                else
                {
                    a.clear();
                    a += "5";
                    term = false;
                }
            }
            else
                b += "5";
            break;
        case 10:
            if (condition == true)
            {
                if (term == false)
                    a += "6";
                else
                {
                    a.clear();
                    a += "6";
                    term = false;
                }
            }
            else
                b += "6";
            break;
        case 12:
            if (condition == true)
            {
                if (term == false)
                    a += "1";
                else
                {
                    a.clear();
                    a += "1";
                    term = false;
                }
            }
            else
                b += "1";
            break;
        case 13:
            if (condition == true)
            {
                if (term == false)
                    a += "2";
                else
                {
                    a.clear();
                    a += "2";
                    term = false;
                }
            }
            else
                b += "2";
            break;
        case 14:
            if (condition == true)
            {
                if (term == false)
                    a += "3";
                else
                {
                    a.clear();
                    a += "3";
                    term = false;
                }
            }
            else
                b += "3";
            break;
        case 16:
            if (condition == true)
            {
                if (term == false)
                    a += "0";
                else
                {
                    a.clear();
                    a += "0";
                    term = false;
                }
            }
            else
                b += "0";
            break;
            //добавление точки (запятой) в число
        case 17:
            if (condition == true)
            {
                if (a != "")
                {
                    for (int i = 0; i < a.length(); i++)
                    {
                        if (a[i] == '.')
                        {
                            points += 1;
                        }
                        if (i == a.length() - 1 && points == 0)
                        {
                            a += ".";
                            break;
                        }
                    }
                    points = 0;
                }
                else
                    a += ".";
            }
            else
            {
                if (b != "")
                {
                    for (int i = 0; i < b.length(); i++)
                    {
                        if (b[i] == '.')
                        {
                            points += 1;
                            break;
                        }
                        if (i == b.length() - 1 && points == 0)
                        {
                            b += ".";
                            break;
                        }
                    }
                    points = 0;
                }
                else
                    b += ".";
            }
            break;
            //сброс
        case 1:
            a.clear();
            b.clear();
            sign = '\0';
            condition = true;
            break;
            //ввод знаков
        case 3:
            if (a != "" && b == "")
            {
                sign = '/';
                condition = false;
            }
            break;
        case 7:
            if (a != "" && b == "")
            {
                sign = '*';
                condition = false;
            }
            break;
        case 11:
            if (a != "" && condition == true)
            {
                sign = '-';
                condition = false;
            }
            else if (a == "")
            {
                a += "-";
            }
            else if (condition == false && b == "")
            {
                b += "-";
            }
            break;
        case 15:
            if (a != "" && b == "")
            {
                sign = '+';
                condition = false;
            }
            break;
        case 18:
            //вывод ответа
            if (a != "" && b != "")
            {
                switch (sign)
                {
                    //при делении
                case '/':
                    first = std::stod(a);
                    second = std::stod(b);
                    result = first / second;
                    strResult = std::to_string(result);
                    for (int i = 0; i < strResult.length(); i++)
                    {
                        buffer[i] = strResult[i];
                    }
                    SetWindowTextA(hStatic, buffer);
                    break;
                    //при умножении
                case '*':
                    first = std::stod(a);
                    second = std::stod(b);
                    result = first * second;
                    strResult = std::to_string(result);
                    for (int i = 0; i < strResult.length(); i++)
                    {
                        buffer[i] = strResult[i];
                    }
                    SetWindowTextA(hStatic, buffer);
                    break;
                    //при разности
                case '-':
                    first = std::stod(a);
                    second = std::stod(b);
                    result = first - second;
                    strResult = std::to_string(result);
                    for (int i = 0; i < strResult.length(); i++)
                    {
                        buffer[i] = strResult[i];
                    }
                    SetWindowTextA(hStatic, buffer);
                    break;
                    //при сложении
                case '+':
                    first = std::stod(a);
                    second = std::stod(b);
                    result = first + second;
                    strResult = std::to_string(result);
                    for (int i = 0; i < strResult.length(); i++)
                    {
                        buffer[i] = strResult[i];
                    }
                    SetWindowTextA(hStatic, buffer);
                    break;
                }
                //сброс после вывода, первое число = итог
                a = strResult;
                b.clear();
                sign = '\0';
                condition = true;
                term = true;
            }
            break;
        case 2:
            //реализация удаления последнего символа
            if (b == "" && sign == '\0' && a != "")
            {
                a.pop_back();
            }
            else if (b == "" && sign != '\0')
            {
                sign = '\0';
                condition = true;
            }
            else if (b != "")
            {
                b.pop_back();
            }
        }
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}