#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "PreCompile.h"
#include "Control.h"

class Animation : public Control
{
public:
	map<int, BmpImage> m_mapData;      // �洢�������ݣ�firstΪ֡�ţ�secondΪÿһ֡��Bmp����
	int m_nCurFrame;                   // ��ǰ֡��
	int m_nTotalFrame;                 // �ܹ�֡��
	int m_nRate;                       // ��������ÿ֡���(ms)
	DWORD m_dwLastTime;                // �ϴβ��ŵ�ʱ��

	Animation();
	~Animation();

	// ���ݵ�ǰʱ����ʾ�ض�֡
	void Draw();

	// ����ָ��·���µ���������BmpͼƬΪ��������
	void LoadAnimation(string strAniPath);
};

#endif
