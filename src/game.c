#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#include "game_state.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#ifdef PLATFORM_WEB
static void MainLoop(void*);
#else
static void MainLoop(GameState*);
#endif

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
