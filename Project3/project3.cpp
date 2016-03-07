//******************  PROGRAM IDENTIFICATION  **********************************
//*                                                                            *
//*  PROGRAM FILE NAME: project3.cpp  ASSIGNMENT #:  3    GRADE: _____         *
//*   	                                                                       *
//*  PROGRAM AUTHOR:   ____________________________________                    *
//*                             Alex Knipfer                                   *
//*                                                                            *
//*  COURSE #:   CSC 36000 11             DUE DATE: March 07, 2015             *
//*                                                                            * 
//******************************************************************************


//********************* PROGRAM DESCRIPTION ************************************
//*    Process: This program utilizes queues to simulate customer processing   *
//*             at a supermarket. Customers will be added to the queues and    *
//*             processed based on the queue process time and their arrival    *
//*             time.                                                          *
//*                                                                            *
//*    USER DEFINED                                                            *
//*     MODULES:       : printHeader - print program header                    *
//*                      printFooter - print program footer                    *
//*                      AddCustomer - read in customer and add to queue       *
//*                      ProcessCustomer - process final customers in queue    *
//*                      PrintData - print customer in the "final queue"       *
//******************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

  //class for customer queue(s)
class LinkedQueueClass
{
  public:
    LinkedQueueClass();
    void AddCustomer(ifstream &);
    void PrintData(ofstream &);
    void ProcessCustomer();
    
  private:
      //1st queue for customers
    LinkedQueueClass *queue1;
    LinkedQueueClass *queue1next;
    int queue1time;
    
      //2nd queue for customers
    LinkedQueueClass *queue2;
    LinkedQueueClass *queue2next;
    int queue2time;
    
      //3rd queue for customers
    LinkedQueueClass *queue3;
    LinkedQueueClass *queue3next;
    int queue3time;
    
    int processTime;
    string name;
    int count;

      //vector to store and print initial list
    vector<string> initialQueue;
      //vector to store final customers to print
    vector<string> finalQueue;
};

  //prototypes for header and footer
void printHeader(ofstream &);
void printFooter(ofstream &);

//******************************************************************************

int main()
{
  LinkedQueueClass customer;
  int arrivalTime;
  
  ifstream inputFile("queue_in.txt");
  ofstream outputFile("output.txt");
  
    //print program header
  printHeader(outputFile);
  
    //read in customer arrival time
  inputFile >> arrivalTime;
    
    //continue reading data until sentinel (-99)
  while(arrivalTime != -99)
  {
      //add customer to initial queue
    customer.AddCustomer(inputFile);
    inputFile >> arrivalTime;
  }
  
    //process customers
  customer.ProcessCustomer();
  
    //print labels for customer listing
  outputFile << "The order of customer arrival is:";
  outputFile << "           ";
  outputFile << "The order of customer departure is:" << endl;
  outputFile << "---------------------------------";
  outputFile << "          ";
  outputFile << "---------------------------------" << endl;
  
    //print the customer data
  customer.PrintData(outputFile);
  
    //print program footer
  printFooter(outputFile);
  
  return 0;
}

//******************************************************************************

LinkedQueueClass::LinkedQueueClass()
{
    //Receives - Nothing
    //Task - Constructor - initializes queue pointers and total times
    //Returns - nothing
    
    //initialize queue 1
  queue1 = NULL;
  queue1next = NULL;
  queue1time = 0;
  
    //initialize queue 2
  queue2 = NULL;
  queue2next = NULL;
  queue2time = 0;
  
    //initialize queue 3
  queue3 = NULL;
  queue3next = NULL;
  queue3time = 0;
  
    //set count to 0 for customer totals
  count = 0;
}

//******************************************************************************

void LinkedQueueClass::AddCustomer(ifstream &inputFile)
{
    //Receives - input file
    //Task - add customer to proper queue based on read in times
    //Returns - nothing
   
    //points to current customer  
  LinkedQueueClass *current;
  
    //points to next customer
  LinkedQueueClass *next;

    //current name read in from file
  string currentName;
  
    //process time read in from file
  int currentProcessTime;
  
    //allocate space for current customer
  current = new LinkedQueueClass;
  
    //read in the customer name
  inputFile >> ws;
  getline(inputFile, currentName);
  
    //read in customer process time
  inputFile >> ws;
  inputFile >> currentProcessTime;
  
    //point current customer to read in name and process time
  current -> name = currentName;
  current -> processTime = currentProcessTime;
  
    //increase customer count in list
  count++;
  
    //add customer to initial vector
  initialQueue.push_back(currentName);
  
    //check to see if the first queue is empty
  if(queue1 == NULL)
  {
      //point queue 1 to current customer
    queue1 = current;
    
      //point current to read in name
    current -> name = currentName;
    
      //decrease process time by 1 since at head of queue
    current -> processTime--;
    
      //increase total queue process time
    queue1time += current -> processTime;
    
      //add customer to final queue vector
    finalQueue.push_back(currentName);
  }
  
    //check to see if the second queue is empty
  else if(queue2 == NULL)
  {
      //point queue 2 to current customer
    queue2 = current;
    
      //point current to read in name
    current -> name = currentName;
    
      //decrease process time by 1 since at head of queue
    current -> processTime--;
    
      //increase total queue process time
    queue2time += current -> processTime;
    
      //add customer to final queue vector
    finalQueue.push_back(currentName);
  }
  
    //check to see if the third queue is empty
  else if(queue3 == NULL)
  {
      //point queue 3 to current customer
    queue3 = current;
      
      //point current to read in name
    current -> name = currentName;
    
      //decrease process time by 1 since at head of queue
    current -> processTime--;
    
      //increase total queue process time
    queue3time += current -> processTime;
    
      //add customer to final queue vector
    finalQueue.push_back(currentName);
  }
  
    //check to see if queue 1 has the least amount of process time
  else if(queue1time < queue2time && queue1time < queue3time)
  {
      //get queue 1 location
    next = queue1;
    
          //loop through queue 1
        while(next->queue1next != NULL)
        {
            //go to next customer in queue
          next = next -> queue1next;
            
            //make sure process time isn't empty
          if(next -> processTime != 0)
          {
              //reduce process time by 1  
            while(next -> processTime != 0)
                next -> processTime--;
            
              //add customer once finished being processed
            if(next -> processTime == 0)
            {
                finalQueue.push_back(next->name);
            }
          }
        }
        
          //set the current queue customer to the next in the list
        next-> queue1next = current;
        
          //add to queue 1 total process time
        queue1time += current->processTime;
  }
  
    //check to see if queue 2 has the least amount of process time
  else if(queue2time < queue1time && queue2time < queue3time)
  {
      //get queue 2 location
    next = queue2;
    
      //loop through queue 2
    while(next->queue2next != NULL)
    {
        //go to next customer in queue
      next = next -> queue2next;
      
        //make sure process time isn't empty
      if(next -> processTime != 0)
      {
          //reduce process time by 1
        while(next -> processTime != 0)
            next -> processTime--;
        
          //add customer once finished being processed
        if(next -> processTime == 0)
        {
            finalQueue.push_back(next->name);
        }
      }
    }
    
      //set the current customer in queue to the next in list
    next-> queue2next = current;
    
      //add to queue 2 total process time
    queue2time += current->processTime;
  }
  
    //check to see if queue 3 has the least amount of process time
  else if(queue3time < queue2time && queue3time < queue1time)
  {
      //get queue 3 location
    next = queue3;
    
      //loop through queue 3
    while(next->queue3next != NULL)
    {
        //go to next customer in queue
      next = next -> queue3next;
      
        //make sure process time isn't empty
      if(next -> processTime != 0)
      {
          //reduce process time by 1
        while(next -> processTime != 0)
            next -> processTime--;
        
          //add customer once finished being processed
        if(next -> processTime == 0)
        {
            finalQueue.push_back(next->name);
        }
      }
    }
    
      //set the current customer in queue to next in list
    next-> queue3next = current;
    
      //add to queue 3 total process time
    queue3time += current->processTime;
  }
  
    //check to see if queue times are equal (queue 1)
  else if(queue1time == queue2time && queue1time == queue3time)
  {
      //get queue 1 location
    next = queue1;
    
      //loop through queue 1
    while(next->queue1next != NULL)
    {
        //go to next customer in queue
      next = next -> queue1next;
      
        //make sure process time isn't empty
      if(next -> processTime != 0)
      {
          //reduce process time by 1
        while(next -> processTime != 0)
            next -> processTime--;
        
          //add customer once finished begin processed
        if(next -> processTime == 0)
        {
            finalQueue.push_back(next->name);
        }
      }
    }
    
      //set the current customer in queue to next in list
    next-> queue1next = current;
    
      //add to queue 1 total time
    queue1time += current->processTime;
  }
  
    //check to see if queue times are equal (queue 2)
  else if(queue2time == queue1time && queue2time == queue3time)
  {
      //get queue 2 location
    next = queue2;
    
      //loop through queue 2
    while(next->queue2next != NULL)
    {
        //loop through queue 2
      next = next -> queue2next;
      
        //make sure process time isn't empty
      if(next -> processTime != 0)
      {
          //reduce process time by 1
        while(next -> processTime != 0)
            next -> processTime--;
        
          //add customer once finished begin processed
        if(next -> processTime == 0)
        {
            finalQueue.push_back(next->name);
        }
      }
    }
    
      //set the current customer in queue to next in list
    next-> queue2next = current;
      
      //add to queue 2 total time
    queue2time += current->processTime;
  }
  
    //check final queue times (queue 3)
  else
  {
      //get queue 3 location
    next = queue3;
    
      //loop through queue 3
    while(next->queue3next != NULL)
    {
        //loop through queue 3
      next = next -> queue3next;
      
        //make sure process time isn't empty
      if(next -> processTime != 0)
      {
          //reduce process time by 1
        while(next -> processTime != 0)
            next -> processTime--;
        
          //add customer once finished being processed
        if(next -> processTime == 0)
        {
            finalQueue.push_back(next->name);
        }
      }
    }
    
      //set the current customer in queue to next in list
    next-> queue3next = current;
    
      //add to queue 3 total time
    queue3time += current->processTime;
  }
}

//******************************************************************************

void LinkedQueueClass::ProcessCustomer()
{
    //Receives - nothing
    //Task - process final customers to add to final queue
    //Returns - nothing
  LinkedQueueClass *first, *second, *last;
  
    //set queues to first, second, and third
  first = queue1;
  second = queue2;
  last = queue3;
  
    //go through 1st queue to check for empty
  while(first -> queue1next != NULL)
  {
    
    first = first -> queue1next;
  }
  
    //go through 2nd queue to check for empty
  while(second -> queue2next != NULL)
  {
    
    second = second -> queue2next;
  }
  
    //go through 3rd queue to check for empty
  while(last -> queue3next != NULL)
  {
    
    last = last -> queue3next;
  }
  
    //add customer to final queue vector
  finalQueue.push_back(first -> name);
  finalQueue.push_back(second -> name);
  finalQueue.push_back(last -> name);
}

//******************************************************************************

void LinkedQueueClass::PrintData(ofstream &outputFile)
{
    //Receives - output file
    //Task - print out customers
    //Returns - nothing
    
    //go through final queue vector to print customer names
  for(int x = 0; x < finalQueue.size(); x++)
  {
    outputFile << initialQueue[x] << "               |";
    outputFile << setw(30) << finalQueue[x] << endl;
  }
}

//******************************************************************************

void printHeader(ofstream &Outfile)
{
		// Receives - the output file
		// Task- Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Alex Knipfer ";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2016";
	Outfile << setw(20) << "Assignment #3" << endl;
	Outfile << setw(35) << "--------------------------------------";
	Outfile << setw(35) << "--------------------------------------\n\n";
	return;
}

//******************************************************************************

void printFooter(ofstream &Outfile)
{
    //Receives - the output file
    //Task - print output footer
    //Returns- nothing
	Outfile << endl;
	Outfile << setw(35) << "--------------------------------" << endl;
	Outfile << setw(35) << "|    END OF PROGRAM OUTPUT     |" << endl;
	Outfile << setw(35) << "--------------------------------" << endl;

	return;
}

//*********************** END OF PROGRAM ************************************//

