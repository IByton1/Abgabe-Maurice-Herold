// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

/************** begin assignment **************/
// In Reverse Polish Notation, the operators follow their operands; for
// instance, to add 3 and 4, one would write 3 4 + rather than 3 + 4. If there
// are multiple operations, operators are given immediately after their second
// operands; so the expression written 3 − 4 + 5 in conventional notation would be
// written 3 4 − 5 + in reverse Polish notation: 4 is first subtracted from 3,
// hen 5 is added to it. An advantage of reverse Polish notation is that it removes
// the need for parentheses that are required by infix notation. While 3 − 4 * 5
// can also be written 3 − (4 * 5), that means something quite different from (3 − 4) * 5.
// In reverse Polish notation, the former could be written 3 4 5 * −, which
// unambiguously means 3 (4 5 *) − which reduces to 3 20 − (which can further be reduced to -17);
// the latter could be written 3 4 − 5 * (or 5 3 4 − *, if keeping similar formatting),
// which unambiguously means (3 4 −) 5 *.
// see also: https://en.wikipedia.org/wiki/Reverse_Polish_notation
//
// Write a program that takes an arithmetical expression in Reverse Polish
// Notation (RPN) and returns the signed integer that the expression evaluates
// to.
// - allowed mathematical operators are: + - * /
// - numbers (operands) and operators are separated by spaces
// - use a "stringstream" for separating the input tokens (numbers and operators)
//   https://www.geeksforgeeks.org/stringstream-c-applications/
// - use a stack<int> for stacking the numbers

/*
Initialize a stack to store the numbers.
Initialize a stringstream with the RPN expression.
Loop through the tokens in the RPN expression.
If the token is an operator, pop the top two numbers from the stack, perform the operation, and push the result onto the stack.
If the token is a number, push it onto the stack.
The result is the only number remaining on the stack.
*/

int eval_rpn(const string &rpn_expression)
{
  // Creates a stack of integers to store the operands of the RPN expressions and perform arithmetic operations.
  stack<int> numbers;

  // Creates a stringstream to read the RPN string.
  stringstream ss{rpn_expression};

  // Iterates through each token in the RPN string.
  while (ss.good())
  {
    // Gets the next token.
    string token;
    ss >> token;

    // If the token is an arithmetic operator (+, -, *, /), the two topmost elements are removed from the stack and the operation is performed on them. The result is pushed back onto the stack.
    if (token == "+")
    {
      int a = numbers.top();
      numbers.pop();
      int b = numbers.top();
      numbers.pop();
      numbers.push(a + b);
    }
    else if (token == "-")
    {
      int a = numbers.top();
      numbers.pop();
      int b = numbers.top();
      numbers.pop();
      numbers.push(b - a);
    }
    else if (token == "*")
    {
      int a = numbers.top();
      numbers.pop();
      int b = numbers.top();
      numbers.pop();
      numbers.push(a * b);
    }
    else if (token == "/")
    {
      int a = numbers.top();
      numbers.pop();
      int b = numbers.top();
      numbers.pop();
      numbers.push(b / a);
    }
    // If the token is a number, it is pushed onto the stack.
    else
    {
      numbers.push(stoi(token));
    }
  }

  // Returns the only element left in the stack, which is the final result.
  return numbers.top();
}

/*************** end assignment ***************/

int main()
{
  {
    string rpn_expression = "5";
    assert(eval_rpn(rpn_expression) == 5);
  }
  {
    string rpn_expression = "6 7 -";
    assert(eval_rpn(rpn_expression) == -1);
  }
  {
    string rpn_expression = "1 2 +";
    assert(eval_rpn(rpn_expression) == 3);
  }
  {
    string rpn_expression = "6 2 *";
    assert(eval_rpn(rpn_expression) == 12);
  }
  {
    string rpn_expression = "12 2 /";
    assert(eval_rpn(rpn_expression) == 6);
  }
  {
    string rpn_expression = "12 2 /";
    assert(eval_rpn(rpn_expression) == 6);
  }
  {
    string rpn_expression = "3 4 + 2 * 1 +"; // (3 + 4) * 2 + 1
    assert(eval_rpn(rpn_expression) == 15);
  }
  {
    string rpn_expression = "3 2 1 + *"; // (1 + 2) * 3
    assert(eval_rpn(rpn_expression) == 9);
  }
  {
    string rpn_expression =
        "4 2 5 * + 1 3 2 * + /"; // (4 + 2 * 5) / (1 + 3 * 2)
    assert(eval_rpn(rpn_expression) == 2);
  }
  {
    string rpn_expression =
        "2 5 * 4 + 3 2 * 1 + /"; // (2 * 5 + 4 ) / (3 * 2 + 1)
    assert(eval_rpn(rpn_expression) == 2);
  }
  {
    string rpn_expression = "3 5 6 + * 12 4 / -"; // ((5 + 6) * 3) - (12 / 4)
    assert(eval_rpn(rpn_expression) == 30);
  }
  {
    string rpn_expression =
        "100 10 2 -7 * * + 41 +"; // ((2 * (-7)) * 10) + 100 + 41
    assert(eval_rpn(rpn_expression) == 1);
  }
  {
    string rpn_expression = "-12 -56 -";
    assert(eval_rpn(rpn_expression) == 44);
  }
  cout << "all tests passed" << endl;
}
