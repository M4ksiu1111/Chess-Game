#include"Rook.h"
#include"Board.h"


Rook::Rook(Board* board, int start_x, int start_y, int index, int color) : Piece(board, start_x, start_y, index,ROOK_POWER, 
	color), is_started(true) {}

bool Rook::Move(int dirX, int dirY) 
{

	int new_x = GetPosX() + dirX;
	int new_y = GetPosY() + dirY;

	if (dirX != 0 && dirY != 0 || dirX==0 && dirY==0 || IsJumpingAbove(new_x,new_y)==false) return false;

	//checks if player want to destroy other piece
	if (board->GetPiece(new_x, new_y) != nullptr)
	{
		if (board->Beat(this, board->GetPiece(new_x, new_y)))
		{
			is_started = false;
			return true;
		}

		else return false;
	}

	else
	{
		board->ChangePos(this, new_x, new_y);
		is_started = false;
		return true;
	}
	

}


bool Rook::GiveCheck(int king_x, int king_y) {

	int dirX = king_x - GetPosX();
	int dirY = king_y - GetPosY();

	if (dirX != 0 && dirY != 0) return false;

	else {
		return IsJumpingAbove(king_x, king_y);
	}

}