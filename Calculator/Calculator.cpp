#include "resource.h"
#include <windows.h>
#include <tchar.h>
#include <string>

//лейблы для выражения и result
static HWND hStaticResult, hStaticExpression;
//переменные, которые будем использовать
std::string a = "", b = "", expression = "", strResult; //первое число; второе; итог (строкой)
double first, second, result;//первое число; второе число; итог (числом)
char sign, buffer[256]; //знак (/*-+); массив для вывода чисел
bool condition = false, term = false; //условие (введен ли знак); выводили ли уже результат
int points = 0; //количество точек в числе
size_t found; //номер последнего не нуля в строке

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

//вывод выражения при вводе
 void outputExpression()
 {
    expression = a + sign + b;
    for (int i = 0; i < expression.length(); i++)
    {
        buffer[i] = expression[i];
    }
    SetWindowTextA(hStaticExpression, buffer);
    memset(buffer, 0, sizeof(buffer));
 }

//вывод промежуточного результата
void outputIntermediateResult()
{
    switch (sign)
    {
        //при делении
    case '/':
        if (a.length() <= 255 && b.length() <= 255 && std::stod(b) != 0)
        {
            first = std::stod(a);
            second = std::stod(b);
            result = first / second;
            if (result != -(0))
            {
                removingZeros();
                for (int i = 0; i < strResult.length(); i++)
                {
                    buffer[i] = strResult[i];
                }
                SetWindowTextA(hStaticResult, buffer);
                memset(buffer, 0, sizeof(buffer));
            }
            else
                SetWindowText(hStaticResult, L"0");
        }
        else
            SetWindowText(hStaticResult, L"ERROR");
        break;
        //при умножении
    case '*':
        if (a.length() <= 255 && b.length() <= 255)
        {
            first = std::stod(a);
            if (b != "-")
            second = std::stod(b);
            else
            {
                SetWindowText(hStaticResult, L"");
                break;
            }
            result = first * second;
            if (result != -(0))
            {
                removingZeros();
                for (int i = 0; i < strResult.length(); i++)
                {
                    buffer[i] = strResult[i];
                }
                SetWindowTextA(hStaticResult, buffer);
                memset(buffer, 0, sizeof(buffer));
            }
            else
                SetWindowText(hStaticResult, L"0");
        }
        else
            SetWindowText(hStaticResult, L"ERROR");
        break;
        //при разности
    case '-':
        if (a.length() <= 255 && b.length() <= 255)
        {
            first = std::stod(a);
            second = std::stod(b);
            result = first - second;
            removingZeros();
            for (int i = 0; i < strResult.length(); i++)
            {
                buffer[i] = strResult[i];
            }
            SetWindowTextA(hStaticResult, buffer);
            memset(buffer, 0, sizeof(buffer));
        }
        else
            SetWindowText(hStaticResult, L"ERROR");
        break;
        //при сложении
    case '+':
        if (a.length() <= 255 && b.length() <= 255)
        {
            first = std::stod(a);
            second = std::stod(b);
            result = first + second;
            removingZeros();
            for (int i = 0; i < strResult.length(); i++)
            {
                buffer[i] = strResult[i];
            }
            SetWindowTextA(hStaticResult, buffer);
            memset(buffer, 0, sizeof(buffer));
        }
        else
            SetWindowText(hStaticResult, L"ERROR");
        break;
    case '^':
        if (a.length() <= 255 && b.length() <= 255)
        {
            first = std::stod(a);
            second = std::stod(b);
            result = pow(first, second);
            removingZeros();
            for (int i = 0; i < strResult.length(); i++)
            {
                buffer[i] = strResult[i];
            }
            SetWindowTextA(hStaticResult, buffer);
            memset(buffer, 0, sizeof(buffer));
        }
        else
            SetWindowText(hStaticResult, L"ERROR");
    }
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
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

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

    SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLongPtr(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX); //отключение возможности открытия окна на весь окран

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
            TEXT("\u232B"), WS_CHILD,
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
            TEXT("."), WS_CHILD,
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

        HWND hButton18;
        hButton18 = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Button"),
            TEXT("^"), WS_CHILD,
            55, 55, 40, 40,
            hWnd, reinterpret_cast<HMENU>(19),
            NULL, NULL
        );
        ShowWindow(hButton18, SW_SHOW);
        UpdateWindow(hButton18);

        //текстовое поле для вывода ответа
        hStaticResult = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Static"),
            TEXT(""), WS_CHILD | SS_CENTERIMAGE | WS_DISABLED | ES_RIGHT,
            10, 30, 175, 20,
            hWnd, NULL,
            hInst, NULL
        );
        ShowWindow(hStaticResult, SW_SHOW);
        UpdateWindow(hStaticResult);

        //текстовое поле для вывода выражения
        hStaticExpression = CreateWindowEx(
            WS_EX_TRANSPARENT, TEXT("Static"),
            TEXT(""), WS_CHILD | ES_RIGHT | SS_CENTERIMAGE,
            10, 10, 175, 20,
            hWnd, NULL,
            hInst, NULL
        );
        ShowWindow(hStaticExpression, SW_SHOW);
        UpdateWindow(hStaticExpression);

    case WM_COMMAND: {
        //ввод первого и второго чисел строкой посимвольно
        switch (LOWORD(wParam))
        {
        case 4:
            if (condition == false)
            {
                if (a != "0")
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
                    a = "7";
            }
            else
            {
                if (b != "0")
                    b += "7";
                else
                    b = "7";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 5:
            if (condition == false)
            {
                if (a != "0")
                {
                    if (term == false)
                        a += "8";
                    else
                    {
                        a.clear();
                        a += "8";
                        term = false;
                        SetWindowText(hStaticResult, L"");
                    }
                }
                else
                    a = "8";
            }
            else
            {
                if (b != "0")
                    b += "8";
                else
                    b = "8";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 6:
            if (condition == false)
            {
                if (a != "0")
                {
                    if (term == false)
                        a += "9";
                    else
                    {
                        a.clear();
                        a += "9";
                        term = false;
                        SetWindowText(hStaticResult, L"");
                    }
                }
                else
                    a = "9";
            }
            else
            {
                if (b != "0")
                    b += "9";
                else
                    b = "9";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 8:
            if (condition == false)
            {
                if (a != "0")
                {
                    if (term == false)
                        a += "4";
                    else
                    {
                        a.clear();
                        a += "4";
                        term = false;
                        SetWindowText(hStaticResult, L"");
                    }
                }
                else
                    a = "4";
            }
            else
            {
                if (b != "0")
                    b += "4";
                else
                    b = "4";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 9:
            if (condition == false)
            {
                if (a != "0")
                {
                    if (term == false)
                        a += "5";
                    else
                    {
                        a.clear();
                        a += "5";
                        term = false;
                        SetWindowText(hStaticResult, L"");
                    }
                }
                else
                    a = "5";
            }
            else
            {
                if (b != "0")
                    b += "5";
                else
                    b = "5";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 10:
            if (condition == false)
            {
                if (a != "0")
                {
                    if (term == false)
                        a += "6";
                    else
                    {
                        a.clear();
                        a += "6";
                        term = false;
                        SetWindowText(hStaticResult, L"");
                    }
                }
                else
                    a = "6";
            }
            else
            {
                if (b != "0")
                    b += "6";
                else
                    b = "6";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 12:
            if (condition == false)
            {
                if (a != "0")
                {
                    if (term == false)
                        a += "1";
                    else
                    {
                        a.clear();
                        a += "1";
                        term = false;
                        SetWindowText(hStaticResult, L"");
                    }
                }
                else
                    a = "1";
            }
            else
            {
                if (b != "0")
                    b += "1";
                else
                    b = "1";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 13:
            if (condition == false)
            {
                if (a != "0")
                {
                    if (term == false)
                        a += "2";
                    else
                    {
                        a.clear();
                        a += "2";
                        term = false;
                        SetWindowText(hStaticResult, L"");
                    }
                }
                else
                    a = "2";
            }
            else
            {
                if (b != "0")
                    b += "2";
                else
                    b = "2";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 14:
            if (condition == false)
            {
                if (a != "0")
                {
                    if (term == false)
                        a += "3";
                    else
                    {
                        a.clear();
                        a += "3";
                        term = false;
                        SetWindowText(hStaticResult, L"");
                    }
                }
                else
                    a = "3";
            }
            else
            {
                if (b != "0")
                    b += "3";
                else
                    b = "3";
                outputIntermediateResult();
            }
            outputExpression();
            break;
        case 16:
            if (condition == false)
            {
                if (term == false)
                {
                    if (a != "")
                    {
                        for (int i = 0; i < a.length(); i++)
                        {
                            if (a[i] == '.')
                                points++;
                            if (i == a.length() - 1 && (points == 1 || a == "-"))
                            {
                                a += "0";
                                outputExpression();
                                points = 0;
                                break;
                            }
                            else if (i == a.length() - 1 && (points == 1 || std::stod(a) != 0))
                            {
                                a += "0";
                                outputExpression();
                                points = 0;
                                break;
                            }
                        }
                    }
                    else
                    {
                        a += "0";
                        outputExpression();
                    }
                }
                else
                {
                    a.clear();
                    a += "0";
                    outputExpression();
                    term = false;
                    SetWindowText(hStaticResult, L"");
                }
            }
            else
            {
                if (b != "")
                {
                    for (int i = 0; i < b.length(); i++)
                    {
                        if (b[i] == '.')
                            points++;
                        if (i == b.length() - 1 && (points == 1 || std::stod(a) != 0))
                        {
                            b += "0";
                            outputExpression();
                            outputIntermediateResult();
                            points = 0;
                            break;
                        }
                    }
                }
                else
                {
                    b += "0";
                    outputExpression();
                    outputIntermediateResult();
                }
            }
            break;
            //добавление точки к числу
        case 17:
            if (condition == false)
            {
                if (a != "")
                {
                    if (term == false)
                    {
                        for (int i = 0; i < a.length(); i++)
                        {
                            if (a[i] == '.')
                                points++;
                            if (i == a.length() - 1 && points == 0)
                            {
                                if (a == "" || a == "-")
                                    a += "0";
                                a += ".";
                                outputExpression();
                                break;
                            }
                        }
                        points = 0;
                    }
                    else
                    {
                        a.clear();
                        if (a == "")
                            a += "0";
                        a += ".";
                        outputExpression();
                        term = false;
                    }
                }
                else
                {
                    if (a == "")
                        a += "0";
                    a += ".";
                    term = false;
                    SetWindowText(hStaticResult, L"");
                    outputExpression();
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
                            points++;
                            break;
                        }
                        if (i == b.length() - 1 && points == 0)
                        {
                            if (b == "" || b == "-")
                                b += "0";
                            b += ".";
                            outputExpression();
                            outputIntermediateResult();
                            break;
                        }
                    }
                    points = 0;
                }
                else
                {
                    if (b == "")
                        b += "0";
                    b += ".";
                    outputExpression();
                    outputIntermediateResult();
                }
            }
            break;
            //сброс
        case 1:
            a.clear();
            b.clear();
            sign = '\0';
            condition = false;
            SetWindowText(hStaticResult, L"");
            SetWindowText(hStaticExpression, L"");
            SetWindowText(hStaticResult, L"");
            break;
            //ввод знаков (действий)
        case 3:
            if (a != "" && b == "")
            {
                if (a != "-")
                {
                    sign = '/';
                    condition = true;
                    outputExpression();
                    SetWindowText(hStaticResult, L"");
                }
            }
            break;
        case 7:
            if (a != "" && b == "")
            {
                if (a != "-")
                {
                    sign = '*';
                    condition = true;
                    outputExpression();
                    SetWindowText(hStaticResult, L"");
                }
            }
            break;
        case 11:
            if (a != "" && condition == false)
            {
                if (a != "-")
                {
                    sign = '-';
                    condition = true;
                    outputExpression();
                    SetWindowText(hStaticResult, L"");
                }
            }
            else if (a == "")
            {
                a += "-";
                outputExpression();
                term = false;
                SetWindowText(hStaticResult, L"");
            }
            else if (condition == true && b == "")
            {
                b += "-";
                outputExpression();
                term = false;
                SetWindowText(hStaticResult, L"");
            }
            else if (condition == true && b != "")
                outputExpression();
            break;
        case 15:
            if (a != "" && b == "")
            {
                if (a != "-")
                {
                    sign = '+';
                    condition = true;
                    outputExpression();
                    SetWindowText(hStaticResult, L"");
                }
            }
            break;
        case 19:
            if (a != "" && b == "")
            {
                if (a != "-")
                {
                    sign = '^';
                    condition = true;
                    outputExpression();
                    SetWindowText(hStaticResult, L"");
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
                    if (a.length() <= 255 && b.length() <= 255 && std::stod(b) != 0)
                    {
                        if (std::stod(a) == -(0))
                            first = 0;
                        else
                            first = std::stod(a);
                        if (std::stod(b) == -(0))
                            second = 0;
                        else
                            second = std::stod(b);
                        result = first / second;
                        removingZeros();
                    }
                    else
                    {
                        SetWindowText(hStaticResult, L"ERROR");
                        strResult = "ERROR";
                    }
                    break;
                    //при умножении
                case '*':
                    if (a.length() <= 255 && b.length() <= 255)
                    {
                        if (std::stod(a) == -(0))
                            first = 0;
                        else
                            first = std::stod(a);
                        if (std::stod(b) == -(0))
                            second = 0;
                        else
                            second = std::stod(b);
                        result = first * second;
                        removingZeros();
                    }
                    else
                        SetWindowText(hStaticResult, L"ERROR");
                    break;
                    //при разности
                case '-':
                    if (a.length() <= 255 && b.length() <= 255)
                    {
                        first = std::stod(a);
                        second = std::stod(b);
                        result = first - second;
                        removingZeros();
                    }
                    else
                        SetWindowText(hStaticResult, L"ERROR");
                    break;
                    //при сложении
                case '+':
                    if (a.length() <= 255 && b.length() <= 255)
                    {
                        first = std::stod(a);
                        second = std::stod(b);
                        result = first + second;
                        removingZeros();
                    }
                    else
                        SetWindowText(hStaticResult, L"ERROR");
                    break;
                case '^':
                    if (a.length() <= 255 && b.length() <= 255)
                    {
                        first = std::stod(a);
                        second = std::stod(b);
                        result = pow(first, second);
                        removingZeros();
                    }
                    else
                        SetWindowText(hStaticResult, L"ERROR");
                    break;
                }
                //сброс после вывода, первое число = итог
                if (strResult != "ERROR")
                {
                    a = strResult;
                    SetWindowText(hStaticResult, L"");
                }
                else
                    a = "";
                b.clear();
                sign = '\0';
                condition = false;
                term = true;
                outputExpression();
            }
            break;
        case 2:
            //удаление последнего символа
            if (b == "" && sign == '\0' && a != "")
            {
                a.pop_back();
                outputExpression();
                SetWindowText(hStaticResult, L"");
                term = false;
            }
            else if (b == "" && sign != '\0')
            {
                sign = '\0';
                condition = false;
                outputExpression();
            }
            else if (b != "")
            {
                b.pop_back();
                outputExpression();
                if (b != "" && b != "-")
                    outputIntermediateResult();
                else
                    SetWindowText(hStaticResult, L"");
            }
        }
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
