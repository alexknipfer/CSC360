//******************  PROGRAM IDENTIFICATION  **********************************
//*                                                                            *
//*  PROGRAM FILE NAME: project2.cpp  ASSIGNMENT #:  2    GRADE: _____         *
//*   	                                                                       *
//*  PROGRAM AUTHOR:   ____________________________________                    *
//*                             Alex Knipfer                                   *
//*                                                                            *
//*  COURSE #:   CSC 36000 11             DUE DATE: February 22, 2015          *
//*                                                                            * 
//******************************************************************************


//********************* PROGRAM DESCRIPTION ************************************
//*    Process: This program keeps track of a mailing list for customers. The  *
//*    program outputs all customer info in alphbetical order to a output file.*
//*    The mailing list is kept current by adding and deleting customers from  *
//*    the list.                                                               *
//*                                                                            *
//*    USER DEFINED                                                            *
//*     MODULES:       : printHeader - print program header                    *
//*                      printFooter - print program footer                    *
//*                      InsertCustomer - insert customer into list            *
//*                      DeleteCustomer - remove customer from list            *
//*                      ChangeCustomer - change customer data                 *
//*                      InsertAsFirstElement - insert first customer          *
//*                      PrintMailingList - print all customer in mailing list *
//*                      isEmpty - check to see if mailing list is empty       *
//******************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

  //structure to hold customer data
struct NodeType
{
  string firstName;
  string lastName;
  string address;
  string city;
  string state;
  string zipCode;
  
    //create node of this structure
  NodeType *next;
};

  //class for implementing linked list
class LinkedListClass
{
  public:
  LinkedListClass();
    void InsertCustomer(NodeType, ofstream &);
    void DeleteCustomer(ifstream &, ofstream &);
    void ChangeCustomer(ifstream &, ofstream &);
    void InsertAsFirstElement(NodeType);
    void PrintMailingList(ofstream &);
    bool isEmpty();

  private:
    NodeType *head;     //keeps track of first node in list
    NodeType *last;     //keeps track of last node in list
    NodeType *current;  //keeps track of current node in list
};

void printHeader(ofstream &);
void printFooter(ofstream &);

//******************************************************************************

int main()
{
  NodeType Temp, Node;
  
    //instantiate object for customer
  LinkedListClass LinkedList;
  
  ifstream inputFile("data.txt");
  ofstream outputFile("output.txt");
  
  
    //add, delete, change, or print records
  char transactionType;
  
    //done reading data from file once Q is hit
  char done = 'Q';
  
    //print program header
  printHeader(outputFile);
  
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
                  LinkedList.InsertCustomer(Node, outputFile);
                  break;
                  
        //delete customer if transaction type is a D            
      case 'D':   LinkedList.DeleteCustomer(inputFile, outputFile);
                  break;
      
        //print mailing list if transaction type is a P            
      case 'P':     
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
                  LinkedList.PrintMailingList(outputFile);
                  break;
                  
        //change customer if trasaction type is a C          
      case 'C':   LinkedList.ChangeCustomer(inputFile, outputFile);
                  break;
    }
    
      //read in next transaction type
    inputFile >> transactionType;
  }
  
    //print program footer
  printFooter(outputFile);
}

//******************************************************************************

LinkedListClass::LinkedListClass()
{
    //Receives - nothing
    //Task - Constructor - initializes head and last pointers to NULL
    //Returns - nothing
    
  head = NULL;
  last = NULL;
}

//******************************************************************************

bool LinkedListClass::isEmpty()
{
    //Receives - nothing
    //Task - check to see if the list is empty (return true if so)
    //Returns - true or false to determine if list is empty
    
    //if the head contains nothing then the list is empty
  if(head == NULL)
  {
    return true;
  }
  
    //return false because the list contains nodes
  else
  {
    return false;
  }
}

//******************************************************************************

void LinkedListClass::InsertAsFirstElement(NodeType Node)
{
    //Receives - node
    //Task - insert node if it's the first node
    //Returns - nothing
    
    //create new temp node of NodeType
  NodeType *temp = new(NodeType);
  
    //point temp to customer data in the current node read in
  temp -> firstName = Node.firstName;
  temp -> lastName = Node.lastName;
  temp -> address = Node.address;
  temp -> city = Node.city;
  temp -> state = Node.state;
  temp -> zipCode = Node.zipCode;
  
    //point to next node and set to null
  temp -> next = NULL;
  
    //reset head and last
  head = temp;
  last = temp;
}

//******************************************************************************

void LinkedListClass::InsertCustomer(NodeType Node, ofstream &outputFile)
{
    //Receives - node, output file
    //Task - insert a customer (node) into the list
    //Returns- nothing
  
    //point current to first node in list
  current = head;
  
    //create temporary variables for swapping customer info to keep
    //alphbetized
  string tempFirst;
  string tempLast;
  string tempAddress;
  string tempCity;
  string tempState;
  string tempZip;
  
    //make sure the list contains nodes
   if(isEmpty())
   {
      //if it's the first node, go insert it
     InsertAsFirstElement(Node);
   }
   
    //if it's not the first node, add to the list
   else
   {
        //create new temporary node
      NodeType *temp = new(NodeType);
      
        //point temp to customer data read in
      temp -> firstName = Node.firstName;
      temp -> lastName = Node.lastName;
      temp -> address = Node.address;
      temp -> city = Node.city;
      temp -> state = Node.state;
      temp -> zipCode = Node.zipCode;
      
        //go through list as long as it contains nodes
        //looping through them to make sure the customer trying to be added
        //isn't already in the list
      while (current != NULL)
      {
          //check to see if customer exists in the list
        if((temp -> firstName == current -> firstName) && (temp -> lastName == current -> lastName))
            {
                //print out error because customer already exists
              outputFile << temp -> firstName << " " << temp -> lastName << " ";
              outputFile << "is already in the list. Attempt to add duplicate record failed!";
              outputFile << endl;
              outputFile << endl;
              
                //set first name to deleted to show their out of the list
              temp -> firstName = "DELETED";
            }
            
          //point current to next node
        current = current -> next;
      }
      
      //reset current to point to head so we can
      //loop through again to sort the names
    current = head;
  
      //loop through the list and sort names by last name
     while(current != NULL)
      {
            //compare first an last name to sort by last name
          if(temp->lastName < current->lastName)
            {
                    //Swap first names.
                tempFirst = current->firstName;
                current->firstName = temp->firstName;
                temp->firstName = tempFirst;
                
                  //swap last names
                tempLast = current->lastName;
                current->lastName = temp->lastName;
                temp->lastName = tempLast;
                
                  //swap address
                tempAddress = current->address;
                current->address = temp->address;
                temp->address = tempAddress;
                
                  //swap city
                tempCity = current->city;
                current->city = temp->city;
                temp->city = tempCity;
                
                  //swap state
                tempState = current->state;
                current->state = temp->state;
                temp->state = tempState;
                
                  //swap zip code
                tempZip = current->zipCode;
                current->zipCode = temp->zipCode;
                temp->zipCode = tempZip;
            }
              //point current to next node
            current = current -> next;
      }
      
        //set next to NULL    
      temp -> next = NULL;
      
        //set next to temp
      last -> next = temp;
      
        //set last to the last node that was added to the list
      last = temp;
   }
}

//******************************************************************************
void LinkedListClass::DeleteCustomer(ifstream &inputFile, ofstream &outputFile)
{
    //Receives - input file, output file
    //Task - remove customer from mailing list
    //Returns - nothing
  
    //check to see if list is empty, this error isn't required, but is good
    //to check in case there wasn't any data added
  if(isEmpty())
  {
    cout << "The database is empty" << endl;
  }
  
    //enter else if list contains data
  else
  {
      //first and last name to be read in from file
    string first;
    string last;
    
      //customer found in current list of customers
    bool found = false;
    
      //temporary node to go through list
    NodeType *temp;
    
      //set temp to first node in list
    temp = head;
    
      //read in first and last name to be deleted
    inputFile >> ws;
    getline(inputFile, first);
    inputFile >> ws;
    getline(inputFile, last);

      //go though list as long as it contains data
    while(temp != NULL)
    {
        //if first and last name is found, delete them
      if(temp -> firstName == first && temp -> lastName == last)
      {
          //set name to deleted
        temp -> firstName = "DELETED";
        
          //customer was found
        found = true;
      }
        //point to next node in list
      temp = temp -> next;
    }
    
      //if the customer wasn't in the list, print error showing they 
      //don't exist in the mailing list
    if(found == false)
    {
      outputFile << "Record of " << first << last;
      outputFile << " not found. Attempt to delete record failed!" << endl;
      outputFile << endl;
    }
  }
}
//******************************************************************************
void LinkedListClass::ChangeCustomer(ifstream &inputFile, ofstream &outputFile)
{
    //Receives - input file, output file
    //Task - change customer data with given parameters
    //Returns - nothing
    
    //data read in representing what is to be changed
  string first;
  string last;
  string newInfo;
  int fieldNumber;
  
    //set current to poing to first node in list
  current = head;
  
    //read in customer data to be changed
  inputFile >> ws;
  getline(inputFile, first);
  inputFile >> ws;
  getline(inputFile, last);
  inputFile >> fieldNumber;
  inputFile >> ws;
  getline(inputFile, newInfo);
  
    //go through list as long as it contains data
  while(current != NULL)
  {
      //make sure customer exists in list, print error if they don't
    if(current -> firstName == "DELETED" && current -> firstName == first)
    {
      outputFile << "Record of " << first << " " << last << " ";
      outputFile << "not found. Attempt to change record failed!" << endl;
      break;
    }
    
      //if the customer does exists, change their data
    else if((current -> firstName == first) && (current -> lastName == last))
    {
        //check field to be changed
      switch(fieldNumber)
      {
          //if field number is 1 change first name
        case 1: current -> firstName = newInfo;
                break;
                
          //if field number is 2 change last name
        case 2: current -> lastName = newInfo;
                break;
                
          //if field number is 3 change address
        case 3: current -> address = newInfo;
                break;
                
          //if field number is 4 change city
        case 4: current -> city = newInfo;
                break;
                
          //if field number is 5 change state
        case 5: current -> state = newInfo;
                break;
                
          //if field number is 6 change zip code
        case 6: current -> zipCode = newInfo;
                break;
      }
    }
    
      //point current to next node in list
    current = current -> next;
  }
}

//******************************************************************************

void LinkedListClass::PrintMailingList(ofstream &outputFile)
{
    //Receives - output file
    //Task - print all customers in mailing list
    //Returns - nothing
  
    //point current to first node in list
  current = head;

    //check to see if list is empty, this error isn't required, but is good
    //to check in case there wasn't any data added
  if(isEmpty())
  {
    cout << "The database is empty!" << endl;
  }
  
  else
  {
      //go through list if it contains data
    while(current != NULL)
    {
        //print customer info as long as their not deleted
      if(current -> firstName != "DELETED")
      {
          //print customer data
        outputFile << left << setw(16) << current -> lastName;
        outputFile << left << setw(17) << current -> firstName;
        outputFile << left << setw(23) << current -> address;
        outputFile << left << setw(13) << current -> city;
        outputFile << left << setw(11) << current -> state;
        outputFile << current -> zipCode;
        outputFile << endl;
      }
        //point current to next node in list
      current = current -> next;
    }
    
      //create proper spacing for output
    for(int x = 0; x < 30; x++)
    {
      outputFile << endl;
    }
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
	Outfile << setw(20) << "Assignment #2" << endl;
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


