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
} Piece;

typedef struct {
	Piece* pieces;
} GameState;

void InitGame(GameState*);

#endif // GAME_STATE_H
