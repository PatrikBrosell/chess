#include <stdio.h>
#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static void MainLoop(void);
static void InitGame(void); // initialize game state
static void DrawBoard(void);
static void DrawGame(void);

typedef enum pieces {
	EMPTY,
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN,
} pieces;

typedef struct Square {
	int x;
	int y;
	int piece;
	int color;
} Square;

#define SQUARE_SIZE 100

Rectangle g_board[10][10] = {0};
Square g_game[8][8] = {0};	// Game state

int g_screenWidth = 950;
int g_screenHeight = 950;

int main(void)
{
	InitGame();

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

void InitGame(void)
{
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 8; ++j) {
			g_game[i][j].x = i;
			g_game[i][j].y = j;
			g_game[i][j].piece = EMPTY;
		}
	}
	g_game[0][0].piece = ROOK;
	g_game[1][0].piece = KNIGHT;
	g_game[2][0].piece = BISHOP;
	g_game[3][0].piece = QUEEN;
	g_game[4][0].piece = KING;
	g_game[5][0].piece = BISHOP;
	g_game[6][0].piece = KNIGHT;
	g_game[7][0].piece = ROOK;
	for(int i = 0; i < 8; ++i) {
		g_game[i][1].piece = PAWN;
		g_game[i][6].piece = PAWN;
	}
	g_game[0][7].piece = ROOK;
	g_game[1][7].piece = KNIGHT;
	g_game[2][7].piece = BISHOP;
	g_game[3][7].piece = QUEEN;
	g_game[4][7].piece = KING;
	g_game[5][7].piece = BISHOP;
	g_game[6][7].piece = KNIGHT;
	g_game[7][7].piece = ROOK;
}

void MainLoop(void)
{
	BeginDrawing();
	DrawGame();
	EndDrawing();
}

void DrawGame(void)
{
	DrawBoard();
}

void DrawBoard(void)
{
	ClearBackground(GetColor(0x151515FF));
	for(int x = 0, black = 0; x < 10; ++x) {
		for(int y = 0; y < 10; ++y) {
			if(x == 0 && y == 0) {
				g_board[x][y] = (Rectangle) {SQUARE_SIZE/2*x, SQUARE_SIZE/2*y, SQUARE_SIZE/2, SQUARE_SIZE/2};
			} else if(x == 9 && y == 9) {
				g_board[x][y] = (Rectangle) {SQUARE_SIZE*x-SQUARE_SIZE/2, SQUARE_SIZE*y-SQUARE_SIZE/2, SQUARE_SIZE/2, SQUARE_SIZE/2};
			} else if(x == 9) {
				g_board[x][y] = (Rectangle) {SQUARE_SIZE*x-SQUARE_SIZE/2, SQUARE_SIZE*y-SQUARE_SIZE/2, SQUARE_SIZE/2, SQUARE_SIZE};
			} else if(y == 9) {
				g_board[x][y] = (Rectangle) {SQUARE_SIZE*x-SQUARE_SIZE/2, SQUARE_SIZE*y-SQUARE_SIZE/2, SQUARE_SIZE, SQUARE_SIZE/2};
			} else if(x == 0) {
				g_board[x][y] = (Rectangle) {SQUARE_SIZE*x, SQUARE_SIZE*y-SQUARE_SIZE/2, SQUARE_SIZE/2, SQUARE_SIZE};
			} else if(y == 0) {
				g_board[x][y] = (Rectangle) {SQUARE_SIZE*x-SQUARE_SIZE/2, SQUARE_SIZE*y, SQUARE_SIZE, SQUARE_SIZE/2};
			} else {
				g_board[x][y] = (Rectangle) {SQUARE_SIZE*x-SQUARE_SIZE/2, SQUARE_SIZE*y-SQUARE_SIZE/2, SQUARE_SIZE, SQUARE_SIZE};
			}
			if(black) {
				DrawRectangleRec(g_board[x][y], BLACK);
			} else {
				DrawRectangleRec(g_board[x][y], WHITE);
			}
			black ^= 1;
		}
		black ^= 1;
	}
}