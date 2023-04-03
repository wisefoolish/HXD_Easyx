#include"Graph.h"

int main()
{
    HWND hwnd = initgraph(640, 480, SHOWCONSOLE);
    setlinecolor(RGB(255, 255, 255));
    rectangle(150, 150, 250, 250);
    setlinecolor(RGB(255,0,0));
    circle(300, 300, 50);
    system("pause");
    return 0;
}
