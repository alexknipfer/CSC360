#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct NodeType
{
  string firstName;
  string lastName;
  string address;
  string city;
  string state;
  string zipCode;
  
  NodeType *NodePtr;
};

class LinkedListClass
{
  public:
  LinkedListClass();
    void InsertNode(NodeType);

  private:
    NodeType *StartPtr;
};

//******************************************************************************

int main()
{
  NodeType Temp, Node;
  
    //instantiate object for customer
  LinkedListClass LinkedList;
  
  ifstream inputFile("testdata.txt");
  ofstream outputFile("output.txt");
  
  
    //add, delete, change, or print records
  char transactionType;
  
    //done reading data from file once Q is hit
  char done = 'Q';
  
    //read in first character to figure out what to do with data
  inputFile >> transactionType;
  
    //continue reading in data until a "Q" is read in
  while(transactionType != done)
  {
      //check to see what to do with customer data
    switch(transactionType)
    {
        //add customer if transaction type is A
      case 'A':   inputFile >> ws;
                  getline(inputFile, Node.firstName);
                  inputFile >> ws;
                  getline(inputFile, Node.lastName);
                  inputFile >> ws;
                  getline(inputFile, Node.address);
                  inputFile >> ws;
                  getline(inputFile, Node.city);
                  inputFile >> ws;
                  getline(inputFile, Node.state);
                  inputFile >> ws;
                  getline(inputFile, Node.zipCode);
                  LinkedList.InsertNode(Node);
      break;
    }
    
      //read in next transaction type
    inputFile >> transactionType;
  }
}

//******************************************************************************

LinkedListClass::LinkedListClass()
{
  StartPtr = NULL;
}

void LinkedListClass::InsertNode(NodeType Node)
{
  NodeType *newPtr, *PreviousPtr, *CurrentPtr;
  
  newPtr = new(NodeType);
  
  if(newPtr == NULL)
  {
    cout << "No memory available" << endl;
  }
  
  else
  {
    newPtr -> firstName = Node.firstName;
    newPtr -> lastName = Node.lastName;
    newPtr -> address = Node.address;
    newPtr -> city = Node.city;
    newPtr -> state = Node.state;
    newPtr -> zipCode = Node.zipCode;
  }
  
  while((CurrentPtr != NULL) && (newPtr->firstName > CurrentPtr->firstName) && (newPtr->lastName > CurrentPtr->lastName))
  {
    PreviousPtr -> firstName = Node.firstName;
    PreviousPtr -> lastName = Node.lastName;
    PreviousPtr -> address = Node.address;
    PreviousPtr -> city = Node.city;
    PreviousPtr -> state = Node.state;
    PreviousPtr -> zipCode = Node.zipCode;
  }
  
  if(CurrentPtr != NULL)
  {
    if(PreviousPtr == NULL)
    {
      //some stuff
    }
  }
  
}
