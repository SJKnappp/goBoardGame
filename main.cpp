  #include "main.h"

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
  bool showGroups = true; //debug option
  //print top line
  char letter ='a'; //keeps letter info
  std::cout << "    "; //puts the first number in the right place
  for(int i=0; i <boardSize; i++){
    std::cout << letter << " "; //prints top row
    letter += 1; // increase letter
  }

  std::cout << std::endl;

  for(int i =0; i < boardSize; i++){
    std::cout << i + 1 << "  "; // prints the number
    if(i < 9){std::cout << " ";} //handles that one digit number
    for(int j=0;j<boardSize;j++){
      if(board.at(j+boardSize*i).state ==0){std::cout << "+ ";} //detecs board state + for no peice
      else if(board.at(j+boardSize*i).state == 1){std::cout << "B ";}//black
      else if(board.at(j+boardSize*i).state == 2){std::cout << "W ";}//white
      // std::cout << board.at(j+boardSize*i).group;
      // std::cout << board.at(j+boardSize*i).state << ' ' << j+boardSize*i << ' ';
    }if(showGroups == true){ //shows the group numbers
      for(int j= 0; j<boardSize; j++){
        std::cout << board.at(j+boardSize*i).group;
      }
    }
    std::cout << '\n'; //ends the lines
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

std::vector<piece> removeGroup(std::vector<piece> v, int boardSize, bool isBlack, int group1, int group2){

std::cout << "/* message */" << group1  << group2 <<' ';
  int stone;
  if(isBlack == true){stone = 1;}else{stone = 2;}
  std::cout << isBlack << '\n';
  for(int i = 0; i < boardSize; i++){
    for(int j =0; j < boardSize; j++){
      if(v.at(i*boardSize + j).state == stone && v.at(i*boardSize + j).group == group2){
        std::cout << "test" << v.at(i*boardSize + j).group << '\n';
          v.at(i*boardSize + j).group = group1;
          std::cout << v.at(i*boardSize + j).group << ' ' << i*boardSize + j <<'\n';
      }
    }
  }
  return v;
}

int main(){
  //initalise variables
  const int boardSize = 19;
  bool isBlack = false; //colour
  bool acceptedVal; int x_at; int y_at; int y_ten; //positional
  std::string input; //cordinate input variables
  bool gameRunning = true; //loop condition

  //keeps track of group value
  std::vector<int> blackGroups;
  std::vector<int> whiteGroups;
  //setup the board and print intial condition
  std::vector<piece> board = initalBoard(boardSize);
  boardPrint(boardSize, board);

  //start main loop
  while(gameRunning == true){
    //dectects player
    // if(isBlack == true){isBlack = false;}else{isBlack =true;}

    //player possition
    std::cout << "please input position ";
    if(isBlack == true){std::cout << "black " << '\n';} else{std::cout << "white ";} std::cout << '\n';
    std::cin >> input;
    acceptedVal = false;

    //while loop for accepting values
    while(acceptedVal == false){
      if(input.length() == 2 || input.length() ==3 ){
        x_at = input.at(0) - 97; //char convestion to number
        y_at = input.at(1) - 49; //char convestion to number
        if(input.length() == 3){y_at = (input.at(1)-48)*10+(input.at(2)-48)-1;}
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
    //left
    if(x_at != 0){if(board.at(x_at + y_at * boardSize).state == board.at(x_at - 1 + y_at * boardSize).state ){std::cout << "test" << '\n';
      board.at(x_at + y_at * boardSize).group = board.at(x_at - 1+ y_at * boardSize).group; groups +=1;}}
    //right
    if(x_at != boardSize-1){if(board.at(x_at + y_at * boardSize).state == board.at(x_at + 1 + y_at * boardSize).state ){
      if(groups > 0){board = removeGroup(board, boardSize, isBlack, board.at(x_at+ y_at * boardSize).group, board.at(x_at + 1 + y_at * boardSize).group);}
      board.at(x_at + y_at * boardSize).group = board.at(x_at + 1 + y_at * boardSize).group; groups+=1;}}
    //up
    if(y_at != 0){if(board.at(x_at + y_at * boardSize).state == board.at(x_at + (y_at -1 ) * boardSize).state ){
      if(groups > 0){board = removeGroup(board, boardSize, isBlack, board.at(x_at+ y_at * boardSize).group, board.at(x_at + (y_at - 1)* boardSize).group);}
      board.at(x_at + y_at * boardSize).group = board.at(x_at + (y_at - 1) * boardSize).group;groups+=1;}}
    //down
    if(y_at != boardSize-1){if(board.at(x_at + y_at * boardSize).state == board.at(x_at + (y_at + 1) * boardSize).state ){
      if(groups > 0){board = removeGroup(board, boardSize, isBlack, board.at(x_at+ y_at * boardSize).group, board.at(x_at + (y_at + 1) * boardSize).group);}
      board.at(x_at + y_at * boardSize).group = board.at(x_at + (y_at + 1) * boardSize).group;groups+=1;}}

    if(groups == 0 && isBlack == true){board.at(x_at + y_at * boardSize).group = blackGroups.size(); blackGroups.push_back(0);}
    if(groups == 0 && isBlack == false){board.at(x_at + y_at * boardSize).group = whiteGroups.size(); whiteGroups.push_back(0);}


    board = updateLib(board, boardSize);
    board = remove(board, boardSize, isBlack);


    boardPrint(boardSize, board);
  }
}
