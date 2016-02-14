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
    void InsertCustomer(NodeType);
    void DeleteCustomer(ifstream &);
    void InsertAsFirstElement(NodeType);
    void PrintMailingList(ofstream &);
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
                  LinkedList.InsertCustomer(Node);
                  break;
      case 'D':   LinkedList.DeleteCustomer(inputFile);
                  break;
      case 'P':   LinkedList.PrintMailingList(outputFile);
                  break;
      break;
    }
    
      //read in next transaction type
    inputFile >> transactionType;
  }
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

void LinkedListClass::InsertCustomer(NodeType Node)
{
  current = head;
  string tempFirst;
  string tempLast;
  string tempAddress;
  string tempCity;
  string tempState;
  string tempZip;
  
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
                
                tempLast = current->lastName;
                current->lastName = temp->lastName;
                temp->lastName = tempLast;
                
                tempAddress = current->address;
                current->address = temp->address;
                temp->address = tempAddress;
                
                tempCity = current->city;
                current->city = temp->city;
                temp->city = tempCity;
                
                tempState = current->state;
                current->state = temp->state;
                temp->state = tempState;
                
                tempZip = current->zipCode;
                current->zipCode = temp->zipCode;
                temp->zipCode = tempZip;
            }
            current = current -> next;
      }
      
            
      temp -> next = NULL;
      last -> next = temp;
      last = temp;
   }
}

//******************************************************************************
void LinkedListClass::DeleteCustomer(ifstream &inputFile)
{
  if(isEmpty())
  {
    cout << "The database is empty" << endl;
  }
  
  else
  {
    string first;
    string last;
    
    NodeType *temp = head;
    
    inputFile >> ws;
    getline(inputFile, first);
    inputFile >> ws;
    getline(inputFile, last);

    
    while(temp != NULL)
    {
      if(temp -> firstName == first && temp -> lastName == last)
      {
        temp -> firstName = "DELETED";
      }
      temp = temp -> next;
    }
    
  }
}
//******************************************************************************

void LinkedListClass::PrintMailingList(ofstream &outputFile)
{
  current = head;

  if(isEmpty())
  {
    cout << "The database is empty!" << endl;
  }
  
  else
  {
    //Print a heading for the mailing list table.
    outputFile << setw(50) << "MAILING LIST" << endl;
    outputFile << "Last Name" << "       ";
    outputFile << "First Name" << "       ";
    outputFile << "Address" << "                ";
    outputFile << "City" << "        ";
    outputFile << "State" << "     ";
    outputFile << "Zip Code" << endl;
    outputFile << "==============================================";
    outputFile << "============================================" << endl;
    
    
    while(current != NULL)
    {
      if(current -> firstName != "DELETED")
      {
        outputFile << left << setw(16) << current -> lastName;
        outputFile << left << setw(17) << current -> firstName;
        outputFile << left << setw(23) << current -> address;
        outputFile << left << setw(13) <<  current -> city;
        outputFile << left << setw(11) << current -> state;
        outputFile << current -> zipCode;
        outputFile << endl;
      }
      current = current -> next;
    }
  }
}


