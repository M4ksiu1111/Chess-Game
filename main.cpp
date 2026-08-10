#include"Pawn.h"
#include"Board.h"
#include"King.h"



#include<iostream>
#include<SDL.h>

using namespace std;


int main(int argc, char* args[])
{

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chess-Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Board* board = new Board();
	board->InitBoard();
	board->LoadTextures(renderer);

    bool running = true;
    SDL_Event event;

    int tmpX=-1,tmpY=-1;

    int turn = 0; //0-white to move 1-black to move


    while (running) {
       
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                running = false;
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (board->IsPromoting()) {
                    continue; 
                }

                bool success_turn = false;
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int clicked_x = event.button.x;
                    int clicked_y = event.button.y;

                    int real_x = clicked_x / SQUARE_SIZE;
                    int real_y = clicked_y / SQUARE_SIZE;

                    if (tmpX != -1 && tmpY != -1)
                    {
                        //check for castling
                        if (dynamic_cast<King*>(board->GetPiece(tmpX, tmpY)) != nullptr)
                        {
                            King* king = dynamic_cast<King*>(board->GetPiece(tmpX, tmpY));

                            if (king->Castle(board->GetPiece(real_x, real_y)))
                            {
                                success_turn = true;
                                tmpX = -1;
                                tmpY = -1;
                                //switch turn
                                turn = 1 - turn;
                            }
                        }
                        
                        //if player decides to move other piece
                        if (tmpX == real_x && tmpY == real_y && success_turn == false) {
                            tmpX = -1;
                            tmpY = -1;
                        }

                        else if (success_turn == false) {
                            int dirX = real_x - tmpX;
                            int dirY = real_y - tmpY;

                            if (board->GetPiece(tmpX, tmpY)->Move(dirX, dirY))
                            {
                                tmpX = -1;
                                tmpY = -1;
                                //switch turn
                                turn = 1 - turn;
                            }
                        }

                    }

                    else if (board->GetPiece(real_x, real_y) != nullptr  && board->GetPiece(real_x, real_y)->GetColor() == turn)
                    {
                       tmpX = real_x;
                       tmpY = real_y;
                    }

                   
                }
            }
        }

        SDL_RenderClear(renderer);
        board->DrawBoard(renderer, tmpX,tmpY);
        board->DrawPawnPromotion(renderer);
        SDL_RenderPresent(renderer);


    }

    // Sprzątanie
    delete board;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



	return 0;
}