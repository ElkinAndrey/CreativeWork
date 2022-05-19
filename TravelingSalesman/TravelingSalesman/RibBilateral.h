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

using namespace std;
using namespace sf;

// ������������� �������
class RibBilateral : public IRib {
private:
    Node node1; // ������ �����
    Node node2; // ������ �����
    int len1; // ���� �� �������� �� ������� �����
    int len2; // ���� �� ������� � ������� �����
    Color color1; // ���� ������� ����
    Color color2; // ���� ������� ����
public:
    // ����������� � �����������
    RibBilateral(const Node& node1, const Node& node2, int len1, int len2, Color color1, Color color2) {
        this->node1 = node1;
        this->node2 = node2;
        this->len1 = len1;
        this->len2 = len2;
        this->color1 = color1;
        this->color2 = color2;
    }

    // ��������� �������
    void Draw(sf::RenderWindow& window) override {
        // ������ �����
        VertexArray line(sf::LinesStrip, 2);
        line[0].position.x = node1.GetX();
        line[0].position.y = node1.GetY();
        line[0].color = color1;
        line[1].position.x = node2.GetX();
        line[1].position.y = node2.GetY();
        line[1].color = color1;
        window.draw(line);

        // ������ ������������
        double Rotation = 0; // ���� �������
        if (node2.GetX() - node1.GetX() > 0)
            Rotation = atan((double)(node2.GetY() - node1.GetY()) / (double)(node2.GetX() - node1.GetX())) + PI / 2;
        else if (node2.GetX() - node1.GetX() < 0)
            Rotation = atan((double)(node2.GetY() - node1.GetY()) / (double)(node2.GetX() - node1.GetX())) - PI / 2;
        else if (node2.GetY() - node1.GetY() > 0)
            Rotation = PI;

        int PositionX = (node1.GetX() + node2.GetX()) / 2; // ������� �� X
        int PositionY = (node1.GetY() + node2.GetY()) / 2; // ������� �� Y

        sf::CircleShape triangle1(8, 3);
        triangle1.setRotation(180 * Rotation / PI);
        triangle1.setPosition(PositionX - 8 * cos(Rotation), PositionY - 8 * sin(Rotation));
        triangle1.setFillColor(color1);
        window.draw(triangle1);
        sf::CircleShape triangle2(8, 3);
        triangle2.setRotation(180 * Rotation / PI + 180);
        triangle2.setPosition(PositionX + 8 * cos(Rotation), PositionY + 8 * sin(Rotation));
        triangle2.setFillColor(color2);
        window.draw(triangle2);

        // ������ �����
        int CenterX1 = ((node1.GetX() + node2.GetX()) / 2 + node1.GetX()) / 2;
        int CenterY1 = ((node1.GetY() + node2.GetY()) / 2 + node1.GetY()) / 2;
        int CenterX2 = ((node1.GetX() + node2.GetX()) / 2 + node2.GetX()) / 2;
        int CenterY2 = ((node1.GetY() + node2.GetY()) / 2 + node2.GetY()) / 2;

        int sizeSquare = 20;
        RectangleShape square1(Vector2f(sizeSquare, sizeSquare));
        square1.setPosition(CenterX1 - sizeSquare / 2, CenterY1 - sizeSquare / 2);
        window.draw(square1);
        RectangleShape square2(Vector2f(sizeSquare, sizeSquare));
        square2.setPosition(CenterX2 - sizeSquare / 2, CenterY2 - sizeSquare / 2);
        window.draw(square2);

        Font font1;
        Text text1;
        font1.loadFromFile("VarelaRound-Regular.ttf");//�������� ������ ������ ���� ������
        text1.setString(to_string(len1));//������ ������ ������
        text1.setFont(font1);
        text1.setStyle(sf::Text::Bold);
        text1.setFillColor(Color(57, 201, 78));
        text1.setCharacterSize(sizeSquare / 1.3);
        text1.setPosition(CenterX1 - 1.1 * text1.getGlobalBounds().width / 2, CenterY1 - 1.8 * text1.getGlobalBounds().height / 2);
        window.draw(text1);

        Font font2;
        Text text2;
        font2.loadFromFile("VarelaRound-Regular.ttf");//�������� ������ ������ ���� ������
        text2.setString(to_string(len2));//������ ������ ������
        text2.setFont(font2);
        text2.setStyle(sf::Text::Bold);
        text2.setFillColor(Color(57, 201, 78));
        text2.setCharacterSize(sizeSquare / 1.3);
        text2.setPosition(CenterX2 - 1.1 * text2.getGlobalBounds().width / 2, CenterY2 - 1.8 * text2.getGlobalBounds().height / 2);
        window.draw(text2);
    }
};