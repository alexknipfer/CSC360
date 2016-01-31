#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Flight
{
  public:
    void processPassengers(ifstream &, ofstream &);
    void initializeSeating();
    void printSeatingChart(ofstream &, int [][3]);
    void addPassengers(int [][3], vector<int> &);
    void printWaitingList(ofstream &, vector<int> &);

  public:
    int fl1010[10][3];  //holds passengers for flight 1010
    int fl1020[10][3];  //holds passengers for flight 1020
    int fl1030[10][3];  //holds passengers for flight 1030
    int fl1040[10][3];  //holds passengers for flight 1040
    int fl1015[10][3];  //holds passengers for flight 1015
    int fl1025[10][3];  //holds passengers for flight 1025
    int fl1035[10][3];  //holds passengers for flight 1035
    int fl1045[10][3];  //holds passengers for flight 1045
    
    vector<int> fl1010w;  //waiting list for flight 1010
    vector<int> fl1020w;  //waiting list for flight 1020
    vector<int> fl1030w;  //waiting list for flight 1030
    vector<int> fl1040w;  //waiting list for flight 1040
    vector<int> fl1015w;  //waiting list for flight 1015
    vector<int> fl1025w;  //waiting list for flight 1025
    vector<int> fl1035w;  //waiting list for flight 1035
    vector<int> fl1045w;  //waiting list for flight 1045

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
  myFlight.processPassengers(inputFile, outputFile);
  
  //********* PRINT FLIGHT 1010 ************************************************
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1010                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Memphis, Tennessee" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1010);
  
  outputFile << "WAITING LIST" << endl;
  
  myFlight.printWaitingList(outputFile, myFlight.fl1010w);
  
  //********* PRINT FLIGHT 1015 ************************************************
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1015                        FROM: Memphis, Tennessee" << endl;
  outputFile << "                                    TO: Jackson, Mississippi" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1015);
  
  outputFile << "WAITING LIST" << endl;
  
  myFlight.printWaitingList(outputFile, myFlight.fl1015w);
  
  //********* PRINT FLIGHT 1020 ************************************************
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1020                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Little Rock, Arkansas" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1020);
  
  outputFile << "WAITING LIST" << endl;
  
  myFlight.printWaitingList(outputFile, myFlight.fl1020w);
  
  //********* PRINT FLIGHT 1025 ************************************************
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1025                        FROM: Little Rock, Arkansas" << endl;
  outputFile << "                                    TO: Jackson, Mississippi" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1025);
  
  outputFile << "WAITING LIST" << endl;
  
  myFlight.printWaitingList(outputFile, myFlight.fl1025w);
  
  //********* PRINT FLIGHT 1030 ************************************************
 
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1030                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Shreveport , Louisiana" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1030);
  
  outputFile << "WAITING LIST" << endl;
  
  myFlight.printWaitingList(outputFile, myFlight.fl1030w);
  
  //********* PRINT FLIGHT 1035 ************************************************
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1035                        FROM: Shreveport, Louisiana" << endl;
  outputFile << "                                    TO: Jackson, Mississippi" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1035);
  
  outputFile << "WAITING LIST" << endl;
  
  myFlight.printWaitingList(outputFile, myFlight.fl1035w);
  
  //********* PRINT FLIGHT 1040 ************************************************
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1040                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Orlando, Florida" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1040);
  
  outputFile << "WAITING LIST" << endl;
  
  myFlight.printWaitingList(outputFile, myFlight.fl1040w);
  
  
 //********* PRINT FLIGHT 1045 ************************************************
  
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1045                        FROM: Orlando, Florida" << endl;
  outputFile << "                                    TO: Jackson, Mississippi" << endl;
  
  myFlight.printSeatingChart(outputFile, myFlight.fl1045);
  
  outputFile << "WAITING LIST" << endl;
  
  myFlight.printWaitingList(outputFile, myFlight.fl1045w);

  
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

void Flight::processPassengers(ifstream &inFile, ofstream &outputFile)
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
          addPassengers(fl1010, fl1010w);
          break;
          
        case 1015: 
          addPassengers(fl1015, fl1015w);
          break;
          
        case 1020: 
          addPassengers(fl1020, fl1020w);
          break;
          
        case 1025: 
          addPassengers(fl1025, fl1025w);
          break;
          
        case 1030: 
          addPassengers(fl1030, fl1030w);
          break;
          
        case 1035: 
          addPassengers(fl1035, fl1035w);
          break;
          
        case 1040: 
          addPassengers(fl1040, fl1040w);
          break;
          
        case 1045: 
          addPassengers(fl1045, fl1045w);
          break;
      }
      inFile >> boardingNumber;
    }
}

//******************************************************************************

void Flight::addPassengers(int seatingChart[10][3], vector<int> &waitingList)
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
      
      if(foundAvailableSeat == false)
      {
        waitingList.push_back(boardingNumber);
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
      
      if(foundAvailableSeat == false)
      {
        waitingList.push_back(boardingNumber);
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
        waitingList.push_back(boardingNumber);
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
}

//******************************************************************************

void Flight::printWaitingList(ofstream &outputFile, vector<int> &waitingList)
{
  int sum = 0;

  for(int i=0; i < waitingList.size(); i++) 
  {
    sum++;
    outputFile << "    " << waitingList[i] << " ";
  }
  
  outputFile << endl;
  
  if(sum == 0)
  {
    outputFile << "    There is no waiting list for this flight" << endl;
  }
  
  for(int x = 0; x < 5; x++)
  {
    outputFile << endl;
  }
}
