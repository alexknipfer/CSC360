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
};

//******************************************************************************

  //class for inventory data (binary tree)
class TreeClass
{
  public:
    TreeClass(){Root = NULL;}
    void Insert(StoreInfoStruct, ofstream &);
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

//******************************************************************************

int main()
{
  char opCode;
  StoreInfoStruct storeInfo;
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
                Tree.Insert(storeInfo, outputFile);
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

void TreeClass::Insert(StoreInfoStruct storeInfo, ofstream &outputFile)
{
    //Receives - inventory structure, output file
    //Task - insert an item into the tree (into the database)
    //Returns - nothing
    
  bool inserted = false;
  StoreInfoStruct *newPtr, *CurrPtr;

    //allocate space for pointer
  newPtr = new StoreInfoStruct;

    //make sure enough space is available
  if(newPtr != NULL)
  {
      //point to the values needed to be inserted
    newPtr -> id = storeInfo.id;
    newPtr -> name = storeInfo.name;
    newPtr -> quantityOnHand = storeInfo.quantityOnHand;
    newPtr -> quantityOnOrder = storeInfo.quantityOnOrder;
    
      //set left and right pointers (left and right subtrees) to null
    newPtr -> Lptr = NULL;
    newPtr -> Rptr = NULL;
    CurrPtr = Root;

      //continue going until inserted successfully
    while(inserted == false)
    {
        //check to see if item needs to be added as root
      if (CurrPtr == NULL)
		  {
		      //reset root
		    Root = newPtr;
		    
		      //output message showing item has been added
		    outputFile << "Item ID Number " << storeInfo.id;
		    outputFile << " successfully entered into the database." << endl;
		    outputFile << "--------------------------------------------------------------------------" << endl;
		    
		      //reset inserted to exit loop
        inserted = true;
		  }

        //if not at the root, do the following
      else
		  {
		      //check to see if ID is greater or less than root to place "in-order"
  		  if (storeInfo.id < CurrPtr -> id)
  		  {
  		      //make sure the left pointer isn't null
  		    if(CurrPtr -> Lptr != NULL )
  			  {
  			      //reset current pointer
  			    CurrPtr = CurrPtr -> Lptr;
  			  }
  			  
  			    //if it was null, then item can be added in location and is successfully inserted
          else
  			  {
  			    CurrPtr -> Lptr = newPtr;
  			    
  			      //output message showing item has been added
  			    outputFile << "Item ID Number " << storeInfo.id;
  			    outputFile << " successfully entered into the database." << endl;
  			    outputFile << "--------------------------------------------------------------------------" << endl;
            inserted = true;
  			  }
  			}
  
          //check to see if item already exists
  			else if(storeInfo.id == CurrPtr -> id)
  			{
  			    //print error message since item already exists in tree (database)
  			  outputFile << "ERROR --- Attempt to insert a duplicate item (" << storeInfo.id;
  			  outputFile << ") into the database." << endl;
  			  outputFile << "--------------------------------------------------------------------------" << endl;
  			  
  			    //reset value to exit loop
  			  inserted = true;
  			}

          //check right side of tree (right pointer)
        else
  			{
  			    //if it's not null go to next location
          if(CurrPtr -> Rptr != NULL)
  			  {
  			      //scan to next location
  			    CurrPtr = CurrPtr -> Rptr;
  			  }

            //if null item can be added
          else
  			  {
  			    CurrPtr -> Rptr = newPtr;
  			    
  			      //print message showing item has been added
  			    outputFile << "Item ID Number " << storeInfo.id;
  			    outputFile << " successfully entered into the database." << endl;
  			    outputFile << "--------------------------------------------------------------------------" << endl;
            inserted = true;
  			  }
  			}
		  }
    }
  }
}

//******************************************************************************

void TreeClass::Delete(StoreInfoStruct &infoToDelete, ofstream &outputFile)
{
    //Receives - inventory structure, output file,
    //Task - delete node from tree (delete item from database)
    //Returns - nothing
    
  StoreInfoStruct *delNode, *parNode, *StrNull, *node1, *node2, *node3;
  
  bool found = false;
  
    //set initial pointer values
  delNode = Root;
  parNode = NULL;
  StrNull = NULL;
  
    //keep scanning until item is found (or not found)
  while((found == false) && (delNode != NULL))
  {
      //if the ID is found print deleted message
    if(infoToDelete.id == delNode -> id)
    {
        //print message item was successfully removed
      outputFile << "Item ID Number (" << infoToDelete.id;
      outputFile << ") successfully deleted from the database." << endl;
      outputFile << "--------------------------------------------------------------------------" << endl;
      
        //reset value to exit loop
      found = true;
    }
    
      //scan to next item in tree
    else
    {
      parNode = delNode;
      
        //check to see if ID is different than the one to be deleted
      if(infoToDelete.id < delNode -> id)
      {
        delNode = delNode -> Lptr;
      }
      else
      {
        delNode = delNode -> Rptr;
      }
    }
  }
  
    //item was not found in database
  if(found == false)
  {
      //print error message because item to be deleted wasn't found
    outputFile << "ERROR --- Attempt to delete an item (" << infoToDelete.id;
    outputFile << ") not in the database list" << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
  }
  
    //delete the node from tree
  else
  {
    if(delNode -> Lptr == NULL)
    {
      if(delNode -> Rptr == NULL)
      {
        PatchParent(StrNull, parNode, delNode);
      }
      else
      {
        PatchParent(delNode -> Rptr, parNode, delNode);
      }
    }
    else
    {
      if(delNode -> Rptr == NULL)
      {
        PatchParent(delNode -> Lptr, parNode, delNode);
      }
      else
      {
        node1 = delNode;
        node2 = delNode -> Lptr;
        node3 = node2 -> Rptr;
        while(node3 != NULL)
        {
          node1 = node2;
          node2 = node3;
          node3 = node2 -> Rptr;
        }
        if(node1 != delNode)
        {
          node1 -> Rptr = node2 -> Lptr;
          node2 -> Lptr = delNode -> Lptr;
        }
        node2 -> Rptr = delNode -> Rptr;
        PatchParent(node2, parNode, delNode);
      } //end else
    } //end else
  } //end else
}

//******************************************************************************

void TreeClass::PatchParent(StoreInfoStruct *NewParNode, StoreInfoStruct *parNode, StoreInfoStruct *delNode)
{
  if(parNode == NULL)
  {
    Root = NewParNode;
  }
  else
  {
    if(parNode -> Lptr == delNode)
    {
      parNode -> Lptr = NewParNode;
    }
    else
    {
      parNode -> Rptr = NewParNode;
    }
  }
}

//******************************************************************************

void TreeClass::TraverseInOrder(StoreInfoStruct *Root, ofstream &outputFile)
{
  if(Root != NULL)
  {
    TraverseInOrder(Root -> Lptr, outputFile);

    outputFile << "  " << Root -> id;
    outputFile << setw(33) << Root -> name;
    outputFile << setw(15) << Root -> quantityOnHand;
    outputFile << setw(15) << Root -> quantityOnOrder << endl;
    
    TraverseInOrder(Root -> Rptr, outputFile);
  }
}

//******************************************************************************

void TreeClass::PrintItem(string id, ofstream &outputFile)
{
  StoreInfoStruct *foundNode, *parNode, *node1, *node2, *node3, *StrNull;
  
  bool found = false;
  
  foundNode = Root;
  parNode = NULL;
  StrNull = NULL;

  while((found == false) && (foundNode != NULL))
  {
    if(id == foundNode -> id)
    {
      PrintInventoryHeader(outputFile);
      outputFile << " " << foundNode -> id;
      outputFile << setw(33) << foundNode -> name;
      outputFile << setw(15) << foundNode -> quantityOnHand;
      outputFile << setw(15) << foundNode -> quantityOnOrder << endl;
      for(int x = 0; x < 10; x++)
      {
        outputFile << endl;
      }
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
  }
}

//******************************************************************************

void TreeClass::AdjustInventoryOnHand(string id, int quantity, ofstream &outputFile)
{
  StoreInfoStruct *foundNode, *parNode, *node1, *node2, *node3, *StrNull;
  
  bool found = false;
  
  foundNode = Root;
  parNode = NULL;
  StrNull = NULL;

  while((found == false) && (foundNode != NULL))
  {
    if(id == foundNode -> id)
    {
      foundNode -> quantityOnHand -= quantity;
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
    outputFile << "Item (" << id << ") not in database. Data not updated." << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
  }
}

//******************************************************************************

void TreeClass::AdjustInventoryOnOrder(string id, int quantity, ofstream &outputFile)
{
  StoreInfoStruct *foundNode, *parNode, *node1, *node2, *node3, *StrNull;
  
  bool found = false;
  
  foundNode = Root;
  parNode = NULL;
  StrNull = NULL;

  while((found == false) && (foundNode != NULL))
  {
    if(id == foundNode -> id)
    {
      foundNode -> quantityOnOrder += quantity;
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
    outputFile << "Item (" << id << ") not in database. Data not updated." << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
  }
}

void TreeClass::AdjustQuantityReceived(string id, int quantity, ofstream &outputFile)
{
  StoreInfoStruct *foundNode, *parNode, *node1, *node2, *node3, *StrNull;
  
  bool found = false;
  
  foundNode = Root;
  parNode = NULL;
  StrNull = NULL;

  while((found == false) && (foundNode != NULL))
  {
    if(id == foundNode -> id)
    {
      foundNode -> quantityOnOrder -= quantity;
      foundNode -> quantityOnHand += quantity;
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
    outputFile << "Item (" << id << ") not in database. Data not updated." << endl;
    outputFile << "--------------------------------------------------------------------------" << endl;
  }
}

