#include "Stdafx.h"
#include "Animation.h"

//멤버 이니셜라이져
Animation::Animation(void) : _frameNum(0),
_frameWidth(0),
_frameHeight(0),
_frameNumWidth(0),
_frameNumHeight(0),
_frameUpdateSec(0),
_elapsedSec(0),
_nowPlayIdx(0),
_isPlay(false),
_loop(false)
{
}

HRESULT Animation::init(int totalW, int totalH, int frameW, int frameH)
{
	// 가로 프레임 수
	_frameWidth = frameW;
	_frameNumWidth = totalW / _frameWidth;

	//세로 프레임 수
	_frameHeight = frameH;
	_frameNumHeight = totalH / _frameHeight;

	//총 프레임 수 계산
	_frameNum = _frameNumWidth * _frameNumHeight;

	_frameList.clear();

	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	// 기본 프레임 셋팅
	setDefPlayFrame();

	return S_OK;
}

void Animation::release(void)
{
	//! Do Nothing
}

// 기본 프레임 셋팅
void Animation::setDefPlayFrame(bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	//다시 돌아오냐? (왕복)
	if (reverse)
	{
		//루프?
		if (_loop)
		{
			//정방향 순환 (갈떄)
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 순환 (올때) //-2를 한 이유는 aniStart()의 예외처리
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}

		else
		{
			//정방향 순환 (갈떄)
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}

			//역방향 순환 (올때)
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//편도
	else
	{
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//원하는 프레임만 재생
void Animation::setPlayFrame(int* playArr, int arrLen, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (_loop)
	{
		for (int i = 0; i < arrLen; i++)
		{
			_playList.push_back(playArr[i]);
		}

		for (int i = arrLen - 2; i > 0; i--)
		{
			_playList.push_back(playArr[i]);
		}
	}
	else
	{
		for (int i = 0; i < arrLen; i++)
		{
			_playList.push_back(playArr[i]);
		}

		for (int i = arrLen - 2; i >= 0; i--)
		{
			_playList.push_back(playArr[i]);
		}
	}
}

//구간을 잘라서 재생
void Animation::setPlayFrame(int start, int end, bool reverse, bool loop)
{
	_loop = loop;
	_playList.clear();

	if (start <= 0) start = 0;
	if (end >= _frameNum) end = _frameNum;
	if (start > end)
	{
		int temp = start;
		start = end;
		end = temp;
	}

	//다시 돌아오냐? (왕복)
	if (reverse)
	{
		//루프?
		if (_loop)
		{
			//정방향 순환 (갈떄)
			for (int i = start; i < end; i++)
			{
				_playList.push_back(i);
			}

			//역방향 순환 (올때) //-2를 한 이유는 aniStart()의 예외처리
			for (int i = end - 2; i > start; i--)
			{
				_playList.push_back(i);
			}
		}

		else
		{
			//정방향 순환 (갈떄)
			for (int i = start; i < end; i++)
			{
				_playList.push_back(i);
			}

			//역방향 순환 (올때)
			for (int i = end - 2; i >= start; i--)
			{
				_playList.push_back(i);
			}
		}
	}

	//편도
	else
	{
		for (int i = start; i < end; i++)
		{
			_playList.push_back(i);
		}
	}
}

void Animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1 / (float)framePerSec;
}

void Animation::frameUpdate(float elapsedTime)
{
	if (_isPlay)
	{
		_elapsedSec += elapsedTime;
		//cout << _elapsedSec << endl;

		//프레임 업데이트 시간이 되었으면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;

			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{
				if (_loop)
				{
					_nowPlayIdx = 0;
				}


				else
				{
					_nowPlayIdx--;
					_isPlay = false;
				}

			}
		}
	}

}

void Animation::aniStart(void)
{
	_isPlay = true;
	_nowPlayIdx = 0;
}

void Animation::aniStop(void)
{
	_isPlay = false;
	_nowPlayIdx = 0;
}

void Animation::aniPause(void)
{
	_isPlay = false;
}

void Animation::aniResume(void)
{
	_isPlay = true;
}