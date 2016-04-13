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
    void Insert(StoreInfoStruct);
    void TraverseInOrder(StoreInfoStruct *);
    void Delete(StoreInfoStruct &);
    void PatchParent(StoreInfoStruct &, StoreInfoStruct &, StoreInfoStruct &);
    StoreInfoStruct *GetRoot(){return Root;}
      
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
                Tree.Insert(storeInfo);
    }
    inputFile >> opCode;
  }
  
  Tree.TraverseInOrder(Tree.GetRoot());
  
  return 0;
}

//******************************************************************************

void TreeClass::Insert(StoreInfoStruct storeInfo)
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
            inserted = true;
  			  } 
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
            inserted = true;
  			  }
  			} 
		  }
    }
  }
}

//******************************************************************************

void TreeClass::TraverseInOrder(StoreInfoStruct *Root)
{
  if(Root != NULL)
  {
    TraverseInOrder(Root -> Lptr);
    cout << Root -> id << endl;
    TraverseInOrder(Root -> Rptr);
  }
}

