#include "stack.h"
#include <iostream>
Stack::Stack(int n){
    if (n > MAX)
    {
        std::abort();
    }
    pitems = new Item[n];
    for (int i = 1; i <= n; i++)
    {
        pitems[i-1] = i;
    }
    size = n;
    top = n-1;
}

Stack::Stack(const Stack& st){
    pitems = new Item[st.size];
    for (int i = 0; i < st.size; i++)
    {
        pitems[i] = st.pitems[i];
    }
    top = st.top;
    size = st.size;
}

Stack::~Stack(){
    delete [] pitems;
}

bool Stack::isempty() const{
    return this->top == -1;
}

bool Stack::isfull() const{
    return this->top == this->size-1;
}

bool Stack::push(const Item &item){
    if (!isfull())
    {
        pitems[++top] = item;
        return true;
    }
    return false;
}

bool Stack::pop(Item &item){
    if (!isempty())
    {
        item = pitems[top--];
        return true;
    }
    return false;
}

Stack& Stack::operator=(const Stack& st){
    if (this == &st)
    {
        return *this;
    }
    delete [] pitems;
    pitems = new Item[st.size];
    for (int i = 0; i < st.size; i++)
    {
        pitems[i] = st.pitems[i];
    }
    top = st.top;
    size = st.size;
    return *this;
}



