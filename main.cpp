#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <stack>
#include <iostream>
using namespace std;
#define WIDTH 1070
#define HEIGHT 920
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My App");


char operators[7] = {'+', '-', '*', '/', '(', ')', '^'};

int priority(char ch){
  if(ch == '+' || ch == '-'){
    return 1;
  }
  else if(ch == '*' || ch == '/'){
    return 2;
  }
  else if(ch == '^'){
    return 3;
  }
  return 0;
}


bool isOP(char ch){
  for(char c : operators){
    if(c == ch)return true;
  }
  return false;
}

struct Nodo {
    char data;
    Nodo* left;
    Nodo* right;
    /* textNode text = textNode("", sf::Color::Red, 26); */
    sf::CircleShape shape; 
    sf::RectangleShape leftone;
    sf::RectangleShape rightone;
    Nodo(char data) {
      this->data = data;
      left = right = nullptr;
    }
};

Nodo* genExpTree(string postfijo) {
  stack<Nodo*> st; // stack para retener nuestro caracter
  Nodo* l, * r, * temp;
  for (int i = 0; i < postfijo.length(); i++) {
    if (!isOP(postfijo[i])) { // si el carácter actual no es un operador
      temp = new Nodo(postfijo[i]); // creamos un nuevo nodo
      st.push(temp); // lo agregamos al stack
    }
    else { // si el carácter actual es un operador
      temp = new Nodo(postfijo[i]); // creamos un nuevo nodo
      l = st.top(); // obtenemos el primer nodo del stack
      st.pop();
      r = st.top(); // obtenemos el segundo nodo del stack
      st.pop();
      temp->left = r; // hacemos que el segundo nodo sea el hijo izquierdo del nuevo nodo
      temp->right = l; // hacemos que el primer nodo sea el hijo derecho del nuevo nodo
      st.push(temp); // agregamos el nuevo nodo al stack
    }
  }
  temp = st.top(); // obtenemos el nodo final del stack, que es la raíz del árbol
  st.pop();
  return temp; // devolvemos la raíz del árbol
}

// función para imprimir la expresión en orden de inorden
void Inorden(Nodo* Raiz, string flag, Nodo* parent, int x = 250, int y= 50, int a = 260, int b = 85) {
  if (Raiz == nullptr) return;
  if(flag == ""){
    cout << "root: " << Raiz->data << endl;
    Raiz->shape.setRadius(20);
    Raiz->shape.setFillColor(sf::Color::White);
    Raiz->shape.setPosition(sf::Vector2f(x, y));
    /* Raiz->text.setText(sf::Vector2f(x, y), to_string(Raiz->data)); */
  }
  else if(flag == "d"){
    cout << "der: " << Raiz->data;
    Raiz->shape.setPosition(sf::Vector2f((x + 50), (y + 50))); 
    parent->rightone.setSize(sf::Vector2f(50, 5)); 
    parent->rightone.setFillColor(sf::Color::Red);
    parent->rightone.setRotation(230);
    parent->rightone.setPosition(sf::Vector2f(a+50, b+40));
    /* Raiz->text.setText(sf::Vector2f(x+50, y+50), to_string(Raiz->data)); */
  }
  else if(flag == "i"){
    cout << "izq: " << Raiz->data;
    Raiz->shape.setPosition(sf::Vector2f((x - 50), (y + 50)));
    parent->leftone.setSize(sf::Vector2f(50, 5));
    parent->leftone.setFillColor(sf::Color::Red);
    parent->leftone.setRotation(130);
    parent->leftone.setPosition(sf::Vector2f(a, b));
    /* Raiz->text.setText(sf::Vector2f(x-50, y+50), to_string(Raiz->data)); */
  }
  if(parent != nullptr){
    cout << " parent: " <<  parent->data << endl;
  }
  Inorden(Raiz->right, "d", Raiz,x + 50, y + 50, a + 50, b + 50 );
  Inorden(Raiz->left, "i", Raiz, x - 50, y + 50, a - 50, b + 50);
}

void Display(Nodo* current){
  if(current == nullptr)return;
  /* window.draw(current->text); */
  window.draw(current->shape);
  if(current->left)window.draw(current->leftone);
  if(current->right)window.draw(current->rightone);
  Display(current->left);
  Display(current->right);
}


string infixToPosfix(string expression){
  string output = "";
  stack<char> stack;
  for(char ch: expression){
    if(!isOP(ch)){
      output += ch;
    }
    else if (ch == '('){
      stack.push(ch);
    }
    else if(ch == ')'){
      while(stack.top() != '('){
	output += stack.top();
	stack.pop();
      }
      stack.pop();
    }
    else{
      while(!stack.empty() && priority(ch) <= priority(stack.top())){
	output += stack.top();
	stack.pop();
      }
      stack.push(ch);
    }
  }
  while(!stack.empty()){
    output += stack.top();
    stack.pop();
  }
  return output;
}


int main(){
  string input;
  cout << "Enter a expression: ";
  cin >> input;
  string result = infixToPosfix(input);
  cout << "Posfijo: " << result << endl;
  cout << "Arbol: " << endl;
  Nodo* Raiz = genExpTree(result); // generamos el árbol de expresión
  Inorden(Raiz, "", nullptr);
  while(window.isOpen()){
    sf::Event event;
    Display(Raiz);
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
	window.close();
      }

      if(event.type == sf::Event::KeyPressed){
	if(event.key.code ==  sf::Keyboard::Escape){
	  window.close();
	}
      }
    }
    window.display();
    window.clear();
  }
}




