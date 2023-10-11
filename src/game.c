#include <stdio.h>
#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static void MainLoop(void);
static void InitGame(void); // initialize game state
static void DrawBoard(void);
static void DrawGame(void);
static void DrawTextCenterRect(const char*, Rectangle, Color);
static void DrawPieces(void);

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

int g_square_size = 100;

Rectangle g_board[10][10] = {0};
Square g_game[8][8] = {0};	// Game state

int g_screenWidth = 800;
int g_screenHeight = 800;

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
	int w = GetScreenWidth();
	int h = GetScreenHeight();

	int win_size = w < h ? w : h;

	// Board is 8 + 0.5 + 0.5 = 9 squares wide
	g_square_size = win_size / 9;


	BeginDrawing();
	DrawGame();
	EndDrawing();
}

void DrawGame(void)
{
	DrawBoard();
	DrawPieces();
}

void DrawPieces(void)
{
	for(int x = 0; x < 8; ++x) {
		for(int y = 0; y < 8; ++y) {
			switch(g_game[x][y].piece) {
				case KING:
					DrawTextCenterRect("Kng", g_board[x+1][y+1], RED);
					break;
				case QUEEN:
					DrawTextCenterRect("Qu", g_board[x+1][y+1], RED);
					break;
				case ROOK:
					DrawTextCenterRect("R", g_board[x+1][y+1], RED);
					break;
				case BISHOP:
					DrawTextCenterRect("B", g_board[x+1][y+1], RED);
					break;
				case KNIGHT:
					DrawTextCenterRect("Kn", g_board[x+1][y+1], RED);
					break;
				case PAWN:
					DrawTextCenterRect("P", g_board[x+1][y+1], RED);
					break;
				case EMPTY:
					continue;
			}
		}
	}
}

void DrawBoard(void)
{
	ClearBackground(GetColor(0x151515FF));
	for(int x = 0, black = 0; x < 10; ++x) {
		for(int y = 0; y < 10; ++y) {
			if(x == 0 && y == 0) {
				g_board[x][y] = (Rectangle) {g_square_size/2*x, g_square_size/2*y, g_square_size/2, g_square_size/2};
			} else if(x == 9 && y == 9) {
				g_board[x][y] = (Rectangle) {g_square_size*x-g_square_size/2, g_square_size*y-g_square_size/2, g_square_size/2, g_square_size/2};
			} else if(x == 9) {
				g_board[x][y] = (Rectangle) {g_square_size*x-g_square_size/2, g_square_size*y-g_square_size/2, g_square_size/2, g_square_size};
			} else if(y == 9) {
				g_board[x][y] = (Rectangle) {g_square_size*x-g_square_size/2, g_square_size*y-g_square_size/2, g_square_size, g_square_size/2};
			} else if(x == 0) {
				g_board[x][y] = (Rectangle) {g_square_size*x, g_square_size*y-g_square_size/2, g_square_size/2, g_square_size};
			} else if(y == 0) {
				g_board[x][y] = (Rectangle) {g_square_size*x-g_square_size/2, g_square_size*y, g_square_size, g_square_size/2};
			} else {
				g_board[x][y] = (Rectangle) {g_square_size*x-g_square_size/2, g_square_size*y-g_square_size/2, g_square_size, g_square_size};
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

	//1..8
	for(int i = 0; i < 10; ++i) {
		switch(i) {
			case 1:
				DrawTextCenterRect("1", g_board[0][i], SKYBLUE);
				DrawTextCenterRect("1", g_board[9][i], SKYBLUE);
				break;
			case 2:
				DrawTextCenterRect("2", g_board[0][i], SKYBLUE);
				DrawTextCenterRect("2", g_board[9][i], SKYBLUE);
				break;
			case 3:
				DrawTextCenterRect("3", g_board[0][i], SKYBLUE);
				DrawTextCenterRect("3", g_board[9][i], SKYBLUE);
				break;
			case 4:
				DrawTextCenterRect("4", g_board[0][i], SKYBLUE);
				DrawTextCenterRect("4", g_board[9][i], SKYBLUE);
				break;
			case 5:
				DrawTextCenterRect("5", g_board[0][i], SKYBLUE);
				DrawTextCenterRect("5", g_board[9][i], SKYBLUE);
				break;
			case 6:
				DrawTextCenterRect("6", g_board[0][i], SKYBLUE);
				DrawTextCenterRect("6", g_board[9][i], SKYBLUE);
				break;
			case 7:
				DrawTextCenterRect("7", g_board[0][i], SKYBLUE);
				DrawTextCenterRect("7", g_board[9][i], SKYBLUE);
				break;
			case 8:
				DrawTextCenterRect("8", g_board[0][i], SKYBLUE);
				DrawTextCenterRect("8", g_board[9][i], SKYBLUE);
				break;
		}
	}

	//A..H
	for(int i = 0; i < 10; ++i) {
		switch(i) {
			case 1:
				DrawTextCenterRect("A", g_board[i][0], SKYBLUE);
				DrawTextCenterRect("A", g_board[i][9], SKYBLUE);
				break;
			case 2:
				DrawTextCenterRect("B", g_board[i][0], SKYBLUE);
				DrawTextCenterRect("B", g_board[i][9], SKYBLUE);
				break;
			case 3:
				DrawTextCenterRect("C", g_board[i][0], SKYBLUE);
				DrawTextCenterRect("C", g_board[i][9], SKYBLUE);
				break;
			case 4:
				DrawTextCenterRect("D", g_board[i][0], SKYBLUE);
				DrawTextCenterRect("D", g_board[i][9], SKYBLUE);
				break;
			case 5:
				DrawTextCenterRect("E", g_board[i][0], SKYBLUE);
				DrawTextCenterRect("E", g_board[i][9], SKYBLUE);
				break;
			case 6:
				DrawTextCenterRect("F", g_board[i][0], SKYBLUE);
				DrawTextCenterRect("F", g_board[i][9], SKYBLUE);
				break;
			case 7:
				DrawTextCenterRect("G", g_board[i][0], SKYBLUE);
				DrawTextCenterRect("G", g_board[i][9], SKYBLUE);
				break;
			case 8:
				DrawTextCenterRect("H", g_board[i][0], SKYBLUE);
				DrawTextCenterRect("H", g_board[i][9], SKYBLUE);
				break;
		}
	}
}

void DrawTextCenterRect(const char* text, Rectangle rect, Color color)
{
	Vector2 xy;
	int x1, x2;
	int y1, y2;
	x1 = rect.x;
	y1 = rect.y;
	x2 = rect.x;
	y2 = rect.y;
	x1 += rect.width/2;
	y1 += rect.height/2;
	x2 += rect.width/2;
	y2 += rect.height/2;
	xy = MeasureTextEx(GetFontDefault(), text, 40, 0);
	x1 -= xy.x/2;
	y1 -= xy.y/2;
	x2 -= xy.x/2;
	y2 -= xy.y/2;
	DrawText(text, x1, y1, 40, color);
	DrawText(text, x2, y2, 40, color);
}
