#pragma once

#include"Piece.h"

class Queen :public Piece
{
public:
	Queen(Board* board, int start_x, int start_y, int index, int color);
	bool Move(int dirX, int dirY) override;
};
