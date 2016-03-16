#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

//************* Create Stack Class *********************************************


class StackClass
{
  public:
    StackClass();
    void Push(char);
    void Pop();
    void Print(string, ofstream &);
    void PrintEvaluationHeader(ofstream &);
    char RetrieveTop();
    bool IsEmpty(){return(TopPtr == NULL);}
    StackClass *GetTop(){return TopPtr;}
    bool IsFull();
    void ProcessEquation(ifstream &, ofstream &);
    void EvaluateExpression(ofstream &);
    
  private:
    StackClass *TopPtr;
    StackClass *next;
    vector<char> postfixExpression;
    vector <char> equationChar;
    vector <char> stackContents;
    stack <char> evaluation;
    char stackSymbol;
    int infixCount;
    int equationCount;
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
  bool foundParen = false;
  bool popComplete = false;
  string myEquation;
  inputFile >> myEquation;

  equationCount = myEquation.length();

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
        equationCount--;
        Print(myEquation, outputFile);
      }
      
      else if(myEquation[x] == '(')
      {
        Push(myEquation[x]);
        equationCount--;
        Print(myEquation, outputFile);
      }
      
        //check to see if operand is a + or -
      else if(myEquation[x] == '+' || myEquation[x] == '-')
      {
          //if the stack is empty add the operand: Step 5.1
        if(IsEmpty())
        {
          Push(myEquation[x]);
          equationCount--;
          Print(myEquation, outputFile);
        }
        
          //if the stack is not empty do the following: Step 5.2
        else
        {
          if(RetrieveTop() == '(')
          {
            Push(myEquation[x]);
            equationCount--;
            Print(myEquation, outputFile);
          }
          
            //Step 5.2.3
          else if(RetrieveTop() == '/' || RetrieveTop() == '*')
          {
            postfixExpression.push_back(RetrieveTop());
            Pop();
            Push(myEquation[x]);
            equationCount--;
            Print(myEquation, outputFile);
          }
          
          else if(RetrieveTop() == '+' || RetrieveTop() == '-')
          {
            postfixExpression.push_back(RetrieveTop());
            Pop();
            Push(myEquation[x]);
            equationCount--;
            Print(myEquation, outputFile);
          }
        }
      }
      
      else if(myEquation[x] == '*' || myEquation[x] == '/')
      {
          //if the stack is empty add the operand: Step 5.1
        if(IsEmpty())
        {
          Push(myEquation[x]);
          equationCount--;
          Print(myEquation, outputFile);
        }
        
        else
        {
          if(RetrieveTop() == '(')
          {
            Push(myEquation[x]);
            equationCount--;
            Print(myEquation, outputFile);
          }
          
          else if(RetrieveTop() == '*' || RetrieveTop() == '/')
          {
            postfixExpression.push_back(RetrieveTop());
            Pop();
            Push(myEquation[x]);
            equationCount--;
            Print(myEquation, outputFile);
          }
          
          else if(RetrieveTop() == '+' || RetrieveTop() == '-')
          {
            Push(myEquation[x]);
            equationCount--;
            Print(myEquation, outputFile);
          }
        }
      }
      
      else if(myEquation[x] == ')')
      {
        while(foundParen == false)
        {
          if(RetrieveTop() == '(')
          {
            Pop();
            foundParen = true;
          }
          
          else
          {
            postfixExpression.push_back(RetrieveTop());
            Pop();
          }
        }
        foundParen = false;
        equationCount--;
        Print(myEquation, outputFile);
      }
    }
    
    while(popComplete == false)
    {
      postfixExpression.push_back(RetrieveTop());
      Pop();
      if(IsEmpty())
      {
        popComplete = true;
      }
    }
    
    popComplete = false;
    
    Print(myEquation, outputFile);
    myEquation.clear();
    equationChar.clear();
    infixCount = 0;
    outputFile << endl;
    
    PrintEvaluationHeader(outputFile);
    EvaluateExpression(outputFile);
    postfixExpression.clear();
    
    inputFile >> myEquation;

          //store string read in into character vector for printing
    for(int x = 0; x < myEquation.length(); x++)
    {
      equationChar.push_back(myEquation[x]);
    }
    
    equationCount = myEquation.length();
    
    if(myEquation != "X")
    {
         //print initial infix expression
      Print(myEquation, outputFile);
    }
  
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

  p = TopPtr;	  
  TopPtr = TopPtr -> next;

  delete p;
  return;
}

//******************************************************************************

char StackClass::RetrieveTop()
{
  char topCharacter;
  
  topCharacter = TopPtr -> stackSymbol;
  
  return topCharacter;
}

//******************************************************************************

void StackClass::PrintEvaluationHeader(ofstream &outputFile)
{
  outputFile << "                         EVALUATION DISPLAY" << endl;
  outputFile << "    POSTFIX Expression                                Stack Contents" << endl;
  outputFile << "                                                     (Top to Bottom)" << endl;
}

//******************************************************************************

void StackClass::EvaluateExpression(ofstream &outputFile)
{
  bool evaluationComplete = false;
  int count = 0;
  int firstVal;
  int secondVal;
  
  for(int x = 0; x < postfixExpression.size(); x++)
  {
    outputFile << postfixExpression[x];
  }
  
  outputFile << "                        Empty" << endl;
  evaluation.push(postfixExpression.front());
  stackContents.push_back(postfixExpression.front());
  postfixExpression.erase(postfixExpression.begin());
  
  while(!postfixExpression.empty())
  {
    if(isdigit(postfixExpression[count]))
    {
      evaluation.push(postfixExpression[count]);
      stackContents.push_back(postfixExpression[count]);
      for(int y = 0; y < postfixExpression.size(); y++)
      {
        outputFile << right << postfixExpression[y];
      }
      postfixExpression.erase(postfixExpression.begin());
      for(int x = stackContents.size(); x --> 0;)
      {
        outputFile << " " << stackContents[x];
      }
      outputFile << endl;
    }
    
    else
    {
      for(int y = 0; y < postfixExpression.size(); y++)
      {
        outputFile << left << postfixExpression[y];
      }
      postfixExpression.erase(postfixExpression.begin());
      cout << postfixExpression[count] << endl;
      outputFile << endl;
    }
    count++;
  }
  
}

//******************************************************************************

void StackClass::Print(string equation, ofstream &outputFile)
{
  StackClass *current;
  current = TopPtr;

  if(equationCount == 0)
  {
        //print proper spacing to right align infix expression
    for(int x = 5; x < infixCount; x++)
    {
      outputFile << " ";
    }
    outputFile << "Empty";
  }
  
  else
  {
        //print proper spacing to right align infix expression
    for(int x = 0; x < infixCount; x++)
    {
      outputFile << right << setw(1) << " ";
    }
    
      //print infix expression
    for(int x = infixCount; x < equationChar.size(); x++)
    {
      outputFile << equationChar[x];
    }
  }

    //if the postfix expression consists of nothing print empty
  if(postfixExpression.empty())
  {
    outputFile << left << setw(20) << " " << "Empty";
  }
  
    //print postfix expression vector
  else
  {
      //create proper spacing before postfix expression
    outputFile << left << setw(20) << " ";
    for(int x = 0; x < postfixExpression.size(); x++)
    {
      outputFile << postfixExpression[x];
    }
  }
  
    //if stack is empty print empty
  if(IsEmpty())
  {
    outputFile << left << setw(30-postfixExpression.size()) << " " << "Empty";
  }
  
    //print stack contents if it is not empty
  else
  {
    outputFile << left << setw(30-postfixExpression.size()) << " ";
    while(current != NULL)
    {
      outputFile << current -> stackSymbol;
      current = current -> next;
    }
  }
  
    //increment infix count for printing infix expression
  if(equationCount != 0)
  {
    infixCount++;
  }
  outputFile << endl;
  return;
}

