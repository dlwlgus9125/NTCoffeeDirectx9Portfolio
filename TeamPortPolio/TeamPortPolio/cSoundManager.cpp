#include "stdafx.h"
#include "cSoundManager.h"

void cSoundManager::Setup()
{
	System_Create(&m_pSystem);
	m_pSystem->init(SOUND_MAX_CHANNEL, FMOD_INIT_NORMAL, 0);


	SOUND->LoadFile("Melee_Charge1", "Sound/Voice/MeleeUnit/Melee_Charge1.wav", false);
	SOUND->LoadFile("Melee_Charge2", "Sound/Voice/MeleeUnit/Melee_Charge2.wav", false);
	SOUND->LoadFile("Melee_Charge3", "Sound/Voice/MeleeUnit/Melee_Charge3.wav", false);

	SOUND->LoadFile("PullBow", "Sound/FightEffect/pull_bow.ogg", false);
	SOUND->LoadFile("ShootBow", "Sound/FightEffect/Shoot_Bow.ogg", false);
}

void cSoundManager::Release()
{
	m_pSystem->release();
	m_pSystem->close();
}

void cSoundManager::Update()
{
	m_pSystem->update();

	list<Channel*>::iterator it;
	for (it = m_channels.begin(); it != m_channels.end(); it++)
	{
		bool isPlaying;
		(*it)->isPlaying(&isPlaying);
		if (!isPlaying)
		{
			m_channels.erase(it);
			break;
		}
	}
}

void cSoundManager::LoadFile(string key, string filename, bool bgm)
{
	Sound* pSound = FindSound(key);
	if (pSound != NULL) return;

	if (bgm)
	{
		m_pSystem->createStream(filename.c_str(),
			FMOD_LOOP_NORMAL, NULL, &pSound);
	}
	else
	{
		m_pSystem->createSound(filename.c_str(),
			FMOD_DEFAULT, NULL, &pSound);
	}

	if (pSound != NULL) m_sounds[key] = pSound;
}

void cSoundManager::Play(string key, float volume)
{
	Sound* pSound = FindSound(key);
	if (pSound == NULL) return;

	Channel* pChannel;
	m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, &pChannel);
	if (pChannel == NULL) return;

	pChannel->setVolume(volume);
	m_channels.push_back(pChannel);
}

void cSoundManager::Stop(string key)
{
	Channel* pChannel = FindChannel(key);
	if (pChannel != NULL) pChannel->stop();
}

void cSoundManager::Pause(string key)
{
	Channel* pChannel = FindChannel(key);
	if (pChannel != NULL) pChannel->setPaused(true);
}

void cSoundManager::Resume(string key)
{
	Channel* pChannel = FindChannel(key);
	if (pChannel != NULL) pChannel->setPaused(false);
}

Sound* cSoundManager::FindSound(string key)
{
	if (m_sounds.find(key) == m_sounds.end()) return NULL;
	return m_sounds[key];
}

Channel* cSoundManager::FindChannel(string key)
{
	Sound* pSound = FindSound(key);
	if (pSound == NULL) return NULL;

	list<Channel*>::iterator it;
	for (it = m_channels.begin(); it != m_channels.end(); it++)
	{
		Sound* pCurrentSound;
		(*it)->getCurrentSound(&pCurrentSound);
		if (pCurrentSound == pSound) return (*it);
	}
	return NULL;
}