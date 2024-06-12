#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);

	HFONT font;
	HFONT oldFont;

	font = CreateFont
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0,
		TEXT(fontName)
	);

	oldFont = (HFONT)SelectObject(hdc, font);
	TextOut(hdc, destX, destY, printString, length);

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	SetTextColor(hdc, RGB(0, 0, 0));
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, int stat, COLORREF color)
{
	char str[30] = "";
	wsprintf(str, "%d", stat);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);

	HFONT font;
	HFONT oldFont;

	font = CreateFont
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0,
		TEXT(fontName)
	);

	oldFont = (HFONT)SelectObject(hdc, font);
	TextOut(hdc, destX, destY, str, strlen(str));

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	SetTextColor(hdc, RGB(0, 0, 0));
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);

	HFONT font;
	HFONT oldFont;

	font = CreateFont
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0,
		TEXT(fontName)
	);

	oldFont = (HFONT)SelectObject(hdc, font);
	for (int i = 0; i < length; i++)
	{
		Sleep(10);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	SetTextColor(hdc, RGB(0, 0, 0));
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);

	HFONT font;
	HFONT oldFont;

	font = CreateFont
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0,
		TEXT(fontName)
	);

	oldFont = (HFONT)SelectObject(hdc, font);

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	SetTextColor(hdc, RGB(0, 0, 0));
}
