#include <iostream>
#include"Deque.h"
using namespace std;


template<typename T>
class Stack{
    Deque<T> s;
public:
    bool empty(){return s.size()==0;}//�Ƿ�Ϊ��
    int size(){return s.size();}//����Ԫ�ظ���
    void push(T x){s.push_back(x);}//ѹ��Ԫ��
    void pop(){s.pop_back();}//����Ԫ��
    T& top()const{return s.back();}//����ĩβԪ��
    void clear(){s.clear();}
};