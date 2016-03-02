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
  
  else if(queue1time < queue2time && queue1time < queue3time)
  {
    next = queue1;
    
        while(next->queue1next != NULL)
        {
            next = next -> queue1next;
            
            if(next -> processTime != 0)
            {
                while(next -> processTime != 0)
                    next -> processTime--;
                
                if(next -> processTime == 0)
                {
                    finalQueue.push_back(next->name);
                }
            }
        }
        
        next-> queue1next = current;
        
        queue1time += current->processTime;
  }
  
  else if(queue2time < queue1time && queue2time < queue3time)
  {
    next = queue2;
    
        while(next->queue2next != NULL)
        {
            next = next -> queue2next;
            
            if(next -> processTime != 0)
            {
                while(next -> processTime != 0)
                    next -> processTime--;
                
                if(next -> processTime == 0)
                {
                    finalQueue.push_back(next->name);
                }
            }
        }
        
        next-> queue2next = current;
        
        queue2time += current->processTime;
  }
  
  else if(queue3time < queue2time && queue3time < queue1time)
  {
    next = queue3;
    
        while(next->queue3next != NULL)
        {
            next = next -> queue3next;
            
            if(next -> processTime != 0)
            {
                while(next -> processTime != 0)
                    next -> processTime--;
                
                if(next -> processTime == 0)
                {
                    finalQueue.push_back(next->name);
                }
            }
        }
        
        next-> queue3next = current;
        
        queue3time += current->processTime;
  }
  
  else if(queue1time == queue2time && queue1time == queue3time)
  {
    next = queue1;
    
        while(next->queue1next != NULL)
        {
            next = next -> queue1next;
            
            if(next -> processTime != 0)
            {
                while(next -> processTime != 0)
                    next -> processTime--;
                
                if(next -> processTime == 0)
                {
                    finalQueue.push_back(next->name);
                }
            }
        }
        
        next-> queue1next = current;
        
        queue1time += current->processTime;
  }
  
  else if(queue2time == queue1time && queue2time == queue3time)
  {
    next = queue2;
    
        while(next->queue2next != NULL)
        {
            next = next -> queue2next;
            
            if(next -> processTime != 0)
            {
                while(next -> processTime != 0)
                    next -> processTime--;
                
                if(next -> processTime == 0)
                {
                    finalQueue.push_back(next->name);
                }
            }
        }
        
        next-> queue2next = current;
        
        queue2time += current->processTime;
  }
  
  else
  {
    next = queue3;
    
        while(next->queue3next != NULL)
        {
            next = next -> queue3next;
            
            if(next -> processTime != 0)
            {
                while(next -> processTime != 0)
                    next -> processTime--;
                
                if(next -> processTime == 0)
                {
                    finalQueue.push_back(next->name);
                }
            }
        }
        
        next-> queue3next = current;
        
        queue3time += current->processTime;
  }
}

//******************************************************************************

void LinkedQueueClass::ProcessCustomer()
{
  LinkedQueueClass *first, *second, *last;
  
  first = queue1;
  second = queue2;
  last = queue3;
  
  while(first -> queue1next != NULL)
  {
    
    first = first -> queue1next;
  }
  
  while(second -> queue2next != NULL)
  {
    
    second = second -> queue2next;
  }
  
  while(last -> queue3next != NULL)
  {
    
    last = last -> queue3next;
  }
  
  finalQueue.push_back(first -> name);
  finalQueue.push_back(second -> name);
  finalQueue.push_back(last -> name);
}

//******************************************************************************

void LinkedQueueClass::PrintData(ofstream &outputFile)
{
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

