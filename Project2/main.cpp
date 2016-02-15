//*********************************************************************
//*                                                                   *
//*     FILE NAME: main.cpp       Assignment: #3                      *
//*                                                                   *
//*     AUTHOR: __________________________                            *
//*                 Tyler Knipfer                                     *
//*                                                                   *
//*     COURSE #: CSC 36000          DUE DATE: March 4th, 2013        *
//*                                                                   *
//*********************************************************************

//***********************Program Description***************************
//* The purpose of this program is to read in customers information   *
//* for a mailing list database that will store all of their data in  *
//* a linked list. As the data is read into the program a decision    *
//* will be made on what it is supposed to do with the data. An 'A'   *
//* means that the customer will be added to the database. An 'D'     *
//* means that the customer will be removed from the database. An 'P' *
//* means that the data will be printed out in a table format of all  *
//* the customers that are currently in the database. An 'C' means    *
//* that some information about the customer needs to be changed and  *
//* that new information is read in from the file. When a 'Q' is read *
//* in the program will stop reading and terminate. The program can   *
//* process any amount of customers as long as there is enough memory *
//* on the computer. It will continue to update, print and add        *
//* customers to the list as long as it does not read in the letter Q *
//*********************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

    //Function Prototypes
void printHeader(ofstream &);
void printFooter(ofstream &);

    //Class definition
class MailingListClass
{
    
public:
    MailingListClass();
    void addRecord(ifstream &, ofstream &);
    void deleteRecord(ifstream &, ofstream &);
    void changeRecord(ifstream &, ofstream &);
    void printRecord(ofstream &);
    
private:
    MailingListClass *rootNode;
    MailingListClass *nextNode;
    string firstName;
    string lastName;
    string streetAddress;
    string city;
    string state;
    string zipCode;
};

int main(int argc, char *argv[])
{
    MailingListClass myMailingList;
    
    char transType;
    
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
    
        //Read in the first trasaction type;
    inputFile >> transType;
    inputFile >> ws;
    
        //Continue to read from file until we reach a Q
        //which means stop reading.
    while(transType != 'Q')
    {
        switch(transType)
        {
                //Print out the record.
            case 'P':
                myMailingList.printRecord(outputFile);
                break;
                
                //Add a record to database.
            case 'A':
                myMailingList.addRecord(inputFile, outputFile);
                break;
                
                //Delete a record from the database.
            case 'D':
                myMailingList.deleteRecord(inputFile, outputFile);
                break;
                
                //Change a record in the database.
            case 'C':
                myMailingList.changeRecord(inputFile, outputFile);
                break;
                
                //Print error message showing invalid transaction.
            default:
                cout << "Invalid Transaction Type" << endl;
                break;
        }
        
            //Read in the next transaction type.
        inputFile >> transType;
        inputFile >> ws;
    }
    
    
	
        //Print message to show program executed
        //successfully.
	printFooter(outputFile);
	
        //Close the input and output files.
	inputFile.close();
	outputFile.close();
    
    //SUCCESS!!!
	return 0;
}

//********************************************************************//

MailingListClass::MailingListClass()
{
    //Receives - Nothing is received.
    
    //Task - Set the root and next node to NULL.
    
    //Returns - The two nodes with the value of NULL.
    
        //Set the root and next node to NULL
        //to start off with.
    rootNode = NULL;
    nextNode = NULL;
    
    return;
}

//********************************************************************//

void MailingListClass::printRecord(ofstream &outputFile)
{
    //Receives - Output file
    
    //Task - To print out a heading and the information for the database.
    
    //Returns - The new information in the file.
    
        //Pointer to travel through the list.
    MailingListClass *travelingPtr;
    
        //Set the traveling pointer to the first
        //node in the list.
    travelingPtr = rootNode;
    
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
    
        //Print out the mailing list while the list
        //still has something in it.
    while(travelingPtr != NULL)
    {
            //Check to see if the customer has been deleted
            //from the database and if so skip them.
        if(travelingPtr->firstName == "DELETED")
        {
                //Go to the next node.
            travelingPtr = travelingPtr->nextNode;
        }
        
            //Print out the customers information lined up with
            //the table.
        else
        {
            outputFile << travelingPtr->lastName;
            outputFile << "       ";
            outputFile << travelingPtr->firstName;
            outputFile << "  ";
            outputFile << travelingPtr->streetAddress;
            outputFile << "   ";
            outputFile << travelingPtr->city;
            outputFile << "  ";
            outputFile << travelingPtr->state;
            outputFile << "        ";
            outputFile << travelingPtr->zipCode;
            outputFile << endl;
    
                //Travel to the next node.
            travelingPtr = travelingPtr->nextNode;
        }
    }
    
        //Seperate the data on a new line.
    for(int x = 0; x < 30; x++)
    {
        outputFile << endl;
    }
    
    return;
}

//********************************************************************//

void MailingListClass::addRecord(ifstream &inputFile, ofstream &outputFile)
{
    //Receives - Input file.
    
    //Task - Add a record to the database keeping it in sorted order
    //according to last name.
    
    //Returns - The new customers information in sorted order.
    
    MailingListClass *nextPtr, *currentPtr;
    
        //Temp values for swapping names.
    string tempLast;
    string tempFirst;
    string tempAddress;
    string tempCity;
    string tempState;
    string tempZip;
    
        //Customer information to read in.
    string fName;
    string lName;
    string stAddr;
    string cty;
    string myState;
    string myZip;
    
        //Create a new mailing list to add to.
    currentPtr = new MailingListClass;
    
        //Read in the customers information from the file.
    getline(inputFile, fName);
    getline(inputFile, lName);
    getline(inputFile, stAddr);
    getline(inputFile, cty);
    getline(inputFile, myState);
    getline(inputFile, myZip);
    
        //Check for duplicate customers.
    if(fName == currentPtr->firstName && lName == currentPtr->lastName)
    {
        outputFile << "Already exists, error adding to database";
        outputFile << endl << endl << endl;
    }
    
    else
    {
            //Add the customer.
        currentPtr->firstName = fName;
        currentPtr->lastName = lName;
        currentPtr->streetAddress = stAddr;
        currentPtr->city = cty;
        currentPtr->state = myState;
        currentPtr->zipCode = myZip;
    }
    
        //Check to see if the list is empty.
    if(rootNode == NULL)
    {
            //Add the first node to the list.
        rootNode = currentPtr;
    }
    
    else
    {
            //Set the next node to the first node.
        nextPtr = rootNode;
        
            //Loop through while something is in the list.
        while(nextPtr->nextNode != NULL)
        {
                //Check to see if the names need swapped.
            if(currentPtr->lastName < nextPtr->lastName)
            {
                    //Swap last names.
                tempLast = currentPtr->lastName;
                currentPtr->lastName = nextPtr->lastName;
                nextPtr->lastName = tempLast;
                
                    //Swap first names.
                tempFirst = currentPtr->firstName;
                currentPtr->firstName = nextPtr->firstName;
                nextPtr->firstName = tempFirst;
                
                    //Swap the address.
                tempAddress = currentPtr->streetAddress;
                currentPtr->streetAddress = nextPtr->streetAddress;
                nextPtr->streetAddress = tempAddress;
                
                    //Swap the city.
                tempCity = currentPtr->city;
                currentPtr->city = nextPtr->city;
                nextPtr->city = tempCity;
                
                    //Swap the state.
                tempState = currentPtr->state;
                currentPtr->state = nextPtr->state;
                nextPtr->state = tempState;
                
                    //Swap the zip code.
                tempZip = currentPtr->zipCode;
                currentPtr->zipCode = nextPtr->zipCode;
                nextPtr->zipCode = tempZip;
            }
            
                //Go to the next node in the list.
            nextPtr = nextPtr->nextNode;
        }
        
            //Set the next node to the current pointer.
        nextPtr->nextNode = currentPtr;
    }
    
    return;
}

//********************************************************************//

void MailingListClass::deleteRecord(ifstream &inputFile, ofstream &outputFile)
{
    //Receives - The input and output files.
    
    //Task - Delete a customer from the database.
    
    //Returns - The customers first names is now DELETED.
    
    MailingListClass *travelingPtr;
    
        //Set the traveling pointer to the first node in the list.
    travelingPtr = rootNode;
    
    string first;
    string last;
    
        //Read in the first and last name to be deleted.
    getline(inputFile, first);
    getline(inputFile, last);
    
        //Loop throught the list until the end is reached.
    while(travelingPtr != NULL)
    {        
        if(travelingPtr->firstName == first && travelingPtr->lastName == last)
        {
                //Set the first name to DELETED.
            travelingPtr->firstName = "DELETED";
        }
        
            //Go to the next item in the list.
        travelingPtr = travelingPtr->nextNode;
    }
    
    return;
}

//********************************************************************//

void MailingListClass::changeRecord(ifstream &inputFile, ofstream &outputFile)
{
    //Receives - The input and output files.
    
    //Task - To change the customers information based on what is read
    //in from the file and then change that piece of information.
    
    //Returns - The new information for the customer.
    
    MailingListClass *travelingPtr;
    
    string first;
    string last;
    string newInformation;
    int fieldNumber;
    
        //Set the traveling pointer to the first item in the list.
    travelingPtr = rootNode;
    
        //Read in the first and last name along with the field number
        //and new information to be changed.
    getline(inputFile, first);
    getline(inputFile, last);
    inputFile >> fieldNumber;
    inputFile >> ws;
    getline(inputFile, newInformation);
    
        //Loop through until the end of the list is reached.
    while(travelingPtr != NULL)
    {
            //Check to see if that customer has been deleted.
        if(travelingPtr->firstName == "DELETED")
        {
                //Print an error message showing that they can not change
                //something that does not exist.
            outputFile << "Attempt to change a non existent record";
            outputFile << endl << endl << endl;
            
                //Go to the next item in the list.
            travelingPtr = travelingPtr->nextNode;
        }
        
        else
        {
                //Check if we found the correct customer.
            if(travelingPtr->firstName == first && travelingPtr->lastName == last)
            {
                switch(fieldNumber)
                {
                    case 1:
                            //Change the first name.
                        travelingPtr->firstName = newInformation;
                        break;
                        
                    case 2:
                            //Change the last name.
                        travelingPtr->lastName = newInformation;
                        break;
                        
                    case 3:
                            //Change the street address.
                        travelingPtr->streetAddress = newInformation;
                        break;
                        
                    case 4:
                            //Change the city.
                        travelingPtr->city = newInformation;
                        break;
                        
                    case 5:
                            //Change the state.
                        travelingPtr->state = newInformation;
                        break;
                        
                    case 6:
                            //Change the zipCode.
                        travelingPtr->zipCode = newInformation;
                        break;
                }
            }
            
                //Go to the next item in the list.
            travelingPtr = travelingPtr->nextNode;
        }
    }
    
    return;
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
    outFile << setw(20) << "Assignment #3" << endl;
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