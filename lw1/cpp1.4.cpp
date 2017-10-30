#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    float a, b, c, x, y;
    cout << "Enter the value a: ";
    cin >> a;
    cout << "Enter the value b: ";
    cin >> b;
    cout << "Enter the value c: ";
    cin >> c;
    if ((b * b - 4 * a * c) > 0)
    {
        x = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
        cout << "First: " << ("%f\n", x) << endl;
        y = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
        cout << "Second: " << ("%f\n", y) << endl;
    }
    else
    {
        cout << "Discriminant less than 0." << endl;
    }
    system("pause");
    return 0;
}