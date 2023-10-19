#ifndef UI_H
#define UI_H

#include "game_state.h"

typedef struct UserInterfaceData {
	int square_size;
	int screen_width;
	int screen_height;
} UserInterfaceData;

void DrawPieces(GameState*);
void DrawTextCenterRect(const char*, Rectangle, Color);

#endif // UI_H
