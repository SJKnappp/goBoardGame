#include <iostream>
#include <vector>
#include <string>

namespace board{

  class piece{
    int state; //0 for unlpayed/taken 1 black 2 for white
    int liberty; //number of surronding empty tiles = 0 for empty space
    int group; // a set of same coulour stones all touching one another = 0 for empty space
  };

  int main();
}
