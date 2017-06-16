#pragma once



class cIScene
{
private:
	int m_tag;

public:
	virtual void OnEnter() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnExit() = 0;
	virtual void OnRender() = 0;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

	int  Tag() { return m_tag; }
	void SetTag(int tag) { m_tag = tag; }
};

#define SCENE cSceneManager::Instance()

class cSceneManager :public Singleton<cSceneManager>
{
private:
	map<int, cIScene*> m_scenes;
	cIScene* m_currentScene;
	int                m_current;
	 
public:
	cSceneManager();
	~cSceneManager();

	void     StartScene(int tag);
	void     Register(int tag, cIScene* pScene);
	void     ChangeScene(int tag);
	void     Update();
	void     Render();
	void     WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int      Current();
	cIScene* GetScene(int tag);
};

