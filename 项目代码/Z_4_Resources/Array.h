#pragma once
#include<iostream>
using namespace std;
class Array {
public:
    template<typename ...Args>
    Array(Args... args);//构造函数

    ~Array();//析构函数
    Array(Array& a);//复制构造函数

    template<typename ...Args>
    void reshape(Args... args);//重塑

    int* get_content();//得到数据的指针

    Array operator[](int index);//重载[]
    Array& operator=(int data);//重载=，将int赋值给底层
    Array& operator=(const Array& a);//重载=，两个类之间传递
    friend Array operator +(Array& a, Array& b);//矩阵加法
    friend Array operator -(Array& a, Array& b);//矩阵减法
    friend Array operator *(Array& a, Array& b);//矩阵乘法
    friend Array operator /(Array& a, Array& b);//矩阵除法
    operator int();//转化为int数据

    int* data;//底层一维数组，储存数据

    int index;//指针，指向当前数据位置（相当于data的下标)

    int shape[16];//储存每一维度信息，便于指针变幻时操作

    int axisNum;//储存总维数

    int nowAxis;//当前维数

    int sum;//数据个数

    bool isSon;//是否是子矩阵

};

template<typename ...Args>
Array::Array(Args... args) {
    // 获取参数包大小并转换为size_t数组
    auto num = sizeof...(args);
    size_t list[16] = { args... };
    if (num >= 16)//限定了一个范围，可以改动
    {
        cout << "输入参数过多！";
        exit(0);
    }

    axisNum = num;//总维数
    nowAxis = 0;//现在处于最底层的0维
    index = 0;//指针指向第0个
    isSon = false;//不是子矩阵

    sum = 1;
    for (int i = 0; i < num; i++)//记录下每一维数的个数
    {
        shape[i] = list[i];
        sum *= list[i];
    }

    if (num != 0)//如果num不是0，就动态申请sum个数据
    {
        data = new int[sum];
    }
    else
        data = NULL;
}

Array::Array(Array& a)
{
    //大部分数据直接平移过去赋值就好了
    index = a.index;
    axisNum = a.axisNum;
    nowAxis = a.nowAxis;
    sum = a.sum;
    for (int i = 0; i < 16; i++)
    {
        shape[i] = a.shape[i];
    }

    if (a.isSon)//如果是子矩阵
    {
        data = a.data;//共用同一段底层一维数据空间
    }
    else//不然就重新申请，并将数据复制过去
    {
        data = new int[sum];
        for (int i = 0; i < sum; i++)
            data[i] = a.data[i];
    }
}


template<typename ...Args>
void Array::reshape(Args... args)
{
    // 获取参数包大小并转换为size_t数组
    auto num = sizeof...(args);
    size_t list[16] = { args... };
    if (num >= 16)
    {
        cout << "输入参数过多！";
        exit(0);
    }

    //改变维数等一些基础数据大小
    axisNum = num;
    nowAxis = 0;
    index = 0;
    isSon = false;

    int nowsum = 1;
    for (int i = 0; i < num; i++)
    {
        shape[i] = list[i];
        nowsum *= list[i];
    }
    if (nowsum != sum)//注意到要判定如果一起的个数相乘出来不相同，就不能重塑
    {
        cout << "不能重塑" << endl;
        exit(0);
    }

}


Array::~Array()
{
    if (nowAxis == 0)//只有原矩阵需要析构
    {
         delete[] data;
    }
}

Array Array::operator[](int n) {//相当于构造一个子矩阵

    Array a;//暂时的子矩阵
    a.nowAxis = nowAxis + 1;//所处的维数+1
    a.axisNum = axisNum - 1;//总维数-1
    a.data = data;
    a.isSon = true;

    if (a.axisNum < 0)//如果进入的维数太高，就失败
    {
        cout << "维数过高" << endl;
        exit(0);
    }

    for (int i = 0; i < a.axisNum; i++)//注意到子矩阵的每一维度的信息是原矩阵下一维度的信息，这样就将原本的第0维信息丢掉了
    {
        a.shape[i] = shape[i + 1];
        a.sum *= shape[i + 1];
    }

    a.index = a.sum * n + index;//记录下现在一开始的指针位置
    return a;//返回子矩阵，调用了复制构造函数
}

Array& Array::operator=(int number) {
    this->data[index] = number;//是给底层的一维数组赋值
    return *this;
}

Array::operator int() {
    return data[index];//返回指针对应的底层数据的值
}

Array operator +(Array& a, Array& b)
{
    if (a.sum != b.sum || a.axisNum != b.axisNum)
    {
        cout << "运算对象不匹配" << endl;
        exit(0);
    }
    Array c;
    c = b;
    for (int i = 0; i < a.sum; i++)//逐项相加
        c.data[i] = a.data[i] + b.data[i];
    return c;
}

Array operator *(Array& a, Array& b)
{
    if (a.sum != b.sum || a.axisNum != b.axisNum)
    {
        cout << "运算对象不匹配" << endl;
        exit(0);
    }
    Array c;
    c = b;
    for (int i = 0; i < a.sum; i++)//逐项相乘
        c.data[i] = a.data[i] * b.data[i];
    return c;
}

Array operator -(Array& a, Array& b)
{
    if (a.sum != b.sum || a.axisNum != b.axisNum)
    {
        cout << "运算对象不匹配" << endl;
        exit(0);
    }
    Array c;
    c = b;
    for (int i = 0; i < a.sum; i++)//逐项相减
        c.data[i] = a.data[i] - b.data[i];
    return c;
}

Array operator /(Array& a, Array& b)
{
    if (a.sum != b.sum||a.axisNum!=b.axisNum )
    {
        cout << "运算对象不匹配" << endl;
        exit(0);
    }
    Array c;
    c = b;
    for (int i = 0; i < a.sum; i++)//逐项相除
        c.data[i] = a.data[i] / b.data[i];
    return c;
}
Array& Array::operator=(const Array& a)//基本上所有操作与复制构造函数相同，就是注意传入的值前面要加const
{
    axisNum = a.axisNum;
    nowAxis = a.nowAxis;
    sum = a.sum;
    for (int i = 0; i < 16; i++)
    {
        shape[i] = a.shape[i];
    }
    if (a.isSon)
    {
        data = a.data;
    }
    else
    {
        data = new int[sum];
        for (int i = 0; i < sum; i++)
            data[i] = a.data[i];
    }
    return *this;
}

int* Array::get_content() {
    return data;//返回底层数据的指针
}
