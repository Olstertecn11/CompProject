#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <iostream>


class textNode: public sf::Drawable{
  private:
    std::string value;
    sf::Font font;
    sf::Color foreground;
    sf::Text text;
    int font_size;
  public:
    sf::Vector2f getPos();
    textNode(std::string, sf::Color, int);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;
    void loadFont();
    void setText(sf::Vector2f, std::string);
};
