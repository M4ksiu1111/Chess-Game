#include"Queen.h"
#include"Statics.h"
#include"Board.h"

#include<cmath>

Queen::Queen(Board* board, int start_x, int start_y, int index, int color) : Piece(board, start_x, start_y, index, QUEEN_POWER, color){}

bool Queen::Move(int dirX, int dirY)
{
	int new_x = GetPosX() + dirX;
	int new_y = GetPosY() + dirY;

	if (!CanMove(new_x, new_y)) return false;

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

bool Queen::CanMove(int targetX, int targetY) {

	int dirX = targetX - pos_x;
	int dirY = targetY - pos_y;

	if (std::abs(dirX) != std::abs(dirY) && dirX != 0 && dirY != 0) {
		return false;
	}

	if (IsJumpingAbove(targetX, targetY) == false) {
		return false;
	}

	if (board->IsMoveSafe(this, targetX, targetY) == false) {
		return false;
	}

	Piece* piece = board->GetPiece(targetX, targetY);
	if ( piece!=nullptr && piece->GetColor() == color) return false;

	return true;

}

bool Queen::GiveCheck(int king_x, int king_y)
{
	int dirX = king_x - GetPosX();
	int dirY = king_y - GetPosY();

	if (dirX != 0 && dirY != 0 && abs(dirX) != abs(dirY)) return false;

	else {
		return IsJumpingAbove(king_x, king_y);
	}

}