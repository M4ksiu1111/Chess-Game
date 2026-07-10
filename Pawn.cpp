#include"Piece.h"
#include"Board.h"
#include"Pawn.h"
#include"Statics.h"


	Pawn::Pawn(Board* board,int start_x, int start_y,int index, int color) :Piece(board,start_x, start_y, index, PAWN_POWER, color), is_started(true) {}

	bool Pawn::Move(int dirX, int dirY) 
	{
		int new_x, new_y;
		int legal_moves[4][2] = { {0,1} , {0,2} , {1,1} , {-1, 1} };

		if (GetColor() == COLOR_WHITE)
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

					 //checks if the player want to destroy other piece
					 if ((dirX == 1 || dirX == -1) && dirY == 1)
					 {
						 if (board->GetPiece(new_x, new_y) == nullptr || board->GetPiece(new_x, new_y)->GetColor() == this->color)
						 return false;
						 else {
							 board->Beat(this, board->GetPiece(new_x, new_y));
							 is_started = false;
							 return true;
						 }

					 }
					 
					 else  if ((dirX == 0 && dirY == 1) || (is_started == true && dirX == 0 && dirY == 2)) {

							 if (board->GetPiece(new_x, new_y) == nullptr && IsJumpingAbove(new_x,new_y) ==true)
							 {
								 board->ChangePos(this,new_x, new_y);
								 is_started = false;
								 return true;
							 }

							 else return false;
							 
					 }

				}
			}

			return false;

		}

		//BLACK LOGIC
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

					//checks if the player want to destroy other piece
					if ((dirX == 1 || dirX == -1) && dirY == -1)
					{
						if (board->GetPiece(new_x, new_y) == nullptr || board->GetPiece(new_x, new_y)->GetColor() == this->color)
							return false;
						else {
							board->Beat(this, board->GetPiece(new_x, new_y));
							is_started = false;
							return true;
						}

					}

					else if ((dirX == 0 && dirY == -1) || (is_started == true && dirX == 0 && dirY == -2)) {

						if (board->GetPiece(new_x, new_y) == nullptr && IsJumpingAbove(new_x, new_y) == true)
						{
							board->ChangePos(this, new_x, new_y);
							is_started = false;
							return true;
						}

						else return false;

					}

				}
			}

			return false;
				
		}

	}



