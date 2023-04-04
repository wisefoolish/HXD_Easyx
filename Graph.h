#pragma once
#include<Windows.h>
#include<tchar.h>
#define DEFAULTWIN  0   // 默认窗口设置
#define SHOWCONSOLE 1   // 展示命令行
#define EM_MOUSE WM_MOUSEMOVE|WM_LBUTTONDOWN|WM_RBUTTONDOWN|WM_LBUTTONUP|WM_RBUTTONUP|WM_MBUTTONDOWN|WM_MBUTTONUP|WM_MOUSEWHEEL
#define EM_KEY WM_KEYDOWN|WM_KEYUP
typedef struct ExMessage
{
    UINT message;
    int x;
    int y;
    BOOL lbutton;
    BOOL rbutton;
    BOOL mbutton;
    int wheel;
    int vkcode;
};
HWND initgraph(int width, int height, int cmd);
void putpixel(int x, int y, COLORREF col);
void setlinecolor(COLORREF col);
void setfillcolor(COLORREF col);
void line(int x1, int y1, int x2, int y2);
void rectangle(int x1, int y1, int x2, int y2);
void fillrectangle(int x1, int y1, int x2, int y2);
void solidrectangle(int x1, int y1, int x2, int y2);
void floodfill(int x, int y, COLORREF col, UINT type);
void circle(int x, int y, int radius);
void fillcircle(int x, int y, int radius);
void solidcircle(int x, int y, int radius);
void setbkcolor(COLORREF col);
void closegraph();
void cleardevice();
void setbkcolor(COLORREF col);
ExMessage getmessage(UINT utype);
BOOL peekmessage(ExMessage* message, UINT utype);
