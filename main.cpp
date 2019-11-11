#include "main.h"

struct pice{
  int state; //0 for unlpayed/taken 1 black 2 for white
  int liberty; //number of surronding empty tiles = 0 for empty space
  int group; // a set of same coulour stones all touching one another = 0 for empty space
};

//initalise the start condition of the board
std::vector<pice> initalBoard(const int boardSize){
  pice board;
  std::vector<pice> v;
  for (size_t j = 0; j < boardSize * boardSize; j++) {
      board.state = 0;
      board.liberty = 0;
      board.group = 0;
      v.push_back(board);
    }
  return v;
}

void boardPrint(int boardSize, std::vector<pice> board){
  for(int i =0; i < boardSize; i++){
    for(int j=0;j<boardSize;j++){
      if(board.at(j+boardSize*i).state ==0){std::cout << "+ ";}
      else if(board.at(j+boardSize*i).state == 1){std::cout << "B ";}
      else if(board.at(j+boardSize*i).state == 2){std::cout << "W ";}
    }
    std::cout << '\n';
  }
}

int main(){
  const int boardSize = 19;
  bool isBlack = true;
  bool acceptedVal;
  std::string input;
  bool gameRunning = true;
  std::vector<pice> board = initalBoard(boardSize);
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

    boardPrint(boardSize, board);
  }
}
