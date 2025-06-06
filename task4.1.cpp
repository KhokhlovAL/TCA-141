#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

double getValue();
double calculateFunction(const double x);
double getPositiveStep();
void calculateAndPrintValues(const double startX, const double endX, const double step);

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Введите начальное значение x: ";
    double startX = getValue();

    cout << "Введите конечное значение x: ";
    double endX = getValue();

    if (startX > endX) {
        cout << "Ошибка: xstart должно быть меньше, чем xend" << endl;
        return 1;
    }

    double step = getPositiveStep();

    cout << "x | y" << endl;
    cout << "--------" << endl;

    calculateAndPrintValues(startX, endX, step);
    return 0;
}

double getValue() {
    double value = 0;
    cin >> value;
    if (cin.fail()) {
        cout << "Некорректное значение" << endl;
        exit(1);
    }
    return value;
}

double calculateFunction(const double x) {
    return tan(x) - 1.0 / 3.0 * pow(tan(x), 3) + 1.0 / 5.0 * pow(tan(x), 5) - 1.0 / 3;
}

double getPositiveStep() {
    cout << "Введите шаг: ";
    double step = getValue();
    
    if (step <= 0) {
        cout << "Ошибка. Шаг должен быть положительным. Повторите ввод." << endl;
        return getPositiveStep(); // Рекурсивный вызов
    }
    
    return step;
}

void calculateAndPrintValues(const double startX, const double endX, const double step) {
    for (double x = startX; x < endX + step; x += step) {
        if (fabs(cos(x)) < numeric_limits<double>::epsilon()) {
            cout << "Ошибка: Тангенс не существует для x = " << x << endl;
        }
        else {
            double y = calculateFunction(x);
            cout << x << " | " << y << endl;
        }
    }
}