#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

//************* Create Stack Class *********************************************

  //class for stack
class StackClass
{
  public:
    StackClass();
    void Push(char);
    void Pop();
    void Print(string, ofstream &);
    void PrintEvaluationHeader(ofstream &);
    void PrintConversionHeader(ofstream &);
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
    stack <int> evaluation;
    char stackSymbol;
    int infixCount;
    int equationCount;
};

//******************************************************************************

int main()
{
    //create stack
  StackClass Stack;
  
    //create input and outputfile for data
  ifstream inputFile("data.txt");
  ofstream outputFile("output.txt");

    //print conversion header
  Stack.PrintEvaluationHeader(outputFile);

    //process infix equation
  Stack.ProcessEquation(inputFile, outputFile);

  return 0;
}

//******************************************************************************

StackClass::StackClass()
{
    //Receives - nothing
    //Task - Constructor - intializes pointers and count
    //Returns - nothing
    
    //initialize next and top pointers
  TopPtr = NULL;
  next = NULL;
  
    //intialize infix count to know when completed equation
  infixCount = 0;
}

//******************************************************************************

void StackClass::ProcessEquation(ifstream &inputFile, ofstream &outputFile)
{
    //Receives - input file, output file
    //Task - process the infix equation and convert to post fix
    //Returns - nothing
    
    //keeps track if parenthesis was found
  bool foundParen = false;
  
    //keeps track of final pop to know when all items are popped
  bool popComplete = false;
  
  string myEquation;
  
    //read in infix equation
  inputFile >> myEquation;

    //get the length of the equation to loop through
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
        //check to see if first is a number
      if(isdigit(myEquation[x]))
      {
          //add to final postfix expression
        postfixExpression.push_back(myEquation[x]);
        
          //reduce equation count to know when complete
        equationCount--;
        
          //print the new postfix and stack
        Print(myEquation, outputFile);
      }
      
        //check to see if next item is a parenthesis
      else if(myEquation[x] == '(')
      {
          //push the item to the stack
        Push(myEquation[x]);
        
          //reduce equation count to know when complete
        equationCount--;
        
          //print the new postfix and stack
        Print(myEquation, outputFile);
      }
      
        //check to see if operand is a + or -
      else if(myEquation[x] == '+' || myEquation[x] == '-')
      {
          //if the stack is empty add the operand
        if(IsEmpty())
        {
            //add the item to the stack
          Push(myEquation[x]);
          
            //reduce equation count to know when complete
          equationCount--;
          
            //print the new postfix and stack
          Print(myEquation, outputFile);
        }
        
          //if the stack is not empty do the following
        else
        {
            //check the top item in stack for parenthesis
          if(RetrieveTop() == '(')
          {
              //add the item to the stack
            Push(myEquation[x]);
            
              //reduce equation count to know when complete
            equationCount--;
            
              //print the new postfix and stack
            Print(myEquation, outputFile);
          }
          
            //check top items in stack for / or *
          else if(RetrieveTop() == '/' || RetrieveTop() == '*')
          {
              //add to final postfix expression
            postfixExpression.push_back(RetrieveTop());
              
              //pop the item off of the stack
            Pop();
            
              //add the item to the stack
            Push(myEquation[x]);
            
              //reduce the equation count to know when complete
            equationCount--;
            
              //print the new postfix and stack
            Print(myEquation, outputFile);
          }
          
            //check top items in stack for + or -
          else if(RetrieveTop() == '+' || RetrieveTop() == '-')
          {
              //add to final postfix expression
            postfixExpression.push_back(RetrieveTop());
            
              //pop item off of the stack
            Pop();
            
              //add the item to the stack
            Push(myEquation[x]);
            
              //reduce the equation count to know when complete
            equationCount--;
            
              //print the new postfix and stack
            Print(myEquation, outputFile);
          }
        }
      }
      
        //check next item in infix equation for * or /
      else if(myEquation[x] == '*' || myEquation[x] == '/')
      {
          //if the stack is empty add the operand
        if(IsEmpty())
        {
            //add item to the stack
          Push(myEquation[x]);
          
            //reduce the equation count to know when complete
          equationCount--;
          
            //print the new postfix and stack
          Print(myEquation, outputFile);
        }
        
          //do the following if the stack is NOT empty
        else
        {
            //check top item in stack for (
          if(RetrieveTop() == '(')
          {
              //push the item to the stack
            Push(myEquation[x]);
            
              //reduce the equation count to know when complete
            equationCount--;
            
              //print the new postfix and stack
            Print(myEquation, outputFile);
          }
          
            //check top item in stack for * or /
          else if(RetrieveTop() == '*' || RetrieveTop() == '/')
          {
              //add top item to final postfix expression
            postfixExpression.push_back(RetrieveTop());
            
              //pop the item off the stack
            Pop();
            
              //add item to stack
            Push(myEquation[x]);
            
              //reduce the equation count to know when complete
            equationCount--;
            
              //print the new postfix and stack
            Print(myEquation, outputFile);
          }
          
            //check top item in stack for + or -
          else if(RetrieveTop() == '+' || RetrieveTop() == '-')
          {
              //add item to stack
            Push(myEquation[x]);
            
              //reduce equation count to know when complete
            equationCount--;
            
              //print the new postfix and stack
            Print(myEquation, outputFile);
          }
        }
      }
      
        //check if next item in infix is a )
      else if(myEquation[x] == ')')
      {
          //continue popping items off stack until a matching parenthesis is found
        while(foundParen == false)
        {
            //if the top item is a closing parenthesis pop item and break out
          if(RetrieveTop() == '(')
          {
              //pop parenthesis off stack and break out of loop
            Pop();
            foundParen = true;
          }
          
            //continue adding items to postfix equation since
            //parenthesis wasn't found
          else
          {
            postfixExpression.push_back(RetrieveTop());
            Pop();
          }
        }
        
          //reset parenthesis variable
        foundParen = false;
        
          //reduce equation count
        equationCount--;
        
          //print new postfix and stack
        Print(myEquation, outputFile);
      }
    }
    
      //now the equation is complete, so pop all remaining items on stack
    while(popComplete == false)
    {
        //add remaining stack items to postfix
      postfixExpression.push_back(RetrieveTop());
      
        //pop items off stack
      Pop();
      
        //once stack is empty break out because equation is complete
      if(IsEmpty())
      {
        popComplete = true;
      }
    }
    
      //reset pop variable
    popComplete = false;
    
      //print new postfix and stack
    Print(myEquation, outputFile);
    
      //clear equation vector
    myEquation.clear();
    
      //clear character vector for equation
    equationChar.clear();
    
      //reset infix count for next expression
    infixCount = 0;
    
    outputFile << endl;
    
      //print evaluation header for equation evaluation
    PrintEvaluationHeader(outputFile);
    
      //go evaluate the expression
    EvaluateExpression(outputFile);
    
      //clear the postfix expression for next equation
    postfixExpression.clear();
    
      //get next equation
    inputFile >> myEquation;
    
      //print next header for conversion
    PrintConversionHeader(outputFile);

      //store string read in into character vector for printing
    for(int x = 0; x < myEquation.length(); x++)
    {
      equationChar.push_back(myEquation[x]);
    }
    
      //get new length of new equation
    equationCount = myEquation.length();
    
      //print initial expression of equation is still valid
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
    //Receives - character from expression
    //Task - push a item (character) to the stack
    //Returns - nothing
    
    //intiailze new pointer for stack
  StackClass *p;
  p = new StackClass;
  
    //add character to the stack (points)
  p -> stackSymbol = symbol;
  
    //adjust top pointer to adjust to top of stack
  p -> next = TopPtr;
  TopPtr = p;
  
  return;
}

//******************************************************************************

void StackClass::Pop()
{
    //Receives - nothing
    //Task - pop item (character) off the stack
    //Returns - nothing
  
  StackClass *p;
  
    //check to see if stack is empty and display error message if true
  if (IsEmpty())
	{
    cout << " Stack is empty. " << endl;
    cout << " Delete Operation Failed. " << endl;
    
      //free up space
    delete p;
    return;
  }		

    //adjust top pointer to top of stack
  p = TopPtr;	  
  TopPtr = TopPtr -> next;

    //free up space of popped item
  delete p;
  return;
}

//******************************************************************************

char StackClass::RetrieveTop()
{
    //Receives - nothing
    //Task - get top item (character) from stack
    //Returns - character on top of stack
    
  char topCharacter;
  
    //get top item
  topCharacter = TopPtr -> stackSymbol;
  
    //return the item
  return topCharacter;
}

//******************************************************************************

void StackClass::PrintConversionHeader(ofstream &outputFile)
{
    //Receives - output file
    //Task - print conversion header
    //Returns - nothing
    
  outputFile << "                         CONVERSION DISPLAY" << endl;
  outputFile << "Infix Expression         POSTFIX Expression               Stack" << endl;
  outputFile << "Contents                                               (Top to Bottom)" << endl;
  outputFile << endl;
}

//******************************************************************************

void StackClass::PrintEvaluationHeader(ofstream &outputFile)
{
    //Receives - output file
    //Task - print evaluation header
    //Returns - nothing
    
  outputFile << "                         EVALUATION DISPLAY" << endl;
  outputFile << "    POSTFIX Expression                                Stack Contents" << endl;
  outputFile << "                                                     (Top to Bottom)" << endl;
}

//******************************************************************************

void StackClass::EvaluateExpression(ofstream &outputFile)
{
    //Receives - output file
    //Task - evaluate the postfix expression
    //Returns - nothing
    
  bool evaluationComplete = false;  //checks completion of evaluation
  int firstVal;   //first value popped off stack
  int secondVal;  //second value popped off stack
  int valTotal;   //total of two values
  int spacing = 1;  //spacing for printing
  
    //print initial postfix expression
  for(int x = 0; x < postfixExpression.size(); x++)
  {
    outputFile << postfixExpression[x];
  }
  
    //print empty, stack will always start empty
  outputFile << "                        Empty" << endl;

    //keep going through postfix expression until done
  while(!postfixExpression.empty())
  {
      //print proper spacing
    for(int x = 0; x < spacing; x++)
    {
      outputFile << " ";
    }
    
      //check if first item in expression is a number
    if(isdigit(postfixExpression[0]))
    {
        //convert to integer and add to final vector
      evaluation.push(postfixExpression[0] - '0');
      
        //add item to printing vector
        
      stackContents.push_back(postfixExpression[0]);
      
        //remove first item from vector
      postfixExpression.erase(postfixExpression.begin());
      
        //print new postfix expression
      for(int y = 0; y < postfixExpression.size(); y++)
      {
        outputFile << right << postfixExpression[y];
      }
      
        //create proper spacing
      outputFile << "                             ";
      
        //print "stack" or vector items
      for (stack<int> dump = evaluation; !dump.empty(); dump.pop())
      {
        outputFile << " " << dump.top();
      }
      outputFile << endl;
    }
    
      //handle operands in expression
    else
    {
      switch(postfixExpression[0])
      {
          //the following pops the top two items off the stack,
          //then adds the 1st value to the second value,
          //then adds the final value to the final vector to print
          //values
        case '+': firstVal = evaluation.top();
                  evaluation.pop();
                  secondVal = evaluation.top();
                  evaluation.pop();
                  valTotal = secondVal + firstVal;
                  evaluation.push(valTotal);
                  break;
                  
          //the following pops the top two items off the stack,
          //then subtracts the 1st value to the second value,
          //then adds the final value to the final vector to print
          //values
        case '-': firstVal = evaluation.top();
                  evaluation.pop();
                  secondVal = evaluation.top();
                  evaluation.pop();
                  valTotal = secondVal - firstVal;
                  evaluation.push(valTotal);
                  break;
                  
          //the following pops the top two items off the stack,
          //then multiplies the 1st value to the second value,
          //then adds the final value to the final vector to print
          //values
        case '*': firstVal = evaluation.top();
                  evaluation.pop();
                  secondVal = evaluation.top();
                  evaluation.pop();
                  valTotal = secondVal * firstVal;
                  evaluation.push(valTotal);
                  break;
                  
          //the following pops the top two items off the stack,
          //then divides the 1st value to the second value,
          //then adds the final value to the final vector to print
          //values
        case '/': firstVal = evaluation.top();
                  evaluation.pop();
                  secondVal = evaluation.top();
                  evaluation.pop();
                  valTotal = secondVal / firstVal;
                  evaluation.push(valTotal);
                  break;
      }
      
        //remove first item from postfix expression
      postfixExpression.erase(postfixExpression.begin());
      
        //check if expression is complete
      if(postfixExpression.size() == 0)
      {
        outputFile << "Empty";
      }
      
        //if not complete print the expression
      else
      {
        for(int y = 0; y < postfixExpression.size(); y++)
        {
          outputFile << left << postfixExpression[y];
        }
      }
      
        //create proper spacing
      outputFile << "                             ";
      
        //print "stack" or vector items
      for(stack<int> dump = evaluation; !dump.empty(); dump.pop())
      {
        outputFile << " " << dump.top();
      }
      outputFile << endl;
      
        //check if expression is complete
      if(postfixExpression.size() == 0)
      {
        evaluation.pop();
        outputFile << "Empty                         Empty";
      }
    }
      //increase for proper spacing
    spacing++;
  }
  outputFile << endl;
}

//******************************************************************************

void StackClass::Print(string equation, ofstream &outputFile)
{
    //Receives - output file
    //Task - print expression output
    //Returns - nothing
    
    //create pointers to go through stack contents
  StackClass *current;
  current = TopPtr;

    //check if equation if complete
  if(equationCount == 0)
  {
        //print proper spacing to right align infix expression
    for(int x = 5; x < infixCount; x++)
    {
      outputFile << " ";
    }
    outputFile << "Empty";
  }
  
    //print equation / expression
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

