#pragma once
#include<iostream>
using namespace std;
class Array {
public:
    template<typename ...Args>
    Array(Args... args);//���캯��

    ~Array();//��������
    Array(Array& a);//���ƹ��캯��

    template<typename ...Args>
    void reshape(Args... args);//����

    int* get_content();//�õ����ݵ�ָ��

    Array operator[](int index);//����[]
    Array& operator=(int data);//����=����int��ֵ���ײ�
    Array& operator=(const Array& a);//����=��������֮�䴫��
    friend Array operator +(Array& a, Array& b);//����ӷ�
    friend Array operator -(Array& a, Array& b);//�������
    friend Array operator *(Array& a, Array& b);//����˷�
    friend Array operator /(Array& a, Array& b);//�������
    operator int();//ת��Ϊint����

    int* data;//�ײ�һά���飬��������

    int index;//ָ�룬ָ��ǰ����λ�ã��൱��data���±�)

    int shape[16];//����ÿһά����Ϣ������ָ����ʱ����

    int axisNum;//������ά��

    int nowAxis;//��ǰά��

    int sum;//���ݸ���

    bool isSon;//�Ƿ����Ӿ���

};

template<typename ...Args>
Array::Array(Args... args) {
    // ��ȡ��������С��ת��Ϊsize_t����
    auto num = sizeof...(args);
    size_t list[16] = { args... };
    if (num >= 16)//�޶���һ����Χ�����ԸĶ�
    {
        cout << "����������࣡";
        exit(0);
    }

    axisNum = num;//��ά��
    nowAxis = 0;//���ڴ�����ײ��0ά
    index = 0;//ָ��ָ���0��
    isSon = false;//�����Ӿ���

    sum = 1;
    for (int i = 0; i < num; i++)//��¼��ÿһά���ĸ���
    {
        shape[i] = list[i];
        sum *= list[i];
    }

    if (num != 0)//���num����0���Ͷ�̬����sum������
    {
        data = new int[sum];
    }
    else
        data = NULL;
}

Array::Array(Array& a)
{
    //�󲿷�����ֱ��ƽ�ƹ�ȥ��ֵ�ͺ���
    index = a.index;
    axisNum = a.axisNum;
    nowAxis = a.nowAxis;
    sum = a.sum;
    for (int i = 0; i < 16; i++)
    {
        shape[i] = a.shape[i];
    }

    if (a.isSon)//������Ӿ���
    {
        data = a.data;//����ͬһ�εײ�һά���ݿռ�
    }
    else//��Ȼ���������룬�������ݸ��ƹ�ȥ
    {
        data = new int[sum];
        for (int i = 0; i < sum; i++)
            data[i] = a.data[i];
    }
}


template<typename ...Args>
void Array::reshape(Args... args)
{
    // ��ȡ��������С��ת��Ϊsize_t����
    auto num = sizeof...(args);
    size_t list[16] = { args... };
    if (num >= 16)
    {
        cout << "����������࣡";
        exit(0);
    }

    //�ı�ά����һЩ�������ݴ�С
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
    if (nowsum != sum)//ע�⵽Ҫ�ж����һ��ĸ�����˳�������ͬ���Ͳ�������
    {
        cout << "��������" << endl;
        exit(0);
    }

}


Array::~Array()
{
    if (nowAxis == 0)//ֻ��ԭ������Ҫ����
    {
         delete[] data;
    }
}

Array Array::operator[](int n) {//�൱�ڹ���һ���Ӿ���

    Array a;//��ʱ���Ӿ���
    a.nowAxis = nowAxis + 1;//������ά��+1
    a.axisNum = axisNum - 1;//��ά��-1
    a.data = data;
    a.isSon = true;

    if (a.axisNum < 0)//��������ά��̫�ߣ���ʧ��
    {
        cout << "ά������" << endl;
        exit(0);
    }

    for (int i = 0; i < a.axisNum; i++)//ע�⵽�Ӿ����ÿһά�ȵ���Ϣ��ԭ������һά�ȵ���Ϣ�������ͽ�ԭ���ĵ�0ά��Ϣ������
    {
        a.shape[i] = shape[i + 1];
        a.sum *= shape[i + 1];
    }

    a.index = a.sum * n + index;//��¼������һ��ʼ��ָ��λ��
    return a;//�����Ӿ��󣬵����˸��ƹ��캯��
}

Array& Array::operator=(int number) {
    this->data[index] = number;//�Ǹ��ײ��һά���鸳ֵ
    return *this;
}

Array::operator int() {
    return data[index];//����ָ���Ӧ�ĵײ����ݵ�ֵ
}

Array operator +(Array& a, Array& b)
{
    if (a.sum != b.sum || a.axisNum != b.axisNum)
    {
        cout << "�������ƥ��" << endl;
        exit(0);
    }
    Array c;
    c = b;
    for (int i = 0; i < a.sum; i++)//�������
        c.data[i] = a.data[i] + b.data[i];
    return c;
}

Array operator *(Array& a, Array& b)
{
    if (a.sum != b.sum || a.axisNum != b.axisNum)
    {
        cout << "�������ƥ��" << endl;
        exit(0);
    }
    Array c;
    c = b;
    for (int i = 0; i < a.sum; i++)//�������
        c.data[i] = a.data[i] * b.data[i];
    return c;
}

Array operator -(Array& a, Array& b)
{
    if (a.sum != b.sum || a.axisNum != b.axisNum)
    {
        cout << "�������ƥ��" << endl;
        exit(0);
    }
    Array c;
    c = b;
    for (int i = 0; i < a.sum; i++)//�������
        c.data[i] = a.data[i] - b.data[i];
    return c;
}

Array operator /(Array& a, Array& b)
{
    if (a.sum != b.sum||a.axisNum!=b.axisNum )
    {
        cout << "�������ƥ��" << endl;
        exit(0);
    }
    Array c;
    c = b;
    for (int i = 0; i < a.sum; i++)//�������
        c.data[i] = a.data[i] / b.data[i];
    return c;
}
Array& Array::operator=(const Array& a)//���������в����븴�ƹ��캯����ͬ������ע�⴫���ֵǰ��Ҫ��const
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
    return data;//���صײ����ݵ�ָ��
}
