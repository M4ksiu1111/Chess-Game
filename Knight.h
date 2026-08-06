#pragma once

#include"Piece.h"

class Knight :public Piece
{
public:
	Knight(Board* board, int start_x, int start_y, int index, int color);
	bool Move(int dirX, int dirY) override;
	bool GiveCheck(int king_x, int king_y) override;
};
