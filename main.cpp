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
  return v.at(i+j*N);
}

int main(){
  //initalise variables
  const int boardSize = 19;
  bool isBlack = true;
  bool acceptedVal; int x_at; int y_at; int y_ten;
  std::string input;
  bool gameRunning = true;

  //setup the board and print intial condition
  std::vector<piece> board = initalBoard(boardSize);
  boardPrint(boardSize, board);

  //start main loop
  while(gameRunning == true){
    //dectects player
    if(isBlack == true){isBlack = false;}else{isBlack =true;}
    std::cout << isBlack;

    //player possition
    std::cout << "please input position ";
    if(isBlack == true){std::cout << "black " << '\n';} else{std::cout << "white ";} std::cout << '\n';
    std::cin >> input;
    acceptedVal = false;
    while(acceptedVal == false){
      if(input.length() == 2 || input.length() == 3){acceptedVal = true;
        x_at = input.at(0) - 97;
        y_at = input.at(1) - 49;
        if(input.length() == 3){y_ten = input.at(3) - 49;
          y_at = 10*y_at + y_ten;}
        if((x_at < 0 || y_at < 0 || x_at > 19 || y_at > 19) && board.at(y_at*boardSize+x_at).state == 0){ break; }
      }
      std::cout << "please renter value ";std::cin >> input;

    }

    board.at(x_at + y_at*boardSize) = updatePiece(board, x_at, y_at, boardSize, isBlack);

    if(isBlack == true){ board.at(x_at + y_at * boardSize).state = true; }
    else{ board.at(x_at + y_at * boardSize).state = false; }


    boardPrint(boardSize, board);
  }
}
