#pragma once

#include"Piece.h"
#include"Statics.h"

class Pawn :public Piece
{

private:
	bool is_started;

public:
	Pawn(Board* board, int start_x, int start_y,int index, int color);
	bool Move(int dirX, int dirY) override;
	
};

