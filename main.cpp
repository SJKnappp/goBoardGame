#include "main.h"

struct piece{
  int state; //0 for unlpayed/taken 1 black 2 for white
  int liberty; //number of surronding empty tiles = 0 for empty space
  int group; // a set of same coulour stones all touching one another = 0 for empty space
};

//initalise the start condition of the board
std::vector<piece> initalBoard(const int boardSize){
  piece board;
  std::vector<piece> v;
  for (size_t j = 0; j < boardSize * boardSize; j++) {
      board.state = 0;
      board.liberty = 0;
      board.group = 0;
      v.push_back(board);
    }
  return v;
}

void boardPrint(int boardSize, std::vector<piece> board){
  for(int i =0; i < boardSize; i++){
    for(int j=0;j<boardSize;j++){
      if(board.at(j+boardSize*i).state ==0){std::cout << "+ ";}
      else if(board.at(j+boardSize*i).state == 1){std::cout << "B ";}
      else if(board.at(j+boardSize*i).state == 2){std::cout << "W ";}
    }
    std::cout << '\n';
  }
}

piece updatePiece(std::vector<piece> v,int i,int j,int N, bool isBlack ){
  int colour;
  if(isBlack == true){colour = 1;}else{colour =2;}
  if(v.at(i+j*N).state == 0){
    v.at(i+j*N).state = colour;
  }else{return v.at(i+j*N);}
}

int main(){
  const int boardSize = 19;
  bool isBlack = true;
  bool acceptedVal; int x_at; int y_at;
  std::string input;
  bool gameRunning = true;
  std::vector<piece> board = initalBoard(boardSize);
  boardPrint(boardSize, board);
  while(gameRunning == true){
    std::cout << "please input position ";
    if(isBlack == true){std::cout << "black " << '\n';} else{std::cout << "white ";} std::cout << '\n';
    std::cin >> input;
    acceptedVal = false;
    while(acceptedVal == false){
      if(input.length() == 2){acceptedVal = true;}else{
        std::cout << "please renter value ";std::cin >> input;
      }
    }
    x_at = input.at(0) - 97;
    y_at = input.at(1) - 49;

    board.at(x_at + y_at*boardSize) = updatePiece(board, x_at, y_at, boardSize, isBlack);

    if(isBlack == true){ board.at(x_at + y_at * boardSize).state = true; }
    else{ board.at(x_at + y_at * boardSize).state = false; }


    boardPrint(boardSize, board);
  }
}
