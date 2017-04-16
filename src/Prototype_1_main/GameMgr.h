#ifndef _GAMEMGR_H_
#define _GAMEMGR_H_

#include <Windows.h>

class GameMgr
{
public:
	GameMgr();
	~GameMgr();

	void InitGame(HWND hWnd);
};

#endif