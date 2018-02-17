#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef _MAPCLASS_H_
#define _MAPCLASS_H_

#include <cstdlib>
#include <WindowsNumerics.h>
#include "Util.h"
#include <ctime>
#include <Windows.h>
#include <string>
#include <SDL_keyboard.h>

struct Range
{
	double MIN;
	double MAX;

	void SET(double a, double b)
	{
		MIN = a;
		MAX = b;
	}
};

struct Map_Rect
{
	
	unsigned char R, G, B;
	unsigned char PLATE_TYPE;

	double PLATE_H;
	double PLATE_P;
	double GEO_H;
	double PLATE_W[2];
	double PLATE_MOVE[8];
	bool A;

	void SET_RGB(unsigned char r, unsigned char g, unsigned char b)
	{
		R = r;
		G = g;
		B = b;
	}
	void SET_RGB(Windows::Foundation::Numerics::float3 a)
	{
		R = a.x;
		G = a.y;
		B = a.z;
	}
};

struct Map_Data
{
	const int MAX_PLATE = 15;
	double PLATE_W[256][2];

	void INIT()
	{
		for (int a = 0; a < MAX_PLATE; a++)
		{
			PLATE_W[a][0] = ((double)(rand() % 1000)*2.0 - 1000) * 0.2;
			PLATE_W[a][1] = ((double)(rand() % 1000)*2.0 - 1000) * 0.2;
			OutputDebugStringA("Plate :");
			OutputDebugStringA(std::to_string(PLATE_W[a][0]).c_str());
			OutputDebugStringA(", ");
			OutputDebugStringA(std::to_string(PLATE_W[a][1]).c_str());
			OutputDebugStringA("\n");
		}
	}
};

class Map {
private:
	const static int MAP_W = 200;
	const static int MAP_H = 120;
	const int W[8][2] = { { 1 ,0 },{ 1 ,-1 },{ 0 ,-1 },{ -1 ,-1 },{ -1 ,0 },{ -1 ,1 },{ 0 ,1 },{ 1 ,1 } };

	Map_Rect GRP_RECT[MAP_W][MAP_H];
	Map_Rect GRP_LINE[MAP_W][MAP_H][4];
	Map_Data Field[MAP_W][MAP_H];
	Util* m_util;
	Map_Data m_data;

	int MMD_ = 1;

	double AVG_H = 0;
	double DIT_H = 0;

	Range MMD_H;
	Range MMD_GH;
	Range MMD_P;

	double PHY_ALL;
	double PHY_STR = 0;
	double PHY_CRS = 0.5;
	double PHY_RGT = 0;
	double PHY_BCK = 0;

	double PLT_MVE = 1.0;

private:
	bool RECT_EQUAL(Map_Rect, Map_Rect);
public:
	void INIT();
	int GET_RECT(int, int, int);
	bool CHECK_RECT(int, int);
	void STEP();
	void KEY(unsigned int);
};

#endif
