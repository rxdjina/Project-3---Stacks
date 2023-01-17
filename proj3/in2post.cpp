#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <fstream>
#include "stack.h"

#define ADDITION_OPERATOR '+'
#define SUBTRACTION_OPERATOR '-'
#define MULTIPLICATION_OPERATOR '*'
#define DIVISION_OPERATOR '/'
#define EXPONENTIAL_OPERATOR '^'
#define OPEN_PARENTHESIS '('
#define CLOSED_PARENTHESIS ')'
#define SPACE_CHARACTER " "
#define OXFORD_COMMA ','
#define DECIMAL_POINT '.'
#define UNDERSCORE '_'

using namespace std;
using namespace cop4530;

static string const FILE_ERROR_MESSAGE = "UNABLE TO RETRIEVE FILE";

int precedance(char c) {
    if (c == ADDITION_OPERATOR || c == SUBTRACTION_OPERATOR) {
        return 1;

    } else if (c == MULTIPLICATION_OPERATOR || c == DIVISION_OPERATOR) {
        return 2;

    } else if (c == EXPONENTIAL_OPERATOR) {
        return 3;
    }
        
    return -1;
}

bool isOperator(char c) {
	if (c == ADDITION_OPERATOR || c == SUBTRACTION_OPERATOR || c == MULTIPLICATION_OPERATOR || c == DIVISION_OPERATOR || c== EXPONENTIAL_OPERATOR) {
        return true;
    } else {
        return false;
    }
}

std::string infixToPostfix(string infix) {
    string postfix;
    Stack<char> operators;

	for(int i = 0; i < infix.length(); i++) {
        if (isspace(infix[i])) {
            postfix += SPACE_CHARACTER; // Append space
        }
		else if (isalpha(infix[i]) || isdigit(infix[i]) || infix[i] == DECIMAL_POINT || infix[i] == UNDERSCORE) {
			postfix += infix[i]; // Append valid characters

        } else if (infix[i] == OPEN_PARENTHESIS) {
			operators.push(infix[i]); // Push open bracket onto stack

		} else if (infix[i] == CLOSED_PARENTHESIS) {
			while((operators.top() != OPEN_PARENTHESIS) && (!operators.empty())) { // Loop until open parenthesis is found OR stack becomes empty
				postfix += operators.top(); // Append operator to expression
				operators.pop(); // Remove operator from stack
			}

			if (operators.top() == OPEN_PARENTHESIS) { 
				operators.pop(); // Remove open parenthesis from stack
			}

		} else if (isOperator(infix[i])) { // Found operator
			if(operators.empty()) {
				operators.push(infix[i]); // If stack is empty, push operator onto stack

			} else {
				if (precedance(infix[i]) > precedance(operators.top())) { // If current opeerator has greater precedance, push to stack
					operators.push(infix[i]);

				} else if ((precedance(infix[i]) == precedance(operators.top())) && (infix[i] == EXPONENTIAL_OPERATOR)) { // If current operator has same precedance, push to stack
					operators.push(infix[i]);

				} else {
					while ((!operators.empty()) && (precedance(infix[i]) <= precedance(operators.top()))) { // If current operator has less precedance, pop from stack
						postfix += operators.top();
                        postfix += SPACE_CHARACTER;
						operators.pop();
					}

					operators.push(infix[i]); // Push operator to stack
				}
			}
		}
	}

    postfix += SPACE_CHARACTER;

	while(!operators.empty()) { // Empty remaining operators from stack
		postfix += operators.top();
        postfix += SPACE_CHARACTER;
		operators.pop();
	}
	
	return postfix; // Return postfix expression
}

bool canEvaluate(string postfix) { // Returns true if there are no variables in expression
    for (auto c : postfix) {
        if (isalpha(c)) {
            return false;
        }
    }

    return true;
}

template <typename T>
T evaluate(string postfix) {
    Stack<T> operands;
    int i;

    T temp1 = 0, temp2 = 0;
    T tempNumber = 0, tempDecimal = 0;
    T power = -1;

    for (i = 0; i < postfix.length(); i++) { 
        auto c = postfix[i];

        if (isdigit(c)) {
            while (i < postfix.length() && (isdigit(postfix[i]) || postfix[i] == '.')) {  // Find digits
                if (postfix[i] == DECIMAL_POINT) { // Check for decimal numbers
                    i++;

                    while (i < postfix.length() && (isdigit(postfix[i]))) { // Loop to get value of decimal numbers
                        tempDecimal = tempDecimal + ((postfix[i] - '0') * pow(10, power));
                        i++;
                        power--;
                    }

                    tempNumber += tempDecimal; // Add decimal numbers to digit
                    
                } else {
                    tempNumber = (tempNumber * 10) + (postfix[i] - '0'); // Add digits
                    i++;
                }
            }

            operands.push(tempNumber);  // Add digit to stack

            tempNumber = 0; // Reset variables
            tempDecimal = 0;
            power = -1;

        } else if (isOperator(c)) { 
            temp1 = operands.top(); // Top previous two values
            operands.pop();

            temp2 = operands.top();
            operands.pop();

            switch (c) { // Evalute
                case ADDITION_OPERATOR: 
                    operands.push(temp2 + temp1); 
                    break;

                case SUBTRACTION_OPERATOR: 
                    operands.push(temp2 - temp1); 
                    break;
                case MULTIPLICATION_OPERATOR: 
                    operands.push(temp2 * temp1); 
                    break;
                case DIVISION_OPERATOR: 
                    operands.push(temp2 / temp1); 
                    break;
                case EXPONENTIAL_OPERATOR: 
                    operands.push(pow(temp2, temp1)); 
                    break;
            }
        }
    }

    return operands.top(); // Return result
}

void print_menu() { // Print menu
    cout << endl;
    cout << "[1] Input Infix Expression" << endl;
    cout << "[2] Input Infix Expression From File" << endl;
    cout << "[3] Quit" << endl;
    cout << "\nChoice: ";
}

int validInput(string expression) { // Error Checking
    int open_brackets = 0, closed_brackets = 0, operators = 0;

    if (expression.length() == 0) { // Missing expression
        return -1;
    }

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == OPEN_PARENTHESIS) {
            open_brackets++;
        } else if (expression[i] == CLOSED_PARENTHESIS) {
            closed_brackets++;
        } else if (isOperator(expression[i])) {
            operators++;
        }
    }
    
    if (open_brackets != closed_brackets) { // Missig parenthesis'
        return 1;
    } else if (operators == 0) { // Missing operartors
        return 2;
    }

    return 0;
}

void evaluateByFile(string const &filename) { // Evalute infix expression by file
    string line, infix, postfix;
    ifstream inputFile(filename);

    if (inputFile.is_open()) { // Open File
        while(getline(inputFile, line)) { // Read Data
            infix = line;

            if (validInput(infix) == 0) {
                postfix = infixToPostfix(infix);
                cout << "\nInfix Expression: " << infix << endl;

                if (canEvaluate(postfix)) {
                    cout << "Result: " << evaluate<double>(postfix) << endl;
                } else {
                    cout << "Postfix Expression: " << postfix << endl;
                }

            } else if (validInput(infix) == 1) { // Missing Brackets
                cout << "\nERROR: MISMATCHED BRACKETS" << endl;
            } else if (validInput(infix) == 2) { // Missing Operators
                cout << "ERROR: MISSING OPERATORS" << endl;
            }
        }

        inputFile.close(); // Close File

    } else { // Unable to Open File
        cout << FILE_ERROR_MESSAGE << endl;
    }
}

int main(void) {
    string infix, postfix, fileName;
    int choice;

    while(choice != 3) {
        print_menu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nInput Infix Expression: \n";
                getline(cin>>ws, infix); 

                while (validInput(infix) != 0) {
                    if (validInput(infix) == 1) { // Missing Brackets
                        cout << "\nERROR: MISMATCHED BRACKETS" << endl;
                    } else if (validInput(infix) == 2) { // Missing Operator
                        cout << "ERROR: MISSING OPERATORS" << endl;
                    } else if (validInput(infix) == -1) { // Missing Expression
                        cout << "ERROR: MISSING EXPRESSION" << endl;
                    }

                    cout << "\nInput Infix Expression: \n";
                    getline(cin>>ws, infix);
                }
                
                postfix = infixToPostfix(infix);
                cout << "\nInfix Expression: " << infix << endl;

                if (canEvaluate(postfix)) {
                    cout << "Result: " << evaluate<double>(postfix) << endl;

                } else {
                    cout << "Postfix Expression: " << postfix << endl;
                }

                break;

            case 2:
                cout << "File Name: ";
                cin >> fileName;
                cout << endl;

                evaluateByFile(fileName);
                break;

            case 3:
                cout << "Termminating Program..." << endl;
                return EXIT_SUCCESS;
                break;

            default:
                cout << "INVALID INPUT" << endl;
        }
    }

    return EXIT_SUCCESS;
}