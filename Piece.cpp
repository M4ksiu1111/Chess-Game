#include<iostream>
#include"Piece.h"
#include"Statics.h"
#include"Board.h"




	Piece::Piece(Board* board, int start_x, int start_y, int index, int power, int color) : board(board),pos_x(start_x), pos_y(start_y), piece_index(index), power(power), color(color), alive(true), attacking(false) {}
	
	Piece::~Piece() {
		alive = false;
	}

	bool Piece::is_attacking() {
		return attacking;
	}

	void Piece::set_attack(bool a) {
		this->attacking = a;
	}

	bool Piece::is_alive()
	{
		return alive;
	}

	void Piece::set_life(bool f) {
		this->alive = f;
	}

	int	Piece::GetPosX()
	{
		return this->pos_x;
	}

	int Piece::GetPosY()
	{
		return this->pos_y;
	}

	void Piece::SetPos(int x, int y)
	{
		this->pos_x = x;
		this->pos_y = y;
	}

	int Piece::GetColor()
	{
		return color;
	}

	int Piece::GetPower()
	{
		return power;
	}

	int Piece::GetIndex()
	{
		return piece_index;
	}

	bool Piece::IsJumpingAbove(int potential_posX, int potential_posY) //checks if for example pawn can move two swuares above or is there any piece between
	{
		int act_posX = GetPosX();
		int act_posY = GetPosY();

		int dir_x = 0;
		int dir_y = 0;

		int x_dif = potential_posX - act_posX;
		int y_dif = potential_posY - act_posY;

		if (x_dif < 0) dir_x = -1;
		else if (x_dif > 0) dir_x = 1;

		
		if (y_dif < 0) dir_y = -1;
		else if (y_dif > 0) dir_y = 1;
		
		int x = act_posX, y = act_posY;

		while (true)
		{
			x += dir_x;
			y += dir_y;

			if (x == potential_posX && y == potential_posY)
			{
				return true;
			}

			else if (board->GetPiece(x, y) != nullptr) {
				return false;
			}

		}

	}


