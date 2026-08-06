#pragma once
#include<iostream>

class Board;

class Piece
{

protected:
	Board* board;
	int pos_x, pos_y;
	const int piece_index;
	const int power;
	const int color;
	bool alive;
	bool attacking;// is attacking other piece(trying to dewastate it)

public:
	Piece(Board* board, int start_x, int start_y, int index, int power, int color);
	virtual ~Piece();

	virtual	bool Move(int dirX, int dirY) = 0; //returns true or false if the piece moved properly

	virtual bool GiveCheck(int king_x, int king_y) = 0;

	bool is_attacking();


	void set_attack(bool a);

	bool is_alive();

	void set_life(bool f);

	int	GetPosX();

	int GetPosY();

	void SetPos(int x, int y);


	int GetColor();

	int GetPower();

	int GetIndex();

	bool IsJumpingAbove(int potential_posX, int potential_posY); //checks if for example pawn can move two swuares above or is there any piece between
	

}; 
