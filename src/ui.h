#ifndef UI_H
#define UI_H

#include "game_state.h"

typedef struct UserInterfaceData {
	int square_size;
	int screen_width;
	int screen_height;
} UserInterfaceData;

void DrawGame(GameState*, UserInterfaceData*);
void DrawPieces(GameState*, UserInterfaceData*);
void DrawTextCenterRect(const char*, Rectangle, Color);
void DrawBoard(GameState*, UserInterfaceData*);

#endif // UI_H
