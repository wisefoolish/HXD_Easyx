#include"Graph.h"

int main()
{
    initgraph(640, 480, SHOWCONSOLE);
    setbkcolor(RGB(255, 255, 255));
    cleardevice();
    setlinecolor(RGB(0, 0, 0));
    int x = 100, y = 100;
    circle(100, 100, 20);
    Sleep(1000);
    circle(110, 110, 20);
    Sleep(1000);
    circle(120, 120, 20); 
    system("pause");
    closegraph();
    return 0;
}
