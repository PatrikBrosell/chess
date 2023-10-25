#ifndef UI_H
#define UI_H

#include <raylib.h>

typedef struct UI_Piece {
	Rectangle position;
	char name[4];
	bool is_black;
	Color color;
} UI_Piece;

typedef struct UI_Square {
	UI_Piece* piece;
} UI_Square;

typedef struct UI_Board {
	Rectangle border_top[8];
	Rectangle border_right[8];
	Rectangle border_bottom[8];
	Rectangle border_left[8];
	Rectangle tl_corner;
	Rectangle tr_corner;
	Rectangle br_corner;
	Rectangle bl_corner;
	Rectangle board[8][8];
} UI_Board;

typedef struct UserInterfaceData {
	int square_size;
	int screen_width;
	int screen_height;
	UI_Piece* selected_piece;
	UI_Board board;
	UI_Piece pieces[32];
	UI_Square squares[8][8];
} UserInterfaceData;

void DrawGame(UserInterfaceData*);
void DrawPieces(UserInterfaceData*);
void DrawTextCenterRect(const char*, Rectangle, Color);
void DrawBoard(UserInterfaceData*);

#endif // UI_H
