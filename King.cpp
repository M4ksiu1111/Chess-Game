#include"King.h"
#include"Statics.h"
#include"Board.h"
#include"Rook.h"

#include <cmath>

King::King(Board* board, int start_x, int start_y, int index, int color) : Piece(board, start_x, start_y, index, KING_POWER, color),
can_castle(true) {}

bool King::IsChecked(int posX, int posY)
{
	for (int i = 0; i < BOARD_SIZEX; i++)
	{
		for (int j = 0; j < BOARD_SIZEY; j++)
		{
			Piece* piece = board->GetPiece(i, j);
			if (piece == nullptr || piece->GetColor()==color) continue;

			if (piece->GiveCheck(posX, posY)) return true;

		}
	}

	return false;

}

bool King::Move(int dirX, int dirY)
{
	
	int new_x = GetPosX() + dirX;
	int new_y = GetPosY() + dirY;

	if (board->GetPiece(new_x, new_y) != nullptr)
	{
		can_castle = false;
		return (board->Beat(this, board->GetPiece(new_x, new_y)));
	}

	else {
		board->ChangePos(this, new_x, new_y);
		can_castle = false;
		return true;
	}

}

bool King::CanMove(int targetX, int targetY) {

	int dirX = targetX - pos_x;
	int dirY = targetY - pos_y;

	if (std::abs(dirX) > 1 || std::abs(dirY) > 1 || (dirX == 0 && dirY == 0)) {
		return false;
	}

	if (board->IsMoveSafe(this, targetX, targetY) == false) {
		return false;
	}

	Piece* piece = board->GetPiece(targetX, targetY);
	if (piece != nullptr && piece->GetColor() == color) return false;

	return true;
}

bool King::GiveCheck(int king_x, int king_y)
{
	int dirX = king_x - GetPosX();
	int dirY = king_y - GetPosY();

	
	if (std::abs(dirX) <= 1 && std::abs(dirY) <= 1 && (dirX != 0 || dirY != 0)) {
		return true;
	}

	return false;
}

bool King::Castle(Piece* piece)
{
	Rook* rookie = dynamic_cast<Rook*>(piece);

	if (rookie == nullptr) return false;

	int targetX = rookie->GetPosX();

	if (can_castle == false || rookie->IsStarted() == false) return false;

	if (rookie->GetColor() != color) return false;

	if (IsJumpingAbove(targetX, pos_y)==false) return false;

	if (IsChecked(pos_x, pos_y)) return false;

	if (targetX > pos_x)
	{
		if (IsChecked(pos_x + 1, pos_y) || IsChecked(pos_x + 2, pos_y)) return false;

		else
		{
			board->ChangePos(rookie, pos_x + 1, pos_y);
			board->ChangePos(this, pos_x + 2, pos_y);
			can_castle = false;
			return true;
		}
	}

	else if (targetX < pos_x)
	{
		if (IsChecked(pos_x - 1, pos_y) || IsChecked(pos_x - 2, pos_y)) return false;

		else
		{
			board->ChangePos(rookie, pos_x - 1, pos_y);
			board->ChangePos(this, pos_x - 2, pos_y);
			can_castle = false;
			return true;
		}
	}
	
	return false;
}