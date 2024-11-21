#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

template <typename T>
class Stack {
  public:

  Stack<T>(unsigned capacity = 20) {
    this->capacity = capacity;
    data = new T[capacity];
    t = -1;
  }

  ~Stack() {
    delete[] data;
  }

  Stack<T>(const Stack<T>& other) {
    this->capacity = other.capacity;
    this->data = new T[capacity];
    for (int i = 0; i < capacity; i++) {
      this->data[i] = other.data[i];
    }
  }

  Stack<T>& operator=(const Stack& other) {
    this->capacity = other.capacity;
    this->data = new T[capacity];
    for (int i = 0; i < capacity; i++) {
      this->data[i] = other.data[i];
      }
    return *this;
  }

  void push(const T& val) {
    if (!full()) {
    data[++t] = val;
  }
    else {
  throw std::string("Full Stack");
    }
}

  void pop() {
    if (!empty()) {
    t--;
  }
    else {
      throw std::string("Empty Stack");
    }
  }

  const T& top() const {
    if (!empty()) {
      return data[t];
  }
    else {
    throw std::string("Empty Stack");
    }
  }

  bool empty() const {
    return (t < 0);
  }

  bool full() const {
    return (t == capacity - 1);
  }

  const int priority(char op) const {
    switch(op) {
      case '^':
        return 5;
        break;
      case '*':
        return 3;
        break;
      case '/':
        return 3;
        break;
      case '%':
        return 2;
        break;
      case '+':
        return 1;
        break;
      case '-':
        return 1;
        break;
      default:
        return -1;
        break;
    }
  }

  std::string to_postfix(std::string val) {
    char ch;
    std::string post;
    std::string num_str;

    for (char a:val) {
      if (isalpha(a)){
        throw std::string("Invalid character\n");
      }
      else if(isspace(a)) {
        throw std::string("Invalid number of operands\n");
      }
    }
    
    if (val.length() < 3) {
      throw std::string("Invalid number of operands");
    } 
    
    for (int i = 0; i < val.length(); i++) { // starting with second char in the string
      ch = val[i];
      if (isdigit(ch)) {
        num_str += ch; 
      
      if (!num_str.empty()) {
       // operand logic
        post += num_str; // append operand to string
        
        num_str.clear();
      }  
    }
      else if (ch == '+' || ch == '-' 
        || ch == '*' || ch == '/'
        || ch == '^' || ch == '%') {

         if (val[i+1] == '+' || val[i+1] == '-' 
          || val[i+1] == '*' || val[i+1] == '/'
          || val[i+1] == '^' || val[i+1] == '%') {
        throw std::string("Invalid number of operands");
          }           

          else if (empty()) { // operator logic
            post += ' ';
            push(ch); // push first operator
          }  
          else {
            post += ' ';
            try {
              char top_op = top();
              int top_prec = priority(top_op);
              
              int cur_prec = priority(ch);
              

              if (cur_prec > top_prec) 
              {
                push(ch);
              } 

          else if (cur_prec <= top_prec) {
            while (!empty() && cur_prec <= top_prec) {
               post += top_op;
               post += ' ';
               pop();
               if (!empty()) {
                  top_op = top();
                      top_prec = priority(top_op);
                  }
                }
                push(ch);        
          }
        }
          
            catch (std::string& ex) {
              std::cerr << "Error: "<< ex << std::endl;
            }
          }
      }        
      else if (ch == '(' || ch == '{') { // open parenthesis/bracket logic
        push(ch);        
        }

        else if (ch == ')' || ch == '}') { // closed parenthesis/bracket logic
        bool found_parenth = false;     
        switch(ch) {
          case ')':
            while (!empty()) {
              char parenth = top();
              if (parenth != '(') {
              post += ' ';
              post += parenth;
              pop();
              }
              else {
                found_parenth = true;
                pop();
                break;
              }
            }
            break;
          case '}':
            while (!empty()) {
            char parenth = top();
            if (parenth != '{') {
            post += ' ';
            post += parenth;
            pop();
            }
            else {
              found_parenth = true;
              pop();
              break;
            }
          }
            break;
        }
        if (!found_parenth) { // invalid char handling
          throw std::string("Invalid parentheses\n");  
          }
      }
      else {
        throw std::string("Invalid character '") + ch + ("' in the expression");
      }
    }   
     // after reading the infix expression
      while (!empty()) {
        char end = top();
        
        post += ' ';
        post += end;
         
        pop();
        }
      if (post[post.length()-1] == '(' || post[post.length()-1] == '{')  {
        throw std::string("Invalid Parentheses");
      }
      return post;
    } 

  void print_postfix(std::string pr) const {
    if(!pr.empty()) {
      std::cout << "Postfix expression: ";
      int i = 0;
      while (i <= pr.length()) {
        std::cout << pr[i];
        i++;
      }
      std::cout << "\n";
    }
  }

 double evaluatePostfix(std::string exp) {
  char c;
  double n = 0.0;
  double eval = 0.0;
  double a = 0.0;
  double b = 0.0;
  std::string num;

  int operator_count = 0;
    for (int i = 0; i < exp.length(); i++) {
      c = exp[i];
      if (c == '+' || c == '-' 
        || c == '*' || c == '/'
        || c == '^' || c == '%') {
        try {
        if (operator_count == 0) {
        b = top();
        pop();
        a = top();
        pop();
      }
        else { 
          b = top();
          pop();
          a = top(); 
          pop();
        }
        switch (c) {
          case '^':
            eval = pow(a,b);
            break;
          case '*':
            eval = a * b;
            break;
          case '/':
            eval = a / b;
            break;
          case '%':
            eval = fmod(a, b);
            break;
          case '+':
            eval = a + b;
            break;
          case '-':
            eval = a - b;
            break;
        }
      } catch(std::string& ex) {
          std::cerr << "Error: " << ex;
      }
      push(eval);
        operator_count++;
      }
    else if (isdigit(c)) {
        num += c;
    }
    else if(c == ' ' && !num.empty()) {
         n = stod(num);
          push(n);
          num.clear();
      }  
    }
   double result = 0.0;
   if (!empty()) {
   result = top();
   pop();
   }
   return result ;
  }

    private:
      T* data;
      int t;
      unsigned capacity;

  };

int main () {
  Stack<char> stack1;
  Stack<double> stack2;
  std::string infixExpression;

  try {
  std::cout << "Enter an infix expression: "; // Prompt the user to enter an input in infix format
    
  getline(std::cin, infixExpression);
    
  std::string postfixExp = stack1.to_postfix(infixExpression); // Transform the infix expression to postfix
    
    stack1.print_postfix(postfixExp); // Print the postfix expression
    
    double result = stack2.evaluatePostfix(postfixExp); // Evaluate the postfix expression
    
  std::cout << "Result: " << std::fixed << std::setprecision(3) << result;
  }
    catch (const std::string& ex) {
      std::cerr << "Error: " << ex << std::endl;
    }

  return 0;
}