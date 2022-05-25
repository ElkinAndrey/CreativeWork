#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;


class Graph {
private:
    vector<vector<int>> mas; // ������� �����
    int size; // ������ �����
public:
    list<char> shortestDetour; // ������ � ���������� �����

    // ����������� ��� ����������
    Graph() {}

    // �����������, ��������� ����, ��� �����, �� �������
    Graph(int size) {
        this->size = size;
        this->mas = vector<vector<int>>(size, vector<int>(size));

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                this->mas[i][j] = -1;
    }

    // �����������, ��������� ���� �� ���������� �������
    Graph(vector<vector<int>> mas) {
        this->size = mas.size();
        this->mas = vector<vector<int>>(size, vector<int>(size));

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                this->mas[i][j] = mas[i][j];
    }

    // ����������� �����������
    Graph(const Graph& graph) {
        this->size = graph.size;
        this->mas = vector<vector<int>>(size, vector<int>(size));

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                this->mas[i][j] = graph.mas[i][j];

        shortestDetour = graph.shortestDetour;

    }

    // ������ ���� � �������
    void SetGraph() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    cout << "������� ���� �� " << char(65 + i) << " �� " << char(65 + j) << " : ";
                    cin >> mas[i][j];
                }
            }
        }
    }

    // ������ ��������� ����
    void SetGraphRand() {
        srand(time(0));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    mas[i][j] = rand() % 100;
                }
            }
        }
    }

    // �������� ������ �����
    void SetSize(int size) {
        vector<vector<int>> mas2 = mas;
        this->size = size;
        this->mas = vector<vector<int>>(size, vector<int>(size, -1));
        for (int i = 0; i < mas2.size() and i < size; i++) {
            for (int j = 0; j < mas2.size() and j < size; j++) {
                this->mas[i][j] = mas2[i][j];
            }
        }
    }

    // �������� ���� �� ������ ����� �� ������
    void SetNode(char node) {
        int i = node - 65;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                cout << "������� ���� �� " << char(65 + i) << " �� " << char(65 + j) << " : ";
                cin >> mas[i][j];
            }
        }
    }

    // �������� ������� �����
    vector<vector<int>> GetGraph() {
        return mas;
    }

    // �������� ������ �����
    int GetSize() {
        return size;
    }

    // ����� ���������� ����, ��� ����������� �� �������� ����� �������� ��� ������ (������ � �����������)
    void ShortestDetour() {
        shortestDetour.clear(); // ���������� ���������� ���� ���������
        vector<vector<int>> mas2 = mas; // ���������� ������� �����, ����� ��� ��������� ������� ���� �� ���������
        list<int*> s; // ������ � ������ �� ����� ����� �� ������
        while (true) {
            vector<int> MinStr = vector<int>(size, 10000000); // ����������� �������� �� �������
            vector<int> MinCol = vector<int>(size, 10000000); // ����������� �������� �� ��������
            // ������� �� �������
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if (mas2[i][j] != -1 and mas2[i][j] < MinStr[i])
                        MinStr[i] = mas2[i][j];
            // ������� �����
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if (mas2[i][j] != -1)
                        mas2[i][j] -= MinStr[i];
            // ������� �� ��������
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if (mas2[i][j] != -1 and mas2[i][j] < MinCol[j])
                        MinCol[j] = mas2[i][j];
            // ������� ��������
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    if (mas2[i][j] != -1)
                        mas2[i][j] -= MinCol[j];

            // ���������� ���������� ������ ��� ������� ���������
            int n[3] = { 0, 0, 0 };
            bool fl = true;
            for (int i = 0; i < size and fl; i++)
                for (int j = 0; j < size; j++)
                    if (mas2[i][j] == 0) {
                        int min1 = 10000000, min2 = 10000000;
                        for (int a = 0; a < size; a++)
                            if (mas2[a][j] != -1 and a != i and mas2[a][j] < min1)
                                min1 = mas2[a][j];
                        for (int a = 0; a < size; a++)
                            if (mas2[i][a] != -1 and a != j and mas2[i][a] < min2)
                                min2 = mas2[i][a];
                        if (min1 == 10000000 or min2 == 10000000) {
                            n[1] = i;
                            n[2] = j;
                            fl = false;
                            break;
                        }
                        if (min1 + min2 > n[0]) {
                            n[0] = min1 + min2;
                            n[1] = i;
                            n[2] = j;
                        }
                    }

            int* m = new int[2]; // ������ � �������� ����� �� �������� � �������� ����� � �������� ����� ����������
            m[0] = n[1];
            m[1] = n[2];
            s.push_back(m); // ������ ����������� � s

            // � ������� ��������� �� ������������ ��������, ������� ��� �������
            mas2[n[2]][n[1]] = -1;
            for (int i = 0; i < size; i++) {
                mas2[n[1]][i] = -1;
                mas2[i][n[2]] = -1;
            }

            // ���� ������� ������� �����, ������� ������ �������, �� ������ ���� ������ �� �����
            if (s.size() >= size)
                break;
        }

        // ������ ������� ����
        list<char> m;
        shortestDetour.push_back(char(65));
        list<int*>::iterator q = s.begin();
        while (shortestDetour.size() < size) {
            if (char((*q)[0] + 65) == *(--shortestDetour.end())) {
                shortestDetour.push_back(char((*q)[1] + 65));
                q = s.begin();
            }
            else
                q++;
        }
    }

    // ������� ������� ����� � �������
    void Print() {
        cout << '\t';
        for (int i = 0; i < size; i++) {
            cout << char(i + 65) << '\t';
        }
        cout << '\n';
        for (int i = 0; i < size; i++) {
            cout << char(i + 65) << '\t';
            for (int j = 0; j < size; j++)
                cout << mas[i][j] << '\t';
            cout << '\n';
        }
    }
};