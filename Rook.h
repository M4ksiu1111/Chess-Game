#pragma once

#include "Piece.h"
#include"Statics.h"

class Rook:public Piece {

private:
	bool is_started; //for castling
public:
	Rook(Board* board, int start_x, int start_y, int index, int color);
	bool Move(int dirX, int dirY) override;
	bool GiveCheck(int king_x, int king_y) override;
	bool IsStarted();



};