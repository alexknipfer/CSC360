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
    void printSeatingChart(ofstream &);
  private:
    int seatingChart[10][3][1];
};

//************************************************

int main()
{
  Flight myFlight;

  ofstream outputFile("output.txt");
  ifstream inputFile("testdata.txt");

  myFlight.initializeSeating();
  myFlight.readData(inputFile);
  myFlight.printSeatingChart(outputFile);
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
      for(int z = 0; z < 1; z++)
      {
        seatingChart[x][y][z] = -999;
      }
    }
  }
}

//************************************************

void Flight::readData(ifstream &inFile)
{
    // Receives - input file
    // Task - read in values from data file
    // Returns - nothing
  //cout << "HELLO" << endl;
}

//************************************************

void Flight::printSeatingChart(ofstream &outFile)
{
    // Receives - output file
    // Task - print out seating chart
    // Returns - nothing
  for(int x = 0; x < 10; x++)
  {
    for(int y = 0; y < 3; y++)
    {
      for(int z = 0; z < 1; z++)
      {
        //outFile << seatingChart[x][y][z];
      }
    }
    outFile << endl;
  }
}
