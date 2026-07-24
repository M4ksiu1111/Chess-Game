#include<iostream>


#include"Piece.h"
#include"Board.h"
#include"Statics.h"
#include"Pawn.h"
#include"Rook.h"

using namespace std;


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

		for (int i = 0; i < 12; i++)
		{
			piece_textures[i] = nullptr;
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

	bool Board::Beat(Piece* piece1, Piece* piece2)//piece1 beats piece2 
	{

		if (piece2 == nullptr || piece1->GetColor() == piece2->GetColor() ) return false;
		
		int p2_x = piece2->GetPosX();
		int p2_y = piece2->GetPosY();

		int p1_x = piece1->GetPosX();
		int p1_y = piece1->GetPosY();

		piece1->SetPos(p2_x, p2_y);
	
		delete piece2;

		pieces[p2_x][p2_y] = piece1;
		pieces[p1_x][p1_y] = nullptr;

		return true;
	
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


	void Board::InitBoard()
	{
		
		for (int i = 0; i < BOARD_SIZEX; i++)
		{
			pieces[i][1] = new Pawn(this, i, 1, BLACK_PAWN_INDEX, COLOR_BLACK);
		}

		for (int i = 0; i < BOARD_SIZEX; i++)
		{
			pieces[i][BOARD_SIZEY - 2] = new Pawn(this, i, BOARD_SIZEY - 2, WHITE_PAWN_INDEX, COLOR_WHITE);
		}

		pieces[0][BOARD_SIZEY - 1] = new Rook(this, 0, BOARD_SIZEY - 1, WHITE_ROOK_INDEX, COLOR_WHITE);
		pieces[BOARD_SIZEX-1][BOARD_SIZEY - 1] = new Rook(this, BOARD_SIZEX - 1, BOARD_SIZEY - 1, WHITE_ROOK_INDEX, COLOR_WHITE);
		
		pieces[0][0]= new Rook(this, 0, 0 , BLACK_ROOK_INDEX, COLOR_BLACK);
		pieces[BOARD_SIZEX-1][0] = new Rook(this, BOARD_SIZEX - 1 , 0, BLACK_ROOK_INDEX, COLOR_BLACK);
	}


	void Board::LoadTextures(SDL_Renderer* renderer)
	{
		SDL_Surface* white_pawn = SDL_LoadBMP("G:\\Mój dysk\\PROJEKTY_SAM\\Chess\\Project1\\img\\white-pawn.bmp");

		if (white_pawn != nullptr) {
			Uint32 color_key = SDL_MapRGB(white_pawn->format, 0, 163, 232);
			SDL_SetColorKey(white_pawn, SDL_TRUE, color_key);
			piece_textures[WHITE_PAWN_INDEX] = SDL_CreateTextureFromSurface(renderer, white_pawn);
			SDL_FreeSurface(white_pawn);
		}

		SDL_Surface* black_pawn= SDL_LoadBMP("G:\\Mój dysk\\PROJEKTY_SAM\\Chess\\Project1\\img\\black-pawn.bmp");

		if (black_pawn != nullptr) {
			Uint32 color_key = SDL_MapRGB(black_pawn->format, 0, 162, 232);
			SDL_SetColorKey(black_pawn, SDL_TRUE, color_key);
			piece_textures[BLACK_PAWN_INDEX] = SDL_CreateTextureFromSurface(renderer, black_pawn);
			SDL_FreeSurface(black_pawn);
		}

		SDL_Surface* white_rook = SDL_LoadBMP("G:\\Mój dysk\\PROJEKTY_SAM\\Chess\\Project1\\img\\white-rook.bmp");

		if (white_rook != nullptr) {
			Uint32 color_key = SDL_MapRGB(white_rook->format, 0, 162, 232);
			SDL_SetColorKey(white_rook, SDL_TRUE, color_key);
			piece_textures[WHITE_ROOK_INDEX] = SDL_CreateTextureFromSurface(renderer, white_rook);
			SDL_FreeSurface(white_rook);
		}

		SDL_Surface* black_rook = SDL_LoadBMP("G:\\Mój dysk\\PROJEKTY_SAM\\Chess\\Project1\\img\\black-rook.bmp");

		if (black_rook != nullptr) {
			Uint32 color_key = SDL_MapRGB(black_rook->format, 0, 162, 232);
			SDL_SetColorKey(black_rook, SDL_TRUE, color_key);
			piece_textures[BLACK_ROOK_INDEX] = SDL_CreateTextureFromSurface(renderer, black_rook);
			SDL_FreeSurface(black_rook);
		}

		


	}

	void Board::DrawBoard(SDL_Renderer* renderer, int selected_x, int selected_y)
	{
		
		for (int x = 0; x < BOARD_SIZEX; x++)
		{
			for (int y = 0; y < BOARD_SIZEY; y++)
			{
				//background(chessboard)
				SDL_Rect tile_rect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };

				if ((x + y) % 2 == 0) {
					SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);
				}

				//highliting selected field
				if (x == selected_x && y == selected_y)
				{
					SDL_SetRenderDrawColor(renderer, 255, 204, 153,255);
				}

				SDL_RenderFillRect(renderer, &tile_rect);

				//PIECES

				if (pieces[x][y] != nullptr)
				{
					int index = pieces[x][y]->GetIndex();

					SDL_Texture* texture = piece_textures[index];

					if (texture != nullptr) {
						
						SDL_RenderCopy(renderer, texture, NULL, &tile_rect);
					}

				}
			}
		}

	}
	