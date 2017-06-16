#pragma once

template <typename T>
class Singleton
{
protected:
	static T* m_pInstance;

	Singleton() { }
	~Singleton() { }

public:
	static T* Instance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new T;
		}
		return m_pInstance;
	}
};

template <typename T>
T* Singleton<T>::m_pInstance;