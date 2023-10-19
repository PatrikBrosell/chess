#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#include "game_state.h"
#include "ui.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

typedef struct main_loop_args_t {
	GameState* gs;
	UserInterfaceData* uid;
} main_loop_args_t;

#ifdef PLATFORM_WEB
static void MainLoop(void*);
#else
static void MainLoop(main_loop_args_t*);
#endif

static void DrawBoard(GameState*, UserInterfaceData*);
static void DrawGame(GameState*, UserInterfaceData*);

int main(void)
{
	main_loop_args_t args = {0};
	GameState game_state = {0};
	UserInterfaceData uid = {0};
	uid.screen_width = 800;
	uid.screen_height = 800;
	args.gs = &game_state;
	args.uid = &uid;
	InitGame(&game_state);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(uid.screen_width, uid.screen_height, "window title name");

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop_arg(MainLoop, &args, 0, 1);
#else

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		MainLoop(&args);
	}
#endif // PLATFORM_WEB

	CloseWindow();	// Close window and unload OpenGL context
	free(game_state.pieces);
	return 0;
}

#ifdef PLATFORM_WEB
void MainLoop(void *_args)
{
	main_loop_args_t* args = (main_loop_args_t*) _args;
#else
void MainLoop(main_loop_args_t* args)
{
#endif
	GameState* game_state = args->gs;
	UserInterfaceData* uid = args->uid;
	uid->square_size = 100;
	int w = GetScreenWidth();
	int h = GetScreenHeight();

	int win_size = w < h ? w : h;

	// Board is 8 + 0.5 + 0.5 = 9 squares wide
	uid->square_size = win_size / 9;

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
				if(CheckCollisionPointRec(mp, game_state->board[i][j])) {
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
			game_state->pieces[i].position = game_state->board[x+1][y+1];
		}
	}


	BeginDrawing();
	DrawGame(game_state, uid);
	EndDrawing();
}

void DrawGame(GameState *game_state, UserInterfaceData *uid)
{
	DrawBoard(game_state, uid);
	DrawPieces(game_state);
}

void DrawBoard(GameState *game_state, UserInterfaceData *uid)
{
	ClearBackground(GetColor(0x151515FF));
	for(int x = 0, black = 0; x < 10; ++x) {
		for(int y = 0; y < 10; ++y) {
			if(x == 0 && y == 0) {
				game_state->board[x][y] = (Rectangle) {uid->square_size/2*x, uid->square_size/2*y, uid->square_size/2, uid->square_size/2};
			} else if(x == 9 && y == 9) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*x-uid->square_size/2, uid->square_size*y-uid->square_size/2, uid->square_size/2, uid->square_size/2};
			} else if(x == 9) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*x-uid->square_size/2, uid->square_size*y-uid->square_size/2, uid->square_size/2, uid->square_size};
			} else if(y == 9) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*x-uid->square_size/2, uid->square_size*y-uid->square_size/2, uid->square_size, uid->square_size/2};
			} else if(x == 0) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*x, uid->square_size*y-uid->square_size/2, uid->square_size/2, uid->square_size};
			} else if(y == 0) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*x-uid->square_size/2, uid->square_size*y, uid->square_size, uid->square_size/2};
			} else {
				game_state->board[x][y] = (Rectangle) {uid->square_size*x-uid->square_size/2, uid->square_size*y-uid->square_size/2, uid->square_size, uid->square_size};
			}
			if(black) {
				DrawRectangleRec(game_state->board[x][y], BLACK);
			} else {
				DrawRectangleRec(game_state->board[x][y], WHITE);
			}
			black ^= 1;
		}
		black ^= 1;
	}

	//1..8
	for(int i = 0; i < 10; ++i) {
		switch(i) {
			case 1:
				DrawTextCenterRect("1", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("1", game_state->board[9][i], SKYBLUE);
				break;
			case 2:
				DrawTextCenterRect("2", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("2", game_state->board[9][i], SKYBLUE);
				break;
			case 3:
				DrawTextCenterRect("3", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("3", game_state->board[9][i], SKYBLUE);
				break;
			case 4:
				DrawTextCenterRect("4", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("4", game_state->board[9][i], SKYBLUE);
				break;
			case 5:
				DrawTextCenterRect("5", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("5", game_state->board[9][i], SKYBLUE);
				break;
			case 6:
				DrawTextCenterRect("6", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("6", game_state->board[9][i], SKYBLUE);
				break;
			case 7:
				DrawTextCenterRect("7", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("7", game_state->board[9][i], SKYBLUE);
				break;
			case 8:
				DrawTextCenterRect("8", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("8", game_state->board[9][i], SKYBLUE);
				break;
		}
	}

	//A..H
	for(int i = 0; i < 10; ++i) {
		switch(i) {
			case 1:
				DrawTextCenterRect("A", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("A", game_state->board[i][9], SKYBLUE);
				break;
			case 2:
				DrawTextCenterRect("B", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("B", game_state->board[i][9], SKYBLUE);
				break;
			case 3:
				DrawTextCenterRect("C", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("C", game_state->board[i][9], SKYBLUE);
				break;
			case 4:
				DrawTextCenterRect("D", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("D", game_state->board[i][9], SKYBLUE);
				break;
			case 5:
				DrawTextCenterRect("E", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("E", game_state->board[i][9], SKYBLUE);
				break;
			case 6:
				DrawTextCenterRect("F", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("F", game_state->board[i][9], SKYBLUE);
				break;
			case 7:
				DrawTextCenterRect("G", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("G", game_state->board[i][9], SKYBLUE);
				break;
			case 8:
				DrawTextCenterRect("H", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("H", game_state->board[i][9], SKYBLUE);
				break;
		}
	}
}
