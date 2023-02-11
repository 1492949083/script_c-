#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <ctime>

using namespace std;

int autoClick(const char* window, const char* text) {
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring wideWindowName = converter.from_bytes(window);
    LPCWSTR lpWindowName = wideWindowName.c_str();
    wstring wideText = converter.from_bytes(text);
    LPCWSTR lpText = wideText.c_str();

    // 首先，使用 FindWindow 函数获取目标程序窗口的句柄
    HWND hWnd = FindWindow(NULL, lpWindowName);
    printf("%s\n",window);

    if (hWnd == NULL)
    {
        std::cout << "无法找到窗口" << std::endl;
        return 1;
    }
    // 设置窗口置顶
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	Sleep(50);
    // 使用 FindWindowEx 函数获取 "重试" 按钮的句柄
    HWND hBtn = FindWindowEx(hWnd, NULL, _T("Button"), lpText);

    if (hBtn == NULL)
    {
        std::cout << "无法找到按钮" << std::endl;
        return 1;
    }

    // 获取按钮的位置和大小
    RECT rect;
    GetWindowRect(hBtn, &rect);

    // 计算鼠标的目标位置
    int x = rect.left + (rect.right - rect.left) / 2;
    int y = rect.top + (rect.bottom - rect.top) / 2;

    // 移动鼠标到目标位置
    SetCursorPos(x, y);

    // 模拟鼠标左键单击事件
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

    std::cout << "按钮点击成功" << std::endl;

    return 0;
}

int main()
{
    while (true)
    {
        if (autoClick("Hogwarts Legacy", "重试") == true)
        {
            autoClick("Hogwarts Legacy", "确定");
            Sleep(1000);
			system("C:/Users/ASUS/Desktop/霍格沃茨之遗.url");
			cout << "启动快捷方式成功" << endl;
        }
        //打印当前时间
        time_t now = time(0);
        char* dt = ctime(&now);
        cout << dt << endl;

        Sleep(100000);
    }
    return 0;
}
