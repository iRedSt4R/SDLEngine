#include <Source/Core/SDLApp.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDLApp* app = nullptr;

int main(int argc, char* args[])
{
	app = new SDLApp();
	app->Init();
	app->StartEventLoop();

	delete app;

	return 0;
}
