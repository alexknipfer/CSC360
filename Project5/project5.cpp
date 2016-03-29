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
//*                      readData - reads in data from file into array         *
//*                      printData - prints inventory array                    *
//*                      sortQuantityOnHand - sorts array by quantity on hand  *
//*                      sortSellingPrice - sorts array by selling price       *
//*                      sortInventoryNumber - sorts array by inventory number *
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
    void sortSellingPrice();
    void sortInventoryNumber(int, int);
    int inventoryCount;
  
  private:
    InventoryStruct inventoryData[50];
    
};

  //prototypes for header and footer
void printHeader(ofstream &);
void printFooter(ofstream &);

//******************************************************************************

int main()
{
  int first, last;
  
    //instantiate inventory class
  InventoryClass myInventory;
  
    //create input and output files
  ifstream inputFile("data5.txt");
  ofstream outputFile("output.txt");
  
    //print program header
  printHeader(outputFile);
  
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
  
    //sort inventory array in descending order by quantity on hand using bubble sort
  myInventory.sortQuantityOnHand();
  
    //print labels for printing inventory
  outputFile << "The Inventory Array sorted in descending order according to the Quantity on Hand" << endl;
  outputFile << "using the Bubble Sort:" << endl;
  outputFile << "Inventory  Item                    Quantity  Reorder  Cost of  Selling " << endl;
  outputFile << " Number    Description             on hand   Number   Item     Price" << endl;
  outputFile << "--------   -----------------       --------  -------  -------  -------" << endl;
  
    //print inventory array
  myInventory.printData(outputFile);
  
  outputFile << endl;
  
    //sort inventory array in descending order by selling price using shell sort
  myInventory.sortSellingPrice();
  
  outputFile << "The Inventory Array sorted in descending order according to the Selling Price" << endl;
  outputFile << "using the Shell Sort:" << endl;
  outputFile << "Inventory  Item                    Quantity  Reorder  Cost of  Selling " << endl;
  outputFile << " Number    Description             on hand   Number   Item     Price" << endl;
  outputFile << "--------   -----------------       --------  -------  -------  -------" << endl;
  
    //print inventory array
  myInventory.printData(outputFile);
  
  outputFile << endl;
  
    //sort inventory array in ascending order by inventory number
  myInventory.sortInventoryNumber(0, myInventory.inventoryCount - 1);
  
    //print labels for printing inventory
  outputFile << "The Inventory Array sorted in ascending order according to the Inventory Number" << endl;
  outputFile << "using the Quick Sort:" << endl;
  outputFile << "Inventory  Item                    Quantity  Reorder  Cost of  Selling " << endl;
  outputFile << " Number    Description             on hand   Number   Item     Price" << endl;
  outputFile << "--------   -----------------       --------  -------  -------  -------" << endl;
  
    //print inventory array
  myInventory.printData(outputFile);
  
    //print program footer
  printFooter(outputFile);
 
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

void InventoryClass::sortSellingPrice()
{
    //Receives - nothing
    //Task - sort inventory array by selling price in descending order using shell sort
    //Returns - nothing
    
    //create temp variables for all swaps
  int i;
  int tempInventoryNumber;
  string tempItemDescription;
  int tempQuantityOnHand;
  int tempReorderNumber;
  double tempCostOfItem;
  double tempSellingPrice;
  
    //intialize flag variable
  int flag = 1;
  
    //get distance of array
  int d = inventoryCount;
  
    //keep sorting until complete (flag is true and d is always more than 1)
  while(flag || (d > 1))
  {
    flag = 0;
    
      //set the stage value
    d = (d + 1) / 2;
    
      //loop through inventory array
    for(i = 0; i < (inventoryCount - d); i++)
    {
        //check of selling price is more than the one next to it
        //sort into descending order
      if(inventoryData[i + d].sellingPrice > inventoryData[i].sellingPrice)
      {
          //swap inventory number
        tempInventoryNumber = inventoryData[i +d].inventoryNumber;
        inventoryData[i + d].inventoryNumber = inventoryData[i].inventoryNumber;
        inventoryData[i].inventoryNumber = tempInventoryNumber;
        
          //swap item description
        tempItemDescription = inventoryData[i +d].itemDescription;
        inventoryData[i + d].itemDescription = inventoryData[i].itemDescription;
        inventoryData[i].itemDescription = tempItemDescription;
        
          //swap quantity on hand values
        tempQuantityOnHand = inventoryData[i +d].quantityOnHand;
        inventoryData[i + d].quantityOnHand = inventoryData[i].quantityOnHand;
        inventoryData[i].quantityOnHand = tempQuantityOnHand;
        
          //swap reorder numbers
        tempReorderNumber = inventoryData[i +d].reorderNumber;
        inventoryData[i + d].reorderNumber = inventoryData[i].reorderNumber;
        inventoryData[i].reorderNumber = tempReorderNumber;
        
          //swap cost of item
        tempCostOfItem = inventoryData[i +d].costOfItem;
        inventoryData[i + d].costOfItem = inventoryData[i].costOfItem;
        inventoryData[i].costOfItem = tempCostOfItem;
        
          //swap selling price
        tempSellingPrice = inventoryData[i +d].sellingPrice;
        inventoryData[i + d].sellingPrice = inventoryData[i].sellingPrice;
        inventoryData[i].sellingPrice = tempSellingPrice;
        
        //reset flag value
        flag = 1;
      }
    }
  }
  
}

//******************************************************************************

void InventoryClass::sortInventoryNumber(int left, int right)
{
    //Receives - first and last bounds of inventory array
    //Task - sort inventory array in ascending order by inventory number
    //Returns - nothing
  
    //get bounds of array
  int i = left, j = right;
  
    //temp variables for swapping
  int tempInventoryNumber;
  string tempItemDescription;
  int tempQuantityOnHand;
  int tempReorderNumber;
  double tempCostOfItem;
  double tempSellingPrice;
  
    //create pivot point (midpoint of array)
  int pivot = inventoryData[(left + right) /2].inventoryNumber;
  
    //use the quicksort algorithm to sort by iventory number
  while(i <= j)
  {
    while(inventoryData[i].inventoryNumber < pivot)
      i++;
    while(inventoryData[j].inventoryNumber > pivot)
      j--;
      
      //test comparing values to see which one is larger
      //sort in ascending order
    if(i <= j)
    {
        //swap inventory numbers
      tempInventoryNumber = inventoryData[i].inventoryNumber;
      inventoryData[i].inventoryNumber = inventoryData[j].inventoryNumber;
      inventoryData[j].inventoryNumber = tempInventoryNumber;
      
        //swap item descriptions
      tempItemDescription = inventoryData[i].itemDescription;
      inventoryData[i].itemDescription = inventoryData[j].itemDescription;
      inventoryData[j].itemDescription = tempItemDescription;
      
        //swap quantity on hand values
      tempQuantityOnHand = inventoryData[i].quantityOnHand;
      inventoryData[i].quantityOnHand = inventoryData[j].quantityOnHand;
      inventoryData[j].quantityOnHand = tempQuantityOnHand;
      
        //swap reorder numbers
      tempReorderNumber = inventoryData[i].reorderNumber;
      inventoryData[i].reorderNumber = inventoryData[j].reorderNumber;
      inventoryData[j].reorderNumber = tempReorderNumber;
      
        //swap cost of item values
      tempCostOfItem = inventoryData[i].costOfItem;
      inventoryData[i].costOfItem = inventoryData[j].costOfItem;
      inventoryData[j].costOfItem = tempCostOfItem;
      
        //swap selling prices
      tempSellingPrice = inventoryData[i].sellingPrice;
      inventoryData[i].sellingPrice = inventoryData[j].sellingPrice;
      inventoryData[j].sellingPrice = tempSellingPrice;
      
      i++;
      j--;
    }
  }
  
    //sort left partition
  if(left < j)
  {
    sortInventoryNumber(left, j);
  }
  
    //sort right partition
  if(i < right)
  {
    sortInventoryNumber(i, right);
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
	Outfile << setw(20) << "Assignment #5" << endl;
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