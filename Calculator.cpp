#include <iostream>
#include <string>
using namespace std;

int main() {
    double num1, num2, result;
    string op;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;
    cout << "Enter operand (add, sub, mul, div): ";
    cin >> op;
    if (op == "add") {
        result = num1 + num2;
        cout << "Result: " << result << endl;
    } else if (op == "sub") {
        result = num1 - num2;
        cout << "Result: " << result << endl;
    } else if (op == "mul") {
        result = num1 * num2;
        cout << "Result: " << result << endl;
    } else if (op == "div") {
        if (num2 == 0) {
            cout << "Error: Division by zero!" << endl;
        } else {
            result = num1 / num2;
            cout << "Result: " << result << endl;
        }
    } else {
        cout << "Invalid operand!" << endl;
    }
    return 0;
}
