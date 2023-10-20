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
	game_state->pieces[0].letter = 'A';
	game_state->pieces[0].number = 1;
	game_state->pieces[0].color = PIECE_WHITE;

	game_state->pieces[1].type = KNIGHT;
	strcpy(game_state->pieces[1].name, "K");
	game_state->pieces[1].letter = 'B';
	game_state->pieces[1].number = 1;
	game_state->pieces[1].color = PIECE_WHITE;

	game_state->pieces[2].type = BISHOP;
	strcpy(game_state->pieces[2].name, "B");
	game_state->pieces[2].letter = 'C';
	game_state->pieces[2].number = 1;
	game_state->pieces[2].color = PIECE_WHITE;

	game_state->pieces[3].type = QUEEN;
	strcpy(game_state->pieces[3].name, "Qu");
	game_state->pieces[3].letter = 'D';
	game_state->pieces[3].number = 1;
	game_state->pieces[3].color = PIECE_WHITE;

	game_state->pieces[4].type = KING;
	strcpy(game_state->pieces[4].name, "Kng");
	game_state->pieces[4].letter = 'E';
	game_state->pieces[4].number = 1;
	game_state->pieces[4].color = PIECE_WHITE;

	game_state->pieces[5].type = BISHOP;
	strcpy(game_state->pieces[5].name, "B");
	game_state->pieces[5].letter = 'F';
	game_state->pieces[5].number = 1;
	game_state->pieces[5].color = PIECE_WHITE;

	game_state->pieces[6].type = KNIGHT;
	strcpy(game_state->pieces[6].name, "K");
	game_state->pieces[6].letter = 'G';
	game_state->pieces[6].number = 1;
	game_state->pieces[6].color = PIECE_WHITE;

	game_state->pieces[7].type = ROOK;
	strcpy(game_state->pieces[7].name, "R");
	game_state->pieces[7].letter = 'H';
	game_state->pieces[7].number = 1;
	game_state->pieces[7].color = PIECE_WHITE;

	game_state->pieces[8].type = PAWN;
	strcpy(game_state->pieces[8].name, "P");
	game_state->pieces[8].letter = 'A';
	game_state->pieces[8].number = 2;
	game_state->pieces[8].color = PIECE_WHITE;

	game_state->pieces[9].type = PAWN;
	strcpy(game_state->pieces[9].name, "P");
	game_state->pieces[9].letter = 'B';
	game_state->pieces[9].number = 2;
	game_state->pieces[9].color = PIECE_WHITE;

	game_state->pieces[10].type = PAWN;
	strcpy(game_state->pieces[10].name, "P");
	game_state->pieces[10].letter = 'C';
	game_state->pieces[10].number = 2;
	game_state->pieces[10].color = PIECE_WHITE;

	game_state->pieces[11].type = PAWN;
	strcpy(game_state->pieces[11].name, "P");
	game_state->pieces[11].letter = 'D';
	game_state->pieces[11].number = 2;
	game_state->pieces[11].color = PIECE_WHITE;

	game_state->pieces[12].type = PAWN;
	strcpy(game_state->pieces[12].name, "P");
	game_state->pieces[12].letter = 'E';
	game_state->pieces[12].number = 2;
	game_state->pieces[12].color = PIECE_WHITE;

	game_state->pieces[13].type = PAWN;
	strcpy(game_state->pieces[13].name, "P");
	game_state->pieces[13].letter = 'F';
	game_state->pieces[13].number = 2;
	game_state->pieces[13].color = PIECE_WHITE;

	game_state->pieces[14].type = PAWN;
	strcpy(game_state->pieces[14].name, "P");
	game_state->pieces[14].letter = 'G';
	game_state->pieces[14].number = 2;
	game_state->pieces[14].color = PIECE_WHITE;

	game_state->pieces[15].type = PAWN;
	strcpy(game_state->pieces[15].name, "P");
	game_state->pieces[15].letter = 'H';
	game_state->pieces[15].number = 2;
	game_state->pieces[15].color = PIECE_WHITE;

	// ------------------

	game_state->pieces[16].type = ROOK;
	strcpy(game_state->pieces[16].name, "R");
	game_state->pieces[16].letter = 'A';
	game_state->pieces[16].number = 8;
	game_state->pieces[16].color = PIECE_BLACK;

	game_state->pieces[17].type = KNIGHT;
	strcpy(game_state->pieces[17].name, "K");
	game_state->pieces[17].letter = 'B';
	game_state->pieces[17].number = 8;
	game_state->pieces[17].color = PIECE_BLACK;

	game_state->pieces[18].type = BISHOP;
	strcpy(game_state->pieces[18].name, "B");
	game_state->pieces[18].letter = 'C';
	game_state->pieces[18].number = 8;
	game_state->pieces[18].color = PIECE_BLACK;

	game_state->pieces[19].type = QUEEN;
	strcpy(game_state->pieces[19].name, "Qu");
	game_state->pieces[19].letter = 'D';
	game_state->pieces[19].number = 8;
	game_state->pieces[19].color = PIECE_BLACK;

	game_state->pieces[20].type = KING;
	strcpy(game_state->pieces[20].name, "K");
	game_state->pieces[20].letter = 'E';
	game_state->pieces[20].number = 8;
	game_state->pieces[20].color = PIECE_BLACK;

	game_state->pieces[21].type = BISHOP;
	strcpy(game_state->pieces[21].name, "B");
	game_state->pieces[21].letter = 'F';
	game_state->pieces[21].number = 8;
	game_state->pieces[21].color = PIECE_BLACK;

	game_state->pieces[22].type = KNIGHT;
	strcpy(game_state->pieces[22].name, "K");
	game_state->pieces[22].letter = 'G';
	game_state->pieces[22].number = 8;
	game_state->pieces[22].color = PIECE_BLACK;

	game_state->pieces[23].type = ROOK;
	strcpy(game_state->pieces[23].name, "R");
	game_state->pieces[23].letter = 'H';
	game_state->pieces[23].number = 8;
	game_state->pieces[23].color = PIECE_BLACK;

	game_state->pieces[24].type = PAWN;
	strcpy(game_state->pieces[24].name, "P");
	game_state->pieces[24].letter = 'A';
	game_state->pieces[24].number = 7;
	game_state->pieces[24].color = PIECE_BLACK;

	game_state->pieces[25].type = PAWN;
	strcpy(game_state->pieces[25].name, "P");
	game_state->pieces[25].letter = 'B';
	game_state->pieces[25].number = 7;
	game_state->pieces[25].color = PIECE_BLACK;

	game_state->pieces[26].type = PAWN;
	strcpy(game_state->pieces[26].name, "P");
	game_state->pieces[26].letter = 'C';
	game_state->pieces[26].number = 7;
	game_state->pieces[26].color = PIECE_BLACK;

	game_state->pieces[27].type = PAWN;
	strcpy(game_state->pieces[27].name, "P");
	game_state->pieces[27].letter = 'D';
	game_state->pieces[27].number = 7;
	game_state->pieces[27].color = PIECE_BLACK;

	game_state->pieces[28].type = PAWN;
	strcpy(game_state->pieces[28].name, "P");
	game_state->pieces[28].letter = 'E';
	game_state->pieces[28].number = 7;
	game_state->pieces[28].color = PIECE_BLACK;

	game_state->pieces[29].type = PAWN;
	strcpy(game_state->pieces[29].name, "P");
	game_state->pieces[29].letter = 'F';
	game_state->pieces[29].number = 7;
	game_state->pieces[29].color = PIECE_BLACK;

	game_state->pieces[30].type = PAWN;
	strcpy(game_state->pieces[30].name, "P");
	game_state->pieces[30].letter = 'G';
	game_state->pieces[30].number = 7;
	game_state->pieces[30].color = PIECE_BLACK;

	game_state->pieces[31].type = PAWN;
	strcpy(game_state->pieces[31].name, "P");
	game_state->pieces[31].letter = 'H';
	game_state->pieces[31].number = 7;
	game_state->pieces[31].color = PIECE_BLACK;
}
