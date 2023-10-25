#include "ui.h"

#include <raylib.h>

void DrawGame(UserInterfaceData *uid)
{
	DrawBoard(uid);
	DrawPieces(uid);
}

void DrawBoard(UserInterfaceData *uid)
{
	ClearBackground(GetColor(0x151515FF));
	for(int x = 0; x < 10; ++x) {
		for(int y = 0; y < 10; ++y) {
			if(x == 0 && y == 0) {
				uid->board.tl_corner = (Rectangle) {0, 0, uid->square_size/2, uid->square_size/2};
			} else if(x == 0 && y == 9) {
				uid->board.tr_corner = (Rectangle) {uid->square_size*y-uid->square_size/2, 0, uid->square_size/2, uid->square_size/2};
			} else if(x == 9 && y == 9) {
				uid->board.br_corner = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x-uid->square_size/2, uid->square_size/2, uid->square_size/2};
			} else if(x == 9 && y == 0) {
				uid->board.bl_corner = (Rectangle) {0, uid->square_size*x-uid->square_size/2, uid->square_size/2, uid->square_size/2};
			} else if(y == 9) {
				uid->board.border_right[x-1] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x-uid->square_size/2, uid->square_size/2, uid->square_size};
			} else if(x == 9) {
				uid->board.border_bottom[y-1] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x-uid->square_size/2, uid->square_size, uid->square_size/2};
			} else if(y == 0) {
				uid->board.border_left[x-1] = (Rectangle) {uid->square_size*y, uid->square_size*x-uid->square_size/2, uid->square_size/2, uid->square_size};
			} else if(x == 0) {
				uid->board.border_top[y-1] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x, uid->square_size, uid->square_size/2};
			} else {
				uid->board.board[x-1][y-1] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x-uid->square_size/2, uid->square_size, uid->square_size};
			}
		}
	}

	DrawRectangleRec(uid->board.tl_corner, WHITE);
	DrawRectangleRec(uid->board.tr_corner, BLACK);
	DrawRectangleRec(uid->board.br_corner, WHITE);
	DrawRectangleRec(uid->board.bl_corner, BLACK);

	for(int y = 0, black = 0; y < 8; ++y) {
		if(black) {
			DrawRectangleRec(uid->board.border_left[y], WHITE);
			DrawRectangleRec(uid->board.border_right[y], BLACK);
			DrawRectangleRec(uid->board.border_bottom[y], BLACK);
			DrawRectangleRec(uid->board.border_top[y], WHITE);
		} else {
			DrawRectangleRec(uid->board.border_left[y], BLACK);
			DrawRectangleRec(uid->board.border_right[y], WHITE);
			DrawRectangleRec(uid->board.border_bottom[y], WHITE);
			DrawRectangleRec(uid->board.border_top[y], BLACK);
		}
		black ^= 1;

	}

	for(int rank = 0, black = 0; rank < 8; ++rank) {
		for(int file = 0; file < 8; ++file) {
			if(black) {
				DrawRectangleRec(uid->board.board[rank][file], BLACK);
			} else {
				DrawRectangleRec(uid->board.board[rank][file], WHITE);
			}
			black ^= 1;
		}
		black ^= 1;
	}

	//1..8
	for(int i = 0; i < 10; ++i) {
		switch(i) {
			case 1:
				DrawTextCenterRect("1", uid->board.border_left[i-1], SKYBLUE);
				DrawTextCenterRect("1", uid->board.border_right[i-1], SKYBLUE);
				break;
			case 2:
				DrawTextCenterRect("2", uid->board.border_left[i-1], SKYBLUE);
				DrawTextCenterRect("2", uid->board.border_right[i-1], SKYBLUE);
				break;
			case 3:
				DrawTextCenterRect("3", uid->board.border_left[i-1], SKYBLUE);
				DrawTextCenterRect("3", uid->board.border_right[i-1], SKYBLUE);
				break;
			case 4:
				DrawTextCenterRect("4", uid->board.border_left[i-1], SKYBLUE);
				DrawTextCenterRect("4", uid->board.border_right[i-1], SKYBLUE);
				break;
			case 5:
				DrawTextCenterRect("5", uid->board.border_left[i-1], SKYBLUE);
				DrawTextCenterRect("5", uid->board.border_right[i-1], SKYBLUE);
				break;
			case 6:
				DrawTextCenterRect("6", uid->board.border_left[i-1], SKYBLUE);
				DrawTextCenterRect("6", uid->board.border_right[i-1], SKYBLUE);
				break;
			case 7:
				DrawTextCenterRect("7", uid->board.border_left[i-1], SKYBLUE);
				DrawTextCenterRect("7", uid->board.border_right[i-1], SKYBLUE);
				break;
			case 8:
				DrawTextCenterRect("8", uid->board.border_left[i-1], SKYBLUE);
				DrawTextCenterRect("8", uid->board.border_right[i-1], SKYBLUE);
				break;
		}
	}

	//A..H
	for(int i = 0; i < 10; ++i) {
		switch(i) {
			case 1:
				DrawTextCenterRect("A", uid->board.border_top[i-1], SKYBLUE);
				DrawTextCenterRect("A", uid->board.border_bottom[i-1], SKYBLUE);
				break;
			case 2:
				DrawTextCenterRect("B", uid->board.border_top[i-1], SKYBLUE);
				DrawTextCenterRect("B", uid->board.border_bottom[i-1], SKYBLUE);
				break;
			case 3:
				DrawTextCenterRect("C", uid->board.border_top[i-1], SKYBLUE);
				DrawTextCenterRect("C", uid->board.border_bottom[i-1], SKYBLUE);
				break;
			case 4:
				DrawTextCenterRect("D", uid->board.border_top[i-1], SKYBLUE);
				DrawTextCenterRect("D", uid->board.border_bottom[i-1], SKYBLUE);
				break;
			case 5:
				DrawTextCenterRect("E", uid->board.border_top[i-1], SKYBLUE);
				DrawTextCenterRect("E", uid->board.border_bottom[i-1], SKYBLUE);
				break;
			case 6:
				DrawTextCenterRect("F", uid->board.border_top[i-1], SKYBLUE);
				DrawTextCenterRect("F", uid->board.border_bottom[i-1], SKYBLUE);
				break;
			case 7:
				DrawTextCenterRect("G", uid->board.border_top[i-1], SKYBLUE);
				DrawTextCenterRect("G", uid->board.border_bottom[i-1], SKYBLUE);
				break;
			case 8:
				DrawTextCenterRect("H", uid->board.border_top[i-1], SKYBLUE);
				DrawTextCenterRect("H", uid->board.border_bottom[i-1], SKYBLUE);
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

void DrawPiece(UI_Piece *piece, int square_size)
{
	int x, y;
	Color color = BLANK;
	Color bg_color = BLANK;
	if(piece->is_black) {
		color = GetColor(0x281900FF);
		bg_color = GetColor(0x000000FF);
	} else if(!piece->is_black) {
		color = GetColor(0xFFD899FF);
		bg_color = GetColor(0xFFFFFFFF);
	}
	x = piece->position.x + piece->position.width/2;
	y = piece->position.y + piece->position.height/2;
	DrawCircle(x, y, square_size/2, BROWN);
	DrawCircle(x, y, square_size/2-4, bg_color);
	DrawTextCenterRect(piece->name, piece->position, color);
}

void DrawPieces(UserInterfaceData *uid)
{
	UI_Piece p;
	for(int i = 0; i < 32; ++i) {
		p = uid->pieces[i];
		if (&p == uid->selected_piece) {
			continue; // draw this piece last (on top)
		}
		DrawPiece(&p, uid->square_size);
	}

	for(int i = 0; i < 32; ++i) {
		p = uid->pieces[i];
		if (&p == uid->selected_piece) {
			DrawPiece(&p, uid->square_size);
		}
	}
}
