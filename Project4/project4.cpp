#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

//************* Create Stack Class *********************************************


class StackClass
{
  public:
    StackClass();
    void Push(char);
    void Pop();
    void Print(string, ofstream &);
    bool RetrieveTop();
    bool IsEmpty(){return(TopPtr == NULL);}
    StackClass *GetTop(){return TopPtr;}
    bool IsFull();
    void ProcessEquation(ifstream &, ofstream &);
    
  private:
    StackClass *TopPtr;
    StackClass *next;
    vector<char> postfixExpression;
    vector <char> equationChar;
    char stackSymbol;
    int infixCount;

};

//******************************************************************************

int main()
{
  StackClass Stack;

  ifstream inputFile("data.txt");
  ofstream outputFile("output.txt");

  outputFile << "                         CONVERSION DISPLAY" << endl;
  outputFile << "Infix Expression         POSTFIX Expression               Stack" << endl;
  outputFile << "Contents                                               (Top to Bottom)" << endl;
  outputFile << endl;

  Stack.ProcessEquation(inputFile, outputFile);

  //Stack.Print();
  return 0;
}

//******************************************************************************

StackClass::StackClass()
{
  TopPtr = NULL;
  next = NULL;
  infixCount = 0;
}

//******************************************************************************

void StackClass::ProcessEquation(ifstream &inputFile, ofstream &outputFile)
{
  string myEquation;
  inputFile >> myEquation;
  
    //store string read in into character vector for printing
  for(int x = 0; x < myEquation.length(); x++)
  {
    equationChar.push_back(myEquation[x]);
  }
  
    //print initial infix expression
  Print(myEquation, outputFile);

    //loop through infix expressions until an X is read in then stop
  while(myEquation != "X")
  {
      //go through infix expression operators and operands
    for(int x = 0; x < myEquation.length(); x++)
    {
      if(isdigit(myEquation[x]))
      {
        postfixExpression.push_back(myEquation[x]);
        Print(myEquation, outputFile);
        return;
      }
      
      else if(myEquation[x] == '(')
      {
        Push(myEquation[x]);
        Print(myEquation, outputFile);
      }
    }
    inputFile >> myEquation;
  }
}

//******************************************************************************

void StackClass::Push(char symbol)
{
  StackClass *p;
  p = new StackClass;
  
  p -> stackSymbol = symbol;
  p -> next = TopPtr;
  TopPtr = p;
  
  return;
}

//******************************************************************************

void StackClass::Pop()
{
  StackClass *p ;
  if (IsEmpty() )
	{
    cout << " Stack is empty. " << endl;
    cout << " Delete Operation Failed. " << endl;
    delete p;
    return;
  }		
              // Save element in the first node
  //symbol = TopPtr -> stackSymbol; 
              // Adjust Stack Top
  p = TopPtr;	  
  TopPtr = TopPtr -> next;

  delete p;
  return;
}

//******************************************************************************

void StackClass::Print(string equation, ofstream &outputFile)
{
  StackClass *current;
  current = TopPtr;

    //print proper spacing to right align infix expression
  for(int x = 0; x < infixCount; x++)
  {
    outputFile << " ";
  }
  
    //print infix expression
  for(int x = infixCount; x < equationChar.size(); x++)
  {
    outputFile << equationChar[x];
  }
  
    //if the postfix expression consists of nothing print empty
  if(postfixExpression.empty())
  {
    outputFile << "                       Empty                       ";
  }
  
    //print postfix expression vector
  else
  {
      //create proper spacing before postfix expression
    outputFile << "                       ";
    for(int x = 0; x < postfixExpression.size(); x++)
    {
      outputFile << postfixExpression[x];
    }
    outputFile << "                             ";
  }
  
    //if stack is empty print empty
  if(IsEmpty())
  {
    outputFile << "Empty ";
  }
  
    //print stack contents if it is not empty
  else
  {
    while(current != NULL)
    {
      outputFile << current -> stackSymbol;
      current = current -> next;
    }
  }
  
    //increment infix count for printing infix expression
  infixCount++;
  outputFile << endl;
  return;
}

