# HXD_Easyx
个人复现easyx，追求代码量最少。适配vs2022。
并没有用到c++的语法，直接c语法运行这个Graph.h和Graph.cpp也是可以的，改个后缀名就行。

需要注意的地方：
1. Windows 中窗口的消息处理和线程绑定，如果你在主线程开辟窗口那你就要在主线程进行消息循环，而 easyx 图形库并没有在主线程进行消息循环，所以 easyx 的窗口在另外的线程中开辟出来并且在另外的线程中进行消息循环。
2. SendMessage(hwnd,WM_PAINT,0,0) 和 PostMessage(hwnd,WM_PAINT,0,0) 都不能真正地重绘窗口，只有用 InvalidateRect(hwnd, NULL, FALSE); 才能真正地重绘一个窗口，InvalidateRect 这个函数的意思是给窗口中增加一个矩形，这个矩形以指针的方式传递进函数的第二个参数中，第三个参数是是否刷新窗口，FALSE 不刷新，TRUE 刷新。传 FALSE 重绘窗口会快一点(情报来自CSDN)。
3. 用双缓冲技术绘图比较有可行性，在另一个线程要获取窗口线程的设备上下文句柄(HDC)得用 GetDC(hwnd)。获取到窗口的HDC后需要获取窗口的内存HDC(CreateCompatibleDC)和窗口位图(CreateCompatibleBitmap)，在窗口的内存HDC中进行绘图其操作会保存至位图中，更新窗口时直接BitBlt就行，具体流程如下
创建：
  HDC winDC = GetDC(HXD_global);
  HXD_memDc = CreateCompatibleDC(winDC);
  HXD_bitmap = CreateCompatibleBitmap(winDC, width, height);
  SelectObject(HXD_memDc, HXD_bitmap);
  ReleaseDC(HXD_global, winDC);
双缓冲：
  case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    BitBlt(hdc, 0, 0, HXD_width, HXD_height, HXD_memDc, 0, 0, SRCCOPY);
    EndPaint(hwnd, &ps);
    break;
程序结束时还要释放系统资源：
  ReleaseDC(HXD_global,HXD_memDc);
  DeleteObject(HXD_bitmap);
4. 由于用到另一个线程作为窗口线程执行消息循环，所以需要进行同步操作避免脏读脏写的问题，比如 hwnd 窗口句柄草创之时得等 hwnd 创建完成才能返回 hwnd 句柄，这时就得用同步操作，比如另一个线程操作完内存HDC了要在回调函数里执行双缓冲操作，也就是BitBlt，这时也需要同步，比如获取窗口消息，用钩子我不太清楚应该怎么做，我这里将所有消息都保存进一个队列里，说是队列其实只是一个数组，每次窗口线程获取到消息都将新获得的消息放入队列中，其他线程需要知道窗口线程获取到的消息只需要访问这个消息队列就行，接收到的消息超出消息队列的上限就出队一个消息然后入队一个消息，每次获取新的消息都只获取到队头的消息。这种操作无疑需要加锁。
5. 第4点提到的消息队列的方式，其实入队和出队用数组保存维护复杂度是O(n)，用首尾相接的环形链表则复杂度是O(1)，用双指针当然也可以达到O(1)的效果，不过逻辑有点复杂，我的这个实现不是最优的，据说还有一种用钩子函数的方法，不确定easyx的peekmessage和getmessage是不是用钩子函数做的SetWindowsHookEx。
6. 为了隐藏cmd窗口，还需要获取到cmd窗口的窗口句柄并且ShowWindow(hwnd,SW_HIDE);来隐藏这个窗口，获取cmd窗口的方法我用了"GetForegroundWindow();"获取程序刚运行时最上层的窗口。
