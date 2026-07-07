#pragma once

#include<iostream>
#pragma once
#include"Piece.h"
#include"Board.h"
#include"Statics.h"


class Board
{

private:
	Piece*** pieces;

public:
	Board();

	~Board();

	void Beat(Piece* piece1, Piece* piece2);//piece1 beats piece2 

	void ChangePos(Piece* piece, int x, int y);

	Piece* GetPiece(int x, int y);

};

