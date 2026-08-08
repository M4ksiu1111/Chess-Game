#pragma once

#include"Piece.h"

class King :public Piece {

private:
	bool can_castle;
	bool checked;
	bool can_move;
public:
	King(Board* board, int start_x, int start_y, int index, int color);
	bool IsChecked(int posX, int posY);
	bool Move(int dirX, int dirY) override;
	bool GiveCheck(int king_x, int king_y) override;

	bool Castle(Piece* piece);


};
