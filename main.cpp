#include <stack>
#include <iostream>
using namespace std;


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
    // representa nuestro nodo dentro de la expresion
    char data;
    Nodo* left;
    Nodo* right;

    Nodo(char data) {
        // hacemos nuestro constructor
        this->data = data;
        left = right = nullptr;
    }
};

// función que determina si un carácter es un operador
/* bool isOperator(char ch) { */
/*     return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'); // Retornamos un valor verdadero cuando nuestro caracter sea un operador */
/* } */

// función para generar el árbol de expresión a partir de una expresión postfija
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
void Inorden(Nodo* Raiz) {
    if (Raiz == nullptr) return;
    cout << Raiz->data;
    Inorden(Raiz->left);
    Inorden(Raiz->right);
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
  Inorden(Raiz);
}




