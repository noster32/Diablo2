#include "Stdafx.h"
#include "Loading.h"

HRESULT LoadItem::initForImage(string strKey, const char* fileName, int width, int height)
{
	_imgKind = LOAD_IMAGE1;
	
	_imageInfo.imgName = strKey;
	_imageInfo.fileName = fileName;
	_imageInfo.width = width;
	_imageInfo.height = height;

	return S_OK;
}

HRESULT LoadItem::initForImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	_imgKind = LOAD_IMAGE2;
	
	_imageInfo.imgName = strKey;
	_imageInfo.fileName = fileName;
	_imageInfo.width = width;
	_imageInfo.height = height;
	_imageInfo.isTrans = isTrans;
	_imageInfo.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::initForImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	_imgKind = LOAD_IMAGE3;

	_imageInfo.imgName = strKey;
	_imageInfo.fileName = fileName;
	_imageInfo.x = x;
	_imageInfo.y = y;
	_imageInfo.width = width;
	_imageInfo.height = height;
	_imageInfo.isTrans = isTrans;
	_imageInfo.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::initForFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	_imgKind = LOAD_FRAMEIMAGE1;

	_imageInfo.imgName = strKey;
	_imageInfo.fileName = fileName;
	_imageInfo.width = width;
	_imageInfo.height = height;
	_imageInfo.maxFrameX = maxFrameX;
	_imageInfo.maxFrameY = maxFrameY;
	_imageInfo.isTrans = isTrans;
	_imageInfo.transColor = transColor;

	return S_OK;
}

HRESULT LoadItem::initForFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	_imgKind = LOAD_FRAMEIMAGE2;
	
	_imageInfo.imgName = strKey;
	_imageInfo.fileName = fileName;
	_imageInfo.x = x;
	_imageInfo.y = y;
	_imageInfo.width = width;
	_imageInfo.height = height;
	_imageInfo.maxFrameX = maxFrameX;
	_imageInfo.maxFrameY = maxFrameY;
	_imageInfo.isTrans = isTrans;
	_imageInfo.transColor = transColor;

	return S_OK;
}

//======================================================================

HRESULT Loading::init(void)
{
	_loadingImg = IMAGEMANAGER->addFrameImage("로딩이미지", "Resources/Images/Object/loading.bmp", 2000, 200, 10, 1, true, RGB(255, 0, 255));

	_loadingImg->setFrameX(0);
	_currentGauge = 0;
	return S_OK;
}

void Loading::release(void)
{
}

void Loading::update(void)
{
	loadingDone();
}

void Loading::render(void)
{
	IMAGEMANAGER->frameRender("로딩이미지", getMemDC(), 300, 200, _loadingImg->getFrameX(), 0);
}

void Loading::LoadingImage(string strKey, const char* fileName, int width, int height)
{
	LoadItem* item = new LoadItem;
	item->initForImage(strKey, fileName, width, height);
	_vLoadingImg.push_back(item);
}

void Loading::LoadingImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->initForImage(strKey, fileName, width, height, isTrans, transColor);
	_vLoadingImg.push_back(item);
}

void Loading::LoadingImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->initForImage(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadingImg.push_back(item);
}

void Loading::LoadingFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->initForFrameImage(strKey, fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadingImg.push_back(item);
}

void Loading::LoadingFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->initForFrameImage(strKey, fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor);
	_vLoadingImg.push_back(item);
}

bool Loading::loadingDone(void)
{
	if (_currentGauge >= _vLoadingImg.size())
	{
		SCENEMANAGER->setIsLoadingImg(false);
		SCENEMANAGER->changeScene("마을");
		return true;
	}

	LoadItem* item = _vLoadingImg[_currentGauge];

	switch (item->getImgKind())
	{
	case LOAD_IMAGE1:
	{
		NewtagImage img = item->getImageInfo();
		IMAGEMANAGER->addImage(img.imgName, img.width, img.height);
	}
	break;
	case LOAD_IMAGE2:
	{
		NewtagImage img = item->getImageInfo();
		IMAGEMANAGER->addImage(img.imgName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
	}
	break;

	case LOAD_IMAGE3:
	{
		NewtagImage img = item->getImageInfo();
		IMAGEMANAGER->addImage(img.imgName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
	}
	break;

	case LOAD_FRAMEIMAGE1:
	{
		NewtagImage img = item->getImageInfo();
		IMAGEMANAGER->addFrameImage(img.imgName, img.fileName, img.width, img.height, img.maxFrameX, img.maxFrameY, img.isTrans, img.transColor);
	}
	break;

	case LOAD_FRAMEIMAGE2:
	{
		NewtagImage img = item->getImageInfo();
		IMAGEMANAGER->addFrameImage(img.imgName, img.fileName, img.x, img.y, img.width, img.height, img.maxFrameX, img.maxFrameY, img.isTrans, img.transColor);
	}
	break;
	case LOAD_SOUND:
	{
	}
	break;
	}
	_currentGauge++;
	
	if (0 <= _currentGauge && _currentGauge < 3) 	_loadingImg->setFrameX(0);
	else if (3 <= _currentGauge && _currentGauge < 5)	_loadingImg->setFrameX(1);
	else if (5 <= _currentGauge && _currentGauge < 8)	_loadingImg->setFrameX(2);
	else if (8 <= _currentGauge && _currentGauge < 12)	_loadingImg->setFrameX(3);
	else if (12 <= _currentGauge && _currentGauge < 20)	_loadingImg->setFrameX(4);
	else if (20 <= _currentGauge && _currentGauge < 30)	_loadingImg->setFrameX(5);
	else if (30 <= _currentGauge && _currentGauge < 46)	_loadingImg->setFrameX(6);
	else if (46 <= _currentGauge && _currentGauge < 52)	_loadingImg->setFrameX(7);
	else if (52 <= _currentGauge && _currentGauge < 58)	_loadingImg->setFrameX(8);
	else												_loadingImg->setFrameX(9);

	return false;
}

