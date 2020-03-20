/* taskbar killer - (c) sarah 2020 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* if you want to pre-define a workarea rect, comment out
 * or remove lines 28-31 and put your preferred rect in here */
RECT screenRect = {0, 0, 1920, 1052};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	/* get the handle to the taskbar */
	HWND taskbarHandle = FindWindowA("Shell_TrayWnd", NULL);
	if(!taskbarHandle) {
		puts("Taskbar window not found! Is explorer running\?");
		exit(1);
	}

	/* the function is called ShowWindow but it can hide windows too */
	ShowWindow(taskbarHandle, 0);

	/* get the size of the full screen */
	screenRect.left =	GetSystemMetrics(SM_XVIRTUALSCREEN);
	screenRect.right =	GetSystemMetrics(SM_CXVIRTUALSCREEN);
	screenRect.top =	GetSystemMetrics(SM_YVIRTUALSCREEN);
	screenRect.bottom =	GetSystemMetrics(SM_CYVIRTUALSCREEN);

	/* after the taskbar is gone, we can modify the workarea size
	 * without the taskbar stomping it
	 * NOTE: if you only want to kill the taskbar but not modify the
	 * workarea size, comment out or remove this line */
	SystemParametersInfo(SPI_SETWORKAREA, 0, &screenRect, 0);

	return 0;
}
