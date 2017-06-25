#include "stdafx.h"
#include "cFontManager.h"

LPD3DXFONT cFontManager::GetFont(FONT_TAG e)
{
	if (m_mapFont.find(e) != m_mapFont.end()) return m_mapFont[e];

	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

	if (e == FONT_DEF)
	{
		fd.Height = 16;									// height와 width를 바꾸면 글씨 크기가 바뀜
		fd.Width = 8;
		fd.Weight = FW_BOLD;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		strcpy_s(fd.FaceName, "바탕체");				// 글자체 지정 가능
	}

	if (e == FONT_SHOP)
	{
		fd.Height = 12;									// height와 width를 바꾸면 글씨 크기가 바뀜
		fd.Width = 6;
		fd.Weight = FW_NORMAL;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		strcpy_s(fd.FaceName, "바탕체");				// 글자체 지정 가능
	}


	D3DXCreateFontIndirect(D3DDevice, &fd, &m_mapFont[e]);
	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
		SAFE_DELETE(it.second);
	}
	m_mapFont.clear();
}