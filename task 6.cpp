#include <iostream>

using namespace std;

// 654 321 487 2 5 3 7 654 321 4879 6547
// 0...32767
int main() {
    int f;
    int d = 0;
  srand(time(0));
  const int N = 9;
  int arr[N];

  /*arr[0] = 3;
  arr[1] = 2;
  arr[2] = 4;
  arr[3] = 7;

  cout << arr[0] << endl;
  cout << arr[1] << endl;
  cout << arr[2] << endl;
  cout << arr[3] << endl;*/

  for (int i = 0; i < N; i++) {
    //cin >> arr[i];
    arr[i] = rand() % 61 - 20; // [0...60] --> [-20...40]
  }

  for (int i = 0; i < N; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  // 1.
  cout << "Найти минимальный элемент массива" << endl;
  
  for ( int i = 1; i < N; i++ ){
      if ( arr[i] < arr[d] ){
        d = i;
        
      }
      
  }
   arr [d] = arr [N/2];
   
   for (int i = 0; i < N; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
  
  
      
      

  // 2.
  cout << "indexes: ";
  for (int i = 1; i < N; i++) {
    if (arr[i] > arr[i - 1]) {
      cout << i << " ";
    }
  }
  cout << endl;

  // 3.
  cout << " Найти две пары с одинаковыми знаками ";
  f = 0;
  for ( int g = 1; g<N; g++){
      if (arr[g]* arr[g-1] >= 0){
    f++;
  }
  }
  if ( f >= 2 ){
      cout << "Две пары есть";
  }
  else{
      cout<<"Двух пар нет";
  }
}