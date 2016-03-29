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