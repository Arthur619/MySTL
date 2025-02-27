#include <iostream>
using namespace std;

template <class T1,class T2>
class MapIterator;//����������


template <class T1,class T2>
class Node_for_map{//�ڵ���
public:
    T1 key;//һ����һ��ֵ
    T2 value;
};


template <class T1,class T2>
class Map{
    Node_for_map<T1,T2> *p{nullptr};
    int elem_num{0};//Ԫ�ظ���
public:
    typedef pair<T1,T2> value_type;//����insert��������value_type����
    typedef MapIterator<T1,T2> iterator;//������
public:
    Map(){}
    ~Map(){p=nullptr;}
    void insert(const pair<T1,T2> x){//��map�в���pairԪ��,˼·��vector��ͬ
        if (count(x.first)==0){//�ж�key�Ƿ��ظ����ظ���ִ��
            Node_for_map<T1, T2> *temp = new Node_for_map<T1, T2>[elem_num + 1];//����size+1���ռ�
            if (p != nullptr)
                memcpy(temp, p, sizeof(Node_for_map<T1, T2>) * elem_num);//��ԭ��Ԫ�ظ�ֵ��temp
            temp[elem_num].key = x.first;//����Ԫ�ظ�ֵ��temp
            temp[elem_num].value = x.second;
            elem_num += 1;
            p = temp;
        }
        else
            cout<<"This key has existed:"<<x.first<<endl;
    }
    Node_for_map<T1,T2>* begin(){//����ͷָ��
        return &p[0];
    }
    Node_for_map<T1,T2>* end(){//����βָ��
        return &p[elem_num];
    }
    T2& operator[](const T1& key){//������ķ�ʽֱ�Ӹ�ֵmap[x]=y
        insert(pair<T1,T2>(key, T2()));//��keyֵ��value��ֵѹ������
        return find(key)->value;//����y�������Թ��޸�         ����˵,ʹ�á�map[x]��ʱ���������й����˼�ֵ�Բ����ؿ�ֵvalue�����ã���ϡ�=y����ɸ�ֵ
    }
    Node_for_map<T1,T2>* find(T1 key){//�ҵ�key��Ӧvalue�ĵ�ַ
        for(int i=0;i<elem_num;i++){
            if(key==p[i].key)
                return &p[i];//�ҵ�֮�󷵻�һ��node*��������key��value
        }
        return &p[elem_num];//���򷵻�end()
    }
    bool count(T1 key){//�ж�key�Ƿ����
        int sum=0;
        for(int i=0;i<elem_num;i++){
            if(key==p[i].key)
                return 1;//���ַ���1
        }
        return 0;//���򷵻�0
    }
    void clear(){//���
        for(int i=0;i<elem_num;i++)
            p[i]=NULL;
        elem_num=0;
    }
    int size()const{return elem_num;}//����Ԫ�ظ���
    bool empty(){return elem_num==0;}//�Ƿ�Ϊ��
    void show(){//���mapԪ��
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
    //Ч������
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
