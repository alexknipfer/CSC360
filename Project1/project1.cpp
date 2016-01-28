#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Flight
{
  public:
    void readData(ifstream &);
    void initializeSeating();
    void printSeatingChart(ofstream &, int);
    void addPassengers();

  private:
    int fl1010L[10][2];
    int fl1010R[10];
    int fl1020L[10][2];
    int fl1020R[10];
    int fl1030L[10][2];
    int fl1030R[10];
    int fl1040L[10][2];
    int fl1040R[10];
    
    int fl1015L[10][2];
    int fl1015R[10];
    int fl1025L[10][2];
    int fl1025R[10];
    int fl1035L[10][2];
    int fl1035R[10];
    int fl1045L[10][2];
    int fl1045R[10];
    
    int boardingNumber;
    int flightNumber;
    char section;
    int seatRow;
    char seatColumn;
    
};

//************************************************

int main()
{
  Flight myFlight;

  ofstream outputFile("output.txt");
  ifstream inputFile("testdata.txt");

  myFlight.initializeSeating();
  myFlight.readData(inputFile);
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << " Flight 1010                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Memphis, Tennessee" << endl;
  
  myFlight.printSeatingChart(outputFile, 1010);
}

//************************************************

void Flight::initializeSeating()
{
    // Receives - nothing
    // Task - initialize all seats to -999
    // Returns - nothing

  for(int x = 0; x < 10; x++)
  {
    for(int y = 0; y < 2; y++)
    {
      fl1010L[x][y] = -999;
      fl1020L[x][y] = -999;
      fl1030L[x][y] = -999;
      fl1040L[x][y] = -999;

      fl1015L[x][y] = -999;
      fl1025L[x][y] = -999;
      fl1035L[x][y] = -999;
      fl1045L[x][y] = -999;
    }
  }
  
  for(int z = 0; z < 10; z++)
  {
    fl1010R[z] = -999;
    fl1020R[z] = -999;
    fl1030R[z] = -999;
    fl1040R[z] = -999;
    
    fl1015R[z] = -999;
    fl1025R[z] = -999;
    fl1035R[z] = -999;
    fl1045R[z] = -999;
  }
}

//******************************************************************************

void Flight::readData(ifstream &inFile)
{
    // Receives - input file
    // Task - read in values from data file
    // Returns - nothing
    
    inFile >> boardingNumber;
    
    while(boardingNumber != -999)
    {
      inFile >> flightNumber;
      inFile >> section;
      inFile >> seatRow;
      inFile >> seatColumn;
      
      addPassengers();
      
      inFile >> boardingNumber;
    }
}

//******************************************************************************

void Flight::addPassengers()
{
  seatRow--;
  bool rowFull = true;
  
  //**** CHECK SEATING FOR FLIGHT 1010 *****************************************
  
  if(flightNumber == 1010)
  {
    if(seatColumn == 'L')
    {
      if(fl1010L[seatRow][0] == -999)
      {
        fl1010L[seatRow][0] = boardingNumber;
        rowFull = false;
      }
      
      else if(fl1010L[seatRow][1] == -999)
      {
        fl1010L[seatRow][1] = boardingNumber;
        rowFull = false;
      }
      
      else if(fl1010R[seatRow] == -999)
      {
        fl1010R[seatRow] = boardingNumber;
        rowFull = false;
      }
      
      else if(rowFull == true)
      {
        for(int x = 0; x < 10; x++)
        {
          for(int y = 0; y < 2; y++)
          {
            if(fl1010L[x][y] == -999)
            {
              fl1010L[x][y] = boardingNumber;
              break;
            }
          }
          if(fl1010R[x] == -999)
          {
            fl1010R[x] = boardingNumber;
            break;
          }
        }
        //cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1010L[seatRow][1] == -999)
      {
        fl1010L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1010L[seatRow][0] == -999)
      {
        fl1010L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1010R[seatRow] == -999)
      {
        fl1010R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1010R[seatRow] == -999)
      {
        fl1010R[seatRow] = boardingNumber;
      }
      
      else if(fl1010L[seatRow][0] == -999)
      {
        fl1010L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1010L[seatRow][1] == -999)
      {
        fl1010L[seatRow][1] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
      
    }
  }

  
  //******* CHECK SEATING FOR FLIGHT 1015 **************************************
  
  else if(flightNumber == 1015)
  {
    if(seatColumn == 'L')
    {
      if(fl1015L[seatRow][0] == -999)
      {
        fl1015L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1015L[seatRow][1] == -999)
      {
        fl1015L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1015R[seatRow] == -999)
      {
        fl1010R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1015L[seatRow][1] == -999)
      {
        fl1015L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1015L[seatRow][0] == -999)
      {
        fl1015L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1015R[seatRow] == -999)
      {
        fl1015R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1015R[seatRow] == -999)
      {
        fl1015R[seatRow] = boardingNumber;
      }
      
      else if(fl1015L[seatRow][0] == -999)
      {
        fl1015L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1015L[seatRow][1] == -999)
      {
        fl1015L[seatRow][1] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;  
      }
      
    }
  }
 
  //******* CHECK SEATING FOR FLIGHT 1020 **************************************
  
  else if(flightNumber == 1020)
  {
    if(seatColumn == 'L')
    {
      if(fl1020L[seatRow][0] == -999)
      {
        fl1020L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1020L[seatRow][1] == -999)
      {
        fl1020L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1020R[seatRow] == -999)
      {
        fl1020R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1020L[seatRow][1] == -999)
      {
        fl1020L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1020L[seatRow][0] == -999)
      {
        fl1020L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1020R[seatRow] == -999)
      {
        fl1020R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1020R[seatRow] == -999)
      {
        fl1020R[seatRow] = boardingNumber;
      }
      
      else if(fl1020L[seatRow][0] == -999)
      {
        fl1020L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1020L[seatRow][1] == -999)
      {
        fl1020L[seatRow][1] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;  
      }
      
    }
  }
  
  //******* CHECK SEATING FOR FLIGHT 1025 **************************************
  
  else if(flightNumber == 1025)
  {
    if(seatColumn == 'L')
    {
      if(fl1025L[seatRow][0] == -999)
      {
        fl1025L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1025L[seatRow][1] == -999)
      {
        fl1025L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1025R[seatRow] == -999)
      {
        fl1025R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1025L[seatRow][1] == -999)
      {
        fl1025L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1025L[seatRow][0] == -999)
      {
        fl1025L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1025R[seatRow] == -999)
      {
        fl1025R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1025R[seatRow] == -999)
      {
        fl1025R[seatRow] = boardingNumber;
      }
      
      else if(fl1025L[seatRow][0] == -999)
      {
        fl1025L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1025L[seatRow][1] == -999)
      {
        fl1025L[seatRow][1] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;  
      }
      
    }
  }
  
  //******* CHECK SEATING FOR FLIGHT 1030 **************************************

  else if(flightNumber == 1030)
  {
    if(seatColumn == 'L')
    {
      if(fl1030L[seatRow][0] == -999)
      {
        fl1030L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1030L[seatRow][1] == -999)
      {
        fl1030L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1030R[seatRow] == -999)
      {
        fl1030R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1030L[seatRow][1] == -999)
      {
        fl1030L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1030L[seatRow][0] == -999)
      {
        fl1030L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1030R[seatRow] == -999)
      {
        fl1030R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1030R[seatRow] == -999)
      {
        fl1030R[seatRow] = boardingNumber;
      }
      
      else if(fl1030L[seatRow][0] == -999)
      {
        fl1030L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1030L[seatRow][1] == -999)
      {
        fl1030L[seatRow][1] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;  
      }
      
    }
  }
  
  //******* CHECK SEATING FOR FLIGHT 1035 **************************************

  else if(flightNumber == 1035)
  {
    if(seatColumn == 'L')
    {
      if(fl1035L[seatRow][0] == -999)
      {
        fl1035L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1035L[seatRow][1] == -999)
      {
        fl1035L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1035R[seatRow] == -999)
      {
        fl1035R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1035L[seatRow][1] == -999)
      {
        fl1035L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1035L[seatRow][0] == -999)
      {
        fl1035L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1035R[seatRow] == -999)
      {
        fl1035R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1035R[seatRow] == -999)
      {
        fl1035R[seatRow] = boardingNumber;
      }
      
      else if(fl1035L[seatRow][0] == -999)
      {
        fl1035L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1035L[seatRow][1] == -999)
      {
        fl1035L[seatRow][1] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;  
      }
      
    }
  }
  
  //******* CHECK SEATING FOR FLIGHT 1040 **************************************
  
  else if(flightNumber == 1040)
  {
    if(seatColumn == 'L')
    {
      if(fl1040L[seatRow][0] == -999)
      {
        fl1040L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1040L[seatRow][1] == -999)
      {
        fl1040L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1040R[seatRow] == -999)
      {
        fl1040R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1040L[seatRow][1] == -999)
      {
        fl1040L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1040L[seatRow][0] == -999)
      {
        fl1040L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1040R[seatRow] == -999)
      {
        fl1040R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1040R[seatRow] == -999)
      {
        fl1040R[seatRow] = boardingNumber;
      }
      
      else if(fl1040L[seatRow][0] == -999)
      {
        fl1040L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1040L[seatRow][1] == -999)
      {
        fl1040L[seatRow][1] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;  
      }
      
    }
  }
  
  //******* CHECK SEATING FOR FLIGHT 1045 **************************************
  
  else if(flightNumber == 1045)
  {
    if(seatColumn == 'L')
    {
      if(fl1045L[seatRow][0] == -999)
      {
        fl1045L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1045L[seatRow][1] == -999)
      {
        fl1045L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1045R[seatRow] == -999)
      {
        fl1045R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1045L[seatRow][1] == -999)
      {
        fl1045L[seatRow][1] = boardingNumber;
      }
      
      else if(fl1045L[seatRow][0] == -999)
      {
        fl1045L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1045R[seatRow] == -999)
      {
        fl1045R[seatRow] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1045R[seatRow] == -999)
      {
        fl1045R[seatRow] = boardingNumber;
      }
      
      else if(fl1045L[seatRow][0] == -999)
      {
        fl1045L[seatRow][0] = boardingNumber;
      }
      
      else if(fl1045L[seatRow][1] == -999)
      {
        fl1045L[seatRow][1] = boardingNumber;
      }
      
      else
      {
        cout << boardingNumber << endl;  
      }
      
    }
  }
}

//******************************************************************************

void Flight::printSeatingChart(ofstream &outFile, int flightNumber)
{
    // Receives - output file
    // Task - print out seating chart
    // Returns - nothing
    
    int rightSeatCount = 0;
    
    if(flightNumber == 1010)
    {
      for(int x = 0; x < 10; x++)
      {
        for(int y = 0; y < 2; y++)
        {
          outFile << fl1010L[x][y] << "         ";
        }
          outFile << fl1010R[rightSeatCount] << endl;
          rightSeatCount++;
      }
    }
}
