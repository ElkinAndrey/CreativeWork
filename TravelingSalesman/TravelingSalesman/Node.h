#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <cmath>

#include "Graph.h"

using namespace std;
using namespace sf;

class Node {
private:
    char str; // �������� �����
    int X; // ���������� X � �����
    int Y; // ���������� Y � �����
    sf::CircleShape circle; // ����
    int radius; // ������ �����
    Font font; // ����� ������
    Text text; // �����

    // ��������� ������ ���������� � ����� � ������
    void Config() {
        circle.setRadius(radius);
        circle.setPosition(X - radius, Y - radius);
        circle.setFillColor(sf::Color(57, 201, 78));

        font.loadFromFile("VarelaRound-Regular.ttf");//�������� ������ ������ ���� ������
        text.setFillColor(sf::Color(255, 255, 255));
        text.setString(str);//������ ������ ������
        text.setFont(font);
        text.setCharacterSize(radius);
        text.setOutlineColor(Color::Red);
        text.setPosition(X - 1.1 * text.getGlobalBounds().width / 2, Y - 1.8 * text.getGlobalBounds().height / 2);
    }
public:
    // ����������� ��� ����������
    Node() {}

    // �����������, ����������� ������, ������ � �������
    Node(char str, int radius, int X, int Y) {
        this->str = str;
        this->radius = radius;
        this->X = X;
        this->Y = Y;
    }
    // ����������� �����������
    Node(const Node& node) {
        this->str = node.str;
        this->radius = node.radius;
        this->X = node.X;
        this->Y = node.Y;
    }

    // �������� X ������� �����
    int GetX() {
        return X;
    }

    // �������� Y ������� �����
    int GetY() {
        return Y;
    }

    // �������� ������ �����
    int GetRadius() {
        return radius;
    }

    // ���������� �����
    void Draw(sf::RenderWindow& window) {
        Config();
        window.draw(this->circle);
        window.draw(this->text);
    }

};