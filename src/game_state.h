#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <raylib.h>

typedef enum PIECE_TYPE {
	EMPTY,
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN,
} PIECE_TYPE;

typedef enum PIECE_COLOR {
	PIECE_BLACK,
	PIECE_WHITE,
} PIECE_COLOR;

typedef struct Piece {
	PIECE_TYPE type;
	PIECE_COLOR color;
	Rectangle position;
	int letter;		// Letter
	int number;		// Number
	bool selected;
	char name[4];
} Piece;

typedef struct {
	Piece* pieces;
	Rectangle board[10][10];
} GameState;

void InitGame(GameState*);
void MovePiece(int dest_letter, int dest_number, Piece*);
bool IsMoveLegal(int dest_letter, int dest_number, int src_letter, int src_number, Piece*);

#endif // GAME_STATE_H
