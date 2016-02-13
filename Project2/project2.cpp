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
  
  NodeType *next;
};

class LinkedListClass
{
  public:
  LinkedListClass();
    void InsertNode(NodeType);
    void InsertAsFirstElement(NodeType);
    void PrintList();
    bool isEmpty();

  private:
    NodeType *head;
    NodeType *last;
    NodeType *current;
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
  LinkedList.PrintList();
}

//******************************************************************************

LinkedListClass::LinkedListClass()
{
  head = NULL;
  last = NULL;
}

//******************************************************************************

bool LinkedListClass::isEmpty()
{
  if(head == NULL)
  {
    return true;
  }
  
  else
  {
    return false;
  }
}

//******************************************************************************

void LinkedListClass::InsertAsFirstElement(NodeType Node)
{
  NodeType *temp = new(NodeType);
  temp -> firstName = Node.firstName;
  temp -> lastName = Node.lastName;
  temp -> address = Node.address;
  temp -> city = Node.city;
  temp -> state = Node.state;
  temp -> zipCode = Node.zipCode;
  temp -> next = NULL;
  head = temp;
  last = temp;
}

//******************************************************************************

void LinkedListClass::InsertNode(NodeType Node)
{
  current = head;
  string tempFirst;
  
   if(isEmpty())
   {
     InsertAsFirstElement(Node);
   }
   
   else
   {
      NodeType *temp = new(NodeType);
      temp -> firstName = Node.firstName;
      temp -> lastName = Node.lastName;
      temp -> address = Node.address;
      temp -> city = Node.city;
      temp -> state = Node.state;
      temp -> zipCode = Node.zipCode;
      
      while(current != NULL)
      {
        if(temp->firstName < current->firstName)
            {
                    //Swap first names.
                tempFirst = current->firstName;
                current->firstName = temp->firstName;
                temp->firstName = tempFirst;
            }
            current = current -> next;
      }
      
            
      temp -> next = NULL;
      last -> next = temp;
      last = temp;
   }
}

void LinkedListClass::PrintList()
{
  current = head;
  

  if(isEmpty())
  {
    cout << "EMPTY" << endl;
  }
  
  else
  {
    while(current != NULL)
    {
      cout << current -> firstName << endl;

      current = current -> next;
    }
  }
}


