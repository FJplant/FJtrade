#pragma once


// FJFutureDiffGraphFrame 프레임입니다.

class FJFutureDiffGraphFrame : public CWnd
{
	DECLARE_DYNCREATE(FJFutureDiffGraphFrame)
public:
	FJFutureDiffGraphFrame();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~FJFutureDiffGraphFrame();

protected:
	DECLARE_MESSAGE_MAP()
};


