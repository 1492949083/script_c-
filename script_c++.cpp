#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

using namespace std;

//自动单击
void autoClick(const char* windowName, const char* buttonName)
{
    HWND hWnd = FindWindowA(NULL, windowName);
    if (hWnd == NULL)
    {
        cout << "没有找到窗口：" << windowName << endl;
        return;
    }

    if (strcmp(buttonName, windowName) == 0)
    {
        cout << "窗口置顶成功" << endl;
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        return;
    }
    else
    {
        cout << buttonName <<windowName;
        // 设置窗口为活动窗口
        SetForegroundWindow(hWnd);
    }
	
    
	HWND btnWnd = FindWindowExA(hWnd, NULL, "Button", buttonName);
    if (btnWnd == NULL)
    {
        cout << "没有找到按钮：" << buttonName << endl;
        return;
    }
    
    // 获取按钮的位置和大小
    RECT rect;
    GetWindowRect(btnWnd, &rect);

    // 计算鼠标的目标位置
    int x = rect.left + (rect.right - rect.left) / 2;
    int y = rect.top + (rect.bottom - rect.top) / 2;

    // 移动鼠标到目标位置
    SetCursorPos(x, y);

    // 模拟鼠标左键单击事件
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

    std::cout << "按钮点击成功" << std::endl;
}

int main()
{
	cout << "如果含有中文请直接在源代码里设置" << endl << "如果窗口名=按钮名则置顶窗口" << endl;
    
    //打印当前时间
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << dt;

    //输入窗口名
    string window;
    cout << "输入窗口名：";
    getline(cin, window);

    Sleep(50);

    //输入按钮名
	string text;
	cout << "输入按钮名：";
	getline(cin, text);
    
	autoClick(window.c_str(), text.c_str());
    //中文不支持
    return 0;
}
