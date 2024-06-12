#pragma once
#include "GameNode.h"

enum LOADING_IMAGE_KIND
{
	LOAD_IMAGE1 = 0, 
	LOAD_IMAGE2,
	LOAD_IMAGE3,
	LOAD_FRAMEIMAGE1,
	LOAD_FRAMEIMAGE2,
	LOAD_SOUND
};

struct NewtagImage
{
	string		imgName;
	const char* fileName;
	float		x;				
	float		y;				
	int			width;			
	int			height;			
	int			maxFrameX;		
	int			maxFrameY;		
	bool		isTrans;
	COLORREF	transColor;
};

class LoadItem
{
private:
	LOADING_IMAGE_KIND _imgKind;
	NewtagImage _imageInfo;

public:
	HRESULT initForImage(string strKey, const char* fileName, int width, int height);
	HRESULT initForImage(string strKey, const char* fileName, int width, int height, bool isTrans, COLORREF transColor);
	HRESULT initForImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	
	HRESULT initForFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	
	LOADING_IMAGE_KIND getImgKind() { return _imgKind; }
	NewtagImage getImageInfo() { return _imageInfo; }

	LoadItem() {}
	~LoadItem() {}
};

class Loading : public GameNode
{
private:
	typedef vector<LoadItem*> vLoading;
	typedef vector<LoadItem*>::iterator viLoading;

private:
	vLoading _vLoadingImg;
	viLoading _viLoadingImg;

	GImage* _loadingImg;
	float _currentGauge;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void  LoadingImage(string strKey, const char* fileName, int width, int height);
	void  LoadingImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void  LoadingImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	
	void  LoadingFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void  LoadingFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	bool loadingDone(void);

	Loading() {}
	~Loading() {}
};
