//*********************************************************************
//*                                                                   *
//*     FILE NAME: RetailQueue.cpp       Assignment: #4               *
//*                                                                   *
//*     AUTHOR: __________________________                            *
//*                 Tyler Knipfer                                     *
//*                                                                   *
//*     COURSE #: CSC 36000          DUE DATE: March 18th, 2013       *
//*                                                                   *
//*********************************************************************

//*********************************************************************
//* The purpose of this program is to read in from a file a cusomters *
//* arrival time, their name, and then their processing time. As the  *
//* customeres are being added to a list of arrival and departure     *
//* times they are processed based on their processing time. When     *
//* their processing time is 0 they are then added to the departure   *
//* list. After all customers are added and processed the program will*
//* finally print out two lists, one that prints the customers as they*
//* arrived and the last list is the list that shows the customers as *
//* they departed from the store.                                     *
//*********************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

    //Function Prototypes
void printHeader(ofstream &);
void printFooter(ofstream &);

class CustomerClass
{
public:
    CustomerClass();
    void addCustomer(ifstream &);
    void printData(ofstream &);
    void processLast();
    
private:
        //The three queues for the customers.
    CustomerClass *firstRoot;
    CustomerClass *nextFirst;
    CustomerClass *secondRoot;
    CustomerClass *nextSecond;
    CustomerClass *thirdRoot;
    CustomerClass *nextThird;
    
    int processingTime;
    int lineOneTotalTime;
    int lineTwoTotalTime;
    int lineThreeTotalTime;
    string customerName;
    
        //Vector to store the arrival and departure lists.
    vector<string> arrivalList;
    vector<string> departureList;    
};

int main()
{
    CustomerClass myCustomer;
    
    int arrival;
    
        //Output all data to outputFile.txt.
	ofstream outputFile("outputFile.txt");
    
        //Check for an error opening the outputFile.
	if(!outputFile)
	{
            //Print error message and exit program.
		cout << "Error opening outputfile" << endl;
		exit(1);
	}
    
        //Read all data from this file.
	ifstream inputFile("data.txt");
	
        //Check for an error opening the inputFile.
	if(!inputFile)
	{
            //Print error message and exit the program.
		cout << "Error opening inputfile" << endl;
		exit(1);
	}
    
        //Print name and class information.
	printHeader(outputFile);
    
        //Get the first arrival time.
    inputFile >> arrival;
    inputFile >> ws;
    
        //Loop through until we reach a negative arrival time.
    while(arrival > 0)
    {
            //Add the customer.
        myCustomer.addCustomer(inputFile);
        
            //Read the next arrival time.
        inputFile >> arrival;
        inputFile >> ws;
    }
    
        //Process the last customers.
    myCustomer.processLast();
    
        //Print the customer arrival
        //and departure table.
    myCustomer.printData(outputFile);    
    
        //Print message to show program completed execution.
	printFooter(outputFile);
    
        //Close the input and output files.
	outputFile.close();
	inputFile.close();
    
        //SUCCESS!!!
	return 0;
}

//********************************************************************//

CustomerClass::CustomerClass()
{
    //Receives - Nothing is received.
    
    //Task - Set all the queus to NULL and the total line times to 0.
    
    //Returns - The three queues with null values, and the line times to 0.
    
    firstRoot = NULL;
    nextFirst = NULL;
    secondRoot = NULL;
    nextSecond = NULL;
    thirdRoot = NULL;
    nextThird = NULL;
    
    lineOneTotalTime = 0;
    lineTwoTotalTime = 0;
    lineThreeTotalTime = 0;
    
    return;
}

//********************************************************************//

void CustomerClass::addCustomer(ifstream &inputFile)
{
    //Receives - The input file.
    
    //Task - Adds the customers to a queue based on the shortest line
    //time and then the customer at the front is processed first and then
    //the next customer is processed and removed from the store
    
    //Returns - The two vectors that store the arrival and departure
    //lists.
    
    CustomerClass *currentPtr;
    CustomerClass *nextPtr;
    
    string name;
    int processing;
    
        //Allocate memory for the queues.
    currentPtr = new CustomerClass;
    
        //Get the customrs information.
    getline(inputFile, name);
    inputFile >> processing;
    inputFile >> ws;
    
        //Set the customers name and processing time.
    currentPtr->customerName = name;
    currentPtr->processingTime = processing;
    
        //Add the original list of names to the arrival list.
    arrivalList.push_back(name);
    
        //Check if the first queue is empty.
    if(firstRoot == NULL)
    {
            //Set the current pointer to the first node. 
        firstRoot = currentPtr;
        
            //Start processing the customer.
        currentPtr->processingTime--;
        
            //Update the total line time for line one.
        lineOneTotalTime += currentPtr->processingTime;
        
            //Add the customer to the departure list.
        departureList.push_back(name);
    }
    
        //Check if the second queue is empty.
    else if(secondRoot == NULL)
    {
            //Set the second node to current pointer.
        secondRoot = currentPtr;
        
            //Start processing the customer. 
        currentPtr->processingTime--;
        
            //Update the line two total time.
        lineTwoTotalTime += currentPtr->processingTime;
        
            //Add customer to the departure list. 
        departureList.push_back(name);
    }
    
        //Check if the third queue is empty.
    else if(thirdRoot == NULL)
    {
            //Set the current pointer to the third node. 
        thirdRoot = currentPtr;
        
            //Start processing the customer.
        currentPtr->processingTime--;
        
            //Update the line three total time. 
        lineThreeTotalTime += currentPtr->processingTime;
        
            //Add customer to departure list. 
        departureList.push_back(name);
    }
    
        //Check if line one is the shortest time.
    else if(lineOneTotalTime < lineTwoTotalTime && lineOneTotalTime < lineThreeTotalTime)
    {
            //Start at the first node of line one.
        nextPtr = firstRoot;
        
            //Keep looping through while there are customers. 
        while(nextPtr->nextFirst != NULL)
        {
                //Go to the next customer.
            nextPtr = nextPtr->nextFirst;
            
                //Check if they have been processed.
            if(nextPtr->processingTime != 0)
            {
                    //Process customer.
                while(nextPtr->processingTime != 0)
                    nextPtr->processingTime--;
                
                    //Add to departure list, if they are processed.
                if(nextPtr->processingTime == 0)
                {
                    departureList.push_back(nextPtr->customerName);
                }
            }
        }
        
            //Set the back of the list ot the current pointer. 
        nextPtr->nextFirst = currentPtr;
        
            //Update the line one total time.
        lineOneTotalTime += currentPtr->processingTime;
    }

        //Check if line two is the shortest time.
    else if(lineTwoTotalTime < lineOneTotalTime && lineTwoTotalTime < lineThreeTotalTime)
    {
            //Start at the second node. 
        nextPtr = secondRoot;
        
            //Make sure there are customers still.
        while(nextPtr->nextSecond != NULL)
        {
                //Go to the next node.
            nextPtr = nextPtr->nextSecond;
            
                //Check if they need processed.
            if(nextPtr->processingTime != 0)
            {
                    //Process the customer. 
                while(nextPtr->processingTime != 0)
                    nextPtr->processingTime--;
                
                    //Add customer to departure list. 
                if(nextPtr->processingTime == 0)
                {
                    departureList.push_back(nextPtr->customerName);
                }
            }
        }
        
            //Update the queue. 
        nextPtr->nextSecond = currentPtr;
        
            //Update the line two total time. 
        lineTwoTotalTime += currentPtr->processingTime;
    }
    
        //Check if line three is the shortest. 
    else if(lineThreeTotalTime < lineOneTotalTime && lineThreeTotalTime < lineTwoTotalTime)
    {
            //Start at the front. 
        nextPtr = thirdRoot;
        
            //Make sure there are still customers. 
        while(nextPtr->nextThird != NULL)
        {
                //Go to the next node.
            nextPtr = nextPtr->nextThird;
            
                //Check if the customer needs processed. 
            if(nextPtr->processingTime != 0)
            {
                    //Process the customer. 
                while(nextPtr->processingTime != 0)
                    nextPtr->processingTime--;
                
                    //Add customer to departure list. 
                if(nextPtr->processingTime == 0)
                {
                    departureList.push_back(nextPtr->customerName);
                }
            }
        }
        
            //Update the queue.
        nextPtr->nextThird = currentPtr;
        
            //Update line three time.
        lineThreeTotalTime += currentPtr->processingTime;
    }
    
        //Check if line one equals line two and three.
    else if(lineOneTotalTime == lineTwoTotalTime && lineOneTotalTime == lineThreeTotalTime)
    {
            //Start at the first node. 
        nextPtr = firstRoot;
        
            //Check if there are still customers.
        while(nextPtr->nextFirst != NULL)
        {
                //Go to the next node.
            nextPtr = nextPtr->nextFirst;
            
                //Check if the customer needs processed. 
            if(nextPtr->processingTime != 0)
            {
                    //Process the customer.
                while(nextPtr->processingTime != 0)
                    nextPtr->processingTime--;
                
                    //Add the customer to departure list. 
                if(nextPtr->processingTime == 0)
                {
                    departureList.push_back(nextPtr->customerName);
                }
            }
        }
        
            //Update the queue. 
        nextPtr->nextFirst = currentPtr;
        
            //Update line one total time.
        lineOneTotalTime += currentPtr->processingTime;
    }
    
        //Check if line two is equal to line one and three.
    else if(lineTwoTotalTime == lineOneTotalTime && lineTwoTotalTime == lineThreeTotalTime)
    {
            //Start at the second node.
        nextPtr = secondRoot;
        
            //Check if there are still customers in queue. 
        while(nextPtr->nextSecond != NULL)
        {
                //Go to the next node.
            nextPtr = nextPtr->nextSecond;
            
                //Check if the customer needs processed. 
            if(nextPtr->processingTime != 0)
            {
                    //Process the customer. 
                while(nextPtr->processingTime != 0)
                    nextPtr->processingTime--;
                
                    //Add customer to departure list. 
                if(nextPtr->processingTime == 0)
                {
                    departureList.push_back(nextPtr->customerName);
                }
                
            }
        }
        
            //Update the queue. 
        nextPtr->nextSecond = currentPtr;
        
            //Update line two total time. 
        lineTwoTotalTime += currentPtr->processingTime;
    }
    
        //Check if line three is equal to line one and line three. 
    else
    {
            //Start at the thrid node. 
        nextPtr = thirdRoot;
        
            //Check if there are still customers. 
        while(nextPtr->nextThird != NULL)
        {
                //Go to the next node.
            nextPtr = nextPtr->nextThird;
            
                //Check if customer needs processed. 
            if(nextPtr->processingTime != 0)
            {
                    //Process the customer.
                while(nextPtr->processingTime != 0)
                    nextPtr->processingTime--;
                
                    //Add customer to departure list.
                if(nextPtr->processingTime == 0)
                {
                    departureList.push_back(nextPtr->customerName);
                }                
            }
        }
        
            //Update the queue. 
        nextPtr->nextThird = currentPtr;
        
            //Update line three total time.
        lineThreeTotalTime += currentPtr->processingTime;
    }

    return;
}

//********************************************************************//

void CustomerClass::processLast()
{
    //Receives - Nothing is received.
    
    //Task - Process the last customers in the queues if there are any.
    
    //Returns - The updated departure list. 
    
    CustomerClass *first, *second, *third;
    
    first = firstRoot;
    second = secondRoot;
    third = thirdRoot;
    
        //Go to the last customer in the first queue.
    while(first->nextFirst != NULL)
    {
        first = first->nextFirst;
    }
    
        //Go to the last customer in the second queue. 
    while(second->nextSecond != NULL)
    {
        second = second->nextSecond;
    }
    
        //Go to the last customer in the third queue. 
    while(third->nextThird != NULL)
    {
        third = third->nextThird;
    }
    
        //Add the customers to the list 
    departureList.push_back(first->customerName);
    departureList.push_back(second->customerName);
    departureList.push_back(third->customerName);
    
    return;
}

//********************************************************************//

void CustomerClass::printData(ofstream &outputFile)
{    
    //Receives - The output file.
    
    //Task - Print out the departure and arrival lists.
    
    //Returns - The updated output file.    
    
        //Print the table heading.
    outputFile << "The order of customer arrival is:";
    outputFile << "     |     The order of customer departure is:";
    outputFile << endl;
    
        //Loop through all of the customers.
    for(int x = 0; x < arrivalList.size(); x++)
    {
            //Print the customers names for the arrival and
            //departure lists.
        outputFile << "        " << arrivalList[x];
        outputFile << "     |             ";
        outputFile << departureList[x];
        outputFile << endl;
    }
}

//********************************************************************//
/*
 * Print out all of my information including my name,
 * and all other class information.
 */
//********************************************************************//
void printHeader(ofstream &outFile)
{
    //Receives the output file
    //Task - Prints the output file
    //Return - nothing
    
    outFile << setw(32) << "Tyler Knipfer";
    outFile << setw(17) << "CSC 36000";
    outFile << setw(15) << "Section 11" << endl;
    outFile << setw(30) << "Spring 2013";
    outFile << setw(20) << "Assignment #4" << endl;
    outFile << setw(35) << "---------------------------------------";
    outFile << setw(35) << "-----------------------------------\n\n";
    
    return;
}

//********************************************************************//
/*
 * Print out a message to show that the program
 * completed successfully.
 */
//********************************************************************//
void printFooter(ofstream &outFile)
{
    //Receives - the output file
    //Task - prints the program footer
    //Returns - nothing
    
    outFile << endl;
    outFile << setw(35) << "-----------------------------------------";
    outFile << endl;
    outFile << setw(35) << "|       END OF PROGRAM OUTPUT           |";
    outFile << endl;
    outFile << setw(35) << "-----------------------------------------";
    outFile << endl;
    
    return;
}

//********************************************************************//