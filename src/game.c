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
				uid->selected_piece = &game_state->pieces[i];
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
		for(int rank = 0; rank < 10; ++rank) {
			for(int file = 0; file < 10; ++file) {
				if(CheckCollisionPointRec(mp, game_state->board[rank][file])) {
					for(int k = 0; k < 32; ++k) {
						if(&game_state->pieces[k] == uid->selected_piece) {
							uid->selected_piece = NULL;
							MovePiece(rank, file, &game_state->pieces[k]);
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < 32; ++i) {
		int file = game_state->pieces[i].file;
		int rank = game_state->pieces[i].rank;
		if(&game_state->pieces[i] != uid->selected_piece) {
			game_state->pieces[i].position = game_state->board[rank][file];
		}
	}


	BeginDrawing();
	DrawGame(game_state, uid);
	EndDrawing();
}
