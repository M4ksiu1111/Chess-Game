#include"Knight.h"
#include"Board.h"
#include"Statics.h"

#include<cmath>

Knight::Knight(Board* board, int start_x, int start_y, int index, int color) : Piece(board, start_x, start_y, index, KNIGHT_POWER, color) {}

bool Knight::Move(int dirX, int dirY)
{
	int new_x = GetPosX() + dirX;
	int new_y = GetPosY() + dirY;

	if (board->IsMoveSafe(this, new_x, new_y) == false) {
		return false;
	}

	if (abs(dirX) == 1 && abs(dirY) == 2 || abs(dirX) == 2 && abs(dirY) == 1)
	{
		if (board->GetPiece(new_x, new_y) != nullptr)
		{
			return (board->Beat(this, board->GetPiece(new_x, new_y)));
		}

		else {
			board->ChangePos(this, new_x, new_y);
			return true;
		}

	}

	else return false;

	

}

bool Knight::GiveCheck(int king_x, int king_y)
{
	int dirX = king_x - GetPosX();
	int dirY = king_y - GetPosY();

	if ( ( abs(dirX) == 1 && abs(dirY) == 2) || ( abs(dirX) == 2 && abs(dirY) == 1) ) {
		return true;
	}
	return false;
}