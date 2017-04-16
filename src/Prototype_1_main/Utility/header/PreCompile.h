#ifndef _PRECOMPILE_H_
#define _PRECOMPILE_H_

#include <fstream>
#include <Windows.h>
#include <strsafe.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

const int VIEWWIDTH                =   1366;
const int VIEWHEIGHT               =   768;

const int MAP_BLOCK_WIDTH          = 1750;
const int MAP_BLOCK_HEIGHT         = 900;

const int BMP_TYPE_32              = 32;

const int LITTLE_MAP_BLOCKS_COL    =   2;
const int LITTLE_MAP_BLOCKS_ROW    =   2;

const int MAP_BLOCK_NUM            =   2;

const int EXCEED_BOUND_WIDTH       = 100;
const int EXCEED_BOUND_HEIGHT      = 50;

const int BIG_MAP_WIDTH            = 10500;
const int BIG_MAP_HEIGHT           = 8100;

const int VIEW_PORT_MAX_X          = 9817;
const int VIEW_PORT_MAX_Y          = 7716;
const int VIEW_PORT_MIN_X          = 683;
const int VIEW_PORT_MIN_Y          = 384;

const string strSrcPath            = "/src/";
const string strCfgSuffix          = ".ini";

#define BITMAP 0x4D42

#endif