#include <iostream>
using namespace std;


//deque与vector的写法基本相同，多出了头部元素的添加删除操作，以及一些细微的调整:)

template <typename T>
class DequeIterator;


//deque类
template<typename T>
class Deque{
    T *p{nullptr};
    int elem_num{0};
public:
    typedef DequeIterator<T> iterator;

public:

    Deque(int s=0):elem_num(s){//构造函数
        if(s==0)
            p=nullptr;
        else
            p=new T(s);
    }
    ~Deque(){//析构函数
        if(p!=nullptr)
            delete[] p;
    }
    Deque(Deque& other){//复制构造
        elem_num=other.elem_num;
        if(other.elem_num==0)
            p=nullptr;
        else{
            p=new T(elem_num);
            memcpy(p,other.p,sizeof(T)*elem_num);
        }
    }
    Deque(int n,T elem){//使用n个elem初始化
        p=new T(n);
        elem_num=n;
        for(int i=0;i<n;i++)
            p[i]=elem;
    }
    
    template <typename...Types>//多参数构造
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
    void func_init(){}//多参数构造的结束

    void assign(int n,T elem){//在第n个元素之后插入elem
        p=new T(n);
        elem_num=n;
        for(int i=0;i<n;i++)
            p[i]=elem;
    }
    Deque& operator=(const Deque& other){//重构=
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
    friend ostream& operator<<(ostream &out,Deque &x){//重构输出
        T* temp=x.begin();
        while(temp!=x.end()){
            out<<*temp<<' ';
            temp++;
            }
        return out;
    } 

    void insert(int n,T elem){//插入
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
    void insert(int n,int x,T elem){//插入
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
    void push_back(T x){//添加尾元素
        T* temp=new T(elem_num+1);
        if(p!=nullptr){
            memcpy(temp,p,sizeof(T)*elem_num);
            // delete[] p;
        } 
        temp[elem_num]=x;
        p=temp; 
        elem_num++;
    }
    void push_front(T x){//添加头元素
        T* temp=new T(elem_num+1);
        memcpy(temp+1,p,sizeof(T)*elem_num);
        temp[0]=x;
        delete[] p;
        p=temp;
        elem_num++;
    }
    void pop_front(){//弹出头元素
        T* temp=new T(elem_num-1);
        memcpy(temp,p+1,sizeof(T)*(elem_num-1));
        delete[] p;
        p=temp;
        elem_num--;
    }
    void pop_back(){//弹出末尾元素
        if(elem_num<=0)
            cout<<"error"<<endl;
        elem_num--;
    }
    bool empty(){return elem_num==0;}//是否为空
    int size()const{return elem_num;}//返回元素个数
    T& front()const{return p[0];}//返回头元素
    T& back()const{return p[elem_num-1];}//返回末尾元素
    T* begin(){return &p[0];}//返回头指针
    T* end(){return &p[elem_num];}//返回尾指针
    T& at(int n){return p[n];} //返回第n个元素
    T& operator[](int n){return p[n];}//重构[]
    void clear(){//清空容器
        for(int i=0;i<elem_num;i++)
            p[i]=NULL;
        elem_num=0;
    }
    

};



//迭代器
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