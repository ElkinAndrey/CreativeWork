#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <cmath>

#include "Graph.h"
#include "Node.h"
#include "IRib.h"
#include "RibUnilateral.h"
#include "RibBilateral.h"

using namespace std;
using namespace sf;

// �����, �������� � ����
class Map {
private:
    vector<Node> Nodes; // ������ �����
    Graph graph; // ����
    int size; // ������ �����
public:
    // �����������, ����������� ����
    Map(Graph graph) {
        this->graph = graph; // ����������� �����
        this->size = graph.GetSize(); // ��������� ������� �����
        Nodes = vector<Node>(size, Node()); // ����������� ���������� �������
        for (int i = 0; i < size; i++) // ���������� �������
            Nodes[i] = Node(65 + i, 40, 400 + 300 * cos(2 * PI * i / size), 400 + 300 * sin(2 * PI * i / size));
    }

    void DrawGraph(sf::RenderWindow& window) {
        vector<vector<int>> mas = graph.GetGraph(); // ���� � ���� �������

        //���������� �������
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                IRib* c; // ��������� �������
                if (mas[i][j] != -1 and mas[j][i] != -1) // ���� ����� ���������� ������� � ���� ������������
                    c = new RibBilateral(Nodes[i], Nodes[j], mas[i][j], mas[j][i], Color(255, 255, 255), Color(255, 255, 255));
                else if (mas[i][j] != -1) // ���� �� ������� ����� �� �������
                    c = new RibUnilateral(Nodes[i], Nodes[j], mas[i][j], Color(255, 255, 255));
                else if (mas[j][i] != -1)   // ���� �� ������� ����� � �������
                    c = new RibUnilateral(Nodes[j], Nodes[i], mas[j][i], Color(255, 255, 255));
                else
                    continue;
                c->Draw(window); // ���������� �������
            }
        }

        // ���������� ������� �������
        for (list<char>::iterator i = graph.shortestDetour.begin(); i != graph.shortestDetour.end();) {
            IRib* c; // ��������� �������
            int a = int(*i) - 65;
            i++;
            if (i == graph.shortestDetour.end()) { // ���������� ������� �� ���������� ����� � �������
                int b = int(*graph.shortestDetour.begin()) - 65;
                if (mas[a][b] != -1 and mas[a][b] != -1)  // ���� ����� ���������� ������� � ���� ������������
                    c = new RibBilateral(Nodes[a], Nodes[b], mas[a][b], mas[b][a], Color(255, 0, 0), Color(255, 255, 255));
                else if (mas[a][b] != -1)// ���� �� ������� ����� �� �������
                    c = new RibUnilateral(Nodes[a], Nodes[b], mas[a][b], Color(255, 0, 0));
                else if (mas[b][a] != -1) // ���� �� ������� ����� � �������
                    c = new RibUnilateral(Nodes[b], Nodes[a], mas[b][a], Color(255, 0, 0));
                else
                    break;
                c->Draw(window);
                break;
            }
            int b = int(*i) - 65;
            if (mas[a][b] != -1 and mas[a][b] != -1)// ���� ����� ���������� ������� � ���� ������������
                c = new RibBilateral(Nodes[a], Nodes[b], mas[a][b], mas[b][a], Color(255, 0, 0), Color(255, 255, 255));
            else if (mas[a][b] != -1)// ���� �� ������� ����� �� �������
                c = new RibUnilateral(Nodes[a], Nodes[b], mas[a][b], Color(255, 0, 0));
            else if (mas[b][a] != -1)// ���� �� ������� ����� � �������
                c = new RibUnilateral(Nodes[b], Nodes[a], mas[b][a], Color(255, 0, 0));
            else
                continue;
            c->Draw(window);
        }

        // ���������� ������
        for (int i = 0; i < size; i++) {
            Nodes[i].Draw(window);
        }
    }

    // ���������� ����
    void Draw(sf::RenderWindow& window) {
        DrawGraph(window);
    }
};