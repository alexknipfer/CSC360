#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

class LinkedQueueClass
{
  public:
    void addCustomers(int, string, int);
    void printCustomers(ofstream &);

  private:
    int count;
    vector<int> arrivalTimes;
    vector<string> names;
    vector<int> processingTimes;
};

//******************************************************************************

int main()
{ 
  LinkedQueueClass customers;
  ifstream inputFile("queue_in.txt");
  ofstream outputFile("output.txt");
  
  int arrivalTime;
  string name;
  int processingTime;
  
  inputFile >> arrivalTime;

  while(arrivalTime != -99)
  {
    inputFile >> ws;
    getline(inputFile, name);
    inputFile >> ws;

    inputFile >> processingTime;
    
    customers.addCustomers(arrivalTime, name, processingTime);

    inputFile >> arrivalTime;
  }
  
  customers.printCustomers(outputFile);
  
  return 0;
}

//******************************************************************************

void LinkedQueueClass::printCustomers(ofstream &outputFile)
{
  for(int x = 0; x < names.size(); x++)
  {
    outputFile << names[x] << endl;
  }
}

void LinkedQueueClass::addCustomers(int arrivalTime, string name, int processingTime)
{
  arrivalTimes.push_back(arrivalTime);
  names.push_back(name);
  processingTimes.push_back(processingTime);
}