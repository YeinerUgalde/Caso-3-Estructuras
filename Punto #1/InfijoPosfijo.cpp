#include <iostream>
#include "../Punto #2,3/Stack.h"
#include "string"

using namespace std;

#include <stdio.h>

int precedencia (char x, char y){
    int prec1, prec2;
    switch(x){
        case '+':prec1=1;break;

        case '-':prec1=1;break;

        case '*':prec1=2;break;

        case '/':prec1=2;break;

        case '%':prec1=3;
    }
    switch(y){

        case '+':prec2=1;break;

        case '-':prec2=1;break;

        case '*':prec2=2;break;

        case '/':prec2=2;break;

        case '%':prec2=3;
    }
    if (x == '(' || x == ')' || y == '(' || y == ')'){
        return 10;
    }
    if (x==' ' || y==' '){
        return 10;
    }
    return prec1-prec2;
}

string lector(string pString){
    Stack<string>* numStack = new Stack<string>();
    Stack<char>* operatorsStack = new Stack<char>();
    int position = 0;
    string operators[] = {"(",")"};
    string posFijo;

    for (int i = 0; i<pString.size();i++){
        if (pString[i]!='.' && !isdigit(pString[i])){
           
            numStack->push(new string(pString.substr(position,i-position))); // Extrae todo el numero hasta el operador encontrado

            posFijo+=pString.substr(position,i-position)+" ";

            string str (1,pString[i]);
            if (str == operators[1]){  // Si se encuentra el parentesis de cierre ")"
                
                string end;
                
                end = *operatorsStack->pop();
             
                while (end!=operators[0]){ // Agrega los operadores hasta el parentesis de cierre "("
                    if (operatorsStack->isEmpy()){ // Si no hay parenteseis de cierre devuelve error
                        cout << "error en la sintaxis" << endl;
                        return "Error en la sintaxis";
                    }
                    
                    posFijo+=end;
                    end = *operatorsStack->pop();;    
                }
            }
            char exTop = ' ';
            if (!operatorsStack->isEmpy()){
                exTop = *operatorsStack->top();  
            }
            operatorsStack->push(new char(pString[i]));
        
            int pre = precedencia(exTop,*operatorsStack->top());

            char temporal = ' ';
            if (pre==0){ // Si tienen la misma precedencia
                //cout << "==\n\n" ;
                temporal = *operatorsStack->pop();
                posFijo += *operatorsStack->pop();
                operatorsStack->push(new char (temporal));
            }
            if (pre>0 && pre<10){ // Si el opererador tiene mayor precedencia
                temporal = *operatorsStack->pop();
                posFijo += *operatorsStack->pop();
                operatorsStack->push(new char (temporal));
            }
             if (pre<0){ //  Si el operador tiene menor precedencia
                
                posFijo += *operatorsStack->pop();
                posFijo += *operatorsStack->pop();

            }
            position = i + 1;
        }
        if (i+1==pString.size() && !isdigit(pString[pString.size()])){
            numStack->push(new string(pString.substr(position,pString.size())));

            posFijo+=pString.substr(position,i-pString.size());
        }
    }

    while(!operatorsStack->isEmpy()){ // Agrega lo que queda en la pila siempre y cuando sea diferente de ")"
        string str(1,*operatorsStack->top());
        if (str!=")"){
            posFijo+= *operatorsStack->pop();
        }
        else{
            *operatorsStack->pop();
        }  
    }
    return posFijo;
    
}
int main(){
    string str = "10*4+(3-2)"; 
    //cin >> str;
    string postFijo = lector(str);
    cout << endl << "InFijo: " << str << endl;
    cout << endl << "postFijo: " << postFijo << "\n\n"; 
}
