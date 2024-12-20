/* TO DO
// 1) Fix the pemdas <-- I have no idea how to do bc it was chatgpt
// 4) simpsons and trapezoidal rule
// 5) allow ln and e
// 1.0 Complete!
*/
#include "expressions.h"
#include "expressions.cpp"
double calcResults(double upper_bound, double lower_bound, double n, string expression, char choice);

int main() {

    char choice = 'Y';
    while (toupper(choice) == 'Y') {
        try {
            string expression;
            cout << "Enter a mathematical expression (use 'x' as a variable): ";
            getline(cin, expression);

            double lower_bound, upper_bound, n, change;
            cin.clear();

            cout << "Enter lower bound, upper bound, and number of subdivisions: ";
            cin >> lower_bound >> upper_bound >> n;

            if (n <= 0) {
                throw invalid_argument("Number of subdivisions must be greater than zero.");
            }

            // Left, right, middle, simpsons, or trapezoidal
            char lrmst;
            cout << "Enter for (L)eft, (R)ight, (M)iddle, (S)impsons, or (T)rapezoidal method: ";
            cin >> lrmst;

            // Calculates Results
            cout << "The result is: " << calcResults(upper_bound, lower_bound, n, expression, toupper(lrmst)) << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }

        // Ask if the user wants to try again
        cout << "\nDo you want to try again? (Y/N): ";
        cin >> choice;

        // Validate input for Y/N
        while (cin.fail() || (toupper(choice) != 'Y' && toupper(choice) != 'N') || cin.peek() != '\n') {
            cout << "Invalid choice! Please enter Y or N: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> choice;
        }
        cin.clear();
        cin.ignore(100, '\n');
    }

    return 0;
}

double calcResults(double upper_bound, double lower_bound, double n, string expression, char choice) {
    double x = lower_bound, area = 0, change = (upper_bound - lower_bound) / n;
    if (choice == 'R') {
        for (double i = 0; i < n; ++i) {
            size_t pos = 0;
            x += change;
            area += parseExpression(expression, pos, x) * change;
        }
    } else if (choice == 'L') {
        for (double i = 0; i < n; ++i) {
            size_t pos = 0;
            area += parseExpression(expression, pos, x) * change;
            x += change;
        }
    } else if (choice == 'M') {
        x += change/2;
        for (double i = 0; i < n; ++i) {
            size_t pos = 0;
            area += parseExpression(expression, pos, x) * change;
            x += change;
        }
    } /*else if (choice == 'S') {
        if (static_cast<int>(n)%2 != 0) {
            ++change;
            cout << "Simpson's Rule requires an even number of subdivisions!" << endl;
            cout << "Subdivisions set to " << static_cast<int>(n) + 1 << endl;
            change = (upper_bound - lower_bound) / (static_cast<int>(n) + 1);
        }
        for (double i = 0; i < n; ++i) {
            size_t pos = 0;
            area += parseExpression(expression, pos, x);
            x += change;
        }
        area = (area * change)/3;
    }*/

    return area;
}


