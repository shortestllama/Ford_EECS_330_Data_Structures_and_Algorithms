#ifndef __MYINFIXCALCULATOR_H__
#define __MYINFIXCALCULATOR_H__

#include <algorithm>
#include <string>

#include "MyStack_j026f603.h"
#include "MyVector_j026f603.h"

class MyInfixCalculator{

  public:
    
    MyInfixCalculator()
    {
        
    }

    ~MyInfixCalculator()
    {
     
    }

    double calculate(const std::string& s)
    {
        // code begins
        MyVector<std::string> t;
        MyVector<std::string> p;
        tokenize(s, t);
        infixToPostfix(t, p);
        return calPostfix(p);
        // code ends
    }

  private:

    // returns operator precedance; the smaller the number the higher precedence
    // returns -1 if the operator is invalid
    // does not consider parenthesis
    int operatorPrec(const char c) const
    {
        switch(c)
        {
            case '*':
                return 2;
            case '/':
                return 2;
            case '+':
                return 3;
            case '-':
                return 3;
            default:
                return -1;
        }
    }

    // checks if a character corresponds to a valid parenthesis
    bool isValidParenthesis(const char c) const
    {
        switch(c)
        {
            case '(':
                return true;
            case ')':
                return true;
            default:
                return false;
        }
    }

    // checks if a character corresponds to a valid digit
    bool isDigit(const char c) const
    {
        if(c >= '0' && c <= '9')
            return true;
        return false;
    }

    bool isOperand(const std::string& s) const {
        if (isDigit(s[0]) || s[0] == '.') {
            return true;
        }

        if (s[0] == '-' && s.length() > 1) {
            return true;
        }

        return false;
    }

    bool isOperator(const char c) const {
        if (isValidParenthesis(c) || operatorPrec(c) > 1) {
            return true;
        }

        return false;
    }

    // computes binary operation given the two operands and the operator in their string form
    double computeBinaryOperation(const std::string& ornd1, const std::string& ornd2, const std::string& opt) const
    {
        double o1 = std::stod(ornd1);
        double o2 = std::stod(ornd2);
        switch(opt[0])
        {
            case '+':
                return o1 + o2;
            case '-':
                return o1 - o2;
            case '*':
                return o1 * o2;
            case '/':
                return o1 / o2;
            default:
                std::cout << "Error: unrecognized operator: " << opt << std::endl;
                return 0.0;
        }
    }


    // tokenizes an infix string s into a set of tokens (operands or operators)
    void tokenize(const std::string& s, MyVector<std::string>& tokens)
    {
        // code begins
        for (int i = 0; i < s.length(); i++) {
            if (isDigit(s[i]) || s[i] == '.' || s[i] == '-') {
                std::string temp;

                if (s[i] == '-' && (i == 0 || operatorPrec(s[i - 1]) > 1 || s[i - 1] == '(') && !isOperator(s[i + 1])) {
                    temp += s[i];
                    i++;
                }

                while (isDigit(s[i]) || s[i] == '.') {
                    temp += s[i];
                    i++;
                }

                if (temp.length() != 0) {
                    tokens.push_back(temp);
                }
            }

            if (isOperator(s[i])) { //ValidParenthesis(s[i]) || operatorPrec(s[i]) == 2 || operatorPrec(s[i]) == 3) {
                std::string t;
                t = s[i];
                tokens.push_back(t);
            }
        }
        // code ends
    }

    // converts a set of infix tokens to a set of postfix tokens
    void infixToPostfix(MyVector<std::string>& infix_tokens, MyVector<std::string>& postfix_tokens)
    {
        // code begins
        MyStack<std::string> stack;

        for (int i = 0; i < infix_tokens.size(); i++) {
            if (isOperand(infix_tokens[i])) {
                postfix_tokens.push_back(infix_tokens[i]);
            }
            
            else if (isOperator(infix_tokens[i][0])) {
                if (isValidParenthesis(infix_tokens[i][0])) {
                    if (infix_tokens[i][0] == '(') {
                        stack.push(infix_tokens[i]);
                    }

                    else {
                        while (stack.top()[0] != '(') {
                            postfix_tokens.push_back(stack.top());
                            stack.pop();
                        }

                        stack.pop();
                    }
                }

                else if (operatorPrec(stack.top()[0]) <= operatorPrec(infix_tokens[i][0]) && operatorPrec(stack.top()[0]) > 1) {
                    while (operatorPrec(stack.top()[0]) <= operatorPrec(infix_tokens[i][0]) && operatorPrec(stack.top()[0]) > 1) {
                        postfix_tokens.push_back(stack.top());
                        stack.pop();
                    }

                    stack.push(infix_tokens[i]);
                }

                else {
                    stack.push(infix_tokens[i]);
                }
            }
        }

        while (!stack.empty()) {
            postfix_tokens.push_back(stack.top());
            stack.pop();
        }
        // code ends
    }

    // calculates the final result from postfix tokens
    double calPostfix(const MyVector<std::string>& postfix_tokens) const
    {
        // code begins
        MyStack<std::string> stack;

        for (int i = 0; i < postfix_tokens.size(); i++) {
            if (isOperand(postfix_tokens[i])) {
                stack.push(postfix_tokens[i]);
            }

            else if (isOperator(postfix_tokens[i][0])) {
                std::string a = stack.top();
                stack.pop();
                std::string b = stack.top();
                stack.pop();
                double ans = computeBinaryOperation(b, a, postfix_tokens[i]);
                stack.push(std::to_string(ans));
            }
        }

        return std::stod(stack.top());
        // code ends
    }
};

#endif // __MYINFIXCALCULATOR_H__