#include<iostream>

#include"Piece.h"
#include"Board.h"
#include"Statics.h"



	Board::Board()
	{
		pieces = new Piece** [BOARD_SIZEX];

		for (int i = 0; i < BOARD_SIZEX; i++)
		{
			pieces[i] = new Piece*[BOARD_SIZEY];
		}

		for (int i = 0; i < BOARD_SIZEX; i++)
		{
			for (int j = 0; j < BOARD_SIZEY; j++)
			{
				pieces[i][j] = nullptr;
			}
		}
	}



	Board::~Board() {
		for (int i = 0; i < BOARD_SIZEX; i++) {
			for (int j = 0; j < BOARD_SIZEY; j++) {
				
				if (pieces[i][j] != nullptr) {
					delete pieces[i][j];
				}
			}

			delete[] pieces[i];
		}
		
		delete[] pieces;
	}

	void Board::Beat(Piece* piece1, Piece* piece2)//piece1 beats piece2 
	{
		int p2_x = piece2->GetPosX();
		int p2_y = piece2->GetPosY();

		int p1_x = piece1->GetPosX();
		int p1_y = piece1->GetPosY();

		piece1->SetPos(p2_x, p2_y);
	
		delete piece2;

		pieces[p2_x][p2_y] = piece1;
		pieces[p1_x][p1_y] = nullptr;
	
	}


	void Board::ChangePos(Piece* piece, int x, int y)
	{
		pieces[piece->GetPosX()][piece->GetPosY()] = nullptr;
		pieces[x][y] = piece;
		piece->SetPos(x, y);
	}


	Piece* Board::GetPiece(int x, int y)
	{
		return pieces[x][y];
	}
