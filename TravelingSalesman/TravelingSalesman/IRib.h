#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// ���������-�������
class IRib {
public:
    IRib() {}
    virtual void Draw(sf::RenderWindow& window) = 0; // ��������� �������
};