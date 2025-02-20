/*
 *	CameraFormat.h
 *
 * 
 *
 *
 *
 */

#pragma once
#include "Typedef.h"


class CameraFormat
{
//////////////////////////////////////////////////////////////////////////////////////////////////////	
// Construction
//////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	CameraFormat();
	virtual ~CameraFormat();

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Attributes
//////////////////////////////////////////////////////////////////////////////////////////////////////
public:

private:
	CameraPtr 	pCam;

	// 해상도
	int64_t		nCapWidth;
	int64_t		nCapHeight;

	// 캡쳐위치
	int64_t		nOffsetX;
	int64_t		nOffsetY;

	// 캡쳐 프레임 레이트
	bool			bFrameRateMode;
	float			fFrameRate;

protected:
	string 			msg;

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	int		SetCameraPtr(CameraPtr pcam);
	CameraPtr	GetCameraPtr() { return pCam; }

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	bool Init();

	// 해상도
	int			SetCapWidth(int64_t width);
	int64_t	GetCapWidth() { return nCapWidth; }

	int			SetCapHeight(int64_t height);
	int64_t	GetCapHeight() { return nCapHeight; }

	// 캡쳐위치
	int			SetOffsetX(int64_t offsetX);
	int64_t	GetOffsetX() { return nOffsetX; }

	int			SetOffsetY(int64_t offsetY);
	int64_t	GetOffsetY() { return nOffsetY; }

	// 캡쳐 프레임 레이트
	int			SetFrameRateMode(bool enable);
	bool		GetFrmareRateMode() { return bFrameRateMode; }
	int			SetFrameRate(float frameRate);
	float		GetFrameRate() { return fFrameRate; }

	// add. by ariari : 2022.05.18
	// 이미지 프로세스
	int 	SetImageProcess(bool bImgProcEn, bool bGammaEn, bool bSharpEn, int nSharpAuto, float fGamma, int nSharp);

	// GPIO
	int 	SetGpioUserMode();
	int 	SetGpioStrobeMode();
	int 	SetTriggerSouce();
	int		SetLineSelector();
	int 	SetLineMode();
	int		SetLineSource();
	int 	SetUserOutputSelector();
	int		SetUserOutputValue(bool value);
	int 	Set3_3Voltage(bool value);

	// Gamma
	int 	SetImageProcess();

private:

protected:

};
