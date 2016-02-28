#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

struct CustomerData
{
  int arrivalTime;
  string name;
  int processingTime;
  CustomerData *next;
};

class LinkedQueueClass
{
  public:
    LinkedQueueClass();
    ~LinkedQueueClass();
    bool IsEmpty(){return ((front==NULL) ? true : false);}
    bool IsFull();
    CustomerData * First();
    CustomerData * Last();
    bool Add(CustomerData);
    void PrintData(ofstream &);
    void ProcessCustomer();
    
  private:
    int count;
    int totalTime;
    vector<string> finalQueue;
    CustomerData *front;
    CustomerData *rear;
    CustomerData *current;
};

//******************************************************************************

int main()
{ 
  CustomerData customer;
  LinkedQueueClass Queue;
  
  ifstream inputFile("data.txt");
  ofstream outputFile("output.txt");
  
  inputFile >> customer.arrivalTime;
  
  while(customer.arrivalTime != -99)
  {
    inputFile >> ws;
    getline(inputFile, customer.name);
    inputFile >> ws;
    inputFile >> customer.processingTime;
    
    Queue.Add(customer);
    
    inputFile >> customer.arrivalTime;
  }
  
  Queue.ProcessCustomer();
  
  outputFile << "The order of customer arrival is:";
  outputFile << "           ";
  outputFile << "The order of customer departure is:" << endl;
  outputFile << "---------------------------------";
  outputFile << "          ";
  outputFile << "---------------------------------" << endl;
  
  Queue.PrintData(outputFile);
  
  return 0;
}

//******************************************************************************

LinkedQueueClass::LinkedQueueClass()
{
  front = NULL;
  rear = NULL;
  count = 0;
  totalTime = 0;
}

//******************************************************************************

LinkedQueueClass::~LinkedQueueClass()
{
  CustomerData *next;
  while(front != NULL)
  {
    next = front -> next;
    delete front;
    front = next;
  }
}

//******************************************************************************

bool LinkedQueueClass::IsFull()
{
  CustomerData *p;
  p = new(CustomerData);
  if(p == NULL)
  {
    delete p;
    cout << "Out of memory. " << endl;
    return true;
  }
  return false;
}

//******************************************************************************

CustomerData * LinkedQueueClass::First()
{
  if(IsEmpty() )
  {
    cout << "Queue is Empty. " << endl;
    return NULL;
  }
  return front;
}

//******************************************************************************

CustomerData * LinkedQueueClass::Last()
{
  if(IsEmpty())
  {
    cout << "Queue is Empty. " << endl;
    return NULL;
  }
  return rear;
}

//******************************************************************************

bool LinkedQueueClass::Add(CustomerData NewNode)
{
  CustomerData *NewPtr;
  NewPtr = new (CustomerData);
  
  if(IsFull())
  {
    return false;
  }
  
  NewPtr -> arrivalTime = NewNode.arrivalTime;
  NewPtr -> name = NewNode.name;
  NewPtr -> processingTime = NewNode.processingTime;
  totalTime += NewNode.processingTime;
  NewPtr -> next = NULL;
  
  if(front == NULL)
  {
    front = NewPtr;
  }
  
  else
  {
    rear -> next = NewPtr;
  }
  
  rear = NewPtr;
  count++;
  return true;
}

//******************************************************************************


void LinkedQueueClass::PrintData(ofstream &outputFile)
{
  cout << totalTime;
  current = front;
  int data = 0;
    while(current != NULL)
    {
      outputFile << current -> name << "               |";
      outputFile << setw(30) << finalQueue[data] << endl;
      current = current -> next;
      data++;
    }
}

//******************************************************************************

void LinkedQueueClass::ProcessCustomer()
{
  bool processed = false;
  int processCount = count;
  current = front;
  
  for(int x = 0; x < totalTime; x++)
  {
   while(current != NULL)
    {
      current -> processingTime -= 1;
      if(current -> processingTime == 0)
      {
        finalQueue.push_back(current -> name);
        processCount--;
      }
      
      current = current -> next;
      //cout << processCount << endl;
    } 
    current = front;
  }
    
}

