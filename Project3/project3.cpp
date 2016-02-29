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
    vector<int> queue1times;
    vector<string> queue1names;
    vector<int> queue2times;
    vector<string> queue2names;
    vector<int> queue3times;
    vector<string> queue3names;
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
  bool empty = false;
  int processCount = count;
  int firstTimes;
  int queue1count = 0;
  int queue2count = 0;
  int queue3count = 0;
  int finalQueueData = 0;
  current = front;
  firstTimes = totalTime;
  
  
  queue1names.push_back(current -> name);
  queue1times.push_back(current -> processingTime);
  firstTimes -= current -> processingTime;
  
  current = current -> next;
  
  queue2names.push_back(current -> name);
  queue2times.push_back(current -> processingTime);
  firstTimes -= current -> processingTime;
  
  current = current -> next;
  
  queue3names.push_back(current -> name);
  queue3times.push_back(current -> processingTime);
  firstTimes -= current -> processingTime;
  
  current = current -> next;
  
  while(current != NULL)
  {
    for(int x = 0; x < queue1times.size(); x++)
    {
      queue1count += queue1times[x];
    }
    
    for(int y = 0; y < queue2times.size(); y++)
    {
      queue2count += queue2times[y];
    }
    
    for(int z = 0; z < queue3times.size(); z++)
    {
      queue3count += queue3times[z];
    }
    
    if(queue1count < queue2count && queue1count < queue3count)
    {
      queue1names.push_back(current -> name);
      queue1times.push_back(current -> processingTime);
    }
    
    else if(queue2count < queue1count && queue2count < queue3count)
    {
      queue2names.push_back(current -> name);
      queue2times.push_back(current -> processingTime);
    }
    
    else if(queue3count < queue1count && queue3count < queue2count)
    {
      queue3names.push_back(current -> name);
      queue3times.push_back(current -> processingTime);
    }
    current = current -> next;
  }
  
  /*while(empty != true)
  {
    for(int x = 0; x < queue1times.size(); x++)
    {
      queue1times[x] -= 1;
      if(queue1times[x] == 0)
      {
        finalQueue[finalQueueData] = queue1names[x];
        finalQueueData++;
        queue1names[x].erase();
        queue1times[x].erase();
      }
    }
    if(queue1names.size() == 0)
    {
      empty = false;
    }
  }*/
  
  for(int x = 0; x < queue1times.size(); x++)
  {
    cout << queue1names[x] << endl;
    finalQueue.push_back(queue1names[x]);
  }
  
  cout << endl;
  
  for(int x = 0; x < queue2times.size(); x++)
  {
    cout << queue2names[x] << endl;
    finalQueue.push_back(queue2names[x]);
  }
  
  cout << endl;
  
  for(int x = 0; x < queue3times.size(); x++)
  {
    cout << queue3names[x] << endl;
    finalQueue.push_back(queue3names[x]);
  }

    
}

/*void LinkedQueueClass::ProcessCustomer()
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
    } 
    current = front;
  }
    
}*/

