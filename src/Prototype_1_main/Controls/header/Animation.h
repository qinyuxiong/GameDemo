#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "PreCompile.h"
#include "Control.h"

class Animation : public Control
{
public:
	map<int, BmpImage> m_mapData;      // 存储动画数据，first为帧号，second为每一帧的Bmp数据
	int m_nCurFrame;                   // 当前帧数
	int m_nTotalFrame;                 // 总共帧数
	int m_nRate;                       // 动画播放每帧间隔(ms)
	DWORD m_dwLastTime;                // 上次播放的时间

	Animation();
	~Animation();

	// 根据当前时间显示特定帧
	void Draw();

	// 加载指定路径下的所有连续Bmp图片为动画数据
	void LoadAnimation(string strAniPath);
};

#endif
