#include<SFML/Graphics.hpp>
#include<cmath>
#define PI 3.14159

class Pendulum {
private:
    sf::Vector2f origin;
    sf::Vector2f bob;
    sf::CircleShape circle;
    sf::Vertex line[2];
    float angle;
    float angleVel;
    float angleAcc;
    float len;
    float gravity;
public:
    Pendulum(float origin_x, float origin_y, float len, float gravity) {
        origin.x = origin_x; origin.y = origin_y; //can also be written as origin = sf::Vector2f(origin_x, origin_y);
        bob = sf::Vector2f();
        circle = sf::CircleShape(30);// gives radius to the bob 
        angle = PI / 4;
        angleVel = 0;
        angleAcc = 0;
        this->len = len;
        this->gravity = gravity;

        circle.setFillColor(sf::Color::White);
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(bob);

      //Creating a visual representation of the pendulum by setting the endpoints of a line object.
        line[0] = sf::Vertex(origin, sf::Color::White); 
        line[1] = sf::Vertex(bob, sf::Color::White);
    }

    void update() {
        float mass = 1; 
        float force = mass * gravity * sin(angle); // force on pendulum = mgsin(angle)
        angleAcc = (-1 * force) / len; //since angular accleration(alpha) = -gsin(angle)/len by formula
        angleVel += angleAcc; // changing the angular velocity each time with respect to angular acceleration
        angle += angleVel; // changint the angle each time w.r.t anglular velocity so that the pendulum swings making angle

        // changing the position of bob as it swings 
        bob.x = len * sin(angle) + origin.x;   
        bob.y = len * cos(angle) + origin.y;

       //angleVel *= 0.99; // for damping and making the bob lose velocity and come to equilibrium 

        circle.setPosition(bob);
         line[1].position = bob; /*updates the visual representation of the pendulum, by drawing a line from the origin point to the current
         position of the bob. */
    }

    void render(sf::RenderWindow& window) {
        window.draw(line, 2, sf::Lines);
        window.draw(circle);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Simple Pendulum");
    window.setFramerateLimit(60);

    Pendulum pend(800, 50, 300, 1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        window.clear();
        pend.update();
        pend.render(window);
        window.display();
    }

    return 0;
}
