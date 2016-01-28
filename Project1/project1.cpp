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
    int fl1010[10][3];
    int fl1020[10][3];
    int fl1030[10][3];
    int fl1040[10][3];

    int fl1015[10][3];
    int fl1025[10][3];
    int fl1035[10][3];
    int fl1045[10][3];

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
    for(int y = 0; y < 3; y++)
    {
      fl1010[x][y] = -999;
      fl1020[x][y] = -999;
      fl1030[x][y] = -999;
      fl1040[x][y] = -999;

      fl1015[x][y] = -999;
      fl1025[x][y] = -999;
      fl1035[x][y] = -999;
      fl1045[x][y] = -999;
    }
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
  bool foundAvailableSeat = false;

  //**** CHECK SEATING FOR FLIGHT 1010 *****************************************
  
  if(flightNumber == 1010)
  {
    if(seatColumn == 'L')
    {
      if(fl1010[seatRow][0] == -999)
      {
        fl1010[seatRow][0] = boardingNumber;
      }
      
      else if(fl1010[seatRow][1] == -999)
      {
        fl1010[seatRow][1] = boardingNumber;
      }
      
      else if(fl1010[seatRow][2] == -999)
      {
        fl1010[seatRow][2] = boardingNumber;
      }
      
      else
      {
        for(int x = 0; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(fl1010[x][y] == -999)
            {
              fl1010[x][y] = boardingNumber;
              return;
            }
          }
        }
        //cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'M')
    {
      if(fl1010[seatRow][1] == -999)
      {
        fl1010[seatRow][1] = boardingNumber;
      }
      
      else if(fl1010[seatRow][0] == -999)
      {
        fl1010[seatRow][0] = boardingNumber;
      }
      
      else if(fl1010[seatRow][2] == -999)
      {
        fl1010[seatRow][2] = boardingNumber;
      }
      
      else
      {
        for(int x = 0; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(fl1010[x][y] == -999)
            {
              fl1010[x][y] = boardingNumber;
              return;
            }
          }
        }
        //cout << boardingNumber << endl;
      }
    }
    
    else if(seatColumn == 'R')
    {
      if(fl1010[seatRow][2] == -999)
      {
        fl1010[seatRow][2] = boardingNumber;
      }
      
      else if(fl1010[seatRow][0] == -999)
      {
        fl1010[seatRow][0] = boardingNumber;
      }
      
      else if(fl1010[seatRow][1] == -999)
      {
        fl1010[seatRow][1] = boardingNumber;
      }
      
      else
      {
        for(int x = 0; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(fl1010[x][y] == -999)
            {
              fl1010[x][y] = boardingNumber;
              foundAvailableSeat = true;
              return;
            }
          }
        }
        //cout << boardingNumber << endl;
        if(foundAvailableSeat == false)
        {
          cout << "added to waiting list" << endl;
        }
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
    
    if(flightNumber == 1010)
    {
      for(int x = 0; x < 10; x++)
      {
        for(int y = 0; y < 3; y++)
        {
          outFile << fl1010[x][y] << "         ";
        }
        outFile << endl;
      }
    }
}
