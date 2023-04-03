#include"Graph.h"

int main()
{
    HWND hwnd = initgraph(640, 480, SHOWCONSOLE);
    setlinecolor(RGB(255, 255, 255));
    /*line(10, 10, 100, 100);
    setlinecolor(RGB(0, 255, 0));
    line(100, 100, 200, 150);
    setfillcolor(RGB(0, 0, 255));*/
    rectangle(150, 150, 250, 250);
    //floodfill(200, 200, RGB(0, 255, 0), FLOODFILLBORDER);
    //setlinecolor(RGB(255, 255, 255));
    circle(300, 300, 50);
    system("pause");
    return 0;
}
