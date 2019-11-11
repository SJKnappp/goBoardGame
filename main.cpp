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

//prints out the board values
void boardPrint(int boardSize, std::vector<piece> board){
  for(int i =0; i < boardSize; i++){
    for(int j=0;j<boardSize;j++){
      if(board.at(j+boardSize*i).state ==0){std::cout << "+ ";}
      else if(board.at(j+boardSize*i).state == 1){std::cout << "B ";}
      else if(board.at(j+boardSize*i).state == 2){std::cout << "W ";}
      std::cout << board.at(j+boardSize*i).group;
      // std::cout << board.at(j+boardSize*i).state << ' ' << j+boardSize*i << ' ';
    }
    std::cout << '\n';
  }
}

//
piece updatePiece(std::vector<piece> v,int i,int j,int N, bool isBlack ){
  int colour;
  if(isBlack == true){colour = 1;}else{colour =2;}
  // std::cout << colour << '\n';
  if(v.at(i+j*N).state == 0){
    v.at(i+j*N).state = colour;
  }else{return v.at(i+j*N);}
  // std::cout << v.at(i+j*N).state << '\n';
  return v.at(i+j*N);
}

//caculates the liberty of each piece
std::vector<piece> updateLib(std::vector<piece> v, int boardSize){
  for(int i = 0; i < boardSize; i++){
    for(int j =0; j < boardSize; j++){
      if(v.at(i*boardSize + j).state != 0){
        v.at(i*boardSize + j).liberty = 0;
        if(i != 0) {
          if(v.at((i-1)*boardSize + j ).state == 0){v.at(i*boardSize + j).liberty += 1; }
        }
        if(i != boardSize - 1){ if( v.at((i+1)*boardSize + j).state == 0) {v.at(i*boardSize + j).liberty += 1; }}
        if(j != 0 ){ if ( v.at(i*boardSize + j - 1).state == 0) {v.at(i*boardSize + j).liberty += 1; }}
        if(j != boardSize - 1) {if ( v.at(i*boardSize + j + 1).state == 0 ) {v.at(i*boardSize + j).liberty += 1;}}
        }


    }
  }
  return v;
}

std::vector<piece> remove(std::vector<piece> v, int boardSize, int isBlack){
  for(int i = 0; i < boardSize; i++){
    for(int j =0; j < boardSize; j++){
      if(v.at((i)*boardSize + j).liberty == 0){
        v.at((i)*boardSize + j).state = 0;
        v.at((i)*boardSize + j).group = 0;
      }
    }
  }
  return v;
}

int main(){
  //initalise variables
  const int boardSize = 19;
  bool isBlack = false;
  bool acceptedVal; int x_at; int y_at; int y_ten;
  std::string input;
  bool gameRunning = true;
  std::vector<int> blackGroups;
  std::vector<int> whiteGroups;
  //setup the board and print intial condition
  std::vector<piece> board = initalBoard(boardSize);
  boardPrint(boardSize, board);

  //start main loop
  while(gameRunning == true){
    //dectects player
    if(isBlack == true){isBlack = false;}else{isBlack =true;}

    //player possition
    std::cout << "please input position ";
    if(isBlack == true){std::cout << "black " << '\n';} else{std::cout << "white ";} std::cout << '\n';
    std::cin >> input;
    acceptedVal = false;

    //while loop for accepting values
    while(acceptedVal == false){
      if(input.length() == 2 || input.length() == 3){
        x_at = input.at(0) - 97;
        y_at = input.at(1) - 49;
        if(input.length() == 3){y_ten = input.at(3) - 49;  y_at = 10*y_at + y_ten;}
        // std::cout << x_at << y_at << '\n';
        if(x_at >= 0 && y_at >= 0 && x_at < 19 && y_at < 19 && board.at(y_at*boardSize+x_at).state == 0){ break; }
      }
      std::cout << "please renter value "; std::cin >> input;
    }

    board.at(x_at + y_at*boardSize) = updatePiece(board, x_at, y_at, boardSize, isBlack);
    // std::cout << board.at(x_at+y_at*boardSize).state << '\n';

    if(isBlack == true){ board.at(x_at + y_at * boardSize).state = 1; }
    else{ board.at(x_at + y_at * boardSize).state = 2; }

    int groups = 0;
    if(x_at != 0){if(board.at(x_at + y_at * boardSize).state == board.at(x_at - 1 + y_at * boardSize).state ){
      board.at(x_at + y_at * boardSize).group = board.at(x_at - 1+ y_at * boardSize).group; groups +=1; std::cout << "/* message */" << '\n';
    }}if(x_at != boardSize){if(board.at(x_at + y_at * boardSize).state == board.at(x_at + 1 + y_at * boardSize).state ){
      board.at(x_at + y_at * boardSize).group = board.at(x_at + 1 + y_at * boardSize).group; groups+=1; std::cout << "/* message */" << '\n';
    }}if(y_at != 0){if(board.at(x_at + y_at * boardSize).state == board.at(x_at - 1 + (y_at -1 ) * boardSize).state ){
      board.at(x_at + y_at * boardSize).group = board.at(x_at + (y_at - 1) * boardSize).group;groups+=1; std::cout << "/* message */" << '\n';
    }}if(y_at != boardSize){if(board.at(x_at + y_at * boardSize).state == board.at(x_at - 1 + (y_at + 1) * boardSize).state ){
      board.at(x_at + y_at * boardSize).group = board.at(x_at + (y_at + 1) * boardSize).group;groups+=1; std::cout << "/* message */" << '\n';
    }}if(groups == 0 && isBlack == true){board.at(x_at + y_at * boardSize).group = blackGroups.size(); blackGroups.push_back(0);}
    if(groups == 0 && isBlack == false){board.at(x_at + y_at * boardSize).group = whiteGroups.size(); whiteGroups.push_back(0);}


    board = updateLib(board, boardSize);
    board = remove(board, boardSize, isBlack);


    boardPrint(boardSize, board);
  }
}
