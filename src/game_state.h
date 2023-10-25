#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum CHESS_FILE {
	FILE_A = 0,
	FILE_B,
	FILE_C,
	FILE_D,
	FILE_E,
	FILE_F,
	FILE_G,
	FILE_H,
} CHESS_FILE;

typedef enum CHESS_RANK {
	RANK_1 = 0,
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
} CHESS_RANK;

typedef enum PIECE_TYPE {
	EMPTY,
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN,
} PIECE_TYPE;

typedef struct Piece {
	PIECE_TYPE type;
	bool is_black;
	int rank;		// Letter
	int file;		// Number
} Piece;

typedef struct {
	Piece* pieces;
} GameState;

void InitGame(GameState*);
void MovePiece(int dest_file, int dest_rank, Piece*);
bool IsMoveLegal(int dest_file, int dest_rank, int src_file, int src_rank, Piece*);

#endif // GAME_STATE_H
