import csv
import matplotlib.pyplot as plt
import numpy as np

def exact_solution(x):
    return x + np.cos(x)

def read_csv(filename):
    x, y = [], []
    with open(filename, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            x.append(float(row[0]))
            y.append(float(row[1]))
    return np.array(x), np.array(y)

# Чтение данных
x_euler, y_euler = read_csv('euler.csv')
x_rk4, y_rk4 = read_csv('rk4.csv')
x_adams2, y_adams2 = read_csv('adams2.csv')
x_adams3, y_adams3 = read_csv('adams3.csv')

# Точное решение
x_exact = np.linspace(0, 1, 100)
y_exact = exact_solution(x_exact)

# Построение графиков решений
plt.figure(figsize=(12, 8))

plt.subplot(2, 2, 1)
plt.plot(x_exact, y_exact, 'k-', label='Точное', linewidth=2)
plt.plot(x_euler, y_euler, 'r--', label='Эйлер', markersize=3)
plt.title('Метод Эйлера')
plt.legend()
plt.grid(True)

plt.subplot(2, 2, 2)
plt.plot(x_exact, y_exact, 'k-', label='Точное', linewidth=2)
plt.plot(x_rk4, y_rk4, 'b--', label='Рунге-Кутта 4', markersize=3)
plt.title('Метод Рунге-Кутта 4 порядка')
plt.legend()
plt.grid(True)

plt.subplot(2, 2, 3)
plt.plot(x_exact, y_exact, 'k-', label='Точное', linewidth=2)
plt.plot(x_adams2, y_adams2, 'g--', label='Адамс 2', markersize=3)
plt.title('Метод Адамса 2 порядка')
plt.legend()
plt.grid(True)

plt.subplot(2, 2, 4)
plt.plot(x_exact, y_exact, 'k-', label='Точное', linewidth=2)
plt.plot(x_adams3, y_adams3, 'm--', label='Адамс 3', markersize=3)
plt.title('Метод Адамса 3 порядка')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig('solutions.png', dpi=300)
plt.show()

# Построение графиков погрешностей
plt.figure(figsize=(12, 8))

plt.subplot(2, 2, 1)
err_euler = np.abs(y_euler - exact_solution(x_euler))
plt.plot(x_euler, err_euler, 'r-', markersize=3)
plt.title('Погрешность: Эйлер')
plt.grid(True)

plt.subplot(2, 2, 2)
err_rk4 = np.abs(y_rk4 - exact_solution(x_rk4))
plt.plot(x_rk4, err_rk4, 'b-', markersize=3)
plt.title('Погрешность: Рунге-Кутта 4')
plt.grid(True)

plt.subplot(2, 2, 3)
err_adams2 = np.abs(y_adams2 - exact_solution(x_adams2))
plt.plot(x_adams2, err_adams2, 'g-', markersize=3)
plt.title('Погрешность: Адамс 2')
plt.grid(True)

plt.subplot(2, 2, 4)
err_adams3 = np.abs(y_adams3 - exact_solution(x_adams3))
plt.plot(x_adams3, err_adams3, 'm-', markersize=3)
plt.title('Погрешность: Адамс 3')
plt.grid(True)

plt.tight_layout()
plt.savefig('errors.png', dpi=300)
plt.show()

print("Графики сохранены: solutions.png, errors.png")
