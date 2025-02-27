#include <iostream>
using namespace std;

template <class T1,class T2>
class MapIterator;//声明迭代器


template <class T1,class T2>
class Node_for_map{//节点类
public:
    T1 key;//一个键一个值
    T2 value;
};


template <class T1,class T2>
class Map{
    Node_for_map<T1,T2> *p{nullptr};
    int elem_num{0};//元素个数
public:
    typedef pair<T1,T2> value_type;//用于insert函数插入value_type数据
    typedef MapIterator<T1,T2> iterator;//迭代器
public:
    Map(){}
    ~Map(){p=nullptr;}
    void insert(const pair<T1,T2> x){//向map中插入pair元素,思路与vector相同
        if (count(x.first)==0){//判断key是否重复，重复则不执行
            Node_for_map<T1, T2> *temp = new Node_for_map<T1, T2>[elem_num + 1];//开辟size+1个空间
            if (p != nullptr)
                memcpy(temp, p, sizeof(Node_for_map<T1, T2>) * elem_num);//将原有元素赋值给temp
            temp[elem_num].key = x.first;//将新元素赋值给temp
            temp[elem_num].value = x.second;
            elem_num += 1;
            p = temp;
        }
        else
            cout<<"This key has existed:"<<x.first<<endl;
    }
    Node_for_map<T1,T2>* begin(){//返回头指针
        return &p[0];
    }
    Node_for_map<T1,T2>* end(){//返回尾指针
        return &p[elem_num];
    }
    T2& operator[](const T1& key){//用数组的方式直接赋值map[x]=y
        insert(pair<T1,T2>(key, T2()));//将key值与value空值压入容器
        return find(key)->value;//返回y的引用以供修改         简单来说,使用“map[x]”时，在容器中构建了键值对并返回空值value的引用，结合“=y”完成赋值
    }
    Node_for_map<T1,T2>* find(T1 key){//找到key对应value的地址
        for(int i=0;i<elem_num;i++){
            if(key==p[i].key)
                return &p[i];//找到之后返回一个node*，包含有key与value
        }
        return &p[elem_num];//否则返回end()
    }
    bool count(T1 key){//判断key是否出现
        int sum=0;
        for(int i=0;i<elem_num;i++){
            if(key==p[i].key)
                return 1;//出现返回1
        }
        return 0;//否则返回0
    }
    void clear(){//清空
        for(int i=0;i<elem_num;i++)
            p[i]=NULL;
        elem_num=0;
    }
    int size()const{return elem_num;}//返回元素个数
    bool empty(){return elem_num==0;}//是否为空
    void show(){//输出map元素
        cout.width(8);
        cout<<"key";
        cout.width(8);
        cout<<"value"<<endl;
        for(auto *_p=&p[0];_p!=&p[elem_num];_p++){
            cout.width(8);
            cout<<_p->key;
            cout.width(8);
            cout<<_p->value<<endl;
        }
    }
    //效果如下
    //     key   value
    //       1       2
};


template <class T1,class T2>
class MapIterator{
    Node_for_map<T1,T2> *p{nullptr};
public:
    friend class Map<T1,T2>;
public:
    MapIterator(){}
    MapIterator(Node_for_map<T1,T2> *_p){p=_p;}
    MapIterator(const MapIterator &v){p=v.p;}
    ~MapIterator(){p=nullptr;}
    MapIterator& operator++(){
        p++;
        return *this;
    }
    MapIterator operator++(int){
        MapIterator temp(*this);
        ++p;
        return temp;
    }
    MapIterator& operator--(){
        p--;
        return *this;
    }
    MapIterator operator--(int){
        MapIterator temp(*this);
        --p;
        return temp;
    }
    MapIterator operator+=(int n){
        p+=n;
        return *this;
    }
    MapIterator operator-=(int n){
        p-=n;
        return *this;
    }
    bool operator==(Node_for_map<T1,T2>* t){
        return p==t;
    }
    bool operator!=(Node_for_map<T1,T2>* t){
        return p!=t;
    }
    Node_for_map<T1,T2>& operator*()const{
        return *p;
    }
    Node_for_map<T1,T2>& operator->()const{
        return &p;
    }
};
