#include <iostream>
using namespace std;


template <class T>
class ListIterator;

// ����ڵ�
template <class T>
struct Node
{
    Node<T>* pre;
    Node<T>* next;
    T data;

    Node():pre(nullptr), next(nullptr){}
    Node(const T& obj):data(obj), pre(nullptr), next(nullptr){}//����Ԫ�ع���
    Node(Node<T>& other):data(other.data), pre(nullptr), next(nullptr){}//��������
};

// ����
template <class T>
class List
{
private:
    Node<T>* head;//ͷָ��
    Node<T>* tail;//βָ��
    int elem_num;//Ԫ�ظ���
public:
    typedef ListIterator<T> iterator;

public:
    List() : head(new Node<T>()), tail(new Node<T>()), elem_num(0){//�޲ι���
        head->next = tail;
        tail->pre = head;
    }
    List(int s) : head(new Node<T>()), tail(new Node<T>()), elem_num(s){//ָ����С����
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
    List(List<T>& other) : head(new Node<T>()), tail(new Node<T>()), elem_num(other.elem_num){// �������캯��
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

    void push_back(Node<T>& other){//�Խڵ���ʽ���β��Ԫ��
        Node<T> *temp = new Node<T>(other);
        tail->pre->next = temp;
        temp->pre = tail->pre;
        temp->next = tail;
        tail->pre = temp;
        ++elem_num;
    }
    void push_back(const T& t){//�Ե���Ԫ����ʽ���β��Ԫ��
        Node<T> *temp = new Node<T>(t);
        tail->pre->next = temp;
        temp->pre = tail->pre;
        temp->next = tail;
        tail->pre = temp;
        ++elem_num;
    }
    void push_front(Node<T>& other){//�Խڵ���ʽ���ͷ��Ԫ��
        Node<T> *temp = new Node<T>(other);
        head->next->pre = temp;
        temp->next = head->next;
        head->next = temp;
        temp->pre = head;
        ++elem_num;
    }
    void push_front(const T& t){//�Ե���Ԫ����ʽ���ͷ��Ԫ��
        Node<T> *temp = new Node<T>(t);
        head->next->pre = temp;
        temp->next = head->next;
        head->next = temp;
        temp->pre = head;
        ++elem_num;
    }
    void pop_front(){//����ͷ��Ԫ��
        if (empty())
            return;
        Node<T> *tmp = head->next;
        head->next = tmp->next;
        tmp->next->pre = head;
        delete tmp;
        --elem_num;
    }
    void pop_back(){//����β��Ԫ��
        if (empty())
            return;
        Node<T> *tmp = tail->pre;
        tmp->pre->next = tail;
        tail->pre = tmp->pre;
        delete tmp;
        --elem_num;
    }
    bool empty(){return elem_num == 0 ;}//�ж��Ƿ�Ϊ��
    void clear(){//���
        while (!empty())
            pop_back();
    }
    Node<T>* begin() const{return head->next;}//����ͷָ��
    Node<T>* end() const{return tail;}//����βָ��,ָ�����һ��Ԫ��֮��
    Node<T>* second_last()const{return tail->pre;}//���ص�����һ��Ԫ�ص�ָ��
    T& front()const{return head->next->data;}//����ͷԪ�ص�����
    T& back()const{return tail->pre->data;}//����βԪ�ص�����
    int size() const{return elem_num;}//��С
    void insert(Node<T>* t, const T& other){
        Node<T>* temp = t;
        Node<T>* new_node = new Node<T>(other);
        temp->pre->next = new_node;
        new_node->pre = temp->pre;
        new_node->next = temp;
        temp->pre = new_node;
        ++elem_num;
    }

    void remove(const T& other){// ֻɾ����һ����ȵĽڵ�
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


//������
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
    ListIterator& operator++(){//ǰ��++
        p = p->next;
        return *this;
    }
    ListIterator operator++(int){//����++
        ListIterator temp = *this;
        ++(*this);
        return temp;
    }
    ListIterator& operator--(){//ǰ��--
        p = p->pre;
        return *this;
    }
    ListIterator operator--(int){//����--
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