/******************************************************************
* ��ע�⣡                                                         *
* ��ͷ�ļ���Ϊ���װ��WinAPI��WIC�ײ㺯�������������ͼƬ��ȡ��������  *
* ���װ�������ⲿ�⣬����������һ����Լ��������������ϸ�Ķ����¹涨  *
*     ��ͷ�ļ����κ�û��TO-DO�ĵط����㲻Ҫ�޸ģ��������������⣬      *
* �뼰ʱ��ϵ��ʦ�����̣�                                            *
*     ÿһ��TO-DO����TO-DO��˵�� (TO-DO) END ����������ɿ��·�����  *
*     readPic()����Ϊ���װ��WinAPI�еķ��������Խ�ͼƬ��ȡΪRGBA��   *
* bitmap���ݣ����Ⲣ�����������ͨ���޸��������ֱ�Ӵﵽ��ȡ�Ҷ�ͼ��   *
* Ŀ�ġ�                                                           *
*     getData()����������Ҫ���Ƶĺ���������ȡ������һάBYTE����ת��   *
* ����ʵ�ֵ�Array�ࡣ                                              *
*     testReader()��demo���ṩ��ȡ���ݵ�����һ��˼·��               *
******************************************************************/
#ifndef PIC_READER_H
#define PIC_READER_H

#include <windows.h>
#include <wincodec.h>
#include <commdlg.h>
#include"Array.h"
#include<iostream>

template <typename T>
inline void SafeRelease(T *&p) {
	if (nullptr != p) {
		p->Release();
		p = nullptr;
	}
}

class PicReader {
public:
	PicReader();
	~PicReader();

	void readPic(LPCSTR);
	void  getData(Array& a,UINT &,UINT &);
	void testReader(BYTE *&,UINT &, UINT &);
private:
	void init();
	bool checkHR(HRESULT);
	void quitWithError(LPCSTR);

	HWND                    hWnd;
	HANDLE                  hFile;
	IWICImagingFactory     *m_pIWICFactory;
	IWICFormatConverter    *m_pConvertedSourceBitmap;

	/*TO-DO��������ܻ���������Ҫ���ڲ���Ա END*/
};

PicReader::PicReader() : m_pConvertedSourceBitmap(nullptr), m_pIWICFactory(nullptr) {
	init();
}

PicReader::~PicReader() {
	if (hFile != NULL) CloseHandle(hFile);
	SafeRelease(m_pConvertedSourceBitmap);
	SafeRelease(m_pIWICFactory);
	CoUninitialize();
}

bool PicReader::checkHR(HRESULT hr) {
	return (hr < 0);
}

void PicReader::quitWithError(LPCSTR message) {
	MessageBoxA(hWnd, message, "Application Error", MB_ICONEXCLAMATION | MB_OK);
	quick_exit(0xffffffff);
}

void PicReader::init() {
	hWnd = GetForegroundWindow();

	// Enables the terminate-on-corruption feature.
	HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

	HRESULT hr = S_OK;

	//Init the WIC
	hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	// Create WIC factory
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pIWICFactory)
	);

	// Throw error if create factor failed
	if (checkHR(hr)) { quitWithError("Init Reader Failed"); }
}

void PicReader::readPic(LPCSTR fileName) {
	HRESULT hr = S_OK;

	// Create a File Handle (WinAPI method not std c)
	if (hFile != NULL) CloseHandle(hFile);
	hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (GetLastError() == ERROR_FILE_NOT_FOUND) {
		quitWithError("Cannot find such file, please retry or check the access");
	}

	// Create a decoder
	IWICBitmapDecoder *pDecoder = nullptr;
	hr = m_pIWICFactory->CreateDecoderFromFileHandle((ULONG_PTR)hFile, nullptr, WICDecodeMetadataCacheOnDemand, &pDecoder);
	if (checkHR(hr)) { quitWithError("Create Decoder Failed"); }

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode *pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (checkHR(hr)) { quitWithError("Get Frame Failed"); }

	// Format convert the frame to 32bppRGBA
	SafeRelease(m_pConvertedSourceBitmap);
	hr = m_pIWICFactory->CreateFormatConverter(&m_pConvertedSourceBitmap);
	if (checkHR(hr)) { quitWithError("Get Format Converter Failed"); }

	hr = m_pConvertedSourceBitmap->Initialize(pFrame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
	if (checkHR(hr)) { quitWithError("Init Bitmap Failed"); }

	// Clean memory
	SafeRelease(pDecoder);
	SafeRelease(pFrame);
}

void PicReader::getData(Array & a,UINT &_x,UINT &_y) {
	HRESULT hr = S_OK;

	// Get the size of Image
	UINT x, y;
	hr = m_pConvertedSourceBitmap->GetSize(&x, &y);
	if (checkHR(hr)) { quitWithError("Check Bitmap Size Failed"); }

	// Create the buffer of pixels, the type of BYTE is unsigned char
	BYTE *data;
	data = new BYTE[x * y * 4];
	memset(data, 0, x * y * 4);

	// Copy the pixels to the buffer
	UINT stride = x * 4;
	hr = m_pConvertedSourceBitmap->CopyPixels(nullptr, stride, x * y * 4, data);
	if (checkHR(hr)) { quitWithError("Copy Pixels Failed"); }
	
	//


	/******************************************************************
	*  TO-DO:                                                         *
	*                                                                 *
	*  ʵ��һ��Array�࣬���������dataת�������Array��                  *
	*                                                                 *
	*  ����˵������Bitmap Copy���������ݣ�ÿ4��Ϊһ�����һ������         *
	*           ����Ϊһ������Ϊͼ���(��*��*4)��һά����                *
	*           �������Ų�Ϊ R G B A R G B A R G B A.....              *
	*                                                                 *
	*  ��ע�⣡  �������ֻ�Ķ��Ӵ˿�ʼ����һ��TO-DO ENDλ�õĴ��룡       *
	******************************************************************/
	//��Ҫ������a������
	_x = x;
	_y = y;
	a.axisNum = 4;
	a.index = 0;
	a.isSon = 0;
	a.nowAxis = 0;
	a.sum = x * y * 4;
	a.data = new int[a.sum];

	for (int i = 0; i < x * y * 4; i++)//�õ�ÿһ�����ص�����
	{
		a.data[i] = (int)data[i];
	}
	a.reshape(y, x, 4);//��ת����4ά��array

	delete[] data;

	/******************************************************************
	*  TO-DO END                                                      *
	******************************************************************/

	// Close the file handle
	CloseHandle(hFile);
	hFile = NULL;
}

void PicReader::testReader(BYTE* &_out, UINT& _x, UINT& _y){
	HRESULT hr = S_OK;

	// Get the size of Image
	UINT x, y;
	hr = m_pConvertedSourceBitmap->GetSize(&x, &y);
	if (checkHR(hr)) { quitWithError("Check Bitmap Size Failed"); }

	// Create the buffer of pixels, the type of BYTE is unsigned char
	BYTE *data;
	data = new BYTE[x * y * 4];
	memset(data, 0, x * y * 4);

	// Copy the pixels to the buffer
	UINT stride = x * 4;
	hr = m_pConvertedSourceBitmap->CopyPixels(nullptr, stride, x * y * 4, data);
	if (checkHR(hr)) { quitWithError("Copy Pixels Failed"); }


	_out = data; _x = x; _y = y;

	// Close the file handle
	CloseHandle(hFile);
	hFile = NULL;
}

#endif