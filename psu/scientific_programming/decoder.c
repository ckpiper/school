
/* ========================================================================== 
    This program decodes raw data from a radiosonde(weather balloon) and puts 
it into a readable form. It only decodes the Mandatory level data(TTAA group). 
It will give you the pressure, altitude(m), Temp (C), Dewpoint Depression,
Dewpoint, Relative Humidity(%), Wind Direction in degrees and Wind Speed (kts)

      Date            Programmer                Desription of Change
      --------        ---------------           -------------------------
      4/18/2013       Colton Piper              Original Program
 ========================================================================== */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

struct wx_data{
    char Elements[20] ;
    int Pres ;
    int Alt ;
    float Temp ;
    float DptDep ;
    float DewPt ;
    float RH ;
    int WDir ;
    int WSpd ;
} ;

/*============================================================================*/

// This prints out all the data within the structure
void Print_Data(Data, count)
struct wx_data Data[50] ;
int count;
{
  FILE *DL ;
  count = count - 1;
  int j, MWind ;
  
  DL = fopen("DataList.txt", "a") ;
  
  fprintf(DL, "Raw Data          | Pres(mb) | Height(m) | Temp(C) | DptDep | Dewpt |    RH  | W-Dir |  WSpd(Kt)|\n") ;
  fprintf(DL, "------------------------------------------------------------------------------------------------|\n") ;
  for(j=0; j<count; j++){
      fprintf(DL, "%18s|", Data[j].Elements) ;
      if(Data[j].Pres == 99){ // Seperates the # Pressures from the words and if the Alt is
          fprintf(DL, "  Surface | %4d (mb) |", Data[j].Alt) ; // the pressure or height.
      }else{
          if(Data[j].Pres == 88){
              fprintf(DL, "    Tropo | %4d (mb) |", Data[j].Alt) ;
          }else{
              if(Data[j].Pres == 77){
                  fprintf(DL, "  MaxWind | %4d (mb) |", Data[j].Alt) ;
              }else{
                  fprintf(DL, "%9d | %9d |", Data[j].Pres, Data[j].Alt) ;
              }
          }
      }
      sscanf(Data[j].Elements, "%2d", &MWind) ;
      if(MWind == 77){
          fprintf(DL, "   !!!!  Data Not Provided  !!!!   |") ;
      }else{
          fprintf(DL, " %7.1f | %6.1f |", Data[j].Temp, Data[j].DptDep) ;
          fprintf(DL, "%6.1f |", Data[j].DewPt) ;
          if(Data[j].RH == -99.0){
              fprintf(DL, " %6.1f |", Data[j].RH) ;
          }else{
              fprintf(DL, " %6.1f |", fabs(Data[j].RH)) ;
          }
      }
      fprintf(DL, " %5d | %8d |\n\n", Data[j].WDir, Data[j].WSpd) ;
  }
  fclose(DL) ;
}

/*============================================================================*/

// This decodes the wind data, Direction and Speed.
void Decode_WindData(Data, i)
struct wx_data Data[50] ;
int i ;
{
  int WDir, WSpd, MDigit, MaxWind ;
  char MWDir, MWSpd ; // The M stands for Missing 
  
  sscanf(Data[i].Elements, "%2d", &MaxWind) ;
  sscanf(Data[i].Elements + 12, "%3d", &WDir) ;
  sscanf(Data[i].Elements + 14, "%d", &MDigit) ;
  sscanf(Data[i].Elements + 15, "%2d", &WSpd) ;
  sscanf(Data[i].Elements + 12, "%c", &MWDir) ;
  sscanf(Data[i].Elements + 15, "%c", &MWSpd) ;
  
  if(MaxWind != 77){
      if(MDigit == 1 || MDigit == 6){      
          WDir = WDir - 1 ;
          WSpd = WSpd + 100 ;
      }
  }
  // This if statement determines if there is missing data 
  if(isdigit(MWDir) == 0 || isdigit(MWSpd) == 0){
      if(isdigit(MWDir) == 0){
          if(isdigit(MWSpd) == 0){ // If this is true both Wind data
              Data[i].WDir = -99 ; // are missing.
              Data[i].WSpd = -99 ;
          }else{
              Data[i].WSpd = WSpd ; 
              Data[i].WDir = -99 ;
          }
      }else{
         Data[i].WSpd = -99 ; 
         Data[i].WDir = WDir ;
      }  
  }else{
      Data[i].WDir = WDir ;
      Data[i].WSpd = WSpd ;
  }
}

/*============================================================================*/

// This Decodes the Temperature, Dewpoint, and Relative Humidity data.
void Decode_TempDptData(Data, i)
struct wx_data Data[50] ;
int i ;
{
  
  float Temp, DD, Dpt, RH ;
  int MaxWind ; 
  char MTemp, MDD ;
  
  sscanf(Data[i].Elements + 6, "%c", &MTemp);
  sscanf(Data[i].Elements + 9, "%c", &MDD);
  sscanf(Data[i].Elements + 6, "%3f", &Temp);
  sscanf(Data[i].Elements + 9, "%2f", &DD);
  sscanf(Data[i].Elements, "%2d", &MaxWind) ;
  
 
  if(MaxWind == 77){
      Data[i].WDir = (int)Temp ;
      Data[i].WSpd = (int)DD ;
  }else{
  
  // This finds out if the temperature is negative or positive
      if(((int)Temp % 2) == 1){
          Temp = Temp * -1 ;
      }
      Temp = Temp/10.0 ;
  
  // This if statement determines if the Dewpoint Depression is higher then 5.
      if(DD > 50){ 
          DD = DD - 50 ;
      }else{
          DD = DD/10.0 ;
      }
  
      Dpt = Temp - DD ; // Find the Dewpoint
      RH = 100.0 - 5.0*(Temp - Dpt) ; // Find Relative Humidty
  
      Data[i].Temp = Temp ;
      Data[i].DptDep = DD ;
      Data[i].DewPt = Dpt ;
      Data[i].RH = RH ;
  }
  
  // This if statement determines if it is Missing Data
  if(isdigit(MTemp) == 0 || isdigit(MDD) == 0){
      if(isdigit(MTemp) == 0){   // If it is not a digit, go in
          if(isdigit(MDD) == 0){
              Data[i].Temp = -99.0 ;
              Data[i].DptDep = -99.0 ;
          }else{
              Data[i].Temp = -99.0 ;
              Data[i].DptDep = DD ;
          }
      }else{
          Temp = Temp / 10.0 ;
          Data[i].Temp = Temp ;
          Data[i].DptDep = -99.0 ;
      }
      Data[i].DewPt = -99.0 ;
      Data[i].RH = -99.0 ;
  }
}

/*============================================================================*/

// This decodes the Pressure level and what altitude that Pressure level is at.
void Decode_PresAltData(Data, i)
struct wx_data Data[50] ;
int i ;
{
  int Pres, Alt ;
  
  sscanf(Data[i].Elements, "%2d", &Pres) ;
  sscanf(Data[i].Elements + 2, "%3d", &Alt) ;

      switch(Pres){
          case(99) : Data[i].Pres = 99 ;
                     if(Alt<800){
                         Data[i].Alt = Alt + 1000 ;
                     }else{
                         Data[i].Alt = Alt ;
                     }
                     break ;
          case(92) : Data[i].Pres = 925 ;
                     Data[i].Alt = Alt ;
                     break ;
          case(85) : Data[i].Pres = 850 ;
                     Data[i].Alt = Alt + 1000 ;
                     break ;
          case(70) : Data[i].Pres = 700 ;
                     Data[i].Alt = Alt + 3000 ;
                     break ;
          case(50) : Data[i].Pres = 500 ;
                     Data[i].Alt = Alt*10 ;
                     break ;
          case(40) : Data[i].Pres = 400 ;
                     Data[i].Alt = Alt*10 ;
                     break ;
          case(30) : Data[i].Pres = 300 ;
                     Data[i].Alt = Alt*10 ;
                     break ;
          case(25) : Data[i].Pres = 250 ;
                     Data[i].Alt = Alt*10 + 10000 ;
                     break ;
          case(20) : Data[i].Pres = 200 ;
                     Data[i].Alt = Alt*10 + 10000 ;
                     break ;
          case(15) : Data[i].Pres = 150 ;
                     Data[i].Alt = Alt*10 + 10000 ;
                     break ;
          case(10) : Data[i].Pres = 100 ;
                     Data[i].Alt = Alt*10 + 10000 ;
                     break ;
          case(88) : Data[i].Pres = 88;
                     Data[i].Alt = Alt ;
                     break ;
          case(77) : Data[i].Pres = 77 ;
                     Data[i].Alt = Alt ;
                     break ;
          case(00) : Data[i].Pres = 1000 ;
                     if(Alt<50){
                         Alt = Alt + 1000;
                     }
                     Data[i].Alt = Alt ;
                     break ;
          default  : break ;
      } 
} 

/*============================================================================*/

// Puts the raw data into raw data of 15 digits that gives you the data at that
int Elements_Data(Line, Data, count)     // pressure level.
char Line[100] ;
struct wx_data Data[50] ;
int count ;
{
  int Lcounter, i; 
  char MergeLine[25] ;
  
  if(Line[0] == ' '){
      Lcounter = 18 ;
      while(Lcounter < strlen(Line)){
          strncpy(Data[count].Elements, Line + Lcounter, 18) ;
          Lcounter += 18 ; 
          count = count + 1 ;             
      }        
  }else{ // This puts the sections together if one was left behind on the 
      Lcounter = 0 ; // last line putting it in the right section.
      while(Lcounter < strlen(Line)){
          if(strlen(Data[count-1].Elements) < 17){
              if(strlen(Data[count-1].Elements) < 11){
                  strncpy(MergeLine, Line, 12) ;
                  MergeLine[12] = '\0' ;
                  strcat(Data[count-1].Elements, MergeLine) ;
                  Lcounter = 12 ;
              }else{
                  strncpy(MergeLine, Line, 6) ;
                  MergeLine[6] = '\0' ;
                  strcat(Data[count-1].Elements, MergeLine) ;
                  Lcounter = 6 ;
              }
          }
          strncpy(Data[count].Elements, Line + Lcounter, 18) ;
          Lcounter += 18 ; 
          count = count + 1 ; 
      }      
  }
  return count ;
}

/*============================================================================*/

// This reads the file and puts each line in the file into a character array.
int Read_File(struct wx_data Data[50])
{
  FILE *DFile ;
  FILE *DL ;
  int i, Date, Hour, WindLevel, Station, count = 0;
  char Line[100] ; 
  
  DL = fopen("DataList.txt", "w") ;

  if((DFile = fopen("RawData.txt", "r")) == (FILE *)NULL) {
      printf("Error: Page could not be opened.\n") ;
  }
  
  while((!feof(DFile)) && (count<200)){
      fgets(Line, sizeof(Line), DFile); // Gets line of data
      if(isspace(Line[strlen(Line)-1])){
          Line[strlen(Line)-1] = '\0' ;
      }
      Line[strlen(Line)] = ' ' ; // Puts space at end of line
      if(!feof(DFile)){
          if(Line[3] == 'B' || Line[3] == 'C' || Line[3] == 'D'){
              count += 300 ;
          }else{
              if(Line[0] == ' '){
                  sscanf(Line + 6, "%2d", &Date) ; 
                  Date = Date - 50 ; 
                  fprintf(DL, "Date of Month  : %d\n", Date) ;
                  sscanf(Line + 8, "%2d", &Hour) ;
                  fprintf(DL, "Hour of Day    : %d\n", Hour) ;
                  sscanf(Line + 10, "%d", &WindLevel) ;
                  fprintf(DL, "Wind Level     : %d\n", WindLevel) ;
                  sscanf(Line + 12, "%5d", &Station) ;
                  fprintf(DL, "Station Adress : %d\n\n", Station) ;
                  count = Elements_Data(Line, Data, count) ;
              }else{
                  count = Elements_Data(Line, Data, count) ;
              }
          }
      } 
  }
  count = count - 300 ;  //  This gets rid of the 300 added to count to get
                         //out of the loop so the original count returns.
  fclose(DFile) ;
  fclose(DL) ;
  return count ;
}

/*============================================================================*/

int main(argc, argv)
int argc;
char *argv[];
{
  int i, count ;

  static struct wx_data Data[50] ;
  
  count = Read_File(Data) ;
  
  for(i=0; i<count; i++){     
      Decode_PresAltData(Data, i) ;
      Decode_TempDptData(Data, i) ;
      Decode_WindData(Data, i) ;
  }    
  Print_Data(Data, count);
  
  exit(0);
}



