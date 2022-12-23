#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

//Функция для тоси-боси записи файла
int writeFile(double ** arr){

  std::ofstream outstream;
  outstream.open("result.txt");
  if(outstream.is_open()){
    for(int i=0; i<3;i++){
    for (int j=0; j<4;j++){
      outstream<<arr[i][j]<<" ";
    }
    outstream<<endl;
  }
  }
}

int main()
{
  setlocale(LC_ALL, "RUSSIAN");

  //Создаем файловый поток и связываем его с файлом
  ifstream in("source.txt");

  if (in.is_open())
  {
    //Если открытие файла прошло успешно

    //Вначале посчитаем сколько чисел в файле
    int count = 0;// число чисел в файле
    int temp;//Временная переменная

    while (!in.eof())// пробегаем пока не встретим конец файла eof
    {
      in >> temp;//в пустоту считываем из файла числа
      count++;// увеличиваем счетчик числа чисел
    }

    //Число чисел посчитано, теперь нам нужно понять сколько
    //чисел в одной строке
    //Для этого посчитаем число пробелов до знака перевода на новую строку

    //Вначале переведем каретку в потоке в начало файла
    in.seekg(0, ios::beg);
    in.clear();

    //Число пробелов в первой строчке вначале равно 0
    int count_space = 0;
    char symbol;
    while (!in.eof())//на всякий случай цикл ограничиваем концом файла
    {
      //теперь нам нужно считывать не числа, а посимвольно считывать данные
      in.get(symbol);//считали текущий символ
      if (symbol == ' ') count_space++;//Если это пробел, то число пробелов увеличиваем
      if (symbol == '\n') break;//Если дошли до конца строки, то выходим из цикла
    }
    //cout << count_space << endl;

    //Опять переходим в потоке в начало файла
    in.seekg(0, ios::beg);
    in.clear();

    //Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.
    //Теперь можем считать матрицу.

    int n = count / (count_space + 1);//число строк
    int m = count_space + 1;//число столбцов на единицу больше числа пробелов
    double **matrix;
    matrix = new double*[n];
    for (int i = 0; i<n; i++) matrix[i] = new double[m];

    //Считаем матрицу из файла
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        in >> matrix[i][j];

    //Выведем матрицу

    cout<<"Before editing matrix: "<<endl;

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
        cout << matrix[i][j] << "\t";
      cout << "\n";
    }

    // for (int i = 0; i<n; i++) delete[] matrix[i];
    // delete[] x;


    //А теперь чики брики ищем максимальный элемент в 4 столбце

    double max_value=0;
    int max_index[2]{0,0};

    for(int i=0; i<3;i++){
      if(max_value<matrix[i][3]){
        max_value=matrix[i][3];
        max_index[0]=i;
        max_index[1]=3;
      }
    }

    cout<<"Max value in 4 column: "<<max_value<<" , index: "<<max_index[0]+1<<","<<max_index[1]+1<<endl; // Нашли и вывели

    //Теперь сумму найдём

    double summ=0;

    for(int i=0;i<4;i++){
      summ=summ+(exp(1-matrix[1][i])+10);
    }

    cout<<"Result of summing func: "<<summ<<endl; //Наша сумма

    //Заменим максимамльный элемент в 4 столбце на эту сумму

    matrix[max_index[0]][max_index[1]]=summ;



    //Запишем в файл результат работы

    writeFile(matrix);


    in.close();//под конец закроем файла
  }
  else
  {
    //Если открытие файла прошло не успешно
    cout << "Файл не найден.";
  }

  system("pause");
  return 0;
}