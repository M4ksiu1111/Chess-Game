#include"Piece.h"
#include"Board.h"
#include"Pawn.h"
#include"King.h"
#include"Statics.h"


	Pawn::Pawn(Board* board,int start_x, int start_y,int index, int color) :Piece(board,start_x, start_y, index, PAWN_POWER, color), 
		is_started(true) {}

	bool Pawn::Move(int dirX, int dirY) 
	{
		int new_x, new_y;
		int legal_moves[4][2] = { {0,1} , {0,2} , {1,1} , {-1, 1} };

		if (GetColor() == COLOR_BLACK)
		{
			//legal moves x;y
			
			for (int i = 0; i < 4; i++)
			{
				if (dirX == legal_moves[i][0] && dirY == legal_moves[i][1])
				{
					 new_x = GetPosX() + dirX;
					 new_y = GetPosY() + dirY;

					 if (new_x < 0 || new_x >= BOARD_SIZEX || new_y < 0 || new_y >= BOARD_SIZEY) {
						 return false;
					 }

					 if (board->IsMoveSafe(this, new_x, new_y) == false) {
						 return false;
					 }

					 //checks if the player want to destroy other piece
					 if ((dirX == 1 || dirX == -1) && dirY == 1)
					 {
						 if (board->Beat(this, board->GetPiece(new_x, new_y)))
						 {
							 is_started = false;
							 if (new_y == BOARD_SIZEY-1) board->SetPawnPromotion(new_x, new_y);
							 return true;
						 }
							
						 return false;
							 
					 }
					 
					 else  if ((dirX == 0 && dirY == 1) || (is_started == true && dirX == 0 && dirY == 2)) {

							 if (board->GetPiece(new_x, new_y) == nullptr && IsJumpingAbove(new_x,new_y) ==true)
							 {
								 board->ChangePos(this,new_x, new_y);
								 is_started = false;
								 if (new_y == BOARD_SIZEY-1) board->SetPawnPromotion(new_x, new_y);
								 return true;
							 }

							 else return false;
							 
					 }

				}
			}

			return false;

		}

		//WHITE LOGIC
		else {
					
			for (int i = 0; i < 4; i++)
			{
				if (dirX == legal_moves[i][0] && dirY == -legal_moves[i][1])
				{
					new_x = GetPosX() + dirX;
					new_y = GetPosY() + dirY;

					if (new_x < 0 || new_x >= BOARD_SIZEX || new_y < 0 || new_y >= BOARD_SIZEY) {
						return false;
					}

					if (board->IsMoveSafe(this, new_x, new_y) == false) {
						return false;
					}

					//checks if the player want to destroy other piece
					if ((dirX == 1 || dirX == -1) && dirY == -1)
					{
						if (board->Beat(this, board->GetPiece(new_x, new_y))) {
							is_started = false;
							if (new_y == 0) board->SetPawnPromotion(new_x, new_y);
							return true;
						}
						return false;

					}

					else if ((dirX == 0 && dirY == -1) || (is_started == true && dirX == 0 && dirY == -2)) {

						if (board->GetPiece(new_x, new_y) == nullptr && IsJumpingAbove(new_x, new_y) == true)
						{
							board->ChangePos(this, new_x, new_y);
							is_started = false;
							if (new_y == 0) board->SetPawnPromotion(new_x, new_y);
							return true;
						}

						else return false;

					}

				}
			}

			return false;
				
		}

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

