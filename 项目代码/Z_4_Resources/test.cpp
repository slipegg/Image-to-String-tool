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
char drch[9000000];//储存字符数据
char drawChar[20] = { 'M','N','H','Q','$','O','C','?','7','>','!',':','-',';','.' };//基础字符
void testP_RandCF(FastPrinter& printer,char* a,int x,int y) {
    char* dataBuffer = a;
    BYTE* frontColorBuffer = new BYTE[x*y * 3];
    BYTE* backColorBuffer = new BYTE[x*y * 3];
    printer.cleanSrceen();//清屏

  for (int i = 0; i < x * y; i++)//设置背景色为白，前景色为黑
    {
        frontColorBuffer[i * 3] = 0;
        frontColorBuffer[i * 3 + 1] = 0;
        frontColorBuffer[i * 3 + 2] = 0;
        backColorBuffer[i * 3] = 255;
        backColorBuffer[i * 3 + 1] = 255;
        backColorBuffer[i * 3 + 2] = 255;
    }

    printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);//设置数据
    printer.draw(true);//绘制
    delete[] frontColorBuffer;
    delete[] backColorBuffer;
}

void changetoPhoto()//对图片操作
{
    PicReader imread;
    BYTE* data = nullptr;
    UINT x, y;
    const char* photoName = { "lena.jpg" };
    if (photoName == NULL)
    {
        cout << "打开图片失败" << endl;
        exit(0);
    }
    imread.readPic(photoName);//读取图片
    Array picdata;
    imread.getData(picdata, x, y);//将图片的像素信息储存到array里
    Array grayPicData(y, x);
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            grayPicData[i][j] = (picdata[i][j][0] * 299 + picdata[i][j][1] * 587 + picdata[i][j][2] * 114 + 500) / 1000;//将每个像素的RGB转化为灰度值
        }
    }

    int n = 0, num = 0;
    for (int i = 0; i + 3 < y; i += 4)
    {
        for (int j = 0; j + 1 < x; j += 2)//将2*4的像素信息求和、平均，转化为字符储存到drch
        {
            num = (grayPicData[i][j] + grayPicData[i + 1][j] + grayPicData[i + 2][j] + grayPicData[i + 3][j] + grayPicData[i][j + 1] + grayPicData[i + 1][j + 1] + grayPicData[i + 2][j + 1] + grayPicData[i + 3][j + 1] + 8);
            drch[n++] = drawChar[num / 8 / 17];
        }
    }

    FastPrinter printer(x / 2,y / 4,5);//设置控制台
    DWORD tic;
    tic = GetTickCount();
    testP_RandCF(printer,drch, x / 2, y / 4);//展示图片
    getchar();
}

void changetoVideo()
{
    system("CLS");
    cout << "正在转化ing"<<endl;
    PicReader imread;
    BYTE* data = nullptr;
    UINT x, y;
    string a1 = "videopicture\\video", a2, a3 = ".jpg", a4 = ".txt",a5="videotxt\\";//图片名称
    for (int i = 0; i < 2254; i++)
    {
        if (i % 100 == 0&&i!=0)//每完成100张就提醒一下
            cout << "已转换" << i << "张" << endl;
        a2 = to_string(i);//数字转化为字符串
        if (i < 10)//设置好0
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

        string pictureName = a1 + a2 + a3;//第i张图片的文件名称
        const char* pictureFIleName = pictureName.c_str();

        ofstream drawFile(a5 + a2+ a4);//创建打开这一txt文件

        imread.readPic(pictureFIleName);//打开第i张图片
        Array picdata;
        imread.getData(picdata, x, y);//获取图片信息
        Array grayPicData(y, x);

        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                grayPicData[i][j] = (picdata[i][j][0] * 299 + picdata[i][j][1] * 587 + picdata[i][j][2] * 114 + 500) / 1000;//转化为灰度值
            }
        }


        int  num = 0;
        char picChar=NULL;
        for (int i = 0; i + 3 < y; i += 4)
        {
            for (int j = 0; j + 1 < x; j += 2)//将2*4的像素信息求和、平均，转化为字符储存到picChar，然后储存到文件中
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

void showVideo()//展示视频
{
    //先读取第一张，这样好知道之后的图片宽和长，然后初始化picdata
    PicReader imread;
    UINT x, y;
    const char* pictureFIleName = "videopicture\\video0000.jpg";
    imread.readPic(pictureFIleName);//打开第0张图片
    Array picdata;
    imread.getData(picdata, x, y);//获取它的信息

    FastPrinter printer(x/2, y/4, 5);//先生成一个控制台
    string   textFront = "videotxt\\",txtnum, txtEnd = ".txt";
    PlaySound(TEXT("辉夜大小姐op.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音乐
    clock_t starttime = clock(), endtime;//记录时间
    for (int i = 0; i < 2254; i++)
    {
        //获取第i张图片对应的txt的文件名
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
        ifstream inDrawFile(textFront + txtnum + txtEnd);//打开图片文件
        if (!inDrawFile)
        {
               cout << "打开图片txt失败";
               exit(0);
        }

        for (int j = 0; j < x * y / 8; j++)//一个一个get字符，然后放到drch里
        {
            drch[j] = inDrawFile.get();
        }

        DWORD tic;
        tic = GetTickCount();
        testP_RandCF(printer, drch, x / 2, y / 4);//展示这张图片
        endtime = clock();
        int sum = endtime - starttime;//得到现在的耗时
        if (sum < 40*(i+1))//停顿相应的时间
        {
            Sleep(40*(i+1) - sum);
        }
    }
}

int main()
{
    cout << "展示图片请安1\n将图片转换为txt请按2\n展示字符视频请按3\n";
    char a;
    a = _getch();
    switch (a)//根据选择进行不同操作
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