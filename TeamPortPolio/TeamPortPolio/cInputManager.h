#pragma once
#include "stdafx.h"

#define INPUT cInputManager::Instance()
#define KEY_COUNT		256
#define MOUSE_COUNT		3

enum KEY_STATE
{
	KEY_NONE, KEY_DOWN, KEY_UP, KEY_PRESS,
};

enum MOUSE_STATE
{
	MOUSE_NONE, MOUSE_DOWN, MOUSE_UP, MOUSE_PRESS, MOUSE_DRAG,
};

enum MOUSE_BUTTON
{
	MOUSE_LEFT, MOUSE_CENTER, MOUSE_RIGHT,
};




class cInputManager :
	public Singleton<cInputManager>
{
	HWND m_hWnd;
	KEY_STATE m_keyStates[KEY_COUNT];
	MOUSE_STATE m_mouseStates[MOUSE_COUNT];
	
	POINT m_mousePrevPos;
	POINT m_mouseBgPos;
	POINT m_mouseCurrentPos;
	POINT m_mouseDeltaPos;

	void UpdateKeyState()
	{
		for (int i = 0; i < KEY_COUNT; i++)
		{
			bool isPressed = GetAsyncKeyState(i) & 0x8000;
			if (isPressed)
			{
				switch (m_keyStates[i])
				{
				case KEY_NONE: m_keyStates[i] = KEY_DOWN; break;
				case KEY_DOWN: m_keyStates[i] = KEY_PRESS; break;
				case KEY_UP: m_keyStates[i] = KEY_DOWN; break;
				}
			}
			else
			{
				switch (m_keyStates[i])
				{
				case KEY_DOWN: m_keyStates[i] = KEY_UP; break;
				case KEY_PRESS: m_keyStates[i] = KEY_UP; break;
				case KEY_UP: m_keyStates[i] = KEY_NONE; break;
				}
			}
		}
	}

	void UpdateMouseState()
	{
		m_mousePrevPos = m_mouseCurrentPos;
		GetCursorPos(&m_mouseCurrentPos);		// 스크린 좌표
		ScreenToClient(g_hWnd, &m_mouseCurrentPos);	// 스크린 -> 작업영역 좌표
		m_mouseDeltaPos.x = m_mouseCurrentPos.x - m_mousePrevPos.x;
		m_mouseDeltaPos.y = m_mouseCurrentPos.y - m_mousePrevPos.y;

		for (int i = 0; i < MOUSE_COUNT; i++)
		{
			int vKey = 0;
			switch (i)
			{
			case MOUSE_LEFT: vKey = VK_LBUTTON; break;
			case MOUSE_CENTER: vKey = VK_MBUTTON; break;
			case MOUSE_RIGHT: vKey = VK_RBUTTON; break;
			}

			bool isPressed = GetAsyncKeyState(vKey) & 0x8000;

			if (isPressed)
			{
				switch (m_mouseStates[i])
				{
				case MOUSE_NONE: m_mouseStates[i] = MOUSE_DOWN; break;
				case MOUSE_DOWN:
					if (m_mouseDeltaPos.x == 0 && m_mouseDeltaPos.y == 0)
					{
						m_mouseStates[i] = MOUSE_PRESS;
					}
					else
					{
						m_mouseStates[i] = MOUSE_DRAG;
					}
					break;
				case MOUSE_PRESS:
					if (m_mouseDeltaPos.x != 0 || m_mouseDeltaPos.y != 0)
					{
						m_mouseStates[i] = MOUSE_DRAG;
					}
					break;
				case MOUSE_DRAG:
					if (m_mouseDeltaPos.x == 0 && m_mouseDeltaPos.y == 0)
					{
						m_mouseStates[i] = MOUSE_PRESS;
					}
					break;
				case MOUSE_UP: m_mouseStates[i] = MOUSE_DOWN; break;
				}
			}
			else
			{
				switch (m_mouseStates[i])
				{
				case MOUSE_DOWN: m_mouseStates[i] = MOUSE_UP; break;
				case MOUSE_PRESS: m_mouseStates[i] = MOUSE_UP; break;
				case MOUSE_DRAG: m_mouseStates[i] = MOUSE_UP; break;
				case MOUSE_UP: m_mouseStates[i] = MOUSE_NONE; break;
				}
			}
		}
	}

public:
	void Init()
	{
		m_hWnd = g_hWnd;
		GetCursorPos(&m_mousePrevPos);
		ScreenToClient(g_hWnd, &m_mousePrevPos);
		m_mouseCurrentPos = m_mousePrevPos;

		for (int i = 0; i < KEY_COUNT; i++)
		{
			m_keyStates[i] = KEY_NONE;
		}

		for (int i = 0; i < MOUSE_COUNT; i++)
		{
			m_mouseStates[i] = MOUSE_NONE;
		}
	}

	void Release()
	{

	}

	void Update()
	{
		UpdateKeyState();
		UpdateMouseState();
	}

	KEY_STATE GetKeyState(int key) { return m_keyStates[key]; }
	MOUSE_STATE GetMouseState(MOUSE_BUTTON btn) { return m_mouseStates[btn]; }

	POINT GetMousePos() { return m_mouseCurrentPos; }
	POINT GetMouseDelta() { return m_mouseDeltaPos; }
	D3DXVECTOR2 GetMousePosVector2() { return D3DXVECTOR2(m_mouseCurrentPos.x, m_mouseCurrentPos.y); }
	D3DXVECTOR3 GetMouseDeltaInVector3() { return D3DXVECTOR3(m_mouseDeltaPos.x, m_mouseDeltaPos.y, 0); }

	bool IsKeyDown(int key) { return GetKeyState(key) == KEY_DOWN; }
	bool IsKeyUp(int key) { return GetKeyState(key) == KEY_UP; }
	bool IsKeyPress(int key) { return GetKeyState(key) == KEY_PRESS; }

	bool IsMouseDown(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_DOWN; }
	bool IsMouseUp(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_UP; }
	bool IsMousePress(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_PRESS; }
	bool IsMouseDrag(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_DRAG; }

};

