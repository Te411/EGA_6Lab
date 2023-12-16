#include <iostream>
#include <vector>
#include <random>
#include <locale.h>
#include <numeric>
using namespace std;
const int N = 15; // число городов

double SearchDistance(vector<double> rowDistance, int& index, vector <int> X) {
	double min = 999;
	int number = 0;
	for (int i = 0; i < X.size(); i++) {
		number = X[i];
		if (min > rowDistance[number] && rowDistance[number] != 0) {
			min = rowDistance[number];
			index = number;
		}
	}
	return min;
}

int main() {
	setlocale(LC_ALL, "rus");
	vector<vector<double>> distance(N, vector<double>(N)); // матрица расстояний
	vector<int> S; // обход городов
	vector<double> Q; // длина обхода
	vector <double> NextVec; // промежуточный вектор для расстояния
	vector <double> rowDistance; // расстояние из одного города в остальные
	int min = 999;
	vector <int> Z; // города - кандидаты на вставку
	vector <pair <int, int>> pairs;
	int Xi = 0; // текущий город
	int index = 0; // индекс города
	int step = 0; // шаг
	random_device rd;
	mt19937 gen(rd());
	vector<int> X; //города
	vector <int> copyX; // промежуточный вектор для городов
	int m = 0;
	int CurrentCity = 0;
	double next = 0.0;

	for (int i = 0; i < N; i++) {
		X.push_back(i);
	}

	cout << "Введите матрицу расстояний:" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> distance[i][j];
		}
		cout << endl;
	}

	cout << "Количество городов: " << X.size() << endl << endl;
	uniform_int_distribution<>diss(0, N - 1);
	index = diss(gen);
	Xi = X[index];
	int FirstCity = Xi;
	X.erase(X.begin() + index);
	cout << "Текущий обход:";
	S.push_back(Xi + 1);
	for (int j = 0; j < S.size(); j++) {
		cout << " " << S[j];
	}
	cout << endl << endl;


	while (!X.empty()) {
		cout << "Шаг " << step + 1 << endl;
		cout << "Кандидаты: " << endl;
		copyX.clear();
		pairs.clear();
		NextVec.clear();
		m = 0;
		CurrentCity = 0;
		next = 0;
		copy(X.begin(), X.end(), back_inserter(copyX));
		while (m < S.size()) {
			CurrentCity = S[m];
			rowDistance = distance[CurrentCity-1];
			next = SearchDistance(rowDistance, index, copyX);
			NextVec.push_back(next);
			pairs.push_back(make_pair(CurrentCity, index + 1));
			cout << "Пара " << m + 1 << ": ";
			cout << pairs[m].first << " - " << pairs[m].second << " и расстояние между ними: " << NextVec[m] << endl;
			m++;
		}

		cout << "Выбран кандидат: ";
		min = 999;
		for (int k = 0; k < NextVec.size(); k++) {
			if (min > NextVec[k]) {
				min = NextVec[k];
				index = k;
			}
		}

		cout << pairs[index].first << " - " << pairs[index].second << endl;
		for (int i = 0; i < S.size(); i++) {
			if (S[i] == pairs[index].first) {
				S.insert(S.begin() + i + 1, pairs[index].second);
				break;
			}
		}

		cout << "Текущий обход:";
		for (int j = 0; j < S.size(); j++) {
			cout << " " << S[j];
		}
		cout << endl;

		cout << "Длина текущего обхода: ";
		Q.clear();
		for (int i = 1; i < S.size(); i++) {
			double dist = 0;
			dist = distance[S[i-1]-1][S[i]-1];
			Q.push_back(dist);
		}
		cout << accumulate(Q.begin(), Q.end(), (double)0) << endl;

		for (int k = 0; k < X.size(); k++) {
			if (X[k] == (pairs[index].second - 1)) {
				X.erase(X.begin() + k);
			}
		}
		cout << endl;
		step++;
	}


	cout << "Шаг " << step + 1 << endl;
	cout << "Текущий обход:";
	for (int j = 0; j < S.size(); j++) {
		cout << " " << S[j];
		Xi = S[j] -1;
	}
	cout << endl;
	cout << "Возвращаемся в первый город: " << FirstCity +1 << endl;
	cout << "Расстояние до него: " << distance[Xi][FirstCity] <<endl;
	Q.push_back(distance[Xi][FirstCity]);
	cout << "Длина обхода: ";
	cout << accumulate(Q.begin(), Q.end(), (double)0) << endl << endl;
	cout << "Итоговый обход: ";
	S.push_back(FirstCity+1);
	for (int city : S) {
		cout << city << " ";
	}
	cout << endl;

	cout << "Итоговый путь: ";
	for (double distance : Q) {
		cout << distance << " ";
	}
	cout << endl;
	cout << "Длина итогового пути: " << accumulate(Q.begin(), Q.end(), (double)0) << endl;
	return 0;
}

/*
0.00 6.08 11.00 10.20 9.22 10.05 12.37 13.89 12.17 3.16 5.10 7.07 13.42 13.60 1.41
6.08 0.00 13.42 5.00 12.81 13.04 13.34 13.04 13.60 3.00 1.00 1.00 13.00 12.17 5.00
11.00 13.42 0.00 13.45 2.83 1.41 3.16 7.07 2.24 12.37 13.00 13.89 6.08 8.00 12.04
10.20 5.00 13.45 0.00 13.89 13.60 12.21 10.44 12.81 7.62 5.83 4.24 10.77 9.22 9.49
9.22 12.81 2.83 13.89 0.00 1.41 5.83 9.49 5.00 11.18 12.21 13.45 8.54 10.20 10.44
10.05 13.04 1.41 13.60 1.41 0.00 4.47 8.25 3.61 11.70 12.53 13.60 7.28 9.06 11.18
12.37 13.34 3.16 12.21 5.83 4.47 0.00 4.00 1.00 13.00 13.15 13.60 3.00 5.10 13.15
13.89 13.04 7.07 10.44 9.49 8.25 4.00 0.00 5.00 13.60 13.15 13.00 1.00 1.41 14.32
12.17 13.60 2.24 12.81 5.00 3.61 1.00 5.00 0.00 13.04 13.34 13.93 4.00 6.08 13.04
3.16 3.00 12.37 7.62 11.18 11.70 13.00 13.60 13.04 0.00 2.00 4.00 13.34 13.00 2.00
5.10 1.00 13.00 5.83 12.21 12.53 13.15 13.15 13.34 2.00 0.00 2.00 13.04 12.37 4.00
7.07 1.00 13.89 4.24 13.45 13.60 13.60 13.00 13.93 4.00 2.00 0.00 13.04 12.04 6.00
13.42 13.00 6.08 10.77 8.54 7.28 3.00 1.00 4.00 13.34 13.04 13.04 0.00 2.24 13.93
13.60 12.17 8.00 9.22 10.20 9.06 5.10 1.41 6.08 13.00 12.37 12.04 2.24 0.00 13.89
1.41 5.00 12.04 9.49 10.44 11.18 13.15 14.32 13.04 2.00 4.00 6.00 13.93 13.89 0.00
*/

/*
0.00 1.00 2.00 3.00 4.00
1.00 0.00 5.00 6.00 7.00
2.00 5.00 0.00 8.00 9.00
3.00 6.00 8.00 0.00 1.00
4.00 7.00 9.00 1.00 0.00
*/