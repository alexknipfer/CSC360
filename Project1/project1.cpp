#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Flight
{
  public:
    void readData(ifstream &, ofstream &);
    void initializeSeating();
    void printSeatingChart(ofstream &, int [][3]);
    void addPassengers(int [][3]);

  public:
    int fl1010[10][3];
    int fl1020[10][3];
    int fl1030[10][3];
    int fl1040[10][3];

    int fl1015[10][3];
    int fl1025[10][3];
    int fl1035[10][3];
    int fl1045[10][3];

  private:
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
  ifstream inputFile("data.txt");

  myFlight.initializeSeating();
  myFlight.readData(inputFile, outputFile);
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << " Flight 1010                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Memphis, Tennessee" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1010);

  
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

void Flight::readData(ifstream &inFile, ofstream &outputFile)
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
      
      switch(flightNumber)
      {
        case 1010: 
          addPassengers(fl1010);
          break;
          
        case 1015: 
          addPassengers(fl1015);
          break;
          
        case 1020: 
          addPassengers(fl1020);
          break;
          
        case 1025: 
          addPassengers(fl1025);
          break;
          
        case 1030: 
          addPassengers(fl1030);
          break;
          
        case 1035: 
          addPassengers(fl1035);
          break;
          
        case 1040: 
          addPassengers(fl1040);
          break;
          
        case 1045: 
          addPassengers(fl1045);
          break;
      }
      inFile >> boardingNumber;
    }
}

//******************************************************************************

void Flight::addPassengers(int seatingChart[10][3])
{
  seatRow--;
  bool foundAvailableSeat = false;

  if(seatColumn == 'L')
  {
    if(seatingChart[seatRow][0] == -999)
    {
      seatingChart[seatRow][0] = boardingNumber;
    }
    
    else if(seatingChart[seatRow][1] == -999)
    {
      seatingChart[seatRow][1] = boardingNumber;
    }
    
    else if(seatingChart[seatRow][2] == -999)
    {
      seatingChart[seatRow][2] = boardingNumber;
    }
    
    else
    {
      if(section == 'C')
      {
        for(int x = 3; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(seatingChart[x][y] == -999)
            {
              seatingChart[x][y] = boardingNumber;
              foundAvailableSeat = true;
              return;
            }
          }
        }
      }
      
      else if(section == 'F')
      {
        for(int x = 0; x < 3; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(seatingChart[x][y] == -999)
            {
              seatingChart[x][y] = boardingNumber;
              foundAvailableSeat = true;
              return;
            }
          }
        }
      }
    }
  }
  
  else if(seatColumn == 'M')
  {
    if(seatingChart[seatRow][1] == -999)
    {
      seatingChart[seatRow][1] = boardingNumber;
    }
    
    else if(seatingChart[seatRow][0] == -999)
    {
      seatingChart[seatRow][0] = boardingNumber;
    }
    
    else if(seatingChart[seatRow][2] == -999)
    {
      seatingChart[seatRow][2] = boardingNumber;
    }
    
    else
    {
      if(section == 'C')
      {
        for(int x = 3; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(seatingChart[x][y] == -999)
            {
              seatingChart[x][y] = boardingNumber;
              foundAvailableSeat = true;
              return;
            }
          }
        }
      }
      
      else if(section == 'F')
      {
        for(int x = 0; x < 3; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(seatingChart[x][y] == -999)
            {
              seatingChart[x][y] = boardingNumber;
              foundAvailableSeat = true;
              return;
            }
          }
        }
      }
    }
  }
  
  else if(seatColumn == 'R')
  {
    if(seatingChart[seatRow][2] == -999)
    {
      seatingChart[seatRow][2] = boardingNumber;
    }
    
    else if(seatingChart[seatRow][0] == -999)
    {
      seatingChart[seatRow][0] = boardingNumber;
    }
    
    else if(seatingChart[seatRow][1] == -999)
    {
      seatingChart[seatRow][1] = boardingNumber;
    }
    
    else
    {
      if(section == 'C')
      {
        for(int x = 3; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(seatingChart[x][y] == -999)
            {
              seatingChart[x][y] = boardingNumber;
              foundAvailableSeat = true;
              return;
            }
          }
        }
      }
      
      else if(section == 'F')
      {
        for(int x = 0; x < 3; x++)
        {
          for(int y = 0; y < 3; y++)
          {
            if(seatingChart[x][y] == -999)
            {
              seatingChart[x][y] = boardingNumber;
              foundAvailableSeat = true;
              return;
            }
          }
        }
      }
      if(foundAvailableSeat == false)
      {
        cout << "added to waiting list" << endl;
      }
    }
    
  }
}

//******************************************************************************

void Flight::printSeatingChart(ofstream &outFile, int seatingChart[10][3])
{
    // Receives - output file
    // Task - print out seating chart
    // Returns - nothing
    
    for(int x = 0; x < 10; x++)
    {
      for(int y = 0; y < 3; y++)
      {
        outFile << seatingChart[x][y] << "         ";
      }
      outFile << endl;
    }
    outFile << endl;
    outFile << endl;
}
