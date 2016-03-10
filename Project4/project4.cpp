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
    void Print();
    bool RetrieveTop();
    bool IsEmpty(){return(TopPtr == NULL);}
    StackClass *GetTop(){return TopPtr;}
    bool IsFull();
    void ProcessEquation(ifstream &);
    
  private:
    StackClass *TopPtr;
    StackClass *next;
    vector<char> postfixExpression;
    char stackSymbol;

};

//******************************************************************************

int main()
{
  StackClass Stack;

  ifstream inputFile("data.txt");
  ofstream outputFile("output.txt");

  Stack.ProcessEquation(inputFile);
  Stack.Print();
  return 0;
}

//******************************************************************************

StackClass::StackClass()
{
  TopPtr = NULL;
  next = NULL;
}

//******************************************************************************

void StackClass::ProcessEquation(ifstream &inputFile)
{
  string myEquation;
  inputFile >> myEquation;
  
  while(myEquation != "X")
  {
    for(int x = 0; x < myEquation.length(); x++)
    {
      if(isdigit(myEquation[x]))
      {
        postfixExpression.push_back(myEquation[x]);
      }
      
      else if(myEquation[x] == '(')
      {
        Push(myEquation[x]);
      }
    }
    inputFile >> myEquation;
  }
  
  /*for(int x = 0; x < postfixExpression.size(); x++)
  {
    cout << postfixExpression[x] << endl;
  }*/
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

void StackClass::Print()
{
  StackClass *current;
  current = TopPtr;
  
  while(current != NULL)
  {
    cout << current -> stackSymbol << endl;
    current = current -> next;
  }
  return;
}

