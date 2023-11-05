#include <iostream>
#include <vector>
#include <random>
#include <locale.h>
#include <numeric>
using namespace std;
const int N = 5; // число городов

int SearchDistance(vector<int> rowDistance, int& index, vector <int> X) {
	int min = 999;
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

void SearchСandidate(vector<int>& copyX, vector<int> rowDistance, vector<vector<int>> distance, 
	int& index, vector<int>& NextVec, vector <pair <int, int>>& pairs ) {
	int m = 0;
	int CurrentCity = 0;
	int next = 0;
	while (m < copyX.size()) {
		CurrentCity = copyX[m];
		rowDistance = distance[CurrentCity];
		next = SearchDistance(rowDistance, index, copyX);
		NextVec.push_back(next);
		pairs.push_back(make_pair(CurrentCity + 1, index + 1));
		cout << "Пара " << m + 1 << ": ";
		cout << pairs[m].first << " - " << pairs[m].second << " и расстояние между ними: " << NextVec[m] << endl;
		m++;
	}
}
int main() {
	setlocale(LC_ALL, "rus");
	vector<vector<int>> distance(N, vector<int>(N)); // матрица расстояний
	vector<int> S; // обход городов
	vector<int> Q; // длина обхода
	vector <int> NextVec; // промежуточный вектор для расстояния
	vector <int> rowDistance; // расстояние из одного города в остальные
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

	for (int i = 0; i < N; i++) {
		X.push_back(i);
	}
	uniform_int_distribution<> dis(1, 9);
	cout << "Матрица расстояний: " << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				distance[i][j] = 0;
				cout << " " << distance[i][j];
			}
			else {
				distance[i][j] = dis(gen);
				cout << " " << distance[i][j];
			}
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
	cout << endl;
	while (!X.empty()) {
		cout << "Шаг " << step + 1 << endl;
		cout << "Кандидаты: " << endl;
		copyX.clear();
		pairs.clear();
		NextVec.clear();
		copy(X.begin(), X.end(), back_inserter(copyX));
		SearchСandidate(copyX, rowDistance, distance, index, NextVec, pairs);
		cout << "Выбран кандидат: ";
		min = 999;
		for (int k = 0; k < NextVec.size(); k++) {
			if (min > NextVec[k]) {
				min = NextVec[k];
				index = k;
			}
		}
		cout << pairs[index].first << " - " << pairs[index].second << endl;
		S.push_back(pairs[index].first);
		S.push_back(pairs[index].second);
		cout << "Текущий обход:";
		for (int j = 0; j < S.size(); j++) {
			cout << " " << S[j];
		}
		cout << endl;
		cout << "Длина текущего обхода: ";
		Q.push_back(distance[Xi][(pairs[index].first) - 1]);
		Q.push_back(min);
		cout << round(accumulate(Q.begin(), Q.end(), 0)) << endl;
		for (int k = 0; k < X.size(); k++) {
			if (X[k] == (pairs[index].first - 1)) {
				X.erase(X.begin() + k);
			}
		}
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
	cout << round(accumulate(Q.begin(), Q.end(), 0)) << endl;
	cout << "Итоговый обход: ";
	S.push_back(FirstCity+1);
	for (int city : S) {
		cout << city << " ";
	}
	cout << endl;

	cout << "Итоговый путь: ";
	for (int distance : Q) {
		cout << distance << " ";
	}
	cout << endl;
	cout << "Длина итогового пути: " << round(accumulate(Q.begin(), Q.end(), 0)) << endl;
	return 0;
}

