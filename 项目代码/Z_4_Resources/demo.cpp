/*****************************************
*  Author: Root
*  ��demo�ṩPicReader��FastPrinter�Ĳ��Է��������ص��עFastPrinter�ķ�����
*  function list:
*      testR()          ����PicReaderͼƬ��ȡ�����ȡ���ݣ��ṩ����demoͼƬ���ֱ�Ϊ���ڡ����ס����졢���̡�����
*      testP_Text()		����FastPrinter���������λ�û��ƣ�2000�Σ�λ�������������ɫ�̶�
*      testP_HRect()	����FastPrinter��������ľ�����ƣ�2000�Σ�λ��������ɫ���
*      testP_SRect()	����FastPrinter�����ʵ�ľ�����ƣ�2000�Σ�λ��������ɫ���
*      testP_RandCF()	����FastPrinter�����ȫ��Ļ���ݻ��ƣ�20�Σ�����ƿ���ڹ����������ɫ
*      testP_RandCA()	����FastPrinter������������ݻ��ƣ�200�Σ�����ƿ���ڹ����������ɫ
*  ��ʾ��ͨ�����ԣ��������Ҫ����������Ӧ�þ����ܵز�ָ����ɫ���л���
*****************************************/

#include "PicReader.h"
#include "FastPrinter.h"
#include <stdio.h>
#include<iostream>
using namespace std;

void testR() {
	PicReader imread;
	BYTE *data = nullptr;
	UINT x, y;

	/******************************************
	*  ˵����readPic()����һ���ַ���ָ���ȡͼƬ
	*       testReader(
	*            BYTE*&, ����BYTEָ�����ã����ڽ���������Ϣ
	*            UINT&,  ��ȡͼ��Ŀ����Ϣ
	*			 UINT&)  ��ȡͼ��ĸ߶���Ϣ
	*       ������Ϣÿ�ĸ�һ��(R G B A)����������ÿ�������һ���ĸ����ִ�����ԭͼһ������
	*       ����testReaderʵ�ֵ���ֱ��ʹ�ú�����������ڴ�ָ�룬��ÿ�μ�������ݺ���Ҫ�ͷ�һ��data
	*******************************************/

	// Pure black
	imread.readPic("test\\black.png");
	imread.testReader(data, x, y);
	//imread.getData();

	// Check the data
	printf("black data, should be 0 0 0 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();

	// Pure white
	imread.readPic("test\\white.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("white data, should be 255 255 255 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();

	// Pure red
	imread.readPic("test\\red.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("red data, should be 255 0 0 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();

	// Pure green
	imread.readPic("test\\green.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("green data, should be 0 255 0 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();

	// Pure blue
	imread.readPic("test\\blue.png");
	imread.testReader(data, x, y);

	// Check the data
	printf("blue data, should be 0 0 255 255 each line, press enter to continue...");
	getchar();
	for (DWORD i = 0; i < x * y * 4; i += 4)
		printf("%u %u %u %u\n", data[i], data[i + 1], data[i + 2], data[i + 3]);
	delete[] data;
	data = nullptr;
	printf("Press enter to continue...");
	getchar();
}

void testP_Text() {
	/******************************************
	*  ˵����FastPrinter(DWORD, DWORD)�ĳ�ʼ������Ϊ���������������Ŵ��ڵĿ�Ⱥ͸߶�
	*        COORDΪһ���ṹ�壬�ڲ���������������X Y����ʾ����������ֵ�һ�����ڴ����ڵ�����(X, Y)
	*       FastPrinter::setText�ṩ�������غ����������ֱ�����
	*       (COORD, const char*) ��ָ������������֣���ɫĬ�Ϻ�ɫ��������ɫǰ��
	*       (COORD, const char*, WORD) ��ָ������������֣���������ɫ
	*       (COORD, const char*, WORD, WORD)  ��ָ������������֣���������ɫ�����ڸ������ִ��ĳ��ȣ��ʸ�Ч�ʻ�΢΢΢΢��������һ��
	*       ��ɫ�����ռ�fp_color���ṩǰ��ɫ16�֡�����ɫ16�֣�f��ͷ��Ϊǰ��ɫ��������ɫ����b��ͷ��Ϊ����ɫ�������ɫ������l��Ϊ��ɫ
	*                           ��Ϸ�ʽΪ(fp_color::f_color | fp_color::b_color)
	*                           ������ڶ���setText���������ӵ�е���ɫΪǰ������ɫ�ͱ�������ɫ
	*******************************************/
	FastPrinter printer(120, 50);//���ڴ�Сx,y
	COORD textXY;
	for (int i = 0; i < 2000; i++) {
		// Note: it will faster if all func give length
		printer.cleanSrceen();
		textXY.X = rand() % 100; textXY.Y = rand() % 50;
		printer.setText(textXY, "Hello world!!!");

		textXY.X = rand() % 100; textXY.Y = rand() % 50;
		printer.setText(textXY, "I have color!!!", rand(), rand(), rand(), rand(), rand(), rand());

		textXY.X = rand() % 100; textXY.Y = rand() % 50;
		printer.setText(textXY, "ABCDEFG?", 8, rand(), rand(), rand(), rand(), rand(), rand()); // 8 is the len of str without '\0'

		printer.draw(true);
	}
}

void testP_HRect() {
	/******************************************
	*  ˵����FastPrinter::setRect(SMALL_RECT, char, WORD)���ú���������SMALL_RECT�ṹ���������������
	*                            ʹ��char��Ϊ����ַ�����ȫ��ˢ�ϵ�����������������ɫ
	*******************************************/
	FastPrinter printer(120, 50);
	SMALL_RECT rectPOS;
	for (int i = 0; i < 2000; i++) {
		printer.cleanSrceen();

		rectPOS.Left = rand() % 58 + 1;
		rectPOS.Right = rectPOS.Left + rand() % 58;
		rectPOS.Top = rand() % 24 + 1;
		rectPOS.Bottom = rectPOS.Top + rand() % 24;

		printer.setRect(rectPOS, rand() % 70 + 48, rand(), rand(), rand(), rand(), rand(), rand());

		printer.draw(true);
	}
}

void testP_SRect() {
	/******************************************
	*  ˵����FastPrinter::setRect(SMALL_RECT, char, WORD)���ú���������SMALL_RECT�ṹ���������������
	*                            ʹ��char��Ϊ����ַ�����ȫ��ˢ�ϵ�����������������ɫ
	*******************************************/
	FastPrinter printer(120, 50);
	SMALL_RECT rectPOS;
	for (int i = 0; i < 2000; i++) {
		printer.cleanSrceen();

		rectPOS.Left = rand() % 58 + 1;
		rectPOS.Right = rectPOS.Left + rand() % 58;
		rectPOS.Top = rand() % 24 + 1;
		rectPOS.Bottom = rectPOS.Top + rand() % 24;

		printer.fillRect(rectPOS, rand() % 70 + 48, rand(), rand(), rand(), rand(), rand(), rand());

		printer.draw(true);
	}
}

void testP_RandCF() {
	/******************************************
	*  ˵����FastPrinter::setData(const char*, const WORD*)
	*                     �ú������ڴ���Ϳ���̨���ڴ�Сһ�µ�һά����������dataBuffer��
	*                     ��Ҫע����Ǵ������һά����ָ��
	*******************************************/
	FastPrinter printer(120, 50);
	char* dataBuffer = new char[120 * 50];
	BYTE* frontColorBuffer = new BYTE[120 * 50 * 3];
	BYTE* backColorBuffer = new BYTE[120 * 50 * 3];

	for (int i = 0; i < 20; i++) {
		printer.cleanSrceen();

		for (int i = 0; i < 120 * 50; i++) {
			dataBuffer[i] = rand() % 70 + 48;
			frontColorBuffer[i * 3] = rand() % 255;
			frontColorBuffer[i * 3 + 1] = rand() % 255;
			frontColorBuffer[i * 3 + 2] = rand() % 255;
			backColorBuffer[i * 3] = rand() % 255;
			backColorBuffer[i * 3 + 1] = rand() % 255;
			backColorBuffer[i * 3 + 2] = rand() % 255;
		}

		printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);

		printer.draw(true);
	}

	delete[] dataBuffer;
	delete[] frontColorBuffer;
	delete[] backColorBuffer;
}

void testP_RandCA() {
	/******************************************
	*  ˵����FastPrinter::setData(const char*, const WORD*, SMALL_RECT)
	*                     �ú������ڴ����SMALL_RECT���������Сһ�µ�һά����������dataBuffer��
	*                     ��Ҫע����Ǵ������һά����ָ��
	*
	*                     ����һ�������������ǣ��⽫ֻ����ָ������������л���
	*******************************************/
	FastPrinter printer(120, 50);
	SMALL_RECT drawArea;
	char* dataBuffer = new char[120 * 50];
	BYTE* frontColorBuffer = new BYTE[120 * 50 * 3];
	BYTE* backColorBuffer = new BYTE[120 * 50 * 3];

	for (int i = 0; i < 200; i++) {
		printer.cleanSrceen();

		drawArea.Left = rand() % 58 + 1;
		drawArea.Right = drawArea.Left + rand() % 58;
		drawArea.Top = rand() % 24 + 1;
		drawArea.Bottom = drawArea.Top + rand() % 24;

		for (int i = 0; i < (drawArea.Right - drawArea.Left) * (drawArea.Bottom - drawArea.Top); i++) {
			dataBuffer[i] = rand() % 70 + 48;
			frontColorBuffer[i * 3] = rand() % 255;
			frontColorBuffer[i * 3 + 1] = rand() % 255;
			frontColorBuffer[i * 3 + 2] = rand() % 255;
			backColorBuffer[i * 3] = rand() % 255;
			backColorBuffer[i * 3 + 1] = rand() % 255;
			backColorBuffer[i * 3 + 2] = rand() % 255;
		}

		printer.setData(dataBuffer, frontColorBuffer, backColorBuffer, drawArea);

		printer.draw(true);
	}

	delete[] dataBuffer;
	delete[] frontColorBuffer;
	delete[] backColorBuffer;
}

int maine() {
	{
	/*	/* PicReader test 
		testR();
		printf("Press enter to continue...");
		getchar();*/
	}


	/* Pinter test */
	{
		/*
		!����!
		���������Ե��ǿ��ٻ��Ƶ�ģ�飬ÿ�λ����Լ2000�β�ͬλ�õ����ֻ�ͬ��״�ľ��Ρ�
		���ڻ��Ʒǳ��죬������ῴ���ǳ����۵�Ч����
		�ɲ��Կ�������Ч������һ�����Ӿ��̼��ԣ������ڲ��Թ������в��ʸУ��뼰ʱ�رճ�����Ϣ��
		�ɲ��Կ�������Ч������һ�����Ӿ��̼��ԣ������ڲ��Թ������в��ʸУ��뼰ʱ�رճ�����Ϣ��
		�ɲ��Կ�������Ч������һ�����Ӿ��̼��ԣ������ڲ��Թ������в��ʸУ��뼰ʱ�رճ�����Ϣ��
		�ɲ��Կ�������Ч������һ�����Ӿ��̼��ԣ������ڲ��Թ������в��ʸУ��뼰ʱ�رճ�����Ϣ��
		�ɲ��Կ�������Ч������һ�����Ӿ��̼��ԣ������ڲ��Թ������в��ʸУ��뼰ʱ�رճ�����Ϣ��
		�ɲ��Կ�������Ч������һ�����Ӿ��̼��ԣ������ڲ��Թ������в��ʸУ��뼰ʱ�رճ�����Ϣ��
		!����!

		TIPS : ��vs2017�а�סalt����ѡ����й�꣬�ɿ��ٽ��ע�͡�
		*/
		 getchar();
		 DWORD tic;
		  // Test Text place print//�������ַ���
		 tic = GetTickCount();//10189218 10202140  10214375
		 cout << tic << endl;
		  testP_Text();
		 printf("Elapsed: %u ms, Press enter to continue...",GetTickCount() - tic);
		 

		 /*
		// Test Hollow Rect draw //�����α�
		 tic = GetTickCount();
		 testP_HRect();
		 printf("Elapsed: %u ms, Press enter to continue...", GetTickCount() - tic);
		 getchar();
		*/

		 /*
		//  Test Solid Rect draw //������
		 tic = GetTickCount();
		 testP_SRect();
		 printf("Elapsed: %u ms, Press enter to continue...", GetTickCount() - tic);
		 getchar();
		*/

		 /*
		 // Test random char&color print with fullscreen //������Ļ�Ĳ�ɫ�ַ�
		 tic = GetTickCount();
		 testP_RandCF();
		 printf("Elapsed: %u ms, Press enter to continue...", GetTickCount() - tic);
		 getchar();
		*/

		 /*
		//  Test random char&color print with random area //����ƶ��ĳ����β�ɫ�ַ�
		 tic = GetTickCount();
		 testP_RandCA();
		 printf("Elapsed: %u ms, Press enter to continue...", GetTickCount() - tic);
		 getchar();
		 */
	}
	printf("Completed! Press enter to exit.");
	getchar();
	return 0;
}

int maian()
{
	testR();
	testP_RandCA();
	FastPrinter a(120, 40);
	SMALL_RECT rectPOS;
	rectPOS.Left = 10;
	rectPOS.Right = 60;
	rectPOS.Top = 5;
	rectPOS.Bottom = 35;
	a.fillRect(rectPOS,'3', 123, 123, 123, 200, 255, 255);
	a.draw(1);
	_getchar_nolock();
	return 0;
}
