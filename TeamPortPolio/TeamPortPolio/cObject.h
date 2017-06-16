#pragma once
enum OBJECT_TAG
{
	OBJECT_CHARACTER,
	OBJECT_UI,
	OBJECT_ITEM,
};



class ISteeringEntity;
class cObject
{
	//vector<ST_PNT_VERTEX> m_vecVertex;
protected:
	ULONG m_ulRefCount;

public:
	cObject();
	virtual ~cObject();
	virtual void Init() {};
	virtual void Update(float deltaTime) {};
	virtual void Render() {};
	virtual void AddRef();
	virtual void Release();

	virtual ISteeringEntity* GetCharacterEntity() { return NULL; }
};
