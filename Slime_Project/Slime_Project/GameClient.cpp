#include "pch.h"
#include "GameClient.h"
#include "Scene.h"

GameClient::GameClient()
{
	_hWnd = nullptr;
	_sceneManager = make_unique<SceneManager>();		// memory leak
}

GameClient::~GameClient()
{
}

void GameClient::Init(HWND hWnd)
{
	_hWnd = hWnd;
	_sceneManager->Init(hWnd);
	GET_SINGLE(Time)->Init();
}

void GameClient::Update()
{
	GET_SINGLE(Time)->Update();				// 시간 업데이트
	_sceneManager->Update(_hWnd);
}

void GameClient::Draw()
{
	PAINTSTRUCT ps;
	HDC hdc, MemDC, tmpDC;
	HBITMAP BackBit, oldBackBit;
	RECT rect;
	hdc = BeginPaint(_hWnd, &ps);

	GetClientRect(_hWnd, &rect);
	MemDC = CreateCompatibleDC(hdc);
	BackBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
	PatBlt(MemDC, 0, 0, rect.right, rect.bottom, WHITENESS);
	tmpDC = hdc;
	hdc = MemDC;
	MemDC = tmpDC;

	_sceneManager->Draw(_hWnd, hdc);

	/** 더블버퍼링 끝처리 입니다. **/
	tmpDC = hdc;
	hdc = MemDC;
	MemDC = tmpDC;
	GetClientRect(_hWnd, &rect);
	BitBlt(hdc, 0, 0, rect.right, rect.bottom, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, oldBackBit);
	DeleteObject(BackBit);
	DeleteDC(MemDC);
	EndPaint(_hWnd, &ps);
}

void GameClient::KeyInput(UINT keyMessage, WPARAM wParam, LPARAM lParam)
{
	_sceneManager->KeyInput(_hWnd, keyMessage,wParam,lParam);
}
