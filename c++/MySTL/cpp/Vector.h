#include <iostream>
using namespace std;

template <typename T>
class VectorIterator;//声明迭代器


//vector类
template<typename T>
class Vector{
    T *p{nullptr};
    int elem_num{0};
public:
    typedef VectorIterator<T> iterator;

public:

    Vector(int s=0):elem_num(s){//构造给定大小的容器
        if(s==0)
            p=nullptr;
        else
            p=new T(s);
    }
    ~Vector(){//析构函数
        if(p!=nullptr)
            delete[] p;
    }
    Vector(Vector& other){//复制构造
        elem_num=other.elem_num;//先将大小复制
        if(other.elem_num==0)
            p=nullptr;
        else{
            p=new T(elem_num);
            memcpy(p,other.p,sizeof(T)*elem_num);//深拷贝，memcpy(目标，现有，大小)，拷贝给定范围的数据给目标
        }
    }
    Vector(int n,T elem){//使用n个elem初始化
        p=new T(n);//开辟空间
        elem_num=n;
        for(int i=0;i<n;i++)//赋值
            p[i]=elem;
    }
    
    //多参数构造
    template <typename...Types>
    Vector(const T &arg,const Types &...args){
        elem_num++;
        p=new T(1);
        p[0]=arg;//先将第一个元素装入容器
        func_init(args...);//将后面所有元素传递给该函数
    }
    template <typename...Types>
    void func_init(const T &arg,const Types &...args){
        push_back(arg);//压入第一个
        func_init(args...);//递归
    }
    void func_init(){}//无元素时进入该函数
    //多参数构造结束

    Vector& operator=(const Vector& other){//重构=
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
    friend ostream& operator<<(ostream &out,Vector &vec){//重构输出
        T* temp=vec.begin();
        while(temp!=vec.end()){
            out<<*temp<<' ';
            temp++;
            }
        out<<endl;
        return out;
    } //  <<a,输出容器a中所有元素

    bool empty(){return elem_num==0;}//判断是否为空
    int size(){return elem_num;}//返回元素个数
    void insert(int n,T elem){//在第n个元素之前插入元素elem
        elem_num++;//元素个数先+1
        T* temp=new T(elem_num);//开辟空间
        for(int i=0;i<n-1;i++){//将前n-1个元素赋值给temp
            temp[i]=p[i];
        }
        temp[n]=elem;//elem赋值给它
        for(int i=n+1;i<elem_num;i++){//再将后面元素赋值给temp
            temp[i]=p[i];
        }
        delete[] p;//删除原指针
        p=temp;
    }
    void insert(int n,int x,T elem){//再第n个位置插入n个elem,思路同上
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
    void push_back(T x){//向尾部添加元素
        T* temp=new T(elem_num+1);//开辟空间
        if(p!=nullptr){
            memcpy(temp,p,sizeof(T)*elem_num);//拷贝元素
            delete[] p;//删除原指针
        } 
        temp[elem_num]=x;//添加新元素
        p=temp; 
        elem_num++;
    }
    void pop_back(){//弹出末尾元素
        if(elem_num<=0)
            cout<<"error"<<endl;
        elem_num--;
    }
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
class VectorIterator{
    T *p{nullptr};
public:
    friend class Vector<T>;
public:
    VectorIterator(){}
    VectorIterator(T *_p){p=_p;}
    VectorIterator(const VectorIterator &v){p=v.p;}
    ~VectorIterator(){p=nullptr;}
    VectorIterator& operator++(){
        p++;
        return *this;
    }
    VectorIterator operator++(int){
        VectorIterator temp(*this);
        ++p;
        return temp;
    }
    VectorIterator& operator--(){
        p--;
        return *this;
    }
    VectorIterator operator--(int){
        VectorIterator temp(*this);
        --p;
        return temp;
    }
    VectorIterator operator+=(int n){
        p+=n;
        return *this;
    }
    VectorIterator operator-=(int n){
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