#include <iostream>
using namespace std;

template <typename T>
class VectorIterator;//����������


//vector��
template<typename T>
class Vector{
    T *p{nullptr};
    int elem_num{0};
public:
    typedef VectorIterator<T> iterator;

public:

    Vector(int s=0):elem_num(s){//���������С������
        if(s==0)
            p=nullptr;
        else
            p=new T(s);
    }
    ~Vector(){//��������
        if(p!=nullptr)
            delete[] p;
    }
    Vector(Vector& other){//���ƹ���
        elem_num=other.elem_num;//�Ƚ���С����
        if(other.elem_num==0)
            p=nullptr;
        else{
            p=new T(elem_num);
            memcpy(p,other.p,sizeof(T)*elem_num);//�����memcpy(Ŀ�꣬���У���С)������������Χ�����ݸ�Ŀ��
        }
    }
    Vector(int n,T elem){//ʹ��n��elem��ʼ��
        p=new T(n);//���ٿռ�
        elem_num=n;
        for(int i=0;i<n;i++)//��ֵ
            p[i]=elem;
    }
    
    //���������
    template <typename...Types>
    Vector(const T &arg,const Types &...args){
        elem_num++;
        p=new T(1);
        p[0]=arg;//�Ƚ���һ��Ԫ��װ������
        func_init(args...);//����������Ԫ�ش��ݸ��ú���
    }
    template <typename...Types>
    void func_init(const T &arg,const Types &...args){
        push_back(arg);//ѹ���һ��
        func_init(args...);//�ݹ�
    }
    void func_init(){}//��Ԫ��ʱ����ú���
    //������������

    Vector& operator=(const Vector& other){//�ع�=
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
    friend ostream& operator<<(ostream &out,Vector &vec){//�ع����
        T* temp=vec.begin();
        while(temp!=vec.end()){
            out<<*temp<<' ';
            temp++;
            }
        out<<endl;
        return out;
    } //  <<a,�������a������Ԫ��

    bool empty(){return elem_num==0;}//�ж��Ƿ�Ϊ��
    int size(){return elem_num;}//����Ԫ�ظ���
    void insert(int n,T elem){//�ڵ�n��Ԫ��֮ǰ����Ԫ��elem
        elem_num++;//Ԫ�ظ�����+1
        T* temp=new T(elem_num);//���ٿռ�
        for(int i=0;i<n-1;i++){//��ǰn-1��Ԫ�ظ�ֵ��temp
            temp[i]=p[i];
        }
        temp[n]=elem;//elem��ֵ����
        for(int i=n+1;i<elem_num;i++){//�ٽ�����Ԫ�ظ�ֵ��temp
            temp[i]=p[i];
        }
        delete[] p;//ɾ��ԭָ��
        p=temp;
    }
    void insert(int n,int x,T elem){//�ٵ�n��λ�ò���n��elem,˼·ͬ��
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
    void push_back(T x){//��β�����Ԫ��
        T* temp=new T(elem_num+1);//���ٿռ�
        if(p!=nullptr){
            memcpy(temp,p,sizeof(T)*elem_num);//����Ԫ��
            delete[] p;//ɾ��ԭָ��
        } 
        temp[elem_num]=x;//�����Ԫ��
        p=temp; 
        elem_num++;
    }
    void pop_back(){//����ĩβԪ��
        if(elem_num<=0)
            cout<<"error"<<endl;
        elem_num--;
    }
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