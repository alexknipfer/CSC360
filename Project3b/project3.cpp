#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

class LinkedQueueClass
{
  public:
    LinkedQueueClass();
    void AddCustomer(ifstream &);
    void PrintData(ofstream &);
    void ProcessCustomer();
    
  private:
    LinkedQueueClass *queue1;
    LinkedQueueClass *queue1next;
    int queue1time;
    
    LinkedQueueClass *queue2;
    LinkedQueueClass *queue2next;
    int queue2time;
    
    LinkedQueueClass *queue3;
    LinkedQueueClass *queue3next;
    int queue3time;
    
    int processTime;
    string name;
    int count;
    string tempName;
    
    vector<string> initialQueue;
    vector<string> finalQueue;
};

//******************************************************************************

int main()
{
  LinkedQueueClass customer;
  int arrivalTime;
  
  ifstream inputFile("data.txt");
  ofstream outputFile("output.txt");
  
  inputFile >> arrivalTime;
  
  while(arrivalTime != -99)
  {
    customer.AddCustomer(inputFile);
    inputFile >> arrivalTime;
  }
  
  customer.ProcessCustomer();
  customer.PrintData(outputFile);
  return 0;
}

//******************************************************************************

LinkedQueueClass::LinkedQueueClass()
{
  queue1 = NULL;
  queue1next = NULL;
  queue1time = 0;
  
  queue2 = NULL;
  queue2next = NULL;
  queue2time = 0;
  
  queue3 = NULL;
  queue3next = NULL;
  queue3time = 0;
  
  count = 0;
}

//******************************************************************************

void LinkedQueueClass::AddCustomer(ifstream &inputFile)
{
  LinkedQueueClass *current;
  LinkedQueueClass *next;
  LinkedQueueClass *temp1;
  LinkedQueueClass *temp2;

  string currentName;
  int currentProcessTime;
  
  current = new LinkedQueueClass;
  
  inputFile >> ws;
  getline(inputFile, currentName);
  inputFile >> ws;
  inputFile >> currentProcessTime;
  
  current -> name = currentName;
  current -> processTime = currentProcessTime;
  count++;
  
  initialQueue.push_back(currentName);
  
  if(queue1 == NULL)
  {
    queue1 = current;
    current -> name = currentName;
    current -> processTime--;
    queue1time += current -> processTime;
    finalQueue.push_back(currentName);
  }
  
  else if(queue2 == NULL)
  {
    queue2 = current;
    current -> name = currentName;
    current -> processTime--;
    queue2time += current -> processTime;
    finalQueue.push_back(currentName);
  }
  
  else if(queue3 == NULL)
  {
    queue3 = current;
    current -> name = currentName;
    current -> processTime--;
    queue3time += current -> processTime;
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

void LinkedQueueClass::PrintData(ofstream &outputFile)
{
  for(int x = 0; x < finalQueue.size(); x++)
  {
    cout << finalQueue[x] << endl;
  }
  cout << endl;
}

