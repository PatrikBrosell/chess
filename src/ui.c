#include "ui.h"
#include "game_state.h"

#include <raylib.h>

void DrawGame(GameState *game_state, UserInterfaceData *uid)
{
	DrawBoard(game_state, uid);
	DrawPieces(game_state, uid);
}

void DrawBoard(GameState *game_state, UserInterfaceData *uid)
{
	ClearBackground(GetColor(0x151515FF));
	for(int x = 0, black = 0; x < 10; ++x) {
		for(int y = 0; y < 10; ++y) {
			if(x == 0 && y == 0) {
				game_state->board[x][y] = (Rectangle) {uid->square_size/2*y, uid->square_size/2*x, uid->square_size/2, uid->square_size/2};
			} else if(x == 9 && y == 9) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x-uid->square_size/2, uid->square_size/2, uid->square_size/2};
			} else if(y == 9) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x-uid->square_size/2, uid->square_size/2, uid->square_size};
			} else if(x == 9) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x-uid->square_size/2, uid->square_size, uid->square_size/2};
			} else if(y == 0) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*y, uid->square_size*x-uid->square_size/2, uid->square_size/2, uid->square_size};
			} else if(x == 0) {
				game_state->board[x][y] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x, uid->square_size, uid->square_size/2};
			} else {
				game_state->board[x][y] = (Rectangle) {uid->square_size*y-uid->square_size/2, uid->square_size*x-uid->square_size/2, uid->square_size, uid->square_size};
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
				DrawTextCenterRect("1", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("1", game_state->board[i][9], SKYBLUE);
				break;
			case 2:
				DrawTextCenterRect("2", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("2", game_state->board[i][9], SKYBLUE);
				break;
			case 3:
				DrawTextCenterRect("3", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("3", game_state->board[i][9], SKYBLUE);
				break;
			case 4:
				DrawTextCenterRect("4", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("4", game_state->board[i][9], SKYBLUE);
				break;
			case 5:
				DrawTextCenterRect("5", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("5", game_state->board[i][9], SKYBLUE);
				break;
			case 6:
				DrawTextCenterRect("6", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("6", game_state->board[i][9], SKYBLUE);
				break;
			case 7:
				DrawTextCenterRect("7", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("7", game_state->board[i][9], SKYBLUE);
				break;
			case 8:
				DrawTextCenterRect("8", game_state->board[i][0], SKYBLUE);
				DrawTextCenterRect("8", game_state->board[i][9], SKYBLUE);
				break;
		}
	}

	//A..H
	for(int i = 0; i < 10; ++i) {
		switch(i) {
			case 1:
				DrawTextCenterRect("A", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("A", game_state->board[9][i], SKYBLUE);
				break;
			case 2:
				DrawTextCenterRect("B", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("B", game_state->board[9][i], SKYBLUE);
				break;
			case 3:
				DrawTextCenterRect("C", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("C", game_state->board[9][i], SKYBLUE);
				break;
			case 4:
				DrawTextCenterRect("D", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("D", game_state->board[9][i], SKYBLUE);
				break;
			case 5:
				DrawTextCenterRect("E", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("E", game_state->board[9][i], SKYBLUE);
				break;
			case 6:
				DrawTextCenterRect("F", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("F", game_state->board[9][i], SKYBLUE);
				break;
			case 7:
				DrawTextCenterRect("G", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("G", game_state->board[9][i], SKYBLUE);
				break;
			case 8:
				DrawTextCenterRect("H", game_state->board[0][i], SKYBLUE);
				DrawTextCenterRect("H", game_state->board[9][i], SKYBLUE);
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

void DrawPiece(Piece *piece, int square_size)
{
	int x, y;
	Color color = BLANK;
	Color bg_color = BLANK;
	if(piece->color == PIECE_BLACK) {
		color = GetColor(0x281900FF);
		bg_color = GetColor(0x000000FF);
	} else if(piece->color == PIECE_WHITE) {
		color = GetColor(0xFFD899FF);
		bg_color = GetColor(0xFFFFFFFF);
	}
	x = piece->position.x + piece->position.width/2;
	y = piece->position.y + piece->position.height/2;
	DrawCircle(x, y, square_size/2, BROWN);
	DrawCircle(x, y, square_size/2-4, bg_color);
	DrawTextCenterRect(piece->name, piece->position, color);
}

void DrawPieces(GameState *game_state, UserInterfaceData *uid)
{
	Piece p;
	for(int i = 0; i < 32; ++i) {
		p = game_state->pieces[i];
		if (&p == uid->selected_piece) {
			continue; // draw this piece last (on top)
		}
		DrawPiece(&p, uid->square_size);
	}

	for(int i = 0; i < 32; ++i) {
		p = game_state->pieces[i];
		if (&p == uid->selected_piece) {
			DrawPiece(&p, uid->square_size);
		}
	}
}
