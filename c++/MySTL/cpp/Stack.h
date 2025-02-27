#include <iostream>
#include"Deque.h"
using namespace std;


template<typename T>
class Stack{
    Deque<T> s;
public:
    bool empty(){return s.size()==0;}//是否为空
    int size(){return s.size();}//返回元素个数
    void push(T x){s.push_back(x);}//压入元素
    void pop(){s.pop_back();}//弹出元素
    T& top()const{return s.back();}//返回末尾元素
    void clear(){s.clear();}
};