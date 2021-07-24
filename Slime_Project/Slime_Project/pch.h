#pragma once
#include <memory>
#include <vector>
#include <list>
#include <atlimage.h>
#include <string>
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

using namespace std;

#define GET_SINGLE(type)	type::GetInstance()
#define WND_WIDTH				1600
#define WND_HEIGHT			900

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