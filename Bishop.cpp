#include"Bishop.h"
#include"Statics.h"
#include"Board.h"
#include"King.h"

#include<cmath>

Bishop::Bishop(Board* board, int start_x, int start_y, int index, int color) : Piece(board, start_x, start_y, index, BISHOP_POWER,
	color) {
}

bool Bishop::Move(int dirX, int dirY)
{
	int new_x = GetPosX() + dirX;
	int new_y = GetPosY() + dirY;

	if (std::abs(dirX) != std::abs(dirY) || dirX == 0 && dirY == 0 || IsJumpingAbove(new_x, new_y) == false) return false;

	if (board->IsMoveSafe(this, new_x, new_y) == false) {
		return false;
	}

	if (board->GetPiece(new_x, new_y) != nullptr)
	{
		return (board->Beat(this, board->GetPiece(new_x, new_y)));
	}

	else 
	{
		board->ChangePos(this, new_x, new_y);
		return true;

	}


}

bool Bishop::GiveCheck(int king_x, int king_y)
{

	int dirX = king_x - GetPosX();
	int dirY = king_y - GetPosY();
	
	if (abs(dirX) != abs(dirY)) return false;

	else {
		return IsJumpingAbove(king_x, king_y);
	}

}

