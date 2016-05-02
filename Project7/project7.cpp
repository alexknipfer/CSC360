//******************  PROGRAM IDENTIFICATION  **********************************
//*                                                                            *
//*  PROGRAM FILE NAME: project6.cpp  ASSIGNMENT #:  6    GRADE: _____         *
//*   	                                                                       *
//*  PROGRAM AUTHOR:   ____________________________________                    *
//*                             Alex Knipfer                                   *
//*                                                                            *
//*  COURSE #:   CSC 36000 11             DUE DATE: April 22, 2015             *
//*                                                                            * 
//******************************************************************************


//********************* PROGRAM DESCRIPTION ************************************
//*    Process: This program employs a binary tree to store and print          *
//*             information on a store's database inventory.                   *
//*                                                                            *
//*    USER DEFINED                                                            *
//*     MODULES:       : printHeader - print program header                    *
//*                      printFooter - print program footer                    *
//*                      Insert - insert item into database (tree)             *
//*                      TraverseInOrder - traverse tree in order              *
//*                      Delete - delete item from database (tree)             *
//*                      PatchParent - restructure tree after delete           *
//*                      GetRoot - get's root of tree                          *
//*                      PrintInventoryHeader - prints header for inventory    *
//*                      PrintItem - prints individual item                    *
//*                      AdjustInventoryOnHand - updates on hand quantity      *
//*                      AdjustInventoryOnOrder - updates on order quantity    *
//*                      AdjustQuantityReceived - updates quantity received    *
//******************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

  //structure for holding store database inventory
struct StoreInfoStruct
{
  string id;
  string name;
  int quantityOnHand;
  int quantityOnOrder;

  StoreInfoStruct *Lptr;
  StoreInfoStruct *Rptr;
  
  int thread;
};

//******************************************************************************

  //class for inventory data (binary tree)
class TreeClass
{
  public:
    TreeClass(){Root = NULL;}
    void Insert(StoreInfoStruct, StoreInfoStruct *, ofstream &);
    void TraverseInOrder(StoreInfoStruct *, ofstream &);
    void Delete(StoreInfoStruct &, ofstream &);
    void PatchParent(StoreInfoStruct *, StoreInfoStruct *, StoreInfoStruct *);
    StoreInfoStruct *GetRoot(){return Root;}
    void PrintInventoryHeader(ofstream &);
    void PrintItem(string, ofstream &);
    void AdjustInventoryOnHand(string, int, ofstream &);
    void AdjustInventoryOnOrder(string, int, ofstream &);
    void AdjustQuantityReceived(string, int, ofstream &);

  private:
    StoreInfoStruct *Root;
};

  //prototypes for header and footer
void printHeader(ofstream &);
void printFooter(ofstream &);

//******************************************************************************

int main()
{
  char opCode;
  StoreInfoStruct storeInfo;
  StoreInfoStruct *newPtr;
  TreeClass Tree;
  
    //new values read in for inventory
  string idToPrint;
  string idToUpdate;
  int quantOnHand;
  int quantOnOrder;
  int quantReceived;

    //create input and output files for data
  ifstream inputFile("tree.in");
  ofstream outputFile("output.txt");
  
    //print program header
  printHeader(outputFile);

    //read in initial op code to figure out what to do with data
  inputFile >> opCode;

    //continue reading in data until sentinel of "Q" is reached
  while(opCode != 'Q')
  {
    switch(opCode)
    {
        //if op code is "I", insert item into tree (insert into database)
      case 'I': inputFile >> ws;
                getline(inputFile, storeInfo.id);
                inputFile >> ws;
                getline(inputFile, storeInfo.name);
                inputFile >> ws;
                inputFile >> storeInfo.quantityOnHand;
                inputFile >> storeInfo.quantityOnOrder;
                
                   //allocate space for pointer
                newPtr = new StoreInfoStruct;
                Tree.Insert(storeInfo, newPtr, outputFile);
                break;
        
        //if op code is "D", delete item from tree (from database)        
      case 'D': inputFile >> ws;
                getline(inputFile, storeInfo.id);
                inputFile >> ws;
                getline(inputFile, storeInfo.name);
                inputFile >> ws;
                Tree.Delete(storeInfo, outputFile);
                break;

        //if op code is "P", print all or 1 item from tree (from database)
      case 'P': inputFile >> opCode;
      
                  //if op code is "E", print all items in tree (database)
                if(opCode == 'E')
                {
                  Tree.PrintInventoryHeader(outputFile);
                  Tree.TraverseInOrder(Tree.GetRoot(), outputFile);
                }
                
                  //if op code is "N", read in item to print
                else if(opCode == 'N')
                {
                  inputFile >> ws;
                  getline(inputFile, idToPrint);
                  inputFile >> ws;
                  Tree.PrintItem(idToPrint, outputFile);
                }
                break;
      
        //if op code is "S", update on hand count          
      case 'S': inputFile >> ws;
                getline(inputFile, idToUpdate);
                inputFile >> ws;
                inputFile >> quantOnHand;
                Tree.AdjustInventoryOnHand(idToUpdate, quantOnHand, outputFile);
                break;
      
        //if op code is "O", update on order count          
      case 'O': inputFile >> ws;
                getline(inputFile, idToUpdate);
                inputFile >> ws;
                inputFile >> quantOnOrder;
                inputFile >> ws;
                Tree.AdjustInventoryOnOrder(idToUpdate, quantOnOrder, outputFile);
                break;
        
        //if op code is "R", update quantity receives count        
      case 'R': inputFile >> ws;
                getline(inputFile, idToUpdate);
                inputFile >> ws;
                inputFile >> quantReceived;
                inputFile >> ws;
                Tree.AdjustQuantityReceived(idToUpdate, quantReceived, outputFile);
                break;
    }
    
      //read in next op code
    inputFile >> opCode;
  }

    //print program footer
  printFooter(outputFile);

  return 0;
}

//******************************************************************************

void TreeClass::PrintInventoryHeader(ofstream &outputFile)
{
    //Receives - output files
    //Task - print header for inventory
    //Returns - nothing
  
    //output inventory header to file
  outputFile << "             JAKE'S HARDWARE INVENTORY REPORT" << endl;
  outputFile <<"     Item           Item                         Quantity       Quantity "<< endl;
  outputFile <<"    ID Number       Description                  On Hand        On Order "<< endl;
  outputFile << "--------------------------------------------------------------------------" << endl;
}

//******************************************************************************

void TreeClass::Insert(StoreInfoStruct storeInfo, StoreInfoStruct *newPtr, ofstream &outputFile)
{
    //Receives - inventory structure, output file
    //Task - insert an item into the tree (into the database)
    //Returns - nothing
    
    StoreInfoStruct *ParentNode;
    
    int Inserted = 0;
    
    ParentNode = Root;
    
    if(ParentNode == NULL)
    {
        newPtr -> id = storeInfo.id;
        newPtr -> name = storeInfo.name;
        newPtr -> quantityOnHand = storeInfo.quantityOnHand;
        newPtr -> quantityOnOrder = storeInfo.quantityOnOrder;
        Root = newPtr;
        return;
    }
    
    else{
      newPtr -> id = storeInfo.id;
      newPtr -> name = storeInfo.name;
      newPtr -> quantityOnHand = storeInfo.quantityOnHand;
      newPtr -> quantityOnOrder = storeInfo.quantityOnOrder;
      ParentNode = Root;
        
      while(Inserted != 1)
      {
          if(newPtr -> id < ParentNode -> id)
          {
              if(ParentNode -> Lptr != NULL)
              {
                  ParentNode = ParentNode -> Lptr;
              }
              else
              {
                  ParentNode -> Lptr = newPtr;
                  newPtr -> Rptr = ParentNode;
                  newPtr -> thread = 1;
                  Inserted = 1;
              }
          }
          else
          {
              if((ParentNode -> Rptr != NULL) && (ParentNode -> thread != 1))
              {
                  ParentNode = ParentNode -> Rptr;
              }
              else
              {
                  newPtr -> Rptr = ParentNode -> Rptr;
                  ParentNode -> Rptr = newPtr;
                  ParentNode -> thread = 0;
                  newPtr -> thread = 1;
                  Inserted = 1;
              }
          }
          return;
      }
    }

}

//******************************************************************************

void TreeClass::Delete(StoreInfoStruct &infoToDelete, ofstream &outputFile)
{
    //Receives - inventory structure, output file,
    //Task - delete node from tree (delete item from database)
    //Returns - nothing
    
  bool found = false;
  StoreInfoStruct *delnode, *parnode, *node1, *node2, *node3;
  
  delnode = Root;
  
  while(found == false && delnode != NULL && delnode -> thread != 1)
  {
    if(infoToDelete.id == delnode -> id)
    {
        //print message item was successfully removed
      outputFile << "Item ID Number (" << infoToDelete.id;
      outputFile << ") successfully deleted from the database." << endl;
      outputFile << "--------------------------------------------------------------------------" << endl;
      found = true;
    }
    else
    {
      parnode = delnode;
      if(infoToDelete.id < delnode -> id)
      {
        delnode = delnode -> Lptr;
      }
      else
      {
        delnode = delnode -> Rptr;
      }
    }
  }
  
  if(found == false)
  {
      //print error message because item to be deleted wasn't found
    outputFile << "ERROR --- Attempt to delete an item (" << infoToDelete.id;
    outputFile << ") not in the database list" << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
    return;
  }
  
  if((delnode -> Lptr == NULL) && ((delnode -> Rptr == NULL) || (delnode -> thread == 1)))
  {
    if(parnode == NULL)
    {
      Root = NULL;
    }
    else
    {
      if(parnode -> Lptr == delnode)
      {
        parnode -> Lptr = NULL;
      }
      else
      {
        parnode -> Rptr = delnode -> Rptr;
        parnode -> thread = 1;
      }
    }
    return;
  }
  
  if((delnode -> Lptr == NULL) && ((delnode -> Rptr != NULL) || (delnode -> thread == 0)))
  {
    if(parnode == NULL)
    {
      Root = delnode -> Rptr;
    }
    else
    {
      if(parnode -> Lptr = delnode)
      {
        parnode -> Lptr = delnode -> Rptr;
      }
      else
      {
        parnode -> Rptr = delnode -> Rptr;
      }
    }
    return;
  }
  
  if((delnode -> Lptr != NULL) && ((delnode -> Rptr == NULL) || (delnode -> thread == 1)))
  {
    if(parnode == NULL)
    {
      Root = delnode -> Lptr;
    }
    else
    {
      if(parnode -> Lptr == delnode)
      {
        parnode -> Lptr = delnode -> Lptr;
      }
      else
      {
        parnode -> Rptr = delnode -> Lptr;
      }
    }
    node1 = delnode -> Lptr;
    while((node1 -> Rptr != NULL) && (node1 -> thread != 1))
    {
      node1 = node1 -> Rptr;
    }
    node1 -> Rptr = delnode -> Rptr;
    return;
  }
  
  if((delnode -> Lptr != NULL) && (delnode -> Rptr != NULL) && (delnode -> thread == 0))
  {
    node1 = delnode;
    node2 = delnode -> Lptr;
    node3 = delnode -> Lptr;
    
    while((node3 != NULL) && (node3 -> thread != 1))
    {
      node2 = node3;
      node3 = node3 -> Rptr;
    }
    
    if(parnode == NULL)
    {
      Root = node3;
    }
    else
    {
      if(parnode -> Lptr == delnode)
      {
        parnode -> Lptr = node3;
      }
      else
      {
        parnode -> Rptr = node3;
      }
    }
    
    if((node3 -> Lptr != NULL) && (node2 != node3))
    {
      node2 -> Rptr = node3 -> Lptr;
      node3 -> Lptr = delnode -> Lptr;
      node3 -> Rptr = delnode -> Rptr;
      node3 -> thread = 0;
    }
    else if(node2 == node3)
    {
      node3 -> Rptr = delnode -> Rptr;
      node3 -> thread = 0;
    }
    else if(node2 -> Rptr != NULL)
    {
      node2 -> Rptr = node3;
      node2 -> thread = 1;
      node3 -> Lptr = delnode -> Lptr;
      node3 -> Rptr = delnode -> Rptr;
      node3 -> thread = 0;
    }
  }
}

//******************************************************************************

void TreeClass::PatchParent(StoreInfoStruct *NewParNode, StoreInfoStruct *parNode, StoreInfoStruct *delNode)
{
    //Receives - new parent node, parent node, and deleted node (to be deleted)
    //Task - restructure tree properly after node has been deleted
    //Returns - nothing
    
    //check parent node, reset root to parent
  if(parNode == NULL)
  {
    Root = NewParNode;
  }
  else
  {
      //reset nodes for deletion
    if(parNode -> Lptr == delNode)
    {
      parNode -> Lptr = NewParNode;
    }
      //reset parent node for deletion
    else
    {
      parNode -> Rptr = NewParNode;
    }
  }
}

//******************************************************************************

void TreeClass::TraverseInOrder(StoreInfoStruct *Root, ofstream &outputFile)
{
    //Receives - root node, output file
    //Task - traverse the tree in order (go through inventory in database)
    //Returns - nothing
    
    int RightThread;
    StoreInfoStruct *CurrPtr;
    
    CurrPtr = Root;
    
    while(CurrPtr -> Lptr != NULL)
        CurrPtr = CurrPtr -> Lptr;
        
    while(CurrPtr != NULL)
    {
               //process and print node (print inventory data in database)
    outputFile << "  " << CurrPtr -> id;
    outputFile << setw(33) << CurrPtr -> name;
    outputFile << setw(15) << CurrPtr -> quantityOnHand;
    outputFile << setw(15) << CurrPtr -> quantityOnOrder << endl;
        
        RightThread = CurrPtr -> thread;
        CurrPtr = CurrPtr -> Rptr;
        
        if((CurrPtr != NULL) && (RightThread == 0))
        {
            while(CurrPtr -> Lptr != NULL)
            {
                CurrPtr = CurrPtr -> Lptr;
            }
        }
    }
    return;
}

//******************************************************************************

void TreeClass::PrintItem(string id, ofstream &outputFile)
{
    //Receives - ID to be printed, output file
    //Task - print specific item given ID
    //Returns - nothing
    
  StoreInfoStruct *foundNode, *parNode;
  
  bool found = false;
  
    //initialize pointers
  foundNode = Root;
  parNode = NULL;

  while((found == false) && (foundNode != NULL) && (foundNode -> thread != 1))
  {
    if(id == foundNode -> id)
    {
        //print header for inventory data
      PrintInventoryHeader(outputFile);
      
        //output the inventory data to file
      outputFile << " " << foundNode -> id;
      outputFile << setw(33) << foundNode -> name;
      outputFile << setw(15) << foundNode -> quantityOnHand;
      outputFile << setw(15) << foundNode -> quantityOnOrder << endl;
      
      found = true;
    }
    else
    {
      parNode = foundNode;
      if(id < foundNode -> id)
      {
        foundNode = foundNode -> Lptr;
      }
      else
      {
        foundNode = foundNode -> Rptr;
      }
    }
  }
  
  if(found == false)
  {
    outputFile << "Item (" << id << ") not in database. Print failed." << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
    return;
  }
}

//******************************************************************************

void TreeClass::AdjustInventoryOnHand(string id, int quantity, ofstream &outputFile)
{
    //Receives - ID, quantity to adjust, output file
    //Task - Update inventory on hand to the inventory ID given with the quantity given
    //Returns - nothing
    
  StoreInfoStruct *foundNode, *parNode;
  
  bool found = false;
  
    //initialize pointers
  foundNode = Root;
  parNode = NULL;

  while(found == false && foundNode != NULL && foundNode -> thread != 1)
  {
    if(id == foundNode -> id)
    {
        //update quantity on hand by subtracting given quantity
      foundNode -> quantityOnHand -= quantity;
      
        //output success message for the update
      outputFile << "Quantity on Hand for item (" << id;
      outputFile << ") successfully updated." << endl;
      outputFile << "--------------------------------------------------------------------------" << endl;
      
      found = true;
    }
    else
    {
      parNode = foundNode;
      if(id < foundNode -> id)
      {
        foundNode = foundNode -> Lptr;
      }
      else
      {
        foundNode = foundNode -> Rptr;
      }
    }
  }
  
  if(found == false)
  {
      //output error message since item didn't exist
    outputFile << "Item (" << id << ") not in database. Data not updated." << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
    return;
  }
}

//******************************************************************************

void TreeClass::AdjustInventoryOnOrder(string id, int quantity, ofstream &outputFile)
{
    //Receives - ID, quantity to be updated, output file
    //Task - ukpdate inventory on order with given quantity to given ID
    //Returns - nothing
    
  StoreInfoStruct *foundNode, *parNode;
  
  bool found = false;
  
    //initialize pointers
  foundNode = Root;
  parNode = NULL;
  
  while(found == false && foundNode != NULL && foundNode -> thread != 1)
  {
    if(id == foundNode -> id)
    {
        //update quantity on hand by subtracting given quantity
      foundNode -> quantityOnOrder += quantity;
      
        //output success message for the update
      outputFile << "Quantity on Order for item (" << id;
      outputFile << ") successfully updated." << endl;
      outputFile << "--------------------------------------------------------------------------" << endl;
      
      found = true;
    }
    else
    {
      parNode = foundNode;
      if(id < foundNode -> id)
      {
        foundNode = foundNode -> Lptr;
      }
      else
      {
        foundNode = foundNode -> Rptr;
      }
    }
  }
  
  if(found == false)
  {
      //output error message since item didn't exist
    outputFile << "Item (" << id << ") not in database. Data not updated." << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
    return;
  }
}

//******************************************************************************

void TreeClass::AdjustQuantityReceived(string id, int quantity, ofstream &outputFile)
{
    //Receives - ID, quantity to be updated, output file
    //Task - updates quantity received with given quantity to given ID
    //Returns - nothing
    
  StoreInfoStruct *foundNode, *parNode;
  
  bool found = false;
  
    //intialize pointers
  foundNode = Root;
  parNode = NULL;
  
  while(found == false && foundNode != NULL && foundNode -> thread != 1)
  {
    if(id == foundNode -> id)
    {
        //update quantity on hand by subtracting given quantity
      foundNode -> quantityOnOrder -= quantity;
      foundNode -> quantityOnHand += quantity;
      
        //output success message
      outputFile << "Item ID Number " << id << " successfully updated with ";
      outputFile << quantity << " items added to the database." << endl;
      outputFile << "--------------------------------------------------------------------------" << endl;
      
      found = true;
    }
    else
    {
      parNode = foundNode;
      if(id < foundNode -> id)
      {
        foundNode = foundNode -> Lptr;
      }
      else
      {
        foundNode = foundNode -> Rptr;
      }
    }
  }
  
  if(found == false)
  {
      //output error message since item didn't exist
    outputFile << "Item (" << id << ") not in database. Data not updated." << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
    return;
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
	Outfile << setw(20) << "Assignment #6" << endl;
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

//*********************** END OF PROGRAM *************************************//

