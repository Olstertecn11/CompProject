#include "textNode.h"
#include <SFML/System/Vector2.hpp>

textNode::textNode(std::string text, sf::Color forecolor, int size) {
  this->value = text;
  this->foreground = forecolor;
  this->font_size = size;
  this->loadFont();
}


void textNode::draw(sf::RenderTarget &target, sf::RenderStates state)const{
  target.draw(this->text, state);
}

void textNode::loadFont(){
  sf::Font font;
  if(!font.loadFromFile("./roboto/Roboto-Medium.ttf")){
    throw("Could not load font :(");
  }
  this->font = font;
}

void textNode::setText(sf::Vector2f pos, std::string val){
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(this->foreground);
  text.setStyle(sf::Text::Bold);
  text.setString(val);
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin((textRect.width/2)-18, (textRect.height/2)-8);
  /* text.setOrigin((textRect.width/2)-12, (textRect.height/2)-5); */
  text.setPosition(pos);
}


sf::Vector2f textNode::getPos(){
  return this->text.getPosition();
}
