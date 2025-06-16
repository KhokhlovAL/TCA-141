#include <iostream>
#include <ctime>
#include <cstdlib>
#include <clocale>  
using namespace std;


void checkN(const int n);
int getSize();  
int getNumber();
void printArray(const int* arr, const int n);  
void fillArrayRandom(int* arr, const int n, const int min, const int max);
void checkRange( const int min, const int max);
void replaceMinWithAverage(int arr[], const int n);  
bool hasTwoPairsWithSameSign(const int arr[], int n);
void printIndicesGreaterThanPrevious(const int arr[], int n);
void fillArray(int* arr, int n, int min, int max);

enum SELECT { RANDOM = 0, MANUALLY = 1 };

int main()
{
    setlocale(LC_ALL, "Russian");
    int n = getSize();  
    int* arr = new int[n];

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
        fillArrayRandom(arr, n, minValue, maxValue);
        break;
    case MANUALLY:
        fillArray(arr, n, minValue, maxValue);
        break;
    default:
        cout << "Ваш выбор неверен" << endl;
        delete[] arr;  
        return -1;
    }

    cout << "Элементы массива:" << endl;
    printArray(arr, n);

    replaceMinWithAverage(arr, n);
    cout << "Массив после замены минимального значения на среднее:" << endl;
    printArray(arr, n);

    printIndicesGreaterThanPrevious(arr, n);

    if (hasTwoPairsWithSameSign(arr, n)) {
        cout << "Есть две пары соседних элементов с одинаковыми знаками.\n";
    } else {
        cout << "Две пары соседних элементов с одинаковыми знаками отсутствуют.\n";
    }

    delete[] arr;
    return 0;
}

void checkN(int n) {
    if (n <= 0) {
        cerr << "Неправильный размер массива" << endl;
        abort();
    }
}

int getSize() {  
    cout << "Введите размер массива: ";
    int n;
    cin >> n;
    checkN(n);
    return n;
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

void printArray(const int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
}

void fillArrayRandom(int* arr, int n, int min, int max) {
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
}

void checkRange(int min, int max) {
    if (min > max) {
        cerr << "Введен неправильный диапазон" << endl;
        abort();
    }
}

void replaceMinWithAverage(int arr[], int n) {
    if (n % 2 == 0) {
        cout << "Размер массива четный, замена не производится." << endl;
        return;
    }

    int minIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }

    
    long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }
    arr[minIndex] = static_cast<int>(sum / n);
}

bool hasTwoPairsWithSameSign(const int arr[], int n) {
    if (n < 3) return false;
    
    size_t count = 0;
    for (size_t i = 0; i < n - 1; ++i) {
        
        if ((arr[i] >= 0) == (arr[i+1] >= 0)) {
            count++;
            if (count >= 2) {
                return true;
            }
        }
    }
    return false;
}

void printIndicesGreaterThanPrevious(const int arr[], int n) {
    for (size_t i = 1; i < static_cast<size_t>(n); ++i) {
        if (arr[i] > arr[i - 1]) {
            cout << "Индекс " << i << ": " << arr[i] << endl;
        }
    }
}

void fillArray(int* arr, size_t n, int min, int max) {
    for (size_t i = 0; i < n; i++) {
        cout << "Введите значение для arr[" << i << "]: ";
        int val = getNumber();
        
       else {
            arr[i] = val;
        }
    }
}