#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
		for(int i = 0; i < 8; ++i) {
			for(int j = 0; j < 8; ++j) {
				Vector2 mouse_pos = GetMousePosition();
				Rectangle r = uid->board.board[i][j];

				if(CheckCollisionPointRec(mouse_pos, r)) {
					if(uid->squares[i][j].piece != NULL) {
						uid->selected_piece = uid->squares[i][j].piece;
					}
				}
			}
		}
	}

	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 mp = GetMouseDelta();
		if(uid->selected_piece != NULL) {
			uid->selected_piece->position.x += mp.x;
			uid->selected_piece->position.y += mp.y;
		}
	} else {
		Vector2 mp = GetMousePosition();
		for(int rank = 0; rank < 8; ++rank) {
			for(int file = 0; file < 8; ++file) {
				if(CheckCollisionPointRec(mp, uid->board.board[rank][file])) {
					for(int k = 0; k < 32; ++k) {
						if(&uid->pieces[k] == uid->selected_piece) {
							uid->selected_piece = NULL;
							MovePiece(rank, file, &game_state->pieces[k]);
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < 32; ++i) {
		int file;
		int rank;
		bool is_black;
		rank = game_state->pieces[i].rank;
		file = game_state->pieces[i].file;
		is_black = game_state->pieces[i].is_black;
		switch(game_state->pieces[i].type) {
			case KING:
				strcpy(uid->pieces[i].name, "Kng");
				break;
			case QUEEN:
				strcpy(uid->pieces[i].name, "Qu");
				break;
			case ROOK:
				strcpy(uid->pieces[i].name, "R");
				break;
			case BISHOP:
				strcpy(uid->pieces[i].name, "B");
				break;
			case KNIGHT:
				strcpy(uid->pieces[i].name, "K");
				break;
			case PAWN:
				strcpy(uid->pieces[i].name, "P");
				break;
			case EMPTY:
				strcpy(uid->pieces[i].name, "ERR");
				break;
		}
		if(&uid->pieces[i] != uid->selected_piece) {
			uid->squares[rank][file].piece = &uid->pieces[i];
			uid->pieces[i].position = uid->board.board[rank][file];
			uid->pieces[i].is_black = is_black;
		}
	}

	BeginDrawing();
	DrawGame(uid);
	EndDrawing();
}
