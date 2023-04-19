#include "PicReader.h"
#include "FastPrinter.h"
#include"Array.h"
#include <stdio.h>
#include<string.h>
#include <sstream>
#include<iostream>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<time.h>
#include<fstream>
#include<conio.h>
#include <stdlib.h>
using namespace std;
char drch[9000000];//�����ַ�����
char drawChar[20] = { 'M','N','H','Q','$','O','C','?','7','>','!',':','-',';','.' };//�����ַ�
void testP_RandCF(FastPrinter& printer,char* a,int x,int y) {
    char* dataBuffer = a;
    BYTE* frontColorBuffer = new BYTE[x*y * 3];
    BYTE* backColorBuffer = new BYTE[x*y * 3];
    printer.cleanSrceen();//����

  for (int i = 0; i < x * y; i++)//���ñ���ɫΪ�ף�ǰ��ɫΪ��
    {
        frontColorBuffer[i * 3] = 0;
        frontColorBuffer[i * 3 + 1] = 0;
        frontColorBuffer[i * 3 + 2] = 0;
        backColorBuffer[i * 3] = 255;
        backColorBuffer[i * 3 + 1] = 255;
        backColorBuffer[i * 3 + 2] = 255;
    }

    printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);//��������
    printer.draw(true);//����
    delete[] frontColorBuffer;
    delete[] backColorBuffer;
}

void changetoPhoto()//��ͼƬ����
{
    PicReader imread;
    BYTE* data = nullptr;
    UINT x, y;
    const char* photoName = { "lena.jpg" };
    if (photoName == NULL)
    {
        cout << "��ͼƬʧ��" << endl;
        exit(0);
    }
    imread.readPic(photoName);//��ȡͼƬ
    Array picdata;
    imread.getData(picdata, x, y);//��ͼƬ��������Ϣ���浽array��
    Array grayPicData(y, x);
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            grayPicData[i][j] = (picdata[i][j][0] * 299 + picdata[i][j][1] * 587 + picdata[i][j][2] * 114 + 500) / 1000;//��ÿ�����ص�RGBת��Ϊ�Ҷ�ֵ
        }
    }

    int n = 0, num = 0;
    for (int i = 0; i + 3 < y; i += 4)
    {
        for (int j = 0; j + 1 < x; j += 2)//��2*4��������Ϣ��͡�ƽ����ת��Ϊ�ַ����浽drch
        {
            num = (grayPicData[i][j] + grayPicData[i + 1][j] + grayPicData[i + 2][j] + grayPicData[i + 3][j] + grayPicData[i][j + 1] + grayPicData[i + 1][j + 1] + grayPicData[i + 2][j + 1] + grayPicData[i + 3][j + 1] + 8);
            drch[n++] = drawChar[num / 8 / 17];
        }
    }

    FastPrinter printer(x / 2,y / 4,5);//���ÿ���̨
    DWORD tic;
    tic = GetTickCount();
    testP_RandCF(printer,drch, x / 2, y / 4);//չʾͼƬ
    getchar();
}

void changetoVideo()
{
    system("CLS");
    cout << "����ת��ing"<<endl;
    PicReader imread;
    BYTE* data = nullptr;
    UINT x, y;
    string a1 = "videopicture\\video", a2, a3 = ".jpg", a4 = ".txt",a5="videotxt\\";//ͼƬ����
    for (int i = 0; i < 2254; i++)
    {
        if (i % 100 == 0&&i!=0)//ÿ���100�ž�����һ��
            cout << "��ת��" << i << "��" << endl;
        a2 = to_string(i);//����ת��Ϊ�ַ���
        if (i < 10)//���ú�0
        {
            a2 = "000" + a2;
        }
        if (i >= 10 && i < 100)
        {
            a2 = "00" + a2;
        }
        if (i >= 100 && i < 1000)
        {
            a2 = "0" + a2;
        }

        string pictureName = a1 + a2 + a3;//��i��ͼƬ���ļ�����
        const char* pictureFIleName = pictureName.c_str();

        ofstream drawFile(a5 + a2+ a4);//��������һtxt�ļ�

        imread.readPic(pictureFIleName);//�򿪵�i��ͼƬ
        Array picdata;
        imread.getData(picdata, x, y);//��ȡͼƬ��Ϣ
        Array grayPicData(y, x);

        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                grayPicData[i][j] = (picdata[i][j][0] * 299 + picdata[i][j][1] * 587 + picdata[i][j][2] * 114 + 500) / 1000;//ת��Ϊ�Ҷ�ֵ
            }
        }


        int  num = 0;
        char picChar=NULL;
        for (int i = 0; i + 3 < y; i += 4)
        {
            for (int j = 0; j + 1 < x; j += 2)//��2*4��������Ϣ��͡�ƽ����ת��Ϊ�ַ����浽picChar��Ȼ�󴢴浽�ļ���
            {
                num = (grayPicData[i][j] + grayPicData[i + 1][j] + grayPicData[i + 2][j] + grayPicData[i + 3][j] + grayPicData[i][j + 1] + grayPicData[i + 1][j + 1] + grayPicData[i + 2][j + 1] + grayPicData[i + 3][j + 1] + 8);
                picChar = drawChar[num / 8 / 17];
                drawFile.put(picChar);
            }
        }
        drawFile.put('\0');
        drawFile.close();
    }
}

void showVideo()//չʾ��Ƶ
{
    //�ȶ�ȡ��һ�ţ�������֪��֮���ͼƬ��ͳ���Ȼ���ʼ��picdata
    PicReader imread;
    UINT x, y;
    const char* pictureFIleName = "videopicture\\video0000.jpg";
    imread.readPic(pictureFIleName);//�򿪵�0��ͼƬ
    Array picdata;
    imread.getData(picdata, x, y);//��ȡ������Ϣ

    FastPrinter printer(x/2, y/4, 5);//������һ������̨
    string   textFront = "videotxt\\",txtnum, txtEnd = ".txt";
    PlaySound(TEXT("��ҹ��С��op.wav"), NULL, SND_FILENAME | SND_ASYNC);//��������
    clock_t starttime = clock(), endtime;//��¼ʱ��
    for (int i = 0; i < 2254; i++)
    {
        //��ȡ��i��ͼƬ��Ӧ��txt���ļ���
        txtnum = to_string(i);
        if (i < 10)
        {
            txtnum = "000" + txtnum;
        }
        if (i >= 10 && i < 100)
        {
            txtnum = "00" + txtnum;
        }
        if (i >= 100 && i < 1000)
        {
            txtnum = "0" + txtnum;
        }

        string h = textFront + txtnum + txtEnd;
        ifstream inDrawFile(textFront + txtnum + txtEnd);//��ͼƬ�ļ�
        if (!inDrawFile)
        {
               cout << "��ͼƬtxtʧ��";
               exit(0);
        }

        for (int j = 0; j < x * y / 8; j++)//һ��һ��get�ַ���Ȼ��ŵ�drch��
        {
            drch[j] = inDrawFile.get();
        }

        DWORD tic;
        tic = GetTickCount();
        testP_RandCF(printer, drch, x / 2, y / 4);//չʾ����ͼƬ
        endtime = clock();
        int sum = endtime - starttime;//�õ����ڵĺ�ʱ
        if (sum < 40*(i+1))//ͣ����Ӧ��ʱ��
        {
            Sleep(40*(i+1) - sum);
        }
    }
}

int main()
{
    cout << "չʾͼƬ�밲1\n��ͼƬת��Ϊtxt�밴2\nչʾ�ַ���Ƶ�밴3\n";
    char a;
    a = _getch();
    switch (a)//����ѡ����в�ͬ����
    {
    case '1':
    {
        changetoPhoto();
        break;
    }
    case '2':
    {
        changetoVideo();
        break;
    }
    case '3':
    {
        showVideo();
        break;
    }
    }
    return 0;
}