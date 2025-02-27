#include "Vector.h"
#include "Stack.h"
#include "Map.h"
#include "List.h"
#include "MyAlgorithm.h"
#include <iostream>
#include <fstream>
using namespace std;


void clear(void)
{
    cout << "====================================" << endl;
}
int fc(int e)
{
    return e * e;
}
int fc2(int e)
{
    return 2 * e;
}
bool fc3(int e)
{
    return (e >= 0);
}
bool fc4(int i) { return ((i % 2) == 1); }
bool fc5(int i, int j) {
   return (i == j);
}
bool IsOdd(int i) { return ((i % 2) == 1); }
bool mypredicate(int i, int j)
{
    return (i == j);
}




int main()
{
    Vector<int> vec;
    ostream_iterator<int> output(cout, " "); // 定义用于输出的流迭代�?
    Vector<int> vec2{10, 2, 7, 8, 9};
    List<int> lis;
    lis.push_back(10);
    lis.push_back(2);
    lis.push_back(7);
    lis.push_back(8);
    lis.push_back(9);

    ifstream myfile("hello.txt");//读入�?
    ofstream outfile("out.txt", ios::app); //从文件末尾开始写，防止原文件丢失�?
    string temp;
    if (!myfile.is_open())
    {
        cout << "can't open file" << endl;
    }
    char ch;
        while(!myfile.eof())
    {
        myfile.get(ch);
        ch=(int)ch-48;
        vec.push_back(ch);
    };


    cout<<"START:"<<endl;
    clear();
    cout<<"(1)mysearch_n:"<<endl;
    for(int i=0;i<5;i++)
        cout<<vec[i]<<endl;
    mysearch_n(vec.begin(),vec.end(),1);//寻找元素，输出位置与个数
    clear();
    mysearch_n(vec.begin(),vec.end(),6);
    clear();


    cout<<"(2)binarySearch:"<<endl;
    cout<<binarySearch(vec.begin(),vec.end(),2)<<endl;//寻找元素，找到返�?1，否�?0
    clear();
    cout<<binarySearch2(vec.begin(),vec.end(),6)<<endl;
    clear();


    Vector<int> vec4(1,2,3,4,5);
    cout<<"(3)myrotate:"<<endl;
    myrotate(vec4.begin(),vec4.begin()+2,vec4.end());//将前n个元素交换到容器末尾
    for(int i=0;i<5;i++)
        cout<<vec4[i]<<endl;
    clear();//12345->34512
    myrotate(vec4.begin(),vec4.begin()+2,vec4.end());//再次进行相同操作
    for(int i=0;i<5;i++)
        cout<<vec4[i]<<endl;
    clear();//34512->51234


    cout<<"(4)generate_n:"<<endl;
    generate_n(vec.begin(),vec.end(),vec2.begin(),vec2.end(),fc,fc2); //根据用户想要的方�?(fc,fc2)对区间元素进行更�?
    for(int i=0;i<5;i++)
        cout<<vec[i]<<endl;
    clear();


    cout<<"(5)myreplace_if:"<<endl;
    myreplace_if(vec2.begin(),vec2.end(),fc3,0);//如果区间内的元素满足fc3，置其为0
    for(int i=0;i<5;i++)
        cout<<vec2[i]<<endl;
    clear();


    cout<<"(6)mycopy:"<<endl;
    mycopy(vec2.begin(),vec2.end(),output);//将选定区间内元素拷贝至另一个容�?
    cout<<endl;
    clear();


    //用顺序或逆序两种方式对元素进行排序�?(0逆续�?1升续)
    cout<<"(7)mysort:"<<endl;
    List<int>::iterator it1=lis.begin();
    List<int>::iterator it2=lis.end();
    mysort(it1,it2,1);
    for (List<int>::iterator it = lis.begin(); it != lis.end(); it++)
        cout << ' ' << *it;
    cout<<endl;
    clear();


    //将区间里面的值赋值到result开始的位置上，除了函数对象(fc4)比对结果为false的值�?
    cout<<"(8)myremove_copy_if:"<<endl;
    int myints[] = { 1,2,3,4,5 };
    Vector<int> myvector(5,0);
    myremove_copy_if(myints, myints + 5, myvector.begin(), fc4);
    cout << "myvector contains:";
    for (Vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        cout << ' ' << *it;
    cout << '\n';
    clear();


    //遍历查找两个容器，返回第一个找到的两个空间中满足函数对象的元素，返回迭代器对�?
    cout<<"(9)mymismatch:"<<endl;
    Vector<int> myvector1;
    for (int i = 1; i < 5; i++)
        myvector1.push_back(i * 10); // myvector1: 10 20 30 40 50
    int s[5]={ 10, 20, 80, 320, 1024 };          //   st: 10 20 80 320 1024
    pair<Vector<int>::iterator, int* > mypair;
    mypair = mymismatch(myvector1.begin(), myvector1.end(), s, fc5);
    cout << "Second mismatching elements: " << *mypair.first;
    cout << " and " << *mypair.second << '\n';
    clear();


    //遍历查找整个容器，返回指向第一个满足函数对�?(fc3)的值的迭代器，否则返回指向最后一个值的迭代器�?
    cout<<"(10)myfind_if:"<<endl;
    cout << *myfind_if(vec.begin(), vec.end(), fc3) << endl;
    clear();


    //测试stack
    cout<<"stack:"<<endl;
    Stack<int> st;
    for (int i = 0; i < 5; i++)
        st.push(i);
    cout <<"size:"<<st.size()<<endl;
    for (int i = 0; i < 5; i++) {
        cout << st.top()<<' ';
        st.pop();
    }
    cout<<endl<<st.empty()<<endl;


    //测试map
    clear();
    cout<<"map:"<<endl;
    Map<string,int> ma;
    ma.insert(pair<string,int>("a",1));//insert插入pair
    ma["b"]=2;//直接赋值插�?
    ma["c"]=3;
    cout<<ma.count("c")<<endl;//是否含有该key，有1�?0
    ma.show();//格式化输出键值对
    cout<<"size:"<<ma.size()<<endl;
    for(Map<string,int>::iterator it=ma.begin();it!=ma.end();it++){//指针操作输出键值对
        cout<<"key:"<<(*it).key<<"  "<<"value:"<<(*it).value<<endl;
    }


    outfile<<"vec:"<<endl;
    for(int i=0;i<5;i++)
        outfile<<vec[i]<<endl;
    outfile<<"myvec:"<<endl;
    for(int i=0;i<5;i++)
        outfile<<myvector[i]<<endl;    
    return 0;
}