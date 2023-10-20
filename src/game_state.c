#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <raylib.h>

#include "game_state.h"

void InitGame(GameState* game_state)
{
	game_state->pieces = calloc(32, sizeof(Piece));

	for(int i = 0; i < 32; ++i) {
		game_state->pieces[i].selected = false;
	}

	game_state->pieces[0].type = ROOK;
	strcpy(game_state->pieces[0].name, "R");
	game_state->pieces[0].file = FILE_A;
	game_state->pieces[0].rank = RANK_1;
	game_state->pieces[0].color = PIECE_WHITE;

	game_state->pieces[1].type = KNIGHT;
	strcpy(game_state->pieces[1].name, "K");
	game_state->pieces[1].file = FILE_B;
	game_state->pieces[1].rank = RANK_1;
	game_state->pieces[1].color = PIECE_WHITE;

	game_state->pieces[2].type = BISHOP;
	strcpy(game_state->pieces[2].name, "B");
	game_state->pieces[2].file = FILE_C;
	game_state->pieces[2].rank = RANK_1;
	game_state->pieces[2].color = PIECE_WHITE;

	game_state->pieces[3].type = QUEEN;
	strcpy(game_state->pieces[3].name, "Qu");
	game_state->pieces[3].file = FILE_D;
	game_state->pieces[3].rank = RANK_1;
	game_state->pieces[3].color = PIECE_WHITE;

	game_state->pieces[4].type = KING;
	strcpy(game_state->pieces[4].name, "Kng");
	game_state->pieces[4].file = FILE_E;
	game_state->pieces[4].rank = RANK_1;
	game_state->pieces[4].color = PIECE_WHITE;

	game_state->pieces[5].type = BISHOP;
	strcpy(game_state->pieces[5].name, "B");
	game_state->pieces[5].file = FILE_F;
	game_state->pieces[5].rank = RANK_1;
	game_state->pieces[5].color = PIECE_WHITE;

	game_state->pieces[6].type = KNIGHT;
	strcpy(game_state->pieces[6].name, "K");
	game_state->pieces[6].file = FILE_G;
	game_state->pieces[6].rank = RANK_1;
	game_state->pieces[6].color = PIECE_WHITE;

	game_state->pieces[7].type = ROOK;
	strcpy(game_state->pieces[7].name, "R");
	game_state->pieces[7].file = FILE_H;
	game_state->pieces[7].rank = RANK_1;
	game_state->pieces[7].color = PIECE_WHITE;

	game_state->pieces[8].type = PAWN;
	strcpy(game_state->pieces[8].name, "P");
	game_state->pieces[8].file = FILE_A;
	game_state->pieces[8].rank = RANK_2;
	game_state->pieces[8].color = PIECE_WHITE;

	game_state->pieces[9].type = PAWN;
	strcpy(game_state->pieces[9].name, "P");
	game_state->pieces[9].file = FILE_B;
	game_state->pieces[9].rank = RANK_2;
	game_state->pieces[9].color = PIECE_WHITE;

	game_state->pieces[10].type = PAWN;
	strcpy(game_state->pieces[10].name, "P");
	game_state->pieces[10].file = FILE_C;
	game_state->pieces[10].rank = RANK_2;
	game_state->pieces[10].color = PIECE_WHITE;

	game_state->pieces[11].type = PAWN;
	strcpy(game_state->pieces[11].name, "P");
	game_state->pieces[11].file = FILE_D;
	game_state->pieces[11].rank = RANK_2;
	game_state->pieces[11].color = PIECE_WHITE;

	game_state->pieces[12].type = PAWN;
	strcpy(game_state->pieces[12].name, "P");
	game_state->pieces[12].file = FILE_E;
	game_state->pieces[12].rank = RANK_2;
	game_state->pieces[12].color = PIECE_WHITE;

	game_state->pieces[13].type = PAWN;
	strcpy(game_state->pieces[13].name, "P");
	game_state->pieces[13].file = FILE_F;
	game_state->pieces[13].rank = RANK_2;
	game_state->pieces[13].color = PIECE_WHITE;

	game_state->pieces[14].type = PAWN;
	strcpy(game_state->pieces[14].name, "P");
	game_state->pieces[14].file = FILE_G;
	game_state->pieces[14].rank = RANK_2;
	game_state->pieces[14].color = PIECE_WHITE;

	game_state->pieces[15].type = PAWN;
	strcpy(game_state->pieces[15].name, "P");
	game_state->pieces[15].file = FILE_H;
	game_state->pieces[15].rank = RANK_2;
	game_state->pieces[15].color = PIECE_WHITE;

	// ------------------

	game_state->pieces[16].type = ROOK;
	strcpy(game_state->pieces[16].name, "R");
	game_state->pieces[16].file = FILE_A;
	game_state->pieces[16].rank = RANK_8;
	game_state->pieces[16].color = PIECE_BLACK;

	game_state->pieces[17].type = KNIGHT;
	strcpy(game_state->pieces[17].name, "K");
	game_state->pieces[17].file = FILE_B;
	game_state->pieces[17].rank = RANK_8;
	game_state->pieces[17].color = PIECE_BLACK;

	game_state->pieces[18].type = BISHOP;
	strcpy(game_state->pieces[18].name, "B");
	game_state->pieces[18].file = FILE_C;
	game_state->pieces[18].rank = RANK_8;
	game_state->pieces[18].color = PIECE_BLACK;

	game_state->pieces[19].type = QUEEN;
	strcpy(game_state->pieces[19].name, "Qu");
	game_state->pieces[19].file = FILE_D;
	game_state->pieces[19].rank = RANK_8;
	game_state->pieces[19].color = PIECE_BLACK;

	game_state->pieces[20].type = KING;
	strcpy(game_state->pieces[20].name, "K");
	game_state->pieces[20].file = FILE_E;
	game_state->pieces[20].rank = RANK_8;
	game_state->pieces[20].color = PIECE_BLACK;

	game_state->pieces[21].type = BISHOP;
	strcpy(game_state->pieces[21].name, "B");
	game_state->pieces[21].file = FILE_F;
	game_state->pieces[21].rank = RANK_8;
	game_state->pieces[21].color = PIECE_BLACK;

	game_state->pieces[22].type = KNIGHT;
	strcpy(game_state->pieces[22].name, "K");
	game_state->pieces[22].file = FILE_G;
	game_state->pieces[22].rank = RANK_8;
	game_state->pieces[22].color = PIECE_BLACK;

	game_state->pieces[23].type = ROOK;
	strcpy(game_state->pieces[23].name, "R");
	game_state->pieces[23].file = FILE_H;
	game_state->pieces[23].rank = RANK_8;
	game_state->pieces[23].color = PIECE_BLACK;

	game_state->pieces[24].type = PAWN;
	strcpy(game_state->pieces[24].name, "P");
	game_state->pieces[24].file = FILE_A;
	game_state->pieces[24].rank = RANK_7;
	game_state->pieces[24].color = PIECE_BLACK;

	game_state->pieces[25].type = PAWN;
	strcpy(game_state->pieces[25].name, "P");
	game_state->pieces[25].file = FILE_B;
	game_state->pieces[25].rank = RANK_7;
	game_state->pieces[25].color = PIECE_BLACK;

	game_state->pieces[26].type = PAWN;
	strcpy(game_state->pieces[26].name, "P");
	game_state->pieces[26].file = FILE_C;
	game_state->pieces[26].rank = RANK_7;
	game_state->pieces[26].color = PIECE_BLACK;

	game_state->pieces[27].type = PAWN;
	strcpy(game_state->pieces[27].name, "P");
	game_state->pieces[27].file = FILE_D;
	game_state->pieces[27].rank = RANK_7;
	game_state->pieces[27].color = PIECE_BLACK;

	game_state->pieces[28].type = PAWN;
	strcpy(game_state->pieces[28].name, "P");
	game_state->pieces[28].file = FILE_E;
	game_state->pieces[28].rank = RANK_7;
	game_state->pieces[28].color = PIECE_BLACK;

	game_state->pieces[29].type = PAWN;
	strcpy(game_state->pieces[29].name, "P");
	game_state->pieces[29].file = FILE_F;
	game_state->pieces[29].rank = RANK_7;
	game_state->pieces[29].color = PIECE_BLACK;

	game_state->pieces[30].type = PAWN;
	strcpy(game_state->pieces[30].name, "P");
	game_state->pieces[30].file = FILE_G;
	game_state->pieces[30].rank = RANK_7;
	game_state->pieces[30].color = PIECE_BLACK;

	game_state->pieces[31].type = PAWN;
	strcpy(game_state->pieces[31].name, "P");
	game_state->pieces[31].file = FILE_H;
	game_state->pieces[31].rank = RANK_7;
	game_state->pieces[31].color = PIECE_BLACK;
}

bool IsMoveLegal(int dest_file, int dest_rank, int src_file, int src_rank, Piece* piece)
{
	switch(piece->type) {
		case KING:
			if (abs(src_file - dest_file) <= 1 && abs(src_rank - dest_rank) <= 1) {
				return true;
			} else {
				return false;
			}
			break;
		case QUEEN:
			if(src_file == dest_file || src_rank == dest_rank) {
				return true;
			}
			if( abs(src_file - dest_file) == abs(src_rank - dest_rank) ) {
				return true;
			}
			break;
		case ROOK:
			if(src_file == dest_file || src_rank == dest_rank) {
				return true;
			}
			break;
		case BISHOP:
			if( abs(src_file - dest_file) == abs(src_rank - dest_rank) ) {
				return true;
			}
			break;
		case KNIGHT:
			if( abs(src_file - dest_file) == 2 && abs(src_rank - dest_rank) == 1 ) {
				return true;
			}
			if( abs(src_rank - dest_rank) == 2 && abs(src_file - dest_file) == 1 ) {
				return true;
			}
			break;
		case PAWN:;
			int direction;
			direction = ((piece->color == PIECE_BLACK) ? 1: -1);
			if( src_rank == 2 || src_rank == 7) {
				if( (src_rank - dest_rank) == 2*direction && src_file == dest_file ) {
					return true;
				}
				if( (src_rank - dest_rank) == direction && src_file == dest_file ) {
					return true;
				}
			} else {
				if( (src_rank - dest_rank) == direction && src_file == dest_file ) {
					return true;
				}
			}
			break;
		case EMPTY:
			return false;
			break;
	}
	return false;
}

void MovePiece(int dest_file, int dest_rank, Piece* piece)
{
	if( IsMoveLegal(dest_file, dest_rank, piece->file, piece->rank, piece) ) {
		piece->file = dest_file;
		piece->rank = dest_rank;
	}
}
