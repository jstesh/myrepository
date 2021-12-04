#include <iostream>// ввод-вывод данных встроенного типа, для cout и cin
#include <fstream> // для считывания данных из файла или записи в файл
#include <string>// работа со строками
#include <vector>
using namespace std;
//теперь считаем с текстового файла вектора
int main() {
    string file = "in.txt";
    ifstream mf;
    mf.open(file);//открыли файл
    string str;//переменная для считывания файла
    int i = 0;
    double h = 0;
    double vx = 0;
    double vy = 0;
    int length = 0;
    double t = 0;
    double g = 9.8;
    vector<double> x1;
    vector<double> h1;
    if (mf.is_open()){
        while (getline(mf, str)){
            i++;
            if (i == 1) {
                h = stod(str.substr(0, str.find(' ')));
            }
            else if (i == 2) {
                vx = stod(str.substr(0, str.find(' ')));
                vy = stod(str.substr(str.find(' ') + 1));
            }
            else {
                x1.push_back(stod(str.substr(0, str.find(' '))));
                h1.push_back(stod(str.substr(str.find(' ') + 1)));
            }

        }
    }
    double h_act = 0;
    double s_x = 0;
    int j = 0;//номер участка
    int k = 0;
    double vx_first = vx;
    double h2 = 0;
    while (h > 0){
        if (vx==0){h = 0;}
        else {
            if (vx_first * vx > 0) { h2 = h1[j]; }
            if (vx_first * vx < 0) { h2 = h1[j - 1]; }
            if (j == 0) { s_x = x1[j]; }
            else { s_x = x1[j] - x1[j - 1]; }
            t = s_x / vx;
            h_act = h + vy * t - (g * g * t * t) / 2;
            if ((h_act > h2)&& (vx_first * vx > 0)) { j++; }
            if ((h_act > h2)&& (vx_first * vx < 0)) { j = j-1; }
            if ((h_act <= h2) && (j != 0)) { vx = -vx; }
            if ((h_act <= h2) && (j == 0)) { h = 0; }
            if (h != 0) { h = h_act; }
            //cout << j << "\n";
        }
    }
    cout << j;
    return 0;
}