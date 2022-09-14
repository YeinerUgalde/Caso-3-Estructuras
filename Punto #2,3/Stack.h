#include "List.h"

#ifndef STACK 

#define STACK 1

template <class T>

class Stack{
    private: 
        List<T> * stackList;

    public:
        Stack(){
            stackList = new List<T>();
        }
        
        T* top(){
            T* result = NULL;
            
            if(!stackList->isEmpty()){
                result = stackList->find(0);
            }
            
            return result;
        }

        //agregar al principio
        void push(T *pValue){
            stackList->insert(0, pValue);
        }

        T* pop(){
            T* result = NULL;
            if(!stackList->isEmpty()){
                result = stackList->find(0);
                stackList->remove(0);
            }
            return result;
        }

        bool isEmpy(){
            return stackList->isEmpty();
        }
};

#endif