/* TO DO
// 1) Fix the pemdas <-- I have no idea how to do bc it was chatgpt
// 5) allow ln and e
// 1.0 Complete!
*/
#include "expressions.h"
#include "expressions.cpp"

void welcome();
double calcResults(double upper_bound, double lower_bound, int n, string expression, char choice);

int main() {

    char choice = 'Y';
    welcome();
    while (toupper(choice) == 'Y') {
        try {
            string expression;
            cout << "Enter a mathematical expression (use 'x' as a variable): ";
            getline(cin, expression);

            double lower_bound, upper_bound, change;
            int n;

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

void welcome() {
    cout << "Welcome to the Riemann Sum Calculator 0.2!" << endl;
    cout << "If you find any bugs, please report it to https://github.com/stereoscoped/Riemann-Sum-Calculator\n" << endl;
    cout << fixed << setprecision(6);
}

double calcResults(double upper_bound, double lower_bound, int n, string expression, char choice) {
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
    } else if (choice == 'S') {
        if (n%2 != 0) {
            ++n;
            cout << "\n(Subdivisions set to " << n << " due to the requirement of even subdivisions)" << endl;
            change = (upper_bound - lower_bound) / n;
        }
        for (int i = 0; i <= n; ++i) {
            size_t pos = 0;
            int factor = (i == 0 || i == n) ? 1 : (i % 2 != 0 ? 4 : 2);
            area += parseExpression(expression, pos, x) * factor;
            x += change;
        }
        area = (area * change)/3;
    } else if (choice == 'T') {
        for (int i = 0; i <= n; ++i) {
            size_t pos = 0;
            int factor = (i == 0 || i == n) ? 1 : 2;
            area += parseExpression(expression, pos, x) * factor;
            x += change;
        }
        area = (area * change)/2;
    }

    return area;
}


