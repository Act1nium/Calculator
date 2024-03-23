#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#include <string>

static HWND hStatic1, hStatic2, hStatic3, hStatic4; //лейблы для result, a, sign, b
//переменные, которые будем использовать
std::string a = "", b = "", strResult; //первое число, второе, итог (строкой)
double first, second, result;//первое число, второе, итог (числом)
char sign, buffer[103]; //знак (/*-+), массив для вывода чисел
bool condition = true, term = false; //условие (введен ли знак), выводили ли уже результат
int points = 0; //количество точек в числе
size_t found; //номер последнего не нуля в строке

//вывод чисел при вводе
void outputA()
{
    for (int i = 0; i < a.length(); i++)
    {
        buffer[i] = a[i];
    }
    SetWindowTextA(hStatic2, buffer);
    memset(buffer, 0, sizeof(buffer));
}

void outputB()
{
    for (int i = 0; i < b.length(); i++)
    {
        buffer[i] = b[i];
    }
    SetWindowTextA(hStatic4, buffer);
    memset(buffer, 0, sizeof(buffer));
}

//вывод результата
void outputResult()
{
    for (int i = 0; i < strResult.length(); i++)
    {
        buffer[i] = strResult[i];
    }
    SetWindowTextA(hStatic1, buffer);
    memset(buffer, 0, sizeof(buffer));
}

//удаление нулей
void removingZeros()
{
    strResult = std::to_string(result);
    found = strResult.find_last_not_of('0');
    if (found != std::string::npos && strResult[found] == '.')
    {
        found--;
    }
    strResult = strResult.substr(0, found + 1);
}

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Calculator");

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
        WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX,
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
            10, 55, 40, 40,
            hWnd, reinterpret_cast<HMENU>(1),
            NULL, NULL
        );
        ShowWindow(hButton0, SW_SHOW);
        UpdateWindow(hButton0);

        HWND hButton1;
        hButton1 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("<-"), WS_CHILD,
            100, 55, 40, 40,
            hWnd, reinterpret_cast<HMENU>(2),
            NULL, NULL
        );
        ShowWindow(hButton1, SW_SHOW);
        UpdateWindow(hButton1);

        HWND hButton2;
        hButton2 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("/"), WS_CHILD,
            145, 55, 40, 40,
            hWnd, reinterpret_cast<HMENU>(3),
            NULL, NULL
        );
        ShowWindow(hButton2, SW_SHOW);
        UpdateWindow(hButton2);

        HWND hButton3;
        hButton3 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("7"), WS_CHILD,
            10, 100, 40, 40,
            hWnd, reinterpret_cast<HMENU>(4),
            NULL, NULL
        );
        ShowWindow(hButton3, SW_SHOW);
        UpdateWindow(hButton3);

        HWND hButton4;
        hButton4 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("8"), WS_CHILD,
            55, 100, 40, 40,
            hWnd, reinterpret_cast<HMENU>(5),
            NULL, NULL
        );
        ShowWindow(hButton4, SW_SHOW);
        UpdateWindow(hButton4);

        HWND hButton5;
        hButton5 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("9"), WS_CHILD,
            100, 100, 40, 40,
            hWnd, reinterpret_cast<HMENU>(6),
            NULL, NULL
        );
        ShowWindow(hButton5, SW_SHOW);
        UpdateWindow(hButton5);

        HWND hButton6;
        hButton6 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("*"), WS_CHILD,
            145, 100, 40, 40,
            hWnd, reinterpret_cast<HMENU>(7),
            NULL, NULL
        );
        ShowWindow(hButton6, SW_SHOW);
        UpdateWindow(hButton6);

        HWND hButton7;
        hButton7 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("4"), WS_CHILD,
            10, 145, 40, 40,
            hWnd, reinterpret_cast<HMENU>(8),
            NULL, NULL
        );
        ShowWindow(hButton7, SW_SHOW);
        UpdateWindow(hButton7);

        HWND hButton8;
        hButton8 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("5"), WS_CHILD,
            55, 145, 40, 40,
            hWnd, reinterpret_cast<HMENU>(9),
            NULL, NULL
        );
        ShowWindow(hButton8, SW_SHOW);
        UpdateWindow(hButton8);

        HWND hButton9;
        hButton9 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("6"), WS_CHILD,
            100, 145, 40, 40,
            hWnd, reinterpret_cast<HMENU>(10),
            NULL, NULL
        );
        ShowWindow(hButton9, SW_SHOW);
        UpdateWindow(hButton9);

        HWND hButton10;
        hButton10 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("-"), WS_CHILD,
            145, 145, 40, 40,
            hWnd, reinterpret_cast<HMENU>(11),
            NULL, NULL
        );
        ShowWindow(hButton10, SW_SHOW);
        UpdateWindow(hButton10);

        HWND hButton11;
        hButton11 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("1"), WS_CHILD,
            10, 190, 40, 40,
            hWnd, reinterpret_cast<HMENU>(12),
            NULL, NULL
        );
        ShowWindow(hButton11, SW_SHOW);
        UpdateWindow(hButton11);

        HWND hButton12;
        hButton12 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("2"), WS_CHILD,
            55, 190, 40, 40,
            hWnd, reinterpret_cast<HMENU>(13),
            NULL, NULL
        );
        ShowWindow(hButton12, SW_SHOW);
        UpdateWindow(hButton12);

        HWND hButton13;
        hButton13 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("3"), WS_CHILD,
            100, 190, 40, 40,
            hWnd, reinterpret_cast<HMENU>(14),
            NULL, NULL
        );
        ShowWindow(hButton13, SW_SHOW);
        UpdateWindow(hButton13);

        HWND hButton14;
        hButton14 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("+"), WS_CHILD,
            145, 190, 40, 40,
            hWnd, reinterpret_cast<HMENU>(15),
            NULL, NULL
        );
        ShowWindow(hButton14, SW_SHOW);
        UpdateWindow(hButton14);

        HWND hButton15;
        hButton15 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("0"), WS_CHILD,
            55, 235, 40, 40,
            hWnd, reinterpret_cast<HMENU>(16),
            NULL, NULL
        );
        ShowWindow(hButton15, SW_SHOW);
        UpdateWindow(hButton15);

        HWND hButton16;
        hButton16 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT(","), WS_CHILD,
            100, 235, 40, 40,
            hWnd, reinterpret_cast<HMENU>(17),
            NULL, NULL
        );
        ShowWindow(hButton16, SW_SHOW);
        UpdateWindow(hButton16);

        HWND hButton17;
        hButton17 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("="), WS_CHILD,
            145, 235, 40, 40,
            hWnd, reinterpret_cast<HMENU>(18),
            NULL, NULL
        );
        ShowWindow(hButton17, SW_SHOW);
        UpdateWindow(hButton17);

        //текстовое поле для вывода ответа
        hStatic1 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Static"),
            TEXT(""), WS_CHILD | SS_CENTERIMAGE,
            10, 30, 175, 20,
            hWnd, NULL,
            hInst, NULL
        );
        ShowWindow(hStatic1, SW_SHOW);
        UpdateWindow(hStatic1);

        //текстовые поля для вывода a, sign и b
        hStatic2 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Static"),
            TEXT(""), WS_CHILD | ES_RIGHT | SS_CENTERIMAGE,
            10, 10, 80, 20,
            hWnd, NULL,
            hInst, NULL
        );
        ShowWindow(hStatic2, SW_SHOW);
        UpdateWindow(hStatic2);

        hStatic3 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Static"),
            TEXT(""), WS_CHILD | SS_CENTERIMAGE | ES_CENTER,
            90, 10, 15, 20,
            hWnd, NULL,
            hInst, NULL
        );
        ShowWindow(hStatic3, SW_SHOW);
        UpdateWindow(hStatic3);

        hStatic4 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Static"),
            TEXT(""), WS_CHILD | ES_RIGHT | SS_CENTERIMAGE,
            105, 10, 80, 20,
            hWnd, NULL,
            hInst, NULL
        );
        ShowWindow(hStatic4, SW_SHOW);
        UpdateWindow(hStatic4);

    case WM_COMMAND: {
        //ввод первого и второго чисел строкой посимвольно
        switch (LOWORD(wParam))
        {
        case 4:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "7";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "7";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "7";
                outputB();
            }
            break;
        case 5:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "8";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "8";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "8";
                outputB();
            }
            break;
        case 6:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "9";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "9";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "9";
                outputB();
            }
            break;
        case 8:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "4";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "4";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "4";
                outputB();
            }
            break;
        case 9:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "5";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "5";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "5";
                outputB();
            }
            break;
        case 10:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "6";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "6";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "6";
                outputB();
            }
            break;
        case 12:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "1";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "1";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "1";
                outputB();
            }
            break;
        case 13:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "2";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "2";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "2";
                outputB();
            }
            break;
        case 14:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "3";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "3";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "3";
                outputB();
            }
            break;
        case 16:
            if (condition == true)
            {
                if (term == false)
                {
                    a += "0";
                    outputA();
                }
                else
                {
                    a.clear();
                    a += "0";
                    outputA();
                    term = false;
                    SetWindowText(hStatic1, L"");
                }
            }
            else
            {
                b += "0";
                outputB();
            }
            break;
            //добавление точки (запятой) к числу
        case 17:
            if (condition == true)
            {
                if (a != "")
                {
                    if (term == false)
                    {
                        for (int i = 0; i < a.length(); i++)
                        {
                            if (a[i] == '.')
                            {
                                points += 1;
                            }
                            if (i == a.length() - 1 && points == 0)
                            {
                                if (a == "")
                                {
                                    a += "0";
                                }
                                a += ".";
                                outputA();
                                break;
                            }
                        }
                        points = 0;
                    }
                    else
                    {
                        a.clear();
                        if (a == "")
                        {
                            a += "0";
                        }
                        a += ".";
                        outputA();
                        term = false;
                    }
                }
                else
                {
                    if (a == "")
                    {
                        a += "0";
                    }
                    a += ".";
                    outputB();
                }
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
                            if (b == "")
                            {
                                b += "0";
                            }
                            b += ".";
                            outputB();
                            break;
                        }
                    }
                    points = 0;
                }
                else
                {
                    if (b == "")
                    {
                        b += "0";
                    }
                    b += ".";
                    outputB();
                }
            }
            break;
            //сброс
        case 1:
            a.clear();
            b.clear();
            sign = '\0';
            condition = true;
            SetWindowText(hStatic1, L"");
            SetWindowText(hStatic2, L"");
            SetWindowText(hStatic3, L"");
            SetWindowText(hStatic4, L"");
            break;
            //ввод знаков
        case 3:
            if (a != "" && b == "")
            {
                if (a != "-")
                {
                    sign = '/';
                    condition = false;
                    SetWindowText(hStatic3, L"/");
                    SetWindowText(hStatic1, L"");
                }
                else
                {
                    a.clear();
                }
            }
            break;
        case 7:
            if (a != "" && b == "")
            {
                if (a != "-")
                {
                    sign = '*';
                    condition = false;
                    SetWindowText(hStatic3, L"*");
                    SetWindowText(hStatic1, L"");
                }
                else
                {
                    a.clear();
                }
            }
            break;
        case 11:
            if (a != "" && condition == true)
            {
                if (a != "-")
                {
                    sign = '-';
                    condition = false;
                    SetWindowText(hStatic3, L"-");
                    SetWindowText(hStatic1, L"");
                }
                else
                {
                    a.clear();
                }
            }
            else if (a == "")
            {
                a += "-";
                outputA();
                term = false;
                SetWindowText(hStatic1, L"");
            }
            else if (condition == false && b == "")
            {
                b += "-";
                outputB();
                term = false;
                SetWindowText(hStatic1, L"");
            }
            break;
        case 15:
            if (a != "" && b == "")
            {
                if (a != "-")
                {
                    sign = '+';
                    condition = false;
                    SetWindowText(hStatic3, L"+");
                    SetWindowText(hStatic1, L"");
                }
                else
                {
                    a.clear();
                }
            }
            break;
        case 18:
            //вывод ответа + удаление нулей и точки на конце на конце
            if (a != "" && b != "" && b != "-")
            {
                switch (sign)
                {
                    //при делении
                case '/':
                    if (a.length() <= 102 && b.length() <= 102 && b != "0" && b != "-0")
                    {
                        first = std::stod(a);
                        second = std::stod(b);
                        result = first / second;
                        if (result != -0)
                        {
                            removingZeros();
                            outputResult();
                            SetWindowText(hStatic3, L"");
                        }
                        else
                            SetWindowText(hStatic1, L"0");
                    }
                    else
                        SetWindowText(hStatic1, L"ERROR");
                    break;
                    //при умножении
                case '*':
                    if (a.length() <= 102 && b.length() <= 102)
                    {
                        first = std::stod(a);
                        second = std::stod(b);
                        result = first * second;
                        if (result != -0)
                        {
                            removingZeros();
                            outputResult();
                            SetWindowText(hStatic3, L"");
                        }
                        else
                            SetWindowText(hStatic1, L"0");
                    }
                    else
                        SetWindowText(hStatic1, L"ERROR");
                    break;
                    //при разности
                case '-':
                    if (a.length() <= 102 && b.length() <= 102)
                    {
                        first = std::stod(a);
                        second = std::stod(b);
                        result = first - second;
                        removingZeros();
                        outputResult();
                        SetWindowText(hStatic3, L"");
                    }
                    else
                        SetWindowText(hStatic1, L"ERROR");
                    break;
                    //при сложении
                case '+':
                    if (a.length() <= 102 && b.length() <= 102)
                    {
                        first = std::stod(a);
                        second = std::stod(b);
                        result = first + second;
                        removingZeros();
                        outputResult();
                        SetWindowText(hStatic3, L"");
                    }
                    else
                        SetWindowText(hStatic1, L"ERROR");
                    break;
                }
                //сброс после вывода, первое число = итог
                a = strResult;
                b.clear();
                sign = '\0';
                condition = true;
                term = true;
                outputA();
                SetWindowText(hStatic4, L"");
            }
            break;
        case 2:
            //удаление последнего символа
            if (b == "" && sign == '\0' && a != "")
            {
                a.pop_back();
                outputA();
            }
            else if (b == "" && sign != '\0')
            {
                sign = '\0';
                condition = true;
                SetWindowText(hStatic3, L"");
            }
            else if (b != "")
            {
                b.pop_back();
                outputB();
            }
        }
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
