#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Точное решение
double exact_solution(double x) {
    return x + cos(x);
}

// Система ОДУ: dy[0]/dx = f0, dy[1]/dx = f1
void f(double x, double y[], double dy[]) {
    dy[0] = y[1];  // y1' = y2
    dy[1] = x * sin(x) - cos(x) * y[1] - sin(x) * y[0];  // y2' из уравнения
}

// Метод Эйлера
void euler(double h, vector<double>& x_vals, vector<double>& y_vals) {
    double x = 0;
    double y[2] = {1, 1};  // u(0)=1, u'(0)=1
    double dy[2];
    
    while (x <= 1.0 + h/2) {
        x_vals.push_back(x);
        y_vals.push_back(y[0]);
        
        f(x, y, dy);
        y[0] += h * dy[0];
        y[1] += h * dy[1];
        x += h;
    }
}

// Метод Рунге-Кутта 4 порядка
void runge_kutta4(double h, vector<double>& x_vals, vector<double>& y_vals) {
    double x = 0;
    double y[2] = {1, 1};
    double dy[2], k1[2], k2[2], k3[2], k4[2], y_temp[2];
    
    while (x <= 1.0 + h/2) {
        x_vals.push_back(x);
        y_vals.push_back(y[0]);
        
        f(x, y, k1);
        y_temp[0] = y[0] + h*k1[0]/2; y_temp[1] = y[1] + h*k1[1]/2;
        f(x + h/2, y_temp, k2);
        y_temp[0] = y[0] + h*k2[0]/2; y_temp[1] = y[1] + h*k2[1]/2;
        f(x + h/2, y_temp, k3);
        y_temp[0] = y[0] + h*k3[0]; y_temp[1] = y[1] + h*k3[1];
        f(x + h, y_temp, k4);
        
        y[0] += h*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0])/6;
        y[1] += h*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1])/6;
        x += h;
    }
}

// Метод Адамса 2 порядка
void adams2(double h, vector<double>& x_vals, vector<double>& y_vals) {
    double x = 0;
    double y[2] = {1, 1};
    double dy[2], dy_prev[2];
    vector<double> f_vals;
    
    // Первые два шага методом Рунге-Кутта
    for (int i = 0; i < 2 && x <= 1.0 + h/2; i++) {
        x_vals.push_back(x);
        y_vals.push_back(y[0]);
        f(x, y, dy);
        f_vals.push_back(dy[0]);
        
        // RK4 для старта
        double k1[2], k2[2], k3[2], k4[2], y_temp[2];
        f(x, y, k1);
        y_temp[0] = y[0] + h*k1[0]/2; y_temp[1] = y[1] + h*k1[1]/2;
        f(x + h/2, y_temp, k2);
        y_temp[0] = y[0] + h*k2[0]/2; y_temp[1] = y[1] + h*k2[1]/2;
        f(x + h/2, y_temp, k3);
        y_temp[0] = y[0] + h*k3[0]; y_temp[1] = y[1] + h*k3[1];
        f(x + h, y_temp, k4);
        y[0] += h*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0])/6;
        y[1] += h*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1])/6;
        x += h;
    }
    
    // Адамс 2 порядка
    while (x <= 1.0 + h/2) {
        x_vals.push_back(x);
        y_vals.push_back(y[0]);
        
        f(x, y, dy);
        double y0_new = y[0] + h*(3*dy[0] - f_vals[f_vals.size()-1])/2;
        double y1_new = y[1] + h*(3*dy[1] - dy_prev[1])/2;
        
        f_vals.push_back(dy[0]);
        dy_prev[0] = dy[0]; dy_prev[1] = dy[1];
        y[0] = y0_new; y[1] = y1_new;
        x += h;
    }
}

// Метод Адамса 3 порядка
void adams3(double h, vector<double>& x_vals, vector<double>& y_vals) {
    double x = 0;
    double y[2] = {1, 1};
    double dy[2], dy_prev[2] = {0, 0}, dy_prev2[2] = {0, 0};
    vector<double> f_vals;
    
    // Первые три шага методом Рунге-Кутта
    for (int i = 0; i < 3 && x <= 1.0 + h/2; i++) {
        x_vals.push_back(x);
        y_vals.push_back(y[0]);
        f(x, y, dy);
        f_vals.push_back(dy[0]);
        
        double k1[2], k2[2], k3[2], k4[2], y_temp[2];
        f(x, y, k1);
        y_temp[0] = y[0] + h*k1[0]/2; y_temp[1] = y[1] + h*k1[1]/2;
        f(x + h/2, y_temp, k2);
        y_temp[0] = y[0] + h*k2[0]/2; y_temp[1] = y[1] + h*k2[1]/2;
        f(x + h/2, y_temp, k3);
        y_temp[0] = y[0] + h*k3[0]; y_temp[1] = y[1] + h*k3[1];
        f(x + h, y_temp, k4);
        y[0] += h*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0])/6;
        y[1] += h*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1])/6;
        x += h;
    }
    
    // Адамс 3 порядка
    while (x <= 1.0 + h/2) {
        x_vals.push_back(x);
        y_vals.push_back(y[0]);
        
        f(x, y, dy);
        double y0_new = y[0] + h*(23*dy[0] - 16*f_vals[f_vals.size()-1] + 5*f_vals[f_vals.size()-2])/12;
        double y1_new = y[1] + h*(23*dy[1] - 16*dy_prev[1] + 5*dy_prev2[1])/12;
        
        f_vals.push_back(dy[0]);
        dy_prev2[0] = dy_prev[0]; dy_prev2[1] = dy_prev[1];
        dy_prev[0] = dy[0]; dy_prev[1] = dy[1];
        y[0] = y0_new; y[1] = y1_new;
        x += h;
    }
}

// Запись в CSV
void write_csv(const string& filename, const vector<double>& x, const vector<double>& y) {
    ofstream file(filename);
    for (size_t i = 0; i < x.size(); i++) {
        file << fixed << setprecision(6) << x[i] << "," << y[i] << endl;
    }
    file.close();
}

// Вычисление погрешности
double max_error(const vector<double>& x, const vector<double>& y) {
    double max_err = 0;
    for (size_t i = 0; i < x.size(); i++) {
        double err = fabs(y[i] - exact_solution(x[i]));
        if (err > max_err) max_err = err;
    }
    return max_err;
}

int main() {
    vector<double> x_euler, y_euler;
    vector<double> x_rk4, y_rk4;
    vector<double> x_adams2, y_adams2;
    vector<double> x_adams3, y_adams3;
    
    // h = 0.05
    euler(0.05, x_euler, y_euler);
    runge_kutta4(0.05, x_rk4, y_rk4);
    adams2(0.05, x_adams2, y_adams2);
    adams3(0.05, x_adams3, y_adams3);
    
    write_csv("euler.csv", x_euler, y_euler);
    write_csv("rk4.csv", x_rk4, y_rk4);
    write_csv("adams2.csv", x_adams2, y_adams2);
    write_csv("adams3.csv", x_adams3, y_adams3);
    
    // Для оценки Рунге - грубая сетка h=0.1
    vector<double> x_adams2_coarse, y_adams2_coarse;
    adams2(0.1, x_adams2_coarse, y_adams2_coarse);
    write_csv("adams2_coarse.csv", x_adams2_coarse, y_adams2_coarse);
    
    // Вывод максимальных погрешностей
    cout << "=== Максимальные погрешности (h=0.05) ===" << endl;
    cout << "Эйлер: " << max_error(x_euler, y_euler) << endl;
    cout << "Рунге-Кутта 4: " << max_error(x_rk4, y_rk4) << endl;
    cout << "Адамс 2: " << max_error(x_adams2, y_adams2) << endl;
    cout << "Адамс 3: " << max_error(x_adams3, y_adams3) << endl;
    
    // Оценка Рунге для Адамса 2 порядка
    cout << "\n=== Оценка Рунге для Адамса 2 порядка ===" << endl;
    cout << "x\t\ty(h=0.1)\t\ty(h=0.05)\t\tR" << endl;
    for (size_t i = 0; i < x_adams2_coarse.size(); i++) {
        double x = x_adams2_coarse[i];
        double y_coarse = y_adams2_coarse[i];
        // Находим соответствующую точку в мелкой сетке
        for (size_t j = 0; j < x_adams2.size(); j++) {
            if (fabs(x_adams2[j] - x) < 1e-6) {
                double y_fine = y_adams2[j];
                double R = fabs(y_fine - y_coarse) / 3.0;  // 2^2 - 1 = 3
                cout << fixed << setprecision(4) << x << "\t\t" 
                     << y_coarse << "\t\t" << y_fine << "\t\t" << R << endl;
                break;
            }
        }
    }
    
    return 0;
}
