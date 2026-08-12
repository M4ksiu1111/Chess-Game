#include"Piece.h"
#include"Board.h"
#include"Pawn.h"
#include"King.h"
#include"Statics.h"

#include<cmath>


	Pawn::Pawn(Board* board,int start_x, int start_y,int index, int color) :Piece(board,start_x, start_y, index, PAWN_POWER, color), 
		is_started(true) {}

	bool Pawn::Move(int dirX, int dirY)
	{
		
		int new_x = GetPosX() + dirX;
		int new_y = GetPosY() + dirY;

		if (!CanMove(new_x, new_y)) return false;

		
		if (board->GetPiece(new_x, new_y) != nullptr)
		{
			board->Beat(this, board->GetPiece(new_x, new_y));
		}
		else
		{
			board->ChangePos(this, new_x, new_y);
		}

		is_started = false;

	
		if (new_y == 0 || new_y == BOARD_SIZEY - 1) {
			board->SetPawnPromotion(new_x, new_y);
		}

		return true;
	}

	bool Pawn::CanMove(int targetX, int targetY)
	{
		int dirX = targetX - pos_x;
		int dirY = targetY - pos_y;

		
		int forward = (color == COLOR_WHITE) ? -1 : 1;

		if (board->IsMoveSafe(this, targetX, targetY) == false) return false;

		Piece* target_piece = board->GetPiece(targetX, targetY);
		if (target_piece != nullptr && target_piece->GetColor() == color) return false;

		
		if (dirX == 0 && dirY == forward) {
			if (target_piece == nullptr) return true;
		}
		
		else if (dirX == 0 && dirY == 2 * forward && is_started) {
			if (target_piece == nullptr && IsJumpingAbove(targetX, targetY)) return true;
		}
		
		else if (std::abs(dirX) == 1 && dirY == forward) {
			if (target_piece != nullptr) return true;
		}

		return false;
	}


	bool Pawn::GiveCheck(int king_x, int king_y) {

		int x = GetPosX();
		int y = GetPosY();

		if (color == COLOR_WHITE) {

			if ( (x - 1 == king_x && y - 1 == king_y) || (x + 1 == king_x && y - 1 == king_y) ) return true;
		}

		else {
			if ( (x - 1 == king_x && y + 1 == king_y) || (x + 1 == king_x && y + 1 == king_y) ) return true;
		}

		return false;


		

	}

