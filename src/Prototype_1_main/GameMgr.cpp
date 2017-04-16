#include "GameMgr.h"
#include "Canvas.h"
#include "MapMgr.h"
#include "DlgMgr.h"

extern Canvas *g_pCanvas;
extern MapMgr *g_pMapMgr;
extern DlgMgr *g_pDlgMgr;

void GameMgr::InitGame(HWND hWnd)
{
	g_pCanvas = new Canvas;
	g_pCanvas->Init(hWnd);

	g_pMapMgr = new MapMgr;

	g_pDlgMgr = new DlgMgr;
}

GameMgr *g_pGameMgr;