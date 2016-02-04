//******************  PROGRAM IDENTIFICATION  **********************************
//*                                                                            *
//*  PROGRAM FILE NAME: project1.cpp  ASSIGNMENT #:  1    GRADE: _____         *
//*   	                                                                       *
//*  PROGRAM AUTHOR:   ____________________________________                    *
//*                             Alex Knipfer                                   *
//*                                                                            *
//*  COURSE #:   CSC 36000 11             DUE DATE: February 08, 2015          *
//*                                                                            * 
//******************************************************************************


//********************* PROGRAM DESCRIPTION ************************************
//*    Process: This program reads in data regarding passenger data for the    * 
//*             flight number they want to board. It processes the data and    *
//*             and places them in the flight seating chart accordingly. If    *
//*             the flight is currently booked the program will try to place   *
//*             them on the flight in another seat based on the airline rules. *
//*                                                                            *
//*    USER DEFINED                                                            *
//*     MODULES:       : printHeader - print program header                    *
//*                      printFooter - print program footer                    *
//******************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class FlightClass
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
    int boardingNumber;   //passenger boarding number
    int flightNumber;     //passenger flight number
    char section;         //passenger requested section
    int seatRow;          //passenger requested row
    char seatColumn;      //passenger requested column
    
};

void printHeader(ofstream &);
void printFooter(ofstream &);

//******************************************************************************

int main()
{
    //instantiate object for flight
  FlightClass myFlight;

  ofstream outputFile("output.txt");
  ifstream inputFile("data.txt");
  
    //print program header
  printHeader(outputFile);

    //go initialize all seats to -999
  myFlight.initializeSeating();
  
    //process passengers from data
  myFlight.processPassengers(inputFile, outputFile);
  
  //********* PRINT FLIGHT 1010 ************************************************
  
    //print label for flight 1010 with destination and arrival locations
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1010                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Memphis, Tennessee" << endl;
  
    //print the seating chart for flight 1010
  myFlight.printSeatingChart(outputFile, myFlight.fl1010);
  
    //print label for waiting list
  outputFile << "WAITING LIST" << endl;
  
    //print the waiting list
  myFlight.printWaitingList(outputFile, myFlight.fl1010w);
  
  //********* PRINT FLIGHT 1015 ************************************************
  
    //print label for flight 1015 with destination and arrival locations
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1015                        FROM: Memphis, Tennessee" << endl;
  outputFile << "                                    TO: Jackson, Mississippi" << endl;
  
    //print the seating chart for flight 1015
  myFlight.printSeatingChart(outputFile, myFlight.fl1015);
  
    //print label for waiting list
  outputFile << "WAITING LIST" << endl;
  
    //print the waiting list
  myFlight.printWaitingList(outputFile, myFlight.fl1015w);
  
  //********* PRINT FLIGHT 1020 ************************************************
  
    //print label for flight 1020 with destination and arrival locations
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1020                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Little Rock, Arkansas" << endl;
  
    //print the seating chart for flight 1020
  myFlight.printSeatingChart(outputFile, myFlight.fl1020);
  
    //print label for waiting list
  outputFile << "WAITING LIST" << endl;
  
    //print the waiting list
  myFlight.printWaitingList(outputFile, myFlight.fl1020w);
  
  //********* PRINT FLIGHT 1025 ************************************************
  
    //print label for flight 1025 with destination and arrival locations
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1025                        FROM: Little Rock, Arkansas" << endl;
  outputFile << "                                    TO: Jackson, Mississippi" << endl;
  
    //print the seating chart for flight 1025
  myFlight.printSeatingChart(outputFile, myFlight.fl1025);
  
    //print the label for waiting list
  outputFile << "WAITING LIST" << endl;
  
    //print the waiting list
  myFlight.printWaitingList(outputFile, myFlight.fl1025w);
  
  //********* PRINT FLIGHT 1030 ************************************************
 
    //print label for flight 1030 with destination and arrival locations
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1030                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Shreveport , Louisiana" << endl;
  
    //print the seating chart for flight 1030
  myFlight.printSeatingChart(outputFile, myFlight.fl1030);
    
    //print the label for waiting list
  outputFile << "WAITING LIST" << endl;
  
    //print the waiting list
  myFlight.printWaitingList(outputFile, myFlight.fl1030w);
  
  //********* PRINT FLIGHT 1035 ************************************************
  
    //print the label for flight 1035 with destination and arrival locations
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1035                        FROM: Shreveport, Louisiana" << endl;
  outputFile << "                                    TO: Jackson, Mississippi" << endl;
  
    //print the seating chart for flight 1035
  myFlight.printSeatingChart(outputFile, myFlight.fl1035);
  
    //print the label for waiting list
  outputFile << "WAITING LIST" << endl;
  
    //print the waiting list
  myFlight.printWaitingList(outputFile, myFlight.fl1035w);
  
  //********* PRINT FLIGHT 1040 ************************************************
  
    //print the label for flight 1040
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1040                        FROM: Jackson, Mississippi" << endl;
  outputFile << "                                    TO: Orlando, Florida" << endl;
  
    //print the seating chart for flight 1040
  myFlight.printSeatingChart(outputFile, myFlight.fl1040);
  
    //print the label for waiting list
  outputFile << "WAITING LIST" << endl;
  
    //print the waiting list
  myFlight.printWaitingList(outputFile, myFlight.fl1040w);
  
  
 //********* PRINT FLIGHT 1045 ************************************************
  
    //print label for flight 1045
  outputFile << "               Southern Comfort Airlines" << endl;
  outputFile << endl;
  outputFile << " Flight 1045                        FROM: Orlando, Florida" << endl;
  outputFile << "                                    TO: Jackson, Mississippi" << endl;
  
    //print the seating chart for flight 1045
  myFlight.printSeatingChart(outputFile, myFlight.fl1045);
  
    //print the label for waiting list
  outputFile << "WAITING LIST" << endl;
  
    //print the waitin glist
  myFlight.printWaitingList(outputFile, myFlight.fl1045w);
  
    //print output footer
  printFooter(outputFile);
}

//******************************************************************************

void FlightClass::initializeSeating()
{
    // Receives - nothing
    // Task - initialize all seats to -999
    // Returns - nothing

    //loop through all "seats" for plane seating
    //and set the values to -999 representing open seats
  for(int x = 0; x < 10; x++)
  {
    for(int y = 0; y < 3; y++)
    {
        //set all values to -999 for each flight array
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

void FlightClass::processPassengers(ifstream &inFile, ofstream &outputFile)
{
    // Receives - input file
    // Task - read in values from data file
    // Returns - nothing
    
      //read in first value (boarding number)
    inFile >> boardingNumber;
    
      //continue reading in values until reach sentinel -999
    while(boardingNumber != -999)
    {
        //read in flight number, section, seat row, then seat column
      inFile >> flightNumber;
      inFile >> section;
      inFile >> seatRow;
      inFile >> seatColumn;
      
        //check the flight number read in
      switch(flightNumber)
      {
          //add passengers to flight 1010 if flight
          //read in was 1010
        case 1010: 
          addPassengers(fl1010, fl1010w);
          break;
          
          //add passengers to flight 1010 if flight
          //read in was 1015
        case 1015: 
          addPassengers(fl1015, fl1015w);
          break;
          
          //add passengers to flight 1010 if flight
          //read in was 1020
        case 1020: 
          addPassengers(fl1020, fl1020w);
          break;
          
          //add passengers to flight 1010 if flight
          //read in was 1025
        case 1025: 
          addPassengers(fl1025, fl1025w);
          break;
          
          //add passengers to flight 1010 if flight
          //read in was 1030
        case 1030: 
          addPassengers(fl1030, fl1030w);
          break;
          
          //add passengers to flight 1010 if flight
          //read in was 1035
        case 1035: 
          addPassengers(fl1035, fl1035w);
          break;
          
          //add passengers to flight 1010 if flight
          //read in was 1040
        case 1040: 
          addPassengers(fl1040, fl1040w);
          break;
          
          //add passengers to flight 1010 if flight
          //read in was 1045
        case 1045: 
          addPassengers(fl1045, fl1045w);
          break;
      }
      
        //read in next boarding number
      inFile >> boardingNumber;
    }
}

//******************************************************************************

void FlightClass::addPassengers(int seatingChart[10][3], vector<int> &waitingList)
{
    // Receives - seating chart array, waiting list vector
    // Task - place passengers in the flight seating chart
    // Returns - nothing
    
    //subtract one so the row isn't the array element value, it needs
    //to be the actual row
  seatRow--;
  
    //initialize to false for empty seats available
  bool foundAvailableSeat = false;

    //if the seat column is left, check that row
  if(seatColumn == 'L')
  {
      //check the seat requested to see if empty
    if(seatingChart[seatRow][0] == -999)
    {
        //set boarding number in that seat
      seatingChart[seatRow][0] = boardingNumber;
    }
    
      //if the seat is full check to the right to see if empty
    else if(seatingChart[seatRow][1] == -999)
    {
        //set boarding number in the seat
      seatingChart[seatRow][1] = boardingNumber;
    }
    
      //if the seat is full check to the far right to see if empty
    else if(seatingChart[seatRow][2] == -999)
    {
        //set boarding number in the seat
      seatingChart[seatRow][2] = boardingNumber;
    }
    
      //if the row they requested is full, check the following seats
      //based on airline rules (start from the top of the seating chart)
    else
    {
        //check their section to see if their in coach
      if(section == 'C')
      {
          //start at 3 where coach seating begins and check for empty seats
        for(int x = 3; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
              //if emtpy seat is found place their boarding number
            if(seatingChart[x][y] == -999)
            {
                //set boarding number in seat
              seatingChart[x][y] = boardingNumber;
              
                //seat found successfully
              foundAvailableSeat = true;
              
                //exit function since seat was found
              return;
            }
          }
        }
      }
      
        //if their section was first class then search seats
      else if(section == 'F')
      {
          //go through first three rows which is first class seating
        for(int x = 0; x < 3; x++)
        {
          for(int y = 0; y < 3; y++)
          {
              //check to see if there is any emtpy seat
            if(seatingChart[x][y] == -999)
            {
                //place their boarding number in the seat
              seatingChart[x][y] = boardingNumber;
                
                //seat found successfully
              foundAvailableSeat = true;
              
                //exit function since seat was found
              return;
            }
          }
        }
      }
      
        //if a seat wasn't found then the boarding number needs
        //to be added to the waiting list for that flight
      if(foundAvailableSeat == false)
      { 
          //add boarding number to the vector
        waitingList.push_back(boardingNumber);
      }
      
    }
  }
  
    //if seat column requested was middle then check the seats
  else if(seatColumn == 'M')
  {
      //if seat requested was empty place them
    if(seatingChart[seatRow][1] == -999)
    {
        //place boarding number in seat
      seatingChart[seatRow][1] = boardingNumber;
    }
    
      //if seat was full check to the left
    else if(seatingChart[seatRow][0] == -999)
    {
        //place boarding number in seat
      seatingChart[seatRow][0] = boardingNumber;
    }
    
      //if seat was full check to the right
    else if(seatingChart[seatRow][2] == -999)
    {
        //place boarding number in seat
      seatingChart[seatRow][2] = boardingNumber;
    }
    
      //check which section they requested
    else
    {
        //if requested section was coach, check for empty seats
      if(section == 'C')
      {
          //go through rows 4 - 10 of seats (coach seating)
        for(int x = 3; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
              //if seat is empty place them
            if(seatingChart[x][y] == -999)
            {
                //place boarding number in seat
              seatingChart[x][y] = boardingNumber;
              
                //seat found successfully
              foundAvailableSeat = true;
                
                //exit function since seat was found
              return;
            }
          }
        }
      }
      
        //if requested section was first class, check for empty seats
      else if(section == 'F')
      {
          //go through first 3 rows to check for empty seats
        for(int x = 0; x < 3; x++)
        {
          for(int y = 0; y < 3; y++)
          {
              //if seat is empty place them
            if(seatingChart[x][y] == -999)
            {
                //place boarding number in seat
              seatingChart[x][y] = boardingNumber;
                
                //seat found successfully
              foundAvailableSeat = true;
              
                //exit function since seat was found
              return;
            }
          }
        }
      }
      
        //if no seat was found, boarding number needs to be added to waiting
        //list
      if(foundAvailableSeat == false)
      {
          //add boarding number to vector
        waitingList.push_back(boardingNumber);
      }
      
    }
  }
  
    //if the requested seat column was right, check seats
  else if(seatColumn == 'R')
  {
      //check their requested seat to see if empty
    if(seatingChart[seatRow][2] == -999)
    {
        //place boarding number in seat
      seatingChart[seatRow][2] = boardingNumber;
    }
    
      //if seat was full check all the way to the left
    else if(seatingChart[seatRow][0] == -999)
    {
        //place boarding number in seat
      seatingChart[seatRow][0] = boardingNumber;
    }
    
      //check middle seat to see if empty
    else if(seatingChart[seatRow][1] == -999)
    {
        //place boarding number in seat
      seatingChart[seatRow][1] = boardingNumber;
    }
    
      //check their requested section
    else
    {
        //if the requested section was coach check seats
      if(section == 'C')
      {
          //check seats in rows 4 - 10 for coach seating
        for(int x = 3; x < 10; x++)
        {
          for(int y = 0; y < 3; y++)
          {
              //if seat is empty place them
            if(seatingChart[x][y] == -999)
            {
                //place boarding number in seat
              seatingChart[x][y] = boardingNumber;
              
                //found seat successfully
              foundAvailableSeat = true;
              
                //exit function if seat was found
              return;
            }
          }
        }
      }
      
        //if the requested section was first class check seats
      else if(section == 'F')
      {
          //check seats in first 3 rows
        for(int x = 0; x < 3; x++)
        {
          for(int y = 0; y < 3; y++)
          {
              //if empty seat was found place them
            if(seatingChart[x][y] == -999)
            {
                //place boarding number in seat
              seatingChart[x][y] = boardingNumber;
              
                //seat found successfully
              foundAvailableSeat = true;
              
                //exit function since seat was found
              return;
            }
          }
        }
      }
      
        //if all seats are full their boarding number needs to be added
        //to the waiting list
      if(foundAvailableSeat == false)
      {
          //add boarding number to vector
        waitingList.push_back(boardingNumber);
      }
    }
    
  }
}

//******************************************************************************

void FlightClass::printSeatingChart(ofstream &outFile, int seatingChart[10][3])
{
    // Receives - output file, seating chart array
    // Task - print out seating chart
    // Returns - nothing
    
      //go though seating chart array
    for(int x = 0; x < 10; x++)
    {
      for(int y = 0; y < 3; y++)
      {
          //print values of seating chart (boarding numbers)
        outFile << "        " << seatingChart[x][y];
      }
        //drop to next line
      outFile << endl;
    }
      //drop to next line
    outFile << endl;
}

//******************************************************************************

void FlightClass::printWaitingList(ofstream &outputFile, vector<int> &waitingList)
{
    // Receives - output file, waiting list vector
    // Task - print the waiting list for flight
    // Returns - nothing
    
    
    //keep sum to see if there is an existing waiting list
  int sum = 0;

    //go through waiting list vector
  for(int i=0; i < waitingList.size(); i++) 
  {
      //increment sum because there is values in the waiting list
    sum++;
    
      //print the boarding number in the waiting list
    outputFile << "    " << waitingList[i] << " ";
  }
  
    //drop to next line
  outputFile << endl;
  
    //if the waiting list vector is empty, then print no waiting list
  if(sum == 0)
  {
      //print no waiting list
    outputFile << "    There is no waiting list for this flight" << endl;
  }
  
    //create proper spacing between flight output
  for(int x = 0; x < 5; x++)
  {
    outputFile << endl;
  }
}

//****************************************************************************//

void printHeader(ofstream &Outfile)
{
		// Receives - the output file
		// Task- Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Alex Knipfer ";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2016";
	Outfile << setw(20) << "Assignment #1" << endl;
	Outfile << setw(35) << "--------------------------------------";
	Outfile << setw(35) << "--------------------------------------\n\n";
	return;
}

//****************************************************************************//

void printFooter(ofstream &Outfile)
{
	Outfile << endl;
	Outfile << setw(35) << "--------------------------------" << endl;
	Outfile << setw(35) << "|    END OF PROGRAM OUTPUT     |" << endl;
	Outfile << setw(35) << "--------------------------------" << endl;

	return;
}

//*********************** END OF PROGRAM ************************************//
