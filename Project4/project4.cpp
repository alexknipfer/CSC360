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
  
  for(int x = 0; x < myEquation.length(); x++)
  {
    equationChar.push_back(myEquation[x]);
  }
  
  Print(myEquation, outputFile);

  while(myEquation != "X")
  {
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

void StackClass::Print(string equation, ofstream &outputFile)
{
  StackClass *current;
  current = TopPtr;

  for(int x = 0; x < infixCount; x++)
  {
    outputFile << " ";
  }
  
  for(int x = infixCount; x < equationChar.size(); x++)
  {
    outputFile << equationChar[x];
  }
  
  if(postfixExpression.empty())
  {
    outputFile << "                       Empty                       ";
  }
  
  else
  {
    outputFile << "                       ";
    for(int x = 0; x < postfixExpression.size(); x++)
    {
      outputFile << postfixExpression[x];
    }
    outputFile << "                             ";
  }
  
  if(IsEmpty())
  {
    outputFile << "Empty ";
  }
  
  else
  {
    while(current != NULL)
    {
      outputFile << current -> stackSymbol;
      current = current -> next;
    }
  }
  
  infixCount++;
  outputFile << endl;
  return;
}

