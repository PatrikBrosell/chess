#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

typedef enum PIECE_TYPE {
	EMPTY,
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN,
} PIECE_TYPE;

typedef struct Square {
	int x;
	int y;
	int piece;
	int color;
} Square;

typedef enum PIECE_COLOR {
	PIECE_BLACK,
	PIECE_WHITE,
} PIECE_COLOR;

typedef struct Piece {
	PIECE_TYPE type;
	PIECE_COLOR color;
	Rectangle position;
	int letter;		// Letter
	int number;		// Number
	bool selected;
} Piece;

typedef struct {
	Piece* pieces;
} GameState;

#ifdef PLATFORM_WEB
static void MainLoop(void*);
#else
static void MainLoop(GameState*);
#endif

static void InitGame(GameState*); // initialize game state
static void DrawBoard(void);
static void DrawGame(GameState*);
static void DrawTextCenterRect(const char*, Rectangle, Color);
static void DrawPieces(GameState*);

int g_square_size = 100;

Rectangle g_board[10][10] = {0};

int g_screenWidth = 800;
int g_screenHeight = 800;

int main(void)
{
	GameState game_state = {0};
	InitGame(&game_state);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(g_screenWidth, g_screenHeight, "window title name");

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop_arg(MainLoop, &game_state, 0, 1);
#else

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		MainLoop(&game_state);
	}
#endif // PLATFORM_WEB

	CloseWindow();	// Close window and unload OpenGL context
	free(game_state.pieces);
	return 0;
}

void InitGame(GameState* game_state)
{
	game_state->pieces = calloc(32, sizeof(Piece));

	for(int i = 0; i < 32; ++i) {
		game_state->pieces[i].selected = false;
	}

	game_state->pieces[0].type = ROOK;
	game_state->pieces[0].letter = 'A';
	game_state->pieces[0].number = 1;
	game_state->pieces[0].color = PIECE_WHITE;

	game_state->pieces[1].type = KNIGHT;
	game_state->pieces[1].letter = 'B';
	game_state->pieces[1].number = 1;
	game_state->pieces[1].color = PIECE_WHITE;

	game_state->pieces[2].type = BISHOP;
	game_state->pieces[2].letter = 'C';
	game_state->pieces[2].number = 1;
	game_state->pieces[2].color = PIECE_WHITE;

	game_state->pieces[3].type = QUEEN;
	game_state->pieces[3].letter = 'D';
	game_state->pieces[3].number = 1;
	game_state->pieces[3].color = PIECE_WHITE;

	game_state->pieces[4].type = KING;
	game_state->pieces[4].letter = 'E';
	game_state->pieces[4].number = 1;
	game_state->pieces[4].color = PIECE_WHITE;

	game_state->pieces[5].type = BISHOP;
	game_state->pieces[5].letter = 'F';
	game_state->pieces[5].number = 1;
	game_state->pieces[5].color = PIECE_WHITE;

	game_state->pieces[6].type = KNIGHT;
	game_state->pieces[6].letter = 'G';
	game_state->pieces[6].number = 1;
	game_state->pieces[6].color = PIECE_WHITE;

	game_state->pieces[7].type = ROOK;
	game_state->pieces[7].letter = 'H';
	game_state->pieces[7].number = 1;
	game_state->pieces[7].color = PIECE_WHITE;

	game_state->pieces[8].type = PAWN;
	game_state->pieces[8].letter = 'A';
	game_state->pieces[8].number = 2;
	game_state->pieces[8].color = PIECE_WHITE;

	game_state->pieces[9].type = PAWN;
	game_state->pieces[9].letter = 'B';
	game_state->pieces[9].number = 2;
	game_state->pieces[9].color = PIECE_WHITE;

	game_state->pieces[10].type = PAWN;
	game_state->pieces[10].letter = 'C';
	game_state->pieces[10].number = 2;
	game_state->pieces[10].color = PIECE_WHITE;

	game_state->pieces[11].type = PAWN;
	game_state->pieces[11].letter = 'D';
	game_state->pieces[11].number = 2;
	game_state->pieces[11].color = PIECE_WHITE;

	game_state->pieces[12].type = PAWN;
	game_state->pieces[12].letter = 'E';
	game_state->pieces[12].number = 2;
	game_state->pieces[12].color = PIECE_WHITE;

	game_state->pieces[13].type = PAWN;
	game_state->pieces[13].letter = 'F';
	game_state->pieces[13].number = 2;
	game_state->pieces[13].color = PIECE_WHITE;

	game_state->pieces[14].type = PAWN;
	game_state->pieces[14].letter = 'G';
	game_state->pieces[14].number = 2;
	game_state->pieces[14].color = PIECE_WHITE;

	game_state->pieces[15].type = PAWN;
	game_state->pieces[15].letter = 'H';
	game_state->pieces[15].number = 2;
	game_state->pieces[15].color = PIECE_WHITE;

	// ------------------

	game_state->pieces[16].type = ROOK;
	game_state->pieces[16].letter = 'A';
	game_state->pieces[16].number = 8;
	game_state->pieces[16].color = PIECE_BLACK;

	game_state->pieces[17].type = KNIGHT;
	game_state->pieces[17].letter = 'B';
	game_state->pieces[17].number = 8;
	game_state->pieces[17].color = PIECE_BLACK;

	game_state->pieces[18].type = BISHOP;
	game_state->pieces[18].letter = 'C';
	game_state->pieces[18].number = 8;
	game_state->pieces[18].color = PIECE_BLACK;

	game_state->pieces[19].type = QUEEN;
	game_state->pieces[19].letter = 'D';
	game_state->pieces[19].number = 8;
	game_state->pieces[19].color = PIECE_BLACK;

	game_state->pieces[20].type = KING;
	game_state->pieces[20].letter = 'E';
	game_state->pieces[20].number = 8;
	game_state->pieces[20].color = PIECE_BLACK;

	game_state->pieces[21].type = BISHOP;
	game_state->pieces[21].letter = 'F';
	game_state->pieces[21].number = 8;
	game_state->pieces[21].color = PIECE_BLACK;

	game_state->pieces[22].type = KNIGHT;
	game_state->pieces[22].letter = 'G';
	game_state->pieces[22].number = 8;
	game_state->pieces[22].color = PIECE_BLACK;

	game_state->pieces[23].type = ROOK;
	game_state->pieces[23].letter = 'H';
	game_state->pieces[23].number = 8;
	game_state->pieces[23].color = PIECE_BLACK;

	game_state->pieces[24].type = PAWN;
	game_state->pieces[24].letter = 'A';
	game_state->pieces[24].number = 7;
	game_state->pieces[24].color = PIECE_BLACK;

	game_state->pieces[25].type = PAWN;
	game_state->pieces[25].letter = 'B';
	game_state->pieces[25].number = 7;
	game_state->pieces[25].color = PIECE_BLACK;

	game_state->pieces[26].type = PAWN;
	game_state->pieces[26].letter = 'C';
	game_state->pieces[26].number = 7;
	game_state->pieces[26].color = PIECE_BLACK;

	game_state->pieces[27].type = PAWN;
	game_state->pieces[27].letter = 'D';
	game_state->pieces[27].number = 7;
	game_state->pieces[27].color = PIECE_BLACK;

	game_state->pieces[28].type = PAWN;
	game_state->pieces[28].letter = 'E';
	game_state->pieces[28].number = 7;
	game_state->pieces[28].color = PIECE_BLACK;

	game_state->pieces[29].type = PAWN;
	game_state->pieces[29].letter = 'F';
	game_state->pieces[29].number = 7;
	game_state->pieces[29].color = PIECE_BLACK;

	game_state->pieces[30].type = PAWN;
	game_state->pieces[30].letter = 'G';
	game_state->pieces[30].number = 7;
	game_state->pieces[30].color = PIECE_BLACK;

	game_state->pieces[31].type = PAWN;
	game_state->pieces[31].letter = 'H';
	game_state->pieces[31].number = 7;
	game_state->pieces[31].color = PIECE_BLACK;
}

#ifdef PLATFORM_WEB
void MainLoop(void *gs)
{
	GameState* game_state = (GameState*) gs;
#else
void MainLoop(GameState *game_state)
{
#endif
	int w = GetScreenWidth();
	int h = GetScreenHeight();

	int win_size = w < h ? w : h;

	// Board is 8 + 0.5 + 0.5 = 9 squares wide
	g_square_size = win_size / 9;

	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		for(int i = 0; i < 32; ++i) {
			Vector2 mouse_pos = GetMousePosition();
			Piece p = game_state->pieces[i];
			if(CheckCollisionPointRec(mouse_pos, p.position)) {
				game_state->pieces[i].selected = true;
			}
		}
	}

	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 mp = GetMouseDelta();
		for(int i = 0; i < 32; ++i) {
			if(game_state->pieces[i].selected) {
				game_state->pieces[i].position.x += mp.x;
				game_state->pieces[i].position.y += mp.y;
			}
		}
	} else {
		Vector2 mp = GetMousePosition();
		for(int i = 0; i < 10; ++i) {
			for(int j = 0; j < 10; ++j) {
				if(CheckCollisionPointRec(mp, g_board[i][j])) {
					for(int k = 0; k < 32; ++k) {
						if(game_state->pieces[k].selected) {
							game_state->pieces[k].selected = false;
							game_state->pieces[k].letter = 'A' + i-1;
							game_state->pieces[k].number = j;
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < 32; ++i) {
		int x = game_state->pieces[i].letter - 'A';
		int y = game_state->pieces[i].number - 1;
		if(!game_state->pieces[i].selected) {
			game_state->pieces[i].position = g_board[x+1][y+1];
		}
	}


	BeginDrawing();
	DrawGame(game_state);
	EndDrawing();
}

void DrawGame(GameState *game_state)
{
	DrawBoard();
	DrawPieces(game_state);
}

void DrawPieces(GameState *game_state)
{
	for(int i = 0; i < 32; ++i) {
		Piece p = game_state->pieces[i];
		Color color;
		if(p.color == PIECE_BLACK) {
			color = GetColor(0x281900FF);
		} else if(p.color == PIECE_WHITE) {
			color = GetColor(0xFFD899FF);
		}
		switch(p.type) {
			case KING:
				DrawTextCenterRect("Kng", p.position, color);
				break;
			case QUEEN:
				DrawTextCenterRect("Qu", p.position, color);
				break;
			case ROOK:
				DrawTextCenterRect("R", p.position, color);
				break;
			case BISHOP:
				DrawTextCenterRect("B", p.position, color);
				break;
			case KNIGHT:
				DrawTextCenterRect("Kn", p.position, color);
				break;
			case PAWN:
				DrawTextCenterRect("P", p.position, color);
				break;
			case EMPTY:
				continue;
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
