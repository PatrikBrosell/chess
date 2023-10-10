#include <stdio.h>
#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static void MainLoop(void);

int g_screenWidth = 950;
int g_screenHeight = 950;

int main(void)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(g_screenWidth, g_screenHeight, "window title name");

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(MainLoop, 0, 1);
#else

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		MainLoop();
	}
#endif // PLATFORM_WEB

	CloseWindow();	// Close window and unload OpenGL context
	return 0;
}

void MainLoop(void)
{
	BeginDrawing();
	EndDrawing();
}
