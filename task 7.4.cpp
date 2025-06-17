#include <iostream>
#include <ctime>
#include <cstdlib>
#include <clocale>  
using namespace std;

void checkDimensions(const int rows, const int cols);
int getDimension(const char* prompt);  
int getNumber();
void printArray(const int* const* arr, const int rows, const int cols);  
void fillArrayRandom(int** arr, const int rows, const int cols, const int min, const int max);
void checkRange(const int min, const int max);
void replaceMinWithAverage(int** arr, const int rows, const int cols);  
bool hasTwoPairsWithSameSign(const int* const* arr, const int rows, const int cols);
void printIndicesGreaterThanPrevious(const int* const* arr, const int rows, const int cols);
void fillArrayManually(int** arr, const int rows, const int cols, const int min, const int max);

enum SELECT { RANDOM = 0, MANUALLY = 1 };

int main()
{
    setlocale(LC_ALL, "Russian");
    int rows = getDimension("Введите количество строк массива: ");
    int cols = getDimension("Введите количество столбцов массива: ");
    checkDimensions(rows, cols);

    int** arr = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
    }

    cout << "Введите минимальное и максимальное значение диапазона: ";
    int minValue = getNumber();
    int maxValue = getNumber();
    checkRange(minValue, maxValue);

    cout << "Введите выбор для заполнения массива: " << endl
         << RANDOM << " Для случайного заполнения" << endl
         << MANUALLY << " Для ручного заполнения" << endl;

    int choice = getNumber();

    switch (static_cast<SELECT>(choice))
    {
    case RANDOM:
        fillArrayRandom(arr, rows, cols, minValue, maxValue);
        break;
    case MANUALLY:
        fillArrayManually(arr, rows, cols, minValue, maxValue);
        break;
    default:
        cout << "Ваш выбор неверен" << endl;
        for (int i = 0; i < rows; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
        return -1;
    }

    cout << "Элементы массива:" << endl;
    printArray(arr, rows, cols);

    replaceMinWithAverage(arr, rows, cols);
    cout << "Массив после замены минимального значения на среднее:" << endl;
    printArray(arr, rows, cols);

    printIndicesGreaterThanPrevious(arr, rows, cols);

    if (hasTwoPairsWithSameSign(arr, rows, cols)) {
        cout << "Есть две пары соседних элементов с одинаковыми знаками.\n";
    } else {
        cout << "Две пары соседних элементов с одинаковыми знаками отсутствуют.\n";
    }

    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}

void checkDimensions(const int rows, const int cols) {
    if (rows <= 0 || cols <= 0) {
        cerr << "Неправильные размеры массива" << endl;
        abort();
    }
}

int getDimension(const char* prompt) {  
    cout << prompt;
    int dim;
    cin >> dim;
    if (cin.fail() || dim <= 0) {
        cerr << "Неправильный ввод данных";
        abort();
    }
    return dim;
}

int getNumber() {
    int number;
    cin >> number;
    if (cin.fail()) {
        cerr << "Неправильный ввод данных";
        abort();
    }
    return number;
}

void printArray(const int* const* arr, const int rows, const int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "arr[" << i << "][" << j << "] = " << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

void fillArrayRandom(int** arr, const int rows, const int cols, const int min, const int max) {
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void checkRange(const int min, const int max) {
    if (min > max) {
        cerr << "Введен неправильный диапазон" << endl;
        abort();
    }
}

void replaceMinWithAverage(int** arr, const int rows, const int cols) {
    if (rows * cols % 2 == 0) {
        cout << "Количество элементов массива четное, замена не производится." << endl;
        return;
    }

    int minRow = 0, minCol = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] < arr[minRow][minCol]) {
                minRow = i;
                minCol = j;
            }
        }
    }

    long sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += arr[i][j];
        }
    }
    arr[minRow][minCol] = static_cast<int>(sum / (rows * cols));
}

bool hasTwoPairsWithSameSign(const int* const* arr, const int rows, const int cols) {
    if (rows * cols < 3) return false;
    
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (j < cols - 1) { // 
                if ((arr[i][j] >= 0) == (arr[i][j + 1] >= 0)) {
                    count++;
                    if (count >= 2) {
                        return true;
                    }
                }
            }
            if (i < rows - 1) { 
                if ((arr[i][j] >= 0) == (arr[i + 1][j] >= 0)) {
                    count++;
                    if (count >= 2) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void printIndicesGreaterThanPrevious(const int* const* arr, const int rows, const int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i > 0 && arr[i][j] > arr[i - 1][j]) { 
                cout << "Элемент [" << i << "][" << j << "] = " << arr[i][j] 
                     << " больше элемента [" << i - 1 << "][" << j << "] = " << arr[i - 1][j] << endl;
            }
            if (j > 0 && arr[i][j] > arr[i][j - 1]) { 
                cout << "Элемент [" << i << "][" << j << "] = " << arr[i][j] 
                     << " больше элемента [" << i << "][" << j - 1 << "] = " << arr[i][j - 1] << endl;
            }
        }
    }
}

void fillArrayManually(int** arr, const int rows, const int cols, const int min, const int max) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Введите значение для arr[" << i << "][" << j << "]: ";
            int val = getNumber();
            if (val < min || val > max) {
                cout << "Значение вне диапазона! Пожалуйста, введите значение от " << min << " до " << max << "." << endl;
                --j; 
            } else {
                arr[i][j] = val;
            }
        }
    }
}