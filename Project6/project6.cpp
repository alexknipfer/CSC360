#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

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

  private:
    StoreInfoStruct *Root;
};

//******************************************************************************

int main()
{
  char opCode;
  StoreInfoStruct storeInfo;
  TreeClass Tree;

  ifstream inputFile("data6.txt");
  ofstream outputFile("output.txt");

  inputFile >> opCode;

  while(opCode != 'Q')
  {
    switch(opCode)
    {
      case 'I': inputFile >> ws;
                getline(inputFile, storeInfo.id);
                inputFile >> ws;
                getline(inputFile, storeInfo.name);
                inputFile >> ws;
                inputFile >> storeInfo.quantityOnHand;
                inputFile >> storeInfo.quantityOnOrder;
                Tree.Insert(storeInfo, outputFile);
                break;
                
      case 'D': inputFile >> ws;
                getline(inputFile, storeInfo.id);
                inputFile >> ws;
                getline(inputFile, storeInfo.name);
                inputFile >> ws;
                Tree.Delete(storeInfo, outputFile);
                break;

      case 'P': inputFile >> opCode;
                if(opCode == 'E')
                {
                  Tree.PrintInventoryHeader(outputFile);
                  Tree.TraverseInOrder(Tree.GetRoot(), outputFile);
                }
                break;
    }
    inputFile >> opCode;
  }


  return 0;
}

//******************************************************************************

void TreeClass::PrintInventoryHeader(ofstream &outputFile)
{
  outputFile << "             JAKE'S HARDWARE INVENTORY REPORT" << endl;
  outputFile <<"     Item           Item                         Quantity       Quantity "<< endl;
  outputFile <<"    ID Number       Description                  On Hand        On Order "<< endl;
  outputFile << "--------------------------------------------------------------------------" << endl;
}

//******************************************************************************

void TreeClass::Insert(StoreInfoStruct storeInfo, ofstream &outputFile)
{
  bool inserted = false;
  StoreInfoStruct *newPtr, *CurrPtr;

  newPtr = new StoreInfoStruct;

  if(newPtr != NULL)
  {
    newPtr -> id = storeInfo.id;
    newPtr -> name = storeInfo.name;
    newPtr -> quantityOnHand = storeInfo.quantityOnHand;
    newPtr -> quantityOnOrder = storeInfo.quantityOnOrder;
    newPtr -> Lptr = NULL;
    newPtr -> Rptr = NULL;
    CurrPtr = Root;

    while(inserted == false)
    {
      if (CurrPtr == NULL)
		  {
		    Root = newPtr;
		    outputFile << "Item ID Number " << storeInfo.id;
		    outputFile << " successfully entered into the database." << endl;
		    outputFile << "--------------------------------------------------------------------------" << endl;
        inserted = true;
		  }

      else
		  {
  		  if (storeInfo.id < CurrPtr -> id)
  		  {
  		    if(CurrPtr -> Lptr != NULL )
  			  {
  			    CurrPtr = CurrPtr -> Lptr;
  			  }
          else
  			  {
  			    CurrPtr -> Lptr = newPtr;
  			    outputFile << "Item ID Number " << storeInfo.id;
  			    outputFile << " successfully entered into the database." << endl;
  			    outputFile << "--------------------------------------------------------------------------" << endl;
            inserted = true;
  			  }
  			}

  			else if(storeInfo.id == CurrPtr -> id)
  			{
  			  outputFile << "ERROR --- Attempt to insert a duplicate item (" << storeInfo.id;
  			  outputFile << ") into the database." << endl;
  			  outputFile << "--------------------------------------------------------------------------" << endl;
  			  inserted = true;
  			}

        else
  			{
          if(CurrPtr -> Rptr != NULL)
  			  {
  			    CurrPtr = CurrPtr -> Rptr;
  			  }

          else
  			  {
  			    CurrPtr -> Rptr = newPtr;
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
  StoreInfoStruct *delNode, *parNode, *StrNull, *node1, *node2, *node3;
  
  bool found = false;
  
  delNode = Root;
  parNode = NULL;
  StrNull = NULL;
  
  while((found == false) && (delNode != NULL))
  {
    if(infoToDelete.id == delNode -> id)
    {
      outputFile << "Item ID Number (" << infoToDelete.id;
      outputFile << ") successfully deleted from the database." << endl;
      found = true;
    }
    else
    {
      parNode = delNode;
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
  
  if(found == false)
  {
    outputFile << "ERROR --- Attempt to delete an item (" << infoToDelete.id;
    outputFile << ") not in the database list" << endl;
  }
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

