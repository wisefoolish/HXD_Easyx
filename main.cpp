#include"Graph.h"
int main()
{
    initgraph(640, 480, DEFAULTWIN);
    ExMessage msg;
    BOOL isExit = FALSE;
    BOOL isLPress = FALSE;
    BOOL isRPress = FALSE;
    while (!isExit)
    {
        msg = getmessage();
        if (msg.message == WM_MOUSEMOVE)
        {
            if (isLPress)
            {
                putpixel(msg.x, msg.y, RGB(255, 0, 0));
            }
            else if (isRPress)
            {
                putpixel(msg.x, msg.y, RGB(0, 255, 0));
            }
            else putpixel(msg.x, msg.y, RGB(255, 255, 255));
        }
        else if (msg.message == WM_LBUTTONDOWN)
        {
            isLPress = TRUE;
        }
        else if (msg.message == WM_RBUTTONDOWN)
        {
            isRPress = TRUE;
        }
        else if (msg.message == WM_LBUTTONUP)
        {
            isLPress = FALSE;
        }
        else if (msg.message == WM_RBUTTONUP)
        {
            isRPress = FALSE;
        }
        else if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) isExit = TRUE;
    }
    closegraph();
    return 0;
}
