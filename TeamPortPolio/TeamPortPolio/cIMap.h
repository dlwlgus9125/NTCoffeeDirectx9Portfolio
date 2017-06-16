#pragma once
class cIMap
{
	SYNTHESIZE(bool, m_drawWired, Wire);

public:
	virtual void Update() = 0;
	virtual bool GetHeight(IN float x, OUT float &y, IN float z) = 0;
	virtual void Render() = 0;
};
