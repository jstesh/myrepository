#include <iostream>// ввод-вывод данных встроенного типа, для cout и cin
#include <cmath> // позволяет писать функции типа sqrt, арккосинус и тп
#include <fstream> // для считывания данных из файла или записи в файл
#include <string>// работа со строками
using namespace std;
// вектор
struct Vect{
    double x;
    double y;
};
// скалярное произведение
double cos1(Vect a, Vect b) {
    return ((a.x * b.x + a.y * b.y)/(sqrt(a.x*a.x+a.y*a.y)*sqrt(b.x*b.x+b.y*b.y)));
}
//теперь считаем с текстового файла вектора
int main() {
    string file = "in.txt";
    ifstream mf;
    mf.open(file);//открыли файл
    string str;//переменная для считывания файла
    Vect a1{};
    Vect maxright{0,0};
    Vect maxleft{0,0};
    Vect maxright1{};
    double cos_left = 1;
    double cos_right = 1;
    int k = 0;
    if (mf.is_open()){
        int i = 0;
        while (getline(mf, str)){
            i++;
            if (i == 1) {
                Vect a{stod(str.substr(0, str.find(' '))), stod(str.substr(str.find(' ') + 1))};
                a1 = {a.x, a.y};
                cout << a1.x << " ";
                cout << a1.y;
                cout << "\n";
            }
            else{
                Vect b{stod(str.substr(0, str.find(' '))), stod(str.substr(str.find(' ') + 1))};
                double mn = cos1(a1,b);
                int D = a1.y*b.x- a1.x*b.y;//определяем, с какой стороны от вектора направлений лежит точка
                if ((D == 0) && ((a1.x * b.x < 0 )||(a1.y * b.y < 0))){ /*вектора состовляют угол 180 градусов и разнонаправлены.
                Будем считать второй вектор лежащим справа, и тогда он составляет наибольший угол с направляющим вектором справа*/
                    maxright1 = {b.x,b.y};
                    k++;
                }
                else if (D < 0){ // точка лежит справа от направляющей прямой
                    if(mn < cos_right){
                        maxright={b.x,b.y};
                        cos_right =  mn;
                    }
                }
                else if (D > 0){ // точка лежит слева от прямой
                    if(mn < cos_left) {
                        maxleft = {b.x, b.y};
                        cos_left = mn;
                    }
                }

            }
        }
   }
    else{
        cout <<  "Error";
    }
    if (k > 0){
        maxright = {maxright1.x,maxright1.y};
    }
    cout << maxright.x <<" "<< maxright.y << "\n"; //координаты точки,составляющей с вектором направления максимальный угол справа
    cout << maxleft.x <<" "<< maxleft.y << "\n"; //координаты точки, составляющей максимальный угол с вектором направления слева
    mf.close();//закрыли файл
    return 0;
}
