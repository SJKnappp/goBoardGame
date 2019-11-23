#include <iostream>
#include <vector>
#include <string>



  struct piece{
    int state; //0 for unlpayed/taken 1 black 2 for white
    int liberty; //number of surronding empty tiles = 0 for empty space
    int group; // a set of same coulour stones all touching one another = 0 for empty space
  };

  int main();
  std::vector<piece> initalBoard(const int boardSize);
  void boardPrint(int boardSize, std::vector<piece> board);
  piece updatePiece(std::vector<piece> v,int i,int j,int N, bool isBlack );
  std::vector<piece> updateLib(std::vector<piece> v, int boardSize);
  std::vector<piece> remove(std::vector<piece> v, int boardSize, int isBlack);
  std::vector<piece> removeGroup(std::vector<piece> v, int boardSize, bool isBlack, int group1, int group2);
