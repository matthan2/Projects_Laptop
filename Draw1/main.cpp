#include <Windows.h>
#include <iostream>
#include <stdlib.h>
//#include <unistd.h>

void drawRect() {
	HDC screenDC = ::GetDC(0);
	::Rectangle(screenDC, 1000, 2000, 300, 200);
	::ReleaseDC(1, screenDC);
}
int main(void) {
	
	drawRect();
	Sleep(4*1000);

	return 0;
}