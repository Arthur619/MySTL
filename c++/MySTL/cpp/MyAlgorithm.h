#include<iostream>
#include<iterator>
#include<functional>
using namespace std;
template<class T>
void myswap(T &a,T &b)
{
    T c(a);
    a=b;
    b=c;
}//交换；


template <class ForwardIterator,class Integer>
void mysearch_n(ForwardIterator first, ForwardIterator last, Integer target)
{
    int position=0;
    int count=0;
    
 try
 {
    for(;first!=last;++first,++position)
    {
        if(*first==target)
            {
                count++;
                cout<<"Located in the "<<position<<" ,";
            }
    }
 
    if(count==0)
    throw invalid_argument("Can't find the element");
}catch(exception &e)
{
    cout<<"Error:"<<e.what()<<endl;
    return;
}
    cout<<"position"<<endl;
    cout<<count<<endl;
}//返回给定区间内所查找内容出现的个数及在区间的位置；


template<class ForwardIterator,class T>
ForwardIterator  lowerBound(ForwardIterator first, ForwardIterator last, const T& val) {
    int len = last - first;  //元素个数
    while (len > 0) {
        int half = len >> 1;//将half右移一位，以取得完整元素；
        auto middle = first + half;
        if (*middle < val) {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else {
            len = half;
        }
    }
    return first;
}//查找第一个等于查找元素的位置,若无，则返回第一个大于他的元素位置，且只能用于有序区间；

template<class ForwardIterator,class T>
ForwardIterator  upperBound(ForwardIterator first, ForwardIterator last, const T& val) {
    int len = last - first;//同上
    while (len > 0) {
        int half = len >> 1;
        auto middle = first + half;
        if (*middle > val) {
            len = half;
        }
        else {
            first = middle;
            ++first;
            len = len - half - 1;
        }
    }
    return first;
}//查找第一个等于查找元素的位置，若无，则返回第一个小于该元素的位置，且只能用于有序区间；

template<class ForwardIterator,class T>
bool binarySearch(ForwardIterator first,ForwardIterator last, const T& val) {
    auto res = lowerBound(first, last, val);
    return res != last && *res == val;
}//利用lower_bound判断是否存在相等的元素，且只能用于有序区间；

template<class ForwardIterator,class T>
bool binarySearch2(ForwardIterator first,ForwardIterator last, const T& val) {
    auto res = upperBound(first, last, val);
    return *(res-1) == val;
}//利用upper_bound判断是否存在相等的元素，且只能用于有序区间；
//二分查找


template <class ForwardIterator>
void myrotate (ForwardIterator first, ForwardIterator middle,ForwardIterator last)
{
  ForwardIterator next = middle;
  while (first!=next)
  {
    myswap(*first++,*next++);
    if (next==last-1) next=middle;
    else if (first==middle) middle=next;
  }
}//翻转元素；将middle后的元素换至middle前；


//remove_copy
template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator myremove_copy_if(InputIterator first, InputIterator last,OutputIterator result, UnaryPredicate pred)
{
    while (first != last) {
        if (!pred(*first)) {
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
}


//copy
template<class InputIterator, class OutputIterator>
OutputIterator mycopy(InputIterator first, InputIterator last, OutputIterator result)
{
    while (first != last) {
        *result = *first;
        ++result; ++first;
    }
    return result;
}


//find_if
template<class InputIterator, class UnaryPredicate>
InputIterator myfind_if(InputIterator first, InputIterator last, UnaryPredicate pred){
    try{
        while (first != last) {
        if (pred(*first))
            return first;           
        ++first;
    }
    throw invalid_argument("The element doesn't exist!");
}catch(exception &e)
{
    cout<<"Error:"<<e.what()<<endl<<"Programming OVER!";
}
}
// template<class T>
// void myiter_swap(T &a,T &b)
// {
//     myswap(*a,*b);
// }

//sort
template <class InputIterator, class UnaryPredicate>
void mysort(InputIterator first, InputIterator last, UnaryPredicate pred) {
    int n = 0;
 for (; first != last; first++) {
        n++;
 }
    for (int i = 0; i < n; i++) {
        first--;
    }
    for (int i = 0; i <n; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (pred){
                if (*(first+j) > *(first+j + 1)){
                    myswap(*(first + j), *(first + j + 1));
                }
            }
            else {
                if (*(first + j) < *(first + j + 1)) {
                    myswap(*(first + j), *(first + j + 1));
                }
            }

        }
    }
}


//mismatch
template <class InputIterator1, class InputIterator2, class UnaryPredicate>
pair<InputIterator1, InputIterator2> 
mymismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, UnaryPredicate pred)
{
    while ( (first1 != last1) && (pred(* first1 , *first2)) )
    {
        ++first1; ++first2;
    }
    return std::make_pair(first1, first2);
}

//对给定两区间内元素分别以不同计算方式进行更改并输出；
template <class ForwardIterator,class annotherIterator,class Function>
void generate_n(ForwardIterator first1,ForwardIterator last1,annotherIterator first2,annotherIterator last2,Function func1,Function func2)
{
    while(first1!=last1&&first2!=last2)
    {
      *first1=func1(*first1);
      *first2=func2(*first2);
      pair<ForwardIterator,annotherIterator>p(first1,first2);
      cout<<*p.first<<" "<<*p.second<<endl; 
      first1++;
      first2++;
    }
}


//根据函数对象将元素值置换为传入参数
template < class ForwardIterator, class UnaryPredicate, class T >
void myreplace_if (ForwardIterator first, ForwardIterator last,
                   UnaryPredicate pred, const T& new_value)
{
  while (first!=last) {
    if (pred(*first))
    *first=new_value;
    ++first;
  }
}