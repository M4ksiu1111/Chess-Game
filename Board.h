#pragma once

#include<iostream>
#include<SDL.h>
#include <SDL_ttf.h>
#pragma once
#include"Piece.h"
#include"Board.h"
#include"Statics.h"


class Board
{

private:
	Piece*** pieces;
	SDL_Texture* piece_textures[12];
	bool is_promoting;
	TTF_Font* font;
	SDL_Cursor* cursor_hand;
	SDL_Cursor* cursor_arrow;
	int promo_x, promo_y;

	bool is_mat, is_pat;
	int lost_color;

public:
	Board();

	~Board();

	bool Beat(Piece* piece1, Piece* piece2);//piece1 beats piece2 

	void ChangePos(Piece* piece, int x, int y);

	Piece* GetPiece(int x, int y);

	void InitBoard();

	void LoadTextures(SDL_Renderer* renderer);

	void DrawBoard(SDL_Renderer* renderer, int selected_x = -1, int selected_y = -1);

	Piece* ReturnKing(int color);

	bool IsMoveSafe(Piece* piece, int target_x, int target_y);

	void SetPawnPromotion(int x, int y);

	void DrawPawnPromotion(SDL_Renderer* renderer);

	bool IsPromoting();

	bool IsFinished(int color);

	void DrawMat(SDL_Renderer* renderer);
	void DrawPat(SDL_Renderer* renderer);
	

};

