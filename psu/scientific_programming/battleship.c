/* ============================================================================= 
      This program replicates the classic game of battleship. Where the human
player faces a random computer generator.  Many printf statements are commented
out because those are used for debugging if the computer ships are acting out of
the ordinary or the computer shots are doing what they are not supposed to.
      
      Date            Programmer                Desription of Change
      --------        ---------------           -------------------------
      4/3/2013        Colton Piper              Original Program
 ============================================================================ */

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <ctype.h>

void GTop(char User) ;
void Bad_Placement(char Use) ;
void Ship_Coordinates(char Ship[], char Symbol, int Len, char User) ;
void CPU_Ship_Coordinates_Orientations(char Symbol, int Len, char User) ;
int CPU_Random_Coordinates() ;
void Ship_Coordinates_Check_One(int Row, int Col, char SPos, int Len, char Symbol, char User) ;
void Ship_Coordinates_Check_Two(int Row, int Col, char SPos, int Len, char Symbol, char User) ;
void Ship_Placement(int Row, int Col, char SPos, int Len, char Symbol, char User) ;
void Firing() ;
void Display_Grid(char User) ;
void Blank_Grid(char User) ;
void Sunken_Ships(int i, char Phrase[]) ;

char GridPlayer[10][10], GridCPU[10][10], GridTrack[10][10] ;
int CPUShipCount[5] = {5,4,3,3,2} ;
int ShipCount[5] = {5,4,3,3,2} ;
int SSCount[5] = {0,0,0,0,0} ; // SS stands for sunken ship count each one is for
int SSCPUCount[5] ={0,0,0,0,0} ;  // each ship once it sinks it will turn to 1 and
                                  // will not say that the ship is sunken over and over again.  
/*============================================================================*/

void GTop(char User)
{
  int GTop[10], i;
  
  if(User == 'P'){
      printf("\n                    Player 1\n\n   ") ; //Centered title is 10 tabs
  }
  else{
      if(User == 'C'){
          printf("\n                    Computer\n\n   ") ;
      }
  }
  
  for(i=1; i<10; i++) {
      GTop[i] = i ; 
      printf("  %d ", GTop[i]) ;
  }
  printf("  %d\n", i) ;
  printf("   +---+---+---+---+---+---+---+---+---+---+\n") ;
}

/*============================================================================*/

void Bad_Placement(char User)
{
  if(User == 'S'){
      printf("   These coordinates aren't on the Grid or the\n") ;
      printf("ship is off the grid. Please type a new legal\n") ;
      printf("coordinate in (Row,Column) format. ") ;
  }
  else{
      if(User == 'F'){
          printf("  The coordinates you requested to fire on, \n") ;
          printf("have already been fired on or are out of the \n"); 
          printf("grid. Please pick new coordinates in \n") ;
          printf("(Row,Column) format. ") ;
      }
  }
}

/*============================================================================*/

// This procedure just asks for the Players Ship Coordinates.

void Ship_Coordinates(char Ship[], char Symbol, int Len, char User)
{
  int Row, Col ;
  char SPos;
  
  printf("   Where would you like your %s\n", Ship) ;
  printf("and what orientation (H or V) would you like\n") ;
  printf("it in. Use (Row,Column,H/V) format. Like\n") ;
  printf("this (1,2,H) ") ;
  scanf(" %d,%d,%c", &Row, &Col, &SPos) ;
  printf("\n") ;
  
  Ship_Coordinates_Check_One(Row, Col, SPos, Len, Symbol, User) ;  
}

/*============================================================================*/

// This gives coordinates to the CPU ships and the orientations of the ships.

void CPU_Ship_Coordinates_Orientations(char Symbol, int Len, char User)
{
  int Row, Col, Pos ;
  char SPos ;
  time_t t ;
  
  srand(time(&t)) ; 
  Row = (rand() % 10) + 1 ; // add one because rand() will give you #s 0-9 
  Col = (rand() % 10) + 1 ;
  Pos = (rand() % 2) ; // 50/50 chance the orientation will be H or V.
  
  if (Pos == 0){
      SPos = 'H' ;
      // printf("H ") ; // Used for Debugging
  }
  else {
      SPos = 'V' ;
      // printf("V ") ;
  }
  // printf("%d,%d\n", Row, Col) ;
  
  Ship_Coordinates_Check_One(Row, Col, SPos, Len, Symbol, User) ;
}

/*============================================================================*/

// This returns a number to where it is called number is used as a Row or Column.

int CPU_Random_Coordinates()
{
  int RoC ;  // RoC stands for Row or Column.
      
  RoC = (rand() % 10) + 1 ;   // add one because rand will give you 0-9
  
  return RoC ;
}

/*============================================================================*/

// This checks the coordinates to make sure the ship is not placed off the grid.

void Ship_Coordinates_Check_One(int Row, int Col, char SPos, int Len, char Symbol, char User)
{
  while((toupper(SPos)!= 'H') && (toupper(SPos)!= 'V')) {
          printf("Wrong Orientation please type a new one. ") ;
          scanf(" %c", &SPos) ;
          printf("\n");
  }
  
  if(toupper(SPos) == 'H') {
      while(((Col-1+Len)>10) || (Row>10) || (Row<1) || (Col<1)) { // The subtraction of 1 is there because if you had it the A.C. in
          if(User == 'P'){                  // Col 6 it would fit but 6+5=11 so it would be true and the
              Bad_Placement('S') ;        // while loop would execute its body.
              scanf(" %d,%d", &Row, &Col) ;   // If it is the computer then the compiler does not need to diplay
              printf("\n") ;                  // and ask for anything.
          }
          else{
              Row = CPU_Random_Coordinates() ;
              Col = CPU_Random_Coordinates() ;
              // printf("%d,%d\n", Row, Col) ;
          }
      }
  }
  else{
      while(((Row-1+Len)>10) || (Col>10) || (Row<1) || (Col<1)) {
          if(User == 'P'){
              Bad_Placement('S') ;
              scanf(" %d,%d", &Row, &Col) ;
              printf("\n") ;
          }
          else{
              Row = CPU_Random_Coordinates() ;
              Col = CPU_Random_Coordinates() ;
              // printf("%d,%d\n", Row, Col) ;
          }
      }
  }
  
  Ship_Coordinates_Check_Two(Row, Col, SPos, Len, Symbol, User) ;
  
}
  
/*============================================================================*/

// This checks to make sure that the ship is not put on top of another ship.

void Ship_Coordinates_Check_Two(int Row, int Col, char SPos, int Len, char Symbol, char User)
{
  int j = 1 ;
  int R, C ;
  
  R = Row ;
  C = Col ;
  
  while(Len >= j) {
      if(User == 'P'){
          if (GridPlayer[R-1][C-1] != ' '){
              printf("This Ship placement coordinate overlaps another\n") ;
              printf("ship please type in new corrdinates for the\n") ;
              printf("ship in (Row,Column,H/V) format. ") ;
              scanf(" %d,%d,%c", &Row, &Col, &SPos) ;
              printf("\n") ;
              Ship_Coordinates_Check_One(Row, Col, SPos, Len, Symbol, User) ;
              j =+ 10 ;
          }
      }
      else{
          if(GridCPU[R-1][C-1] != ' '){
              Row = CPU_Random_Coordinates() ;
              Col = CPU_Random_Coordinates() ;
              // printf("%d,%d\n", Row, Col) ;
              Ship_Coordinates_Check_One(Row, Col, SPos, Len, Symbol, User) ;
              j =+ 10 ;
          }
      }
      
      if(Len == j){
          Ship_Placement(Row, Col, SPos, Len, Symbol, User) ;
      }
      
      j++ ;
      
      if(toupper(SPos) == 'H'){
          C++ ;
      }
      else{
          R++ ;
      }
  }  
}

/*============================================================================*/
 
// This places the ships symbols on the grid.

void Ship_Placement(int Row, int Col, char SPos, int Len, char Symbol, char User)
{
  int j = 1 ;
  
  if(User == 'P') {
      while (Len>=j) {
          GridPlayer[Row-1][Col-1] = Symbol ;
          j++ ;
          if(toupper(SPos) == 'H'){
              Col++ ;
          }
          else{
              Row++ ;
          }
      }
      Display_Grid(User) ;
  }
  else {
      while (Len>=j) {
          GridCPU[Row-1][Col-1] = Symbol ;
          j++ ;
          if(toupper(SPos) == 'H'){
              Col++ ;
          }
          else{
              Row++ ;
          }
      }
  }
}

/*============================================================================*/

void Firing()
{
  int Row, Col, i;
  
  printf("Where do you want to fire?(Row,Column) ") ;
  scanf("%d,%d", &Row, &Col) ;
  printf("\n") ;
  
  // This loop checks the row the Player inputted to make sure it isnt out of the grid or already been fired on.
  while((Row>10) || (Row<1) || (Col>10) || (Col<1) || (GridTrack[Row-1][Col-1] == 'H') || (GridTrack[Row-1][Col-1] == 'M')){
      Bad_Placement('F') ; 
      scanf(" %d,%d", &Row, &Col) ; 
      printf("\n") ;
  }
  
  // Checks to see if your shot got a hit.
  if((GridCPU[Row-1][Col-1] != ' ')){
      printf("               You got a hit!!!!\n\n") ;\
      switch(GridCPU[Row-1][Col-1]){
          case('A') : CPUShipCount[0] = CPUShipCount[0] - 1 ;
                      break ;
          case('B') : CPUShipCount[1] = CPUShipCount[1] - 1 ;
                      break ;
          case('C') : CPUShipCount[2] = CPUShipCount[2] - 1 ;
                      break ;
          case('S') : CPUShipCount[3] = CPUShipCount[3] - 1 ;
                      break ;
          case('P') : CPUShipCount[4] = CPUShipCount[4] - 1 ;
                      break ;
          default   : printf("Im finally free!!!\n") ;
                      break ;  
      }
      GridTrack[Row-1][Col-1] = 'H' ;
  }
  else{
      printf("You did not get a hit.\n\n") ;
      GridTrack[Row-1][Col-1] = 'M' ;
  }
  
  printf("The computer is now taking a shot.") ;
  
  Row = CPU_Random_Coordinates() ;
  Col = CPU_Random_Coordinates() ;
  printf("%d,%d\n", Row, Col);
  
  // Checks that the computer hasnt already shot here.
  while ((GridPlayer[Row-1][Col-1] == 'H') || (GridPlayer[Row-1][Col-1] == 'M')){
      Row = CPU_Random_Coordinates() ;
      Col = CPU_Random_Coordinates() ;
      // printf("%d,%d\n", Row, Col);
  }
  
  // Checks if the Computer hit one of our ships.
  if(GridPlayer[Row-1][Col-1] != ' '){
      printf(" %d,%d\n", Row, Col) ;
      switch(GridPlayer[Row-1][Col-1]){
          case('A') : ShipCount[0] = ShipCount[0] - 1 ;
                      printf("The computer hit your Aircraft Carrier!!\n\n") ;
                      break ;
          case('B') : ShipCount[1] = ShipCount[1] - 1 ;
                      printf("The computer hit your Battleship!!\n\n") ;
                      break ;
          case('C') : ShipCount[2] = ShipCount[2] - 1 ;
                      printf("The computer hit your Cruiser!!\n\n") ;
                      break ;
          case('S') : ShipCount[3] = ShipCount[3] - 1 ;
                      printf("The computer hit your Submarine!!\n\n") ;
                      break ;
          case('P') : ShipCount[4] = ShipCount[4] - 1 ;
                      printf("The computer hit your Patrol Boat!!\n\n") ;
                      break ;
          default   : break ;  
      }
      GridPlayer[Row-1][Col-1] = 'H' ;
  }
  else{
      printf(" %d,%d\n", Row, Col) ;
      printf("The computer missed!!\n") ;
      GridPlayer[Row-1][Col-1] = 'M' ;
  }
  
  Display_Grid('T') ;
  
  Display_Grid('P') ;
  
  // Checks to see if you sunk one of the enemies ships.
  for(i=0; i<5; i++){
      if(CPUShipCount[i] == 0){
          if(SSCPUCount[i] == 0){   // This is to see if the sunken ship has already been printed.
              Sunken_Ships(i, "You sunk the computer's") ;
              SSCPUCount[i] = 1 ; 
          }
      }
  }
  
  // Checks to see if the computer sunk any of your ships.
  for(i=0; i<5; i++){
      if(ShipCount[i] == 0){
          if(SSCount[i] == 0){
              Sunken_Ships(i, "The computer sunk your") ;
              SSCount[i] = 1 ;
          }
      }
  }
}

/*============================================================================*/

// This procedure diplays the grid.

void Display_Grid(char User)
{
int R, C;

  if(User == 'P'){
      GTop('P') ;
      for(R=0; R<10; R++){
          printf(" %2d", R+1) ;
          for(C=0; C<10; C++){ 
            printf("| %c ", GridPlayer[R][C]) ;
          }                      
          printf("|\n") ;
          printf("   +---+---+---+---+---+---+---+---+---+---+\n") ;
      }
  }
  else{
      if(User == 'C'){
          GTop('C') ;
          for(R=0; R<10; R++){
              printf(" %2d", R+1) ;
              for(C=0; C<10; C++){ 
                printf("| %c ", GridCPU[R][C]) ;
              }                      
              printf("|\n") ;
              printf("   +---+---+---+---+---+---+---+---+---+---+\n") ;
          }
      }
      else{
          GTop('C') ;
          for(R=0; R<10; R++){
              printf(" %2d", R+1) ;
              for(C=0; C<10; C++){ 
                printf("| %c ", GridTrack[R][C]) ;
              }                      
              printf("|\n") ;
              printf("   +---+---+---+---+---+---+---+---+---+---+\n") ;
          }
      }
  }
}

/*============================================================================*/

// This blanks out both the CPUs and Humans Grid.

void Blank_Grid(char User)
{
int Row, Col;
  if(User == 'P'){
      for(Row=0; Row<10; Row++){
          printf(" %2d", Row+1) ;
          for(Col=0; Col<10; Col++){
              GridPlayer[Row][Col] = ' ' ; // Makes the original grid with capital 'o' for Ocean.
              printf("| %c ", GridPlayer[Row][Col]) ; // which means you havent fired upon it yet.
          }                                    // or your opponent has fired on you yet.
          printf("|\n") ;
          printf("   +---+---+---+---+---+---+---+---+---+---+\n") ;
      }
  }
  else{
      if(User == 'C'){
          for(Row=0; Row<10; Row++){
              printf(" %2d", Row+1) ;
              for(Col=0; Col<10; Col++){
                  GridCPU[Row][Col] = ' ' ; 
                  printf("| %c ", GridCPU[Row][Col]) ; 
              }          
              printf("|\n") ;
              printf("   +---+---+---+---+---+---+---+---+---+---+\n") ;
          }
      }
      else{
          for(Row=0; Row<10; Row++){
              for(Col=0; Col<10; Col++){
                  GridTrack[Row][Col] = ' ' ; 
              }
          }
      }
  }
}

/*============================================================================*/

void Sunken_Ships(int i, char Phrase[])
{
  switch(i){
      case(0) : printf("\n\n  !!! %s A.C. Carrier. !!!\n\n\n", Phrase) ;
                break ;
      case(1) : printf("\n\n  !!! %s Battleship. !!!\n\n\n", Phrase) ;
                break ;
      case(2) : printf("\n\n  !!! %s Cruiser. !!!\n\n\n", Phrase) ;
                break ;
      case(3) : printf("\n\n  !!! %s Submarine. !!!\n\n\n", Phrase) ;
                break ;
      case(4) : printf("\n\n  !!! %s Patrol Boat. !!!\n\n\n", Phrase) ;
                break ;
      default : break ;
  }
}
                
/*============================================================================*/

int main(argc, argv)
int argc;
char *argv[];
{

  char SPos ;
  int Row, Col, i, j, k ;
  
  // Directions and rules of the game.
  printf("\n           !!!!!! BattleShip !!!!!!\n\n") ;
  printf("    You will be playing the classic game of\n") ;
  printf("battleship, against a computer. In the Grid\n") ;
  printf("there will be 7 different letters maximum but\n") ;
  printf("only one letter in each coordinate. The boats\n") ;
  printf("will be named by 'A' for Aircraft Carrier, 'B'\n") ;
  printf("for Battleship, 'C' for Cruiser, 'S' for\n") ;
  printf("Submarine, and 'P' for Patrol Boat. The other\n") ;
  printf("letters will be 'H' for hit and 'M' for miss.\n") ;\
  
  // This is your Grid that will have your ships on it.
  GTop('P') ;
  Blank_Grid('P') ;

  // This is the Grid the Computer will have its ships on it.
  GTop('C') ;
  Blank_Grid('C') ;
  
  Blank_Grid('T') ;
  
  // Where the player picks to place their ships.
  Ship_Coordinates("Aircraft Carrier", 'A', 5, 'P') ;
  Ship_Coordinates("Battleship", 'B', 4, 'P') ;
  Ship_Coordinates("Cruiser", 'C', 3, 'P') ;
  Ship_Coordinates("Submarine", 'S', 3, 'P') ;
  Ship_Coordinates("Patrol Boat", 'P', 2, 'P') ;
  
  printf("Your Ships have taken their positions!\n\n") ;
  printf("The CPU ships are now taking their spots.\n\n") ;
  
  // Where the CPU places their ships at random.
  CPU_Ship_Coordinates_Orientations('A', 5, 'C') ;
  CPU_Ship_Coordinates_Orientations('B', 4, 'C') ;
  CPU_Ship_Coordinates_Orientations('C', 3, 'C') ;
  CPU_Ship_Coordinates_Orientations('S', 3, 'C') ;
  CPU_Ship_Coordinates_Orientations('P', 2, 'C') ;
  
   
  // Display_Grid('C') ;
  
  printf("The enemy ships have taken their positions!\n\n") ;
  
  while((j!=0) && (k!=0)){
      Firing() ;
      printf("\n") ;
      j = 0 ;
      k = 0 ;
      for(i=0; i<5; i++){
          j = j + ShipCount[i] ;
          k = k + CPUShipCount[i] ;
      }
  }
  
  if(k == 0){
      printf("\n\n\n\n\n\n\n                Congratulations!!!!\n");
      printf("             You have won the game!!!!\n\n\n\n\n\n\n\n") ;
  }
  else{
      if(j == 0){
          printf("\n\n\n\n\n\n\n             Your ships have been sunk.\n") ;
          printf("                   YOU LOSE!!!!\n\n\n\n\n\n\n\n") ;
      }
  }

  exit(0) ;
}



