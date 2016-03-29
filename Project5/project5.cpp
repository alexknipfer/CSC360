//******************  PROGRAM IDENTIFICATION  **********************************
//*                                                                            *
//*  PROGRAM FILE NAME: project2.cpp  ASSIGNMENT #:  5    GRADE: _____         *
//*   	                                                                       *
//*  PROGRAM AUTHOR:   ____________________________________                    *
//*                             Alex Knipfer                                   *
//*                                                                            *
//*  COURSE #:   CSC 36000 11             DUE DATE: April 08, 2015             *
//*                                                                            * 
//******************************************************************************


//********************* PROGRAM DESCRIPTION ************************************
//*    Process: This program reads in inventory data and sorts it three times  *
//*             by a different "key" each time. This program utilizes the      *
//*             bubble sort, shell sort, and quick sort. The inventory data is *
//*             printed to a file after each sort.                             *
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

  //structure for holding each piece of data for inventory
struct InventoryStruct
{
  int inventoryNumber;
  string itemDescription;
  int quantityOnHand;
  int reorderNumber;
  double costOfItem;
  double sellingPrice;
};

//******************************************************************************

  //class for inventory data
class InventoryClass
{
  public:
    InventoryClass();
    void readData(ifstream &);
    void printData(ofstream &);
    void sortQuantityOnHand();
  
  private:
    InventoryStruct inventoryData[50];
    int inventoryCount;
};

//******************************************************************************

int main()
{
    //instantiate inventory class
  InventoryClass myInventory;
  
    //create input and output files
  ifstream inputFile("data5.txt");
  ofstream outputFile("output.txt");
  
    //read in inventory data from file
  myInventory.readData(inputFile);
  
    //print labels for printing inventory
  outputFile << "The Original Inventory Array:" << endl;
  outputFile << "Inventory  Item                    Quantity  Reorder  Cost of  Selling " << endl;
  outputFile << " Number    Description             on hand   Number   Item     Price" << endl;
  outputFile << "--------   -----------------       --------  -------  -------  -------" << endl;
  
    //print intial inventory data
  myInventory.printData(outputFile);
  
  outputFile << endl;
  
    //sort inventory array in descending order by quantity on hand
  myInventory.sortQuantityOnHand();
  
    //print labels for printing inventory
  outputFile << "The Inventory Array sorted in descending order according to the Quantity on Hand" << endl;
  outputFile << "using the Bubble Sort:" << endl;
  outputFile << "Inventory  Item                    Quantity  Reorder  Cost of  Selling " << endl;
  outputFile << " Number    Description             on hand   Number   Item     Price" << endl;
  outputFile << "--------   -----------------       --------  -------  -------  -------" << endl;
  
    //print inventory array
  myInventory.printData(outputFile);
 
  return 0;
}

//******************************************************************************

InventoryClass::InventoryClass()
{
    //Receives - nothing
    //Task - Constructor - initialize count for array holding inventory
    //Returns - nothing
    
  inventoryCount = 0;
}

//******************************************************************************

void InventoryClass::readData(ifstream &inputFile)
{
    //Receives - input file
    //Task - read in data from file into array of inventory structures
    //Returns - nothing
    
    //instantiate inventory structure
  InventoryStruct currentInventory;
  
    //read in initial inventory number
  inputFile >> currentInventory.inventoryNumber;
  
    //continue reading in from file until inventory number is invalid (negative)
  while(currentInventory.inventoryNumber > 0)
  {
    inputFile >> ws;
    getline(inputFile, currentInventory.itemDescription);
    inputFile >> ws;
    inputFile >> currentInventory.quantityOnHand;
    inputFile >> currentInventory.reorderNumber;
    inputFile >> currentInventory.costOfItem;
    inputFile >> currentInventory.sellingPrice;
    
      //store current inventory item into array
    inventoryData[inventoryCount] = currentInventory;
    inventoryCount++;
    inputFile >> currentInventory.inventoryNumber;
  }
}

//******************************************************************************

void InventoryClass::sortQuantityOnHand()
{
    //Receives - nothing
    //Task - sort inventory array by quantity on hand (descending order)
    //Returns - nothing
    
    //create temp variables for all swaps
  int tempInventoryNumber;
  string tempItemDescription;
  int tempQuantityOnHand;
  int tempReorderNumber;
  double tempCostOfItem;
  double tempSellingPrice;
  
    //bubble sort the inventory array by quantity on hand (in descending order)
  for(int x = 0; x < inventoryCount - 1; x++)
  {
    for(int y = 0; y < inventoryCount - 1; y++)
    {
        //check to see if current quantity on hand is less than the adjacent one
      if(inventoryData[y].quantityOnHand < inventoryData[y + 1].quantityOnHand)
      {
          //swap inventory number
        tempInventoryNumber = inventoryData[y].inventoryNumber;
        inventoryData[y].inventoryNumber = inventoryData[y + 1].inventoryNumber;
        inventoryData[y + 1].inventoryNumber = tempInventoryNumber;
        
          //swap item description
        tempItemDescription = inventoryData[y].itemDescription;
        inventoryData[y].itemDescription = inventoryData[y + 1].itemDescription;
        inventoryData[y + 1].itemDescription = tempItemDescription;
        
          //swap quantity on hand
        tempQuantityOnHand = inventoryData[y].quantityOnHand;
        inventoryData[y].quantityOnHand = inventoryData[y + 1].quantityOnHand;
        inventoryData[y + 1].quantityOnHand = tempQuantityOnHand;
        
          //swap reorder number
        tempReorderNumber = inventoryData[y].reorderNumber;
        inventoryData[y].reorderNumber = inventoryData[y + 1].reorderNumber;
        inventoryData[y + 1].reorderNumber = tempReorderNumber;
        
          //swap cost of item
        tempCostOfItem = inventoryData[y].costOfItem;
        inventoryData[y].costOfItem = inventoryData[y + 1].costOfItem;
        inventoryData[y + 1].costOfItem = tempCostOfItem;
        
          //swap selling price
        tempSellingPrice = inventoryData[y].sellingPrice;
        inventoryData[y].sellingPrice = inventoryData[y + 1].sellingPrice;
        inventoryData[y + 1].sellingPrice = tempSellingPrice;
      }
    }
  }
}

//******************************************************************************

void InventoryClass::printData(ofstream &outputFile)
{
    //Receives - output file
    //Task - print inventory data
    //Returns - nothing
    
    //go through array of all inventory and print out each inventory item
  for(int x = 0; x < inventoryCount; x++)
  {
    outputFile << inventoryData[x].inventoryNumber;
    outputFile << setw(32) << inventoryData[x].itemDescription;
    outputFile << setw(5) << inventoryData[x].quantityOnHand;
    outputFile << setw(8) << inventoryData[x].reorderNumber;
    outputFile << setw(11) << inventoryData[x].costOfItem;
    outputFile << setw(9) << inventoryData[x].sellingPrice;
    outputFile << endl;
  }
}