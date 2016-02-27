#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

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

  private:
    int count;
    CustomerData *front;
    CustomerData *rear;
};

//******************************************************************************

int main()
{ 
    return 0;
}

//******************************************************************************

LinkedQueueClass::LinkedQueueClass()
{
  front = NULL;
  rear = NULL;
  count = 0;
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

bool LinkedQueueClass()
{
  
}