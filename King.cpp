#include"King.h"
#include"Statics.h"
#include"Board.h"

King::King(Board* board, int start_x, int start_y, int index, int color) : Piece(board, start_x, start_y, index, KING_POWER, color) {}

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
	if (std::abs(dirX) > 1 || std::abs(dirY) > 1 || (dirX == 0 && dirY == 0)) {
		return false;
	}

	int new_x = GetPosX() + dirX;
	int new_y = GetPosY() + dirY;

	if (IsChecked(new_x, new_y)) return false;

	if (board->GetPiece(new_x, new_y) != nullptr)
	{
		return (board->Beat(this, board->GetPiece(new_x, new_y)));
	}

	else {
		board->ChangePos(this, new_x, new_y);
		return true;
	}

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