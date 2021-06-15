#include "Application.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Sleep(3000); // wait for the prev app to close (in case of updating)

	Application app;

	app.run();

	return 0;

}
