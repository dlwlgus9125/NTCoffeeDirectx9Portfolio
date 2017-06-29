// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
// 

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <afxwin.h>
#include <windows.h>
#include <process.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <conio.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//>> 자료형
#include <vector>
#include <map>
#include <list>
#include <queue>
//<<

//>> 기능
#include <string>
#include <set>
#include <functional>
#include <iostream>
#include <assert.h>
#include <ctime>
#include <dshow.h>
#pragma comment(lib, "Strmiids.lib")

#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <Windows.h>
#include <mmsystem.h >
#pragma comment(lib, "winmm.lib")
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
using namespace std;
//<<

//<<::
// Mouse Whell
#define VK_WHELLUP		120
#define VK_WHELLDOWN	-120
#define DIST_LIMITS	  4.0f

// <<: KEY 
// Getkeysate "0x8000" == "KF_UP"
#define VK_A			0x41
#define VK_B			0x42
#define VK_C			0x43
#define VK_D			0x44
#define VK_E			0x45
#define VK_F			0x46
#define VK_G			0x47
#define VK_H			0x48
#define VK_I			0x49
#define VK_J			0x49
#define VK_K			0x4A
#define VK_L			0x4B
#define VK_M			0x4C
#define VK_N			0x4E
#define VK_O			0x4F
#define VK_P			0x50
#define VK_Q			0x51
#define VK_R			0x52
#define VK_S			0x53
#define VK_T			0x54
#define VK_U			0x55
#define VK_V			0x56
#define VK_W			0x57
#define VK_X			0x58
#define VK_Y			0x59
#define VK_Z			0x5A


// NUM KEY
#define VK_0		0x30
#define VK_1		0x31
#define VK_2		0x32
#define VK_3		0x33
#define VK_4		0x34
#define VK_5		0x35
#define VK_6		0x36
#define VK_7		0x37
#define VK_8		0x38
#define VK_9		0x39
// <<:

enum SCENE_TAG
{
	SCENE_NONE, SCENE_LOADING, SCENE_LOGIN, SCENE_SELECT, SCENE_HELP,
	SCENE_TOWN_HUMAN, SCENE_TOWN_ORC, SCENE_BATTLE_HUMAN, SCENE_BATTLE_ORC, 
};

enum UI_TAG
{
	UI_NONE, UI_OBJECT, UI_IMAGE, UI_TEXT, UI_BUTTON, UI_MINIMAP, UI_TAB,UI_SLOT, UI_MSGBOX, UI_PROGRESSBAR, UI_INVENTORY,
};

enum UI_STATE
{
	UI_IDLE, UI_MOUSEOVER, UI_PRESSED, UI_CLICKED, UI_SELECTED, 
};

enum FONT_TAG
{
	FONT_DEF, FONT_SHOP,
};

enum FONT_BOWMOTION
{
	BOW_NORMAL,
	BOW_PULL,
	BOW_PUSH,
};

enum LEADER_TYPE
{
	LEADER_MELEE,
	LEADER_BOW,
	LEADER_CAVALRY,
};

//>> define 및 구조체
extern HWND	g_hWnd;
extern HCURSOR g_Cursor;
#include "cLog.h"
extern cLog* g_pLog;
#define SAFE_RELEASE(p) { if(p) p->Release(); p = NULL; }
#define SAFE_DELETE(p) { if(p) delete p; p = NULL; }	// << :
#define SAFE_ADD_REF(p) { if(p) p->AddRef() ; }
#define SAFE_DELETE_ARRAY(p) {if(p) delete[] p; p = NULL;}
// >> : 
#define SINGLETONE(class_name) \
		private : \
			class_name(void) ;  \
			~class_name(void) ; \
		public :\
			static class_name* GetInstance() \
			{ \
				static class_name instance ; \
				return &instance ; \
			} 

#define EPSILON             0.0001f
#define ANGLE_TO_RADIAN		0.0174533f
#define RADIAN_TO_ANGLE		57.2958f
#define COS45	0.52532198881f
#define WND_WIDTH 1280
#define WND_HEIGHT 768

#define MAX_LOADSTRING 100


#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
	}\
}

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };

	bool operator == (ST_PNT_VERTEX pnt) { return p == pnt.p&&n == pnt.n	&&t == pnt.t; }
};

struct ST_LINE_VERTEX
{
	D3DXVECTOR3 a;
	D3DXVECTOR3 b;
	ST_LINE_VERTEX(D3DXVECTOR3 a, D3DXVECTOR3 b)
	{
		this->a = a;
		this->b = b;
	}
};
struct ST_POS_SAMPLE
{
	int			n;
	D3DXVECTOR3 v;

	ST_POS_SAMPLE()
		: n(0), v(0, 0, 0)
	{
	}
};

struct ST_ROT_SAMPLE
{
	int				n;
	D3DXQUATERNION  v;

	ST_ROT_SAMPLE()
		: n(0), v(0, 0, 0, 0)
	{
	}
};

struct MeshSpere
{
	LPD3DXMESH       m_pMeshSphere;
	D3DMATERIAL9    m_stMtlSphere;
	D3DXVECTOR3     m_vCenter;
	float           m_radius;
	MeshSpere() {};
};

struct ST_SPHERE
{
	ST_SPHERE() {}
	ST_SPHERE(D3DXVECTOR3 pos, float radius) { vCenter = pos; fRadius = radius; isPicked = false; }
	bool isPicked;
	D3DXVECTOR3 vCenter;
	float fRadius;
};

struct ST_SIZEN
{
	int nWidth;
	int nHeight;
	ST_SIZEN() : nWidth(0), nHeight(0) {}
	ST_SIZEN(int _w, int _h) : nWidth(_w), nHeight(_h) {}
};

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};

// 플레이어 모드 추가.
enum PLAYER_MODE_STATE
{
	FIGHTING_PLAYER_MODE,
	IDLE_PLAYER_MODE,
};
//

struct ST_TAB
{
	string text;
	D3DXVECTOR3 pos;
	int state;

	ST_TAB(string text, D3DXVECTOR3 pos, int state)
	{
		this->text = text;
		this->pos = pos;
		this->state = state;
	}
};

struct ST_SLOT
{
	D3DXVECTOR3 rectPos;
	ST_SIZEN rectSize;
	D3DXVECTOR3 imagePos;
	ST_SIZEN imageSize;
	D3DXVECTOR3 textPos;
	ST_SIZEN textSize;

	ST_SLOT(D3DXVECTOR3 rectPos, ST_SIZEN rectSize, D3DXVECTOR3 imagePos, ST_SIZEN imageSize, D3DXVECTOR3 textPos, ST_SIZEN textSize)
	{
		this->rectPos = rectPos;
		this->rectSize = rectSize;
		this->imagePos = imagePos;
		this->imageSize = imageSize;
		this->textPos = textPos;
		this->textSize = textSize;
	}
	D3DXVECTOR2 LeftTop() {return D3DXVECTOR2(rectPos.x, rectPos.y);}
	D3DXVECTOR2 RightBottom() { return D3DXVECTOR2(rectPos.x + rectSize.nWidth, rectPos.y + rectSize.nHeight); }
};

struct ST_SLOTDATA
{
	int itemID;
	string imagePath;
	string info;
	string name;
	int cost;

	ST_SLOTDATA(int itemID, string name, string imagePath, string info, int cost)
	{
		this->itemID = itemID;
		this->name = name;
		this->imagePath = imagePath;
		this->info = info;
		this->cost = cost;
	}

	~ST_SLOTDATA() {}
};



enum MODE_STATE
{
	FIGHTING_MODE, 
	DEFENDING_MODE,
};

/////////////////////////////////////////////////////////////////
// 애니메이션 키 값
/////////////////////////////////////////////////////////////////
// 플레이어 키값
enum P_STATE // P: Player
{
	P_STAND,
	P_WALK,
	P_BACKWALK,
	P_RUN,
	P_READYATTACK,
	P_BATTLEWALK,
	P_BATTLERUN,
	P_ATTACK1,
	P_ATTACK2,
	P_ATTACK3,
	P_BOWATTACK1,
	P_BOWATTACK2,
	P_SHEILDBLOCK,
	P_SHEILDUP,
	P_HIT,
	P_BATTLECRY,
	P_KNOCKDOWN,
	P_DEATH,

};



// 보병
enum FG_STATE // F: Footman, G: Grunt
{
	FG_STAND,
	FG_WALK,
	FG_BACKWALK,
	FG_RUN,
	FG_READYATTACK,
	FG_BATTLEWALK,
	FG_BATTLERUN,
	FG_ATTACK1,
	FG_ATTACK2,
	FG_ATTACK3,
	FG_SHEILDBLOCK,
	FG_SHEILDUP,
	FG_HIT,
	FG_BATTLECRY,
	FG_KNOCKDOWN,
	FG_DEATH,
};

// 궁병
enum BOWMAN_STATE
{
	B_STAND,
	B_WALK,
	B_BACKWALK,
	B_RUN,
	B_READYATTACK,
	B_BATTLEWALK,
	B_BATTLERUN,
	B_BOWATTACK1,
	B_BOWATTACK2,
	B_BOWSHEILD,
	B_HIT,
	B_BATTLECRY,
	B_KNOCKDOWN,
	B_DEATH,
};

// 기병
enum KNIGHT_STATE
{
	K_STAND,
	K_WALK,
	K_RUN,
	K_HIT,
	K_BATTLECRY,
	K_DEATH,
};
enum EVENTID
{
	LOGIN_BTN_START = 1, LOGIN_BTN_HELP, LOGIN_BTN_EXIT,

	TITLE_BTN_FMT_RECT = 100, TITLE_BTN_FMT_TRI, TITLE_BTN_ATTSTATE, TITLE_BTN_DEFSTATE,

	TOWN_TAB_SHOP_ATT = 200, TOWN_TAB_SHOP_DEF, TOWN_TAB_RECRUIT, TOWN_BTN_SHOPEXIT, TOWN_TAB_INVENTORY, TOWN_TAB_INVENTORY_EQUIP, TOWN_INVENTORY, TOWN_MINIMAP, TOWN_BTN_BATTLE_ORC, TOWN_BTN_BATTLE_HUMAN,
	TOWN_MINIMAP_TROOPTYPE, TOWN_BTN_MELEE, TOWN_BTN_BOW, TOWN_BTN_CAVALRY, TOWN_TAB_TROOPINFO,

	SELECT_BTN_ORC = 300, SELECT_BTN_HUMAN, SELECT_BTN_CREATE, SELECT_BTN_BACK, SELECT_MSGBOX_ORC, SELECT_MSGBOX_HUMAN,

	BATTLE_MINIMAP_VICTORY, BATTLE_MINIMAP_DEFEAT, BATTLE_MINIMAP_RESULT,
};

enum UNIT_STATE
{
	UNIT_STATE_MELEE_IDLE,
	UNIT_STATE_MELEE_WALK,
	UNIT_STATE_MELEE_BATTLE,
	UNIT_STATE_MELEE_DEFENCE,
	UNIT_STATE_MELEE_DEATH,

	UNIT_STATE_BOW_IDLE,
	UNIT_STATE_BOW_WALK,
	UNIT_STATE_BOW_BATTLE,
	UNIT_STATE_BOW_DEATH,

	UNIT_STATE_CAVALRY_IDLE,
	UNIT_STATE_CAVALRY_WALK,
	UNIT_STATE_CAVALRY_BATTLE,
	UNIT_STATE_CAVALRY_DEATH,
};

enum CAMP_STATE
{
	CAMP_PLAYER,
	CAMP_ENEMY1,
	CAMP_NONE,
};

struct ST_WEATHER
{
	SYNTHESIZE(bool, m_isSnowOn, SnowOn);
	SYNTHESIZE(float, m_fMove_Snow, Move_Snow);
	SYNTHESIZE(float, m_fSpeed_Snow, Speed_Snow);
	SYNTHESIZE(int, m_nCount_Snow, Count_Snow);

	SYNTHESIZE(bool, m_isRainOn, RainOn);
	SYNTHESIZE(float, m_fMove_Rain, Move_Rain);
	SYNTHESIZE(float, m_fSpeed_Rain, Speed_Rain);
	SYNTHESIZE(int, m_nCount_Rain, Count_Rain);

	SYNTHESIZE(int, m_nPassIndex, FogPassIndex);
	SYNTHESIZE(bool, m_isFogOn, FogOn);

	ST_WEATHER()
	{
		m_isSnowOn = false;
		m_fMove_Snow = 0;
		m_fSpeed_Snow = 0;
		m_nCount_Snow = 0;

		m_isRainOn = false;
		 m_fMove_Rain = 0;
		m_fSpeed_Rain = 0;
		m_nCount_Rain = 0;

		m_nPassIndex = 0;
		m_isFogOn = false;
	}
};

struct ST_SHADOW
{
	SYNTHESIZE(bool, m_isShadowOn, ShadowOn);
	SYNTHESIZE(float, m_diffuseAlpha, ShadowDiffuseAlpha);
};

struct ST_NPC_INFO
{
	int nSID;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;
	float fRotX, fRotY, fRotZ;
	ST_NPC_INFO() {}
	ST_NPC_INFO(int nSID, D3DXVECTOR3 pos, D3DXVECTOR3 scale, float fRotX, float fRotY, float fRotZ)
	{
		this->nSID= nSID; //smallID
		this->pos = pos;
		this->scale = scale;
		this->fRotX = fRotX;
		this->fRotY = fRotY;
		this->fRotZ = fRotZ;
	}

};


extern bool g_showColider;
//>>include
#include "cEffectManager.h"
#include "cThreadManager.h"
#include "cDeviceManager.h"
#include "cInputManager.h"
#include "cObjectManager.h"
#include "cTimeManager.h"
#include "cTextureManager.h"
#include "cAstarManager.h"
#include "cMapManager.h"
#include "cUIManager.h"
#include "cFontManager.h"
#include "cSoundManager.h"
#include "cSceneManager.h"

#include "Singleton.h"
#include "cCamera.h"
#include "Math.h"
#include "cStateMachine.h"
#include "cObjectDB.h"
#include "cCharacterDB.h"
#include "cObject.h"
#include "cItemDB.h"
#include "cShadowManager.h"
#include "cNpcDB.h"
#include "cNpcManager.h"

#include "cRay.h"
//<<


