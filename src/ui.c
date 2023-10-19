#include "ui.h"
#include "game_state.h"

#include <raylib.h>

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
