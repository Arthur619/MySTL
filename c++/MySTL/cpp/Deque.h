#include <iostream>
using namespace std;


//deque��vector��д��������ͬ�������ͷ��Ԫ�ص����ɾ���������Լ�һЩϸ΢�ĵ���:)

template <typename T>
class DequeIterator;


//deque��
template<typename T>
class Deque{
    T *p{nullptr};
    int elem_num{0};
public:
    typedef DequeIterator<T> iterator;

public:

    Deque(int s=0):elem_num(s){//���캯��
        if(s==0)
            p=nullptr;
        else
            p=new T(s);
    }
    ~Deque(){//��������
        if(p!=nullptr)
            delete[] p;
    }
    Deque(Deque& other){//���ƹ���
        elem_num=other.elem_num;
        if(other.elem_num==0)
            p=nullptr;
        else{
            p=new T(elem_num);
            memcpy(p,other.p,sizeof(T)*elem_num);
        }
    }
    Deque(int n,T elem){//ʹ��n��elem��ʼ��
        p=new T(n);
        elem_num=n;
        for(int i=0;i<n;i++)
            p[i]=elem;
    }
    
    template <typename...Types>//���������
    Deque(const T &arg,const Types &...args){
        elem_num++;
        p=new T(1);
        p[0]=arg;
        func_init(args...);
    }
    template <typename...Types>
    void func_init(const T &arg,const Types &...args){
        push_back(arg);
        func_init(args...);
    }
    void func_init(){}//���������Ľ���

    void assign(int n,T elem){//�ڵ�n��Ԫ��֮�����elem
        p=new T(n);
        elem_num=n;
        for(int i=0;i<n;i++)
            p[i]=elem;
    }
    Deque& operator=(const Deque& other){//�ع�=
        if(p==other.p)
            return *this;
        elem_num=other.elem_num;
        if(elem_num==0)
            p=nullptr;
        else{
            p=new T(elem_num);
            memcpy(p,other.p,sizeof(T)*elem_num);
        }
        return *this;
    }
    friend ostream& operator<<(ostream &out,Deque &x){//�ع����
        T* temp=x.begin();
        while(temp!=x.end()){
            out<<*temp<<' ';
            temp++;
            }
        return out;
    } 

    void insert(int n,T elem){//����
        elem_num++;
        T* temp=new T(elem_num);
        for(int i=0;i<n-1;i++){
            temp[i]=p[i];
        }
        temp[n]=elem;
        for(int i=n+1;i<elem_num;i++){
            temp[i]=p[i];
        }
        delete[] p;
        p=temp;
    }
    void insert(int n,int x,T elem){//����
        T* temp=new T(elem_num+x);
        for(int i=0;i<n-1;i++){
            temp[i]=p[i];
        }
        for(int i=-1;i<x;i++){
            temp[n+i]==elem;
        }
        for(int i=n;i<elem_num;i++){
            temp[n+x+i-1]=p[i];
        }
        delete[] p;
        p=temp;
        elem_num+=x;
    }
    void push_back(T x){//���βԪ��
        T* temp=new T(elem_num+1);
        if(p!=nullptr){
            memcpy(temp,p,sizeof(T)*elem_num);
            // delete[] p;
        } 
        temp[elem_num]=x;
        p=temp; 
        elem_num++;
    }
    void push_front(T x){//���ͷԪ��
        T* temp=new T(elem_num+1);
        memcpy(temp+1,p,sizeof(T)*elem_num);
        temp[0]=x;
        delete[] p;
        p=temp;
        elem_num++;
    }
    void pop_front(){//����ͷԪ��
        T* temp=new T(elem_num-1);
        memcpy(temp,p+1,sizeof(T)*(elem_num-1));
        delete[] p;
        p=temp;
        elem_num--;
    }
    void pop_back(){//����ĩβԪ��
        if(elem_num<=0)
            cout<<"error"<<endl;
        elem_num--;
    }
    bool empty(){return elem_num==0;}//�Ƿ�Ϊ��
    int size()const{return elem_num;}//����Ԫ�ظ���
    T& front()const{return p[0];}//����ͷԪ��
    T& back()const{return p[elem_num-1];}//����ĩβԪ��
    T* begin(){return &p[0];}//����ͷָ��
    T* end(){return &p[elem_num];}//����βָ��
    T& at(int n){return p[n];} //���ص�n��Ԫ��
    T& operator[](int n){return p[n];}//�ع�[]
    void clear(){//�������
        for(int i=0;i<elem_num;i++)
            p[i]=NULL;
        elem_num=0;
    }
    

};



//������
template <typename T>
class DequeIterator{
    T *p{nullptr};
public:
    friend class Deque<T>;
    
public:
    DequeIterator(){}
    DequeIterator(T *_p){p=_p;}
    DequeIterator(const DequeIterator &v){p=v.p;}
    ~DequeIterator(){p=nullptr;}
    DequeIterator& operator++(){
        p++;
        return *this;
    }
    DequeIterator operator++(int){
        DequeIterator temp(*this);
        ++p;
        return temp;
    }
    DequeIterator& operator--(){
        p--;
        return *this;
    }
    DequeIterator operator--(int){
        DequeIterator temp(*this);
        --p;
        return temp;
    }
    DequeIterator operator+=(int n){
        p+=n;
        return *this;
    }
    DequeIterator operator-=(int n){
        p-=n;
        return *this;
    }
    bool operator==(T* t){
        return p==t;
    }
    bool operator!=(T* t){
        return p!=t;
    }
    T& operator*()const{
        return *p;
    }
    T& operator->()const{
        return &p;
    }
};