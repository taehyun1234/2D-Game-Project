#pragma once
#include <memory>
#include <vector>
#include <list>
#include <atlimage.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define GET_SINGLE(type)	type::GetInstance()
#define WND_WIDTH				1600
#define WND_HEIGHT			900
#define OPEN					0
#define CLOSE					1
#define PLAYER				2
#define BOSS					3


#define MAP_WIDTH			32
#define MAP_HEIGHT			18

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#define DECLARE_SINGLE(type)		\
private:							\
	type() {}						\
	~type() {}						\
public:								\
	static type* GetInstance()		\
	{								\
		static type instance;		\
		return &instance;			\
	}								\

// ΩÃ±€≈Ê ≈¨∑°Ω∫
using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;
using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;


enum SCENE
{
	SCENE_TITLE = 0,
	SCENE_MAIN,
	SCENE_MAPTOOL,
	SCENE_COUNT,
};


// Get/Set
#define SFC_GETSET(ret, fname, var)\
ret Get##fname()\
{\
return var;\
}\
void Set##fname(ret tmp)\
{\
var = tmp;\
}

class Point2D
{
public:
	int _x;
	int _y;
	int _g;
	int _h;
	int _f;
	Point2D* _parentPoint;
public:
	Point2D(int x, int y) :_x(x), _y(y), _g(0), _h(0), _f(0), _parentPoint(nullptr) {}
	void CalcF() { _f = _g + _h; }
};
