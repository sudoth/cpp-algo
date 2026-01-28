#include <iostream>
#include <vector>

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	int a, b, x, y, k1, k2;
	std::cout << "Введите количство строк и столбцов" << std::endl;
	std::cin >> a >> b;
	int matrix1[100][100];

	std::cout << "Введите матрицу" << std::endl;

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			std::cin >> matrix1[i][j];
		}
	}

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			std::cout <<  matrix1[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Вывести элемент с координатами x, y;" << std::endl;

	std::cin >> x >> y;

	std::cout << std::endl;

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (j == x - 1 && i == y - 1) {
				std::cout<< "элемент с координатами x, y равен " << matrix1[i][j] << std::endl;
			}
		}
	}

	std::cout << "Хотите удалить столбец ( 1 - да, 0 - нет)" << std::endl;

	std::cin >> k1;

	if (k1 == 1) {
		std::cout << "Введите номер столбца" << std::endl;
		std::cin >> k1;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				if (j != k1 - 1) {
					std::cout << matrix1[i][j] << " ";
				}
			}
			std::cout << std::endl;
		}
	}

	std::cout << "Хотите удалить строку (1 - да, 0 - нет)" << std::endl;

	std::cin >> k2;

	if (k2 == 1) {
		std::cout << "Введите номер строки" << std::endl;
		std::cin >> k2;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				if (i != k2 - 1 && j != k1 - 1) {
					std::cout << matrix1[i][j] << " ";
				}
			}
			std::cout << std::endl;
		}
	}



	return 0;
}