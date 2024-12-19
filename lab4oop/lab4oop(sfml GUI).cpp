#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <memory>

class Circle
{
private:
    int x, y, radius;
    sf::CircleShape shape;
public:
    Circle(int x, int y, int r) : x(x), y(y), radius(r), shape(r) 
    {
        shape.setFillColor(sf::Color::Black);
        UpdatePosition();
    }
    void Draw(sf::RenderWindow& window)
    {
        UpdatePosition();
        window.draw(shape);
    }
    void MoveRight() 
    {
        x += 5;
    }
    void UpdatePosition() 
    {
        shape.setPosition(x - radius, y - radius);
    }
};
class Square 
{
private:
    int x, y, sideLength;
    sf::RectangleShape shape;
public:
    Square(int x, int y, int side) : x(x), y(y), sideLength(side), shape(sf::Vector2f(side, side)) 
    {
        shape.setFillColor(sf::Color::Black);
        UpdatePosition();
    }
    void Draw(sf::RenderWindow& window) 
    {
        UpdatePosition();
        window.draw(shape);
    }
    void MoveRight() 
    {
        x += 5;
    }
    void UpdatePosition() 
    {
        shape.setPosition(x - sideLength / 2, y - sideLength / 2);
    }
};
class Rhomb 
{
private:
    int x, y, horDiagLen, vertDiagLen;
    sf::ConvexShape shape;
public:
    Rhomb(int x, int y, int h, int v) : x(x), y(y), horDiagLen(h), vertDiagLen(v) 
    {
        shape.setPointCount(4);
        shape.setFillColor(sf::Color::Black);
        UpdatePosition();
    }
    void Draw(sf::RenderWindow& window) 
    {
        UpdatePosition();
        window.draw(shape);
    }
    void MoveRight() 
    {
        x += 5;
    }
    void UpdatePosition() 
    {
        shape.setPoint(0, sf::Vector2f(x, y - vertDiagLen / 2));
        shape.setPoint(1, sf::Vector2f(x + horDiagLen / 2, y));
        shape.setPoint(2, sf::Vector2f(x, y + vertDiagLen / 2));
        shape.setPoint(3, sf::Vector2f(x - horDiagLen / 2, y));
    }
};
int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dynamic Figures");
    std::vector<std::shared_ptr<Circle>> circles;
    std::vector<std::shared_ptr<Square>> squares;
    std::vector<std::shared_ptr<Rhomb>> rhombs;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) 
            {
                if (event.key.code == sf::Keyboard::C) 
                {
                    circles.push_back(std::make_shared<Circle>(100, 300, 50));
                }
                else if (event.key.code == sf::Keyboard::S) 
                {
                    squares.push_back(std::make_shared<Square>(100, 300, 100));
                }
                else if (event.key.code == sf::Keyboard::R) 
                {
                    rhombs.push_back(std::make_shared<Rhomb>(100, 300, 120, 80));
                }
            }
        }
        window.clear(sf::Color::White);
        for (auto& circle : circles) {
            circle->MoveRight();
            circle->Draw(window);
        }
        for (auto& square : squares) 
        {
            square->MoveRight();
            square->Draw(window);
        }
        for (auto& rhomb : rhombs) 
        {
            rhomb->MoveRight();
            rhomb->Draw(window);
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
