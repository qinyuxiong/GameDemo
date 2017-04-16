#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "PreCompile.h"
#include "Widget.h"

class Animation : public Widget
{
public:
	map<int, Image> m_mapData;      // �洢�������ݣ�firstΪ֡�ţ�secondΪÿһ֡��Bmp����
	int m_nCurFrame;                   // ��ǰ֡��
	int m_nTotalFrame;                 // �ܹ�֡��
	int m_nRate;                       // ��������ÿ֡���(ms)
	DWORD m_dwLastTime;                // �ϴβ��ŵ�ʱ��
	BOOL m_bStarted;

	Animation();
	~Animation();

	virtual void Create(vector<string> &vecInit, Widget *pParent);

	// ���ݵ�ǰʱ����ʾ�ض�֡
	void Draw(Canvas *pCanvas, int nStartX, int nEndX, int nWidth, int nStartY, int nEndY);

	// ����ָ��·���µ���������BmpͼƬΪ��������
	void LoadAnimation(string strAniPath);

	// ��ʼ
	void Start();

	// ֹͣ
	void Stop();

	BOOL IsStart(){ return m_bStarted; }
};

#endif
