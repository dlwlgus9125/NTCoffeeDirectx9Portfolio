#pragma once
#include "fmod\fmod.hpp"
#pragma comment (lib, "fmod/fmodex_vc.lib")
using namespace FMOD;

#define	SOUND					cSoundManager::Instance()
#define SOUND_MAX_CHANNEL	20

class cSoundManager : public Singleton<cSoundManager>
{
private:
	System* m_pSystem;
	map<string, Sound*> m_sounds;
	list<Channel*> m_channels;

public:
	void Setup();
	void Release();
	void Update();

	void LoadFile(string key, string filename, bool bgm);
	void Play(string key, float volume = 1.0f);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	Sound* FindSound(string key);
	Channel* FindChannel(string key);
};