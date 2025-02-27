#include <iostream>
using namespace std;


template <class T>
class ListIterator;

// 链表节点
template <class T>
struct Node
{
    Node<T>* pre;
    Node<T>* next;
    T data;

    Node():pre(nullptr), next(nullptr){}
    Node(const T& obj):data(obj), pre(nullptr), next(nullptr){}//单个元素构造
    Node(Node<T>& other):data(other.data), pre(nullptr), next(nullptr){}//拷贝构造
};

// 链表
template <class T>
class List
{
private:
    Node<T>* head;//头指针
    Node<T>* tail;//尾指针
    int elem_num;//元素个数
public:
    typedef ListIterator<T> iterator;

public:
    List() : head(new Node<T>()), tail(new Node<T>()), elem_num(0){//无参构造
        head->next = tail;
        tail->pre = head;
    }
    List(int s) : head(new Node<T>()), tail(new Node<T>()), elem_num(s){//指定大小构造
        head->next = tail;
        tail->pre = head;
        for (int i = 0; i < elem_num; i++)
        {
            Node<T>* tmp = new Node<T>();
            tail->pre->next = tmp;
            tmp->pre = tail->pre;
            tmp->next = tail;
            tail->pre = tmp;
        }
    }
    List(List<T>& other) : head(new Node<T>()), tail(new Node<T>()), elem_num(other.elem_num){// 拷贝构造函数
        head->next = tail;
        tail->pre = head;
        for (Node<T>* it = other.begin(); it != other.end(); it++)
            push_back(*it);
    }
    ~List(){
        if (head != NULL)
            delete head;
        if (tail != NULL)
            delete tail;
    }

    void push_back(Node<T>& other){//以节点形式添加尾部元素
        Node<T> *temp = new Node<T>(other);
        tail->pre->next = temp;
        temp->pre = tail->pre;
        temp->next = tail;
        tail->pre = temp;
        ++elem_num;
    }
    void push_back(const T& t){//以单个元素形式添加尾部元素
        Node<T> *temp = new Node<T>(t);
        tail->pre->next = temp;
        temp->pre = tail->pre;
        temp->next = tail;
        tail->pre = temp;
        ++elem_num;
    }
    void push_front(Node<T>& other){//以节点形式添加头部元素
        Node<T> *temp = new Node<T>(other);
        head->next->pre = temp;
        temp->next = head->next;
        head->next = temp;
        temp->pre = head;
        ++elem_num;
    }
    void push_front(const T& t){//以单个元素形式添加头部元素
        Node<T> *temp = new Node<T>(t);
        head->next->pre = temp;
        temp->next = head->next;
        head->next = temp;
        temp->pre = head;
        ++elem_num;
    }
    void pop_front(){//弹出头部元素
        if (empty())
            return;
        Node<T> *tmp = head->next;
        head->next = tmp->next;
        tmp->next->pre = head;
        delete tmp;
        --elem_num;
    }
    void pop_back(){//弹出尾部元素
        if (empty())
            return;
        Node<T> *tmp = tail->pre;
        tmp->pre->next = tail;
        tail->pre = tmp->pre;
        delete tmp;
        --elem_num;
    }
    bool empty(){return elem_num == 0 ;}//判断是否为空
    void clear(){//清空
        while (!empty())
            pop_back();
    }
    Node<T>* begin() const{return head->next;}//返回头指针
    Node<T>* end() const{return tail;}//返回尾指针,指向最后一个元素之后
    Node<T>* second_last()const{return tail->pre;}//返回倒数第一个元素的指针
    T& front()const{return head->next->data;}//返回头元素的引用
    T& back()const{return tail->pre->data;}//返回尾元素的引用
    int size() const{return elem_num;}//大小
    void insert(Node<T>* t, const T& other){
        Node<T>* temp = t;
        Node<T>* new_node = new Node<T>(other);
        temp->pre->next = new_node;
        new_node->pre = temp->pre;
        new_node->next = temp;
        temp->pre = new_node;
        ++elem_num;
    }

    void remove(const T& other){// 只删除第一个相等的节点
        if (empty())
            return;
        else{
            for (Node<T>* t = begin(); t != end(); t++){
                if (*t == other){
                    Node<T>* temp = t;
                    temp->next->pre = temp->pre;
                    temp->pre->next = temp->next;
                    delete temp;
                    --elem_num;
                    return;
                }
            }
        }
    }

    List<T>& operator=(const List<T> &other){
        if (this == &other)
            return *this;
        else{
            this->clear();
            Node<T>* it = other.begin();
            for (; it != other.end(); it++)
                push_back(*it);
            return *this;
        }
    }
    friend bool operator>(Node<T> n1,Node<T> n2){
        return n1.data>n2.data;
    }
    friend bool operator<(Node<T> n1,Node<T> n2){
        return n1.data<n2.data;
    }
};


//迭代器
template<class T>
class ListIterator
{
    Node<T> * p;
public:
    friend class List<T>;

public:
    ListIterator() :p(nullptr){}
    ListIterator(Node<T>* t):p(t){}
    ~ListIterator(){}
    ListIterator& operator++(){//前置++
        p = p->next;
        return *this;
    }
    ListIterator operator++(int){//后置++
        ListIterator temp = *this;
        ++(*this);
        return temp;
    }
    ListIterator& operator--(){//前置--
        p = p->pre;
        return *this;
    }
    ListIterator operator--(int){//后置--
        ListIterator temp = *this;
        --(*this);
        return temp;
    }
    ListIterator operator+(int i){
        ListIterator temp = *this;
        while(i>0)
        {
            temp.p=temp.p->next;
            i--;}
        return temp;
    }
    ListIterator operator-(int i){
        ListIterator temp = *this;
        while(i>0)
        {
            temp.p=temp.p->pre;
            i--;}
        return temp;
    }
    bool operator==(const ListIterator & other){
        return p == other.p;
    }

    bool operator!=(const ListIterator & other){
        return !(p == other.p);
    }

    Node<T>& operator->()const{return &p;}
    T& operator*(){return p->data;}
};