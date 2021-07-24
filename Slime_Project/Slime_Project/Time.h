#pragma once
class Time
{
	DECLARE_SINGLE(Time);
public:
	void	Init();
	void	Update();

	int		GetFps() { return _fps; }
	float	GetDeltaTime() { return _deltaTime; }

private:
	uint64	_frequency = 0;
	uint64	_prevCount = 0;
	float	_deltaTime = 0.f;

private:
	uint32	_frameCount = 0;
	float	_frameTime = 0.f;
	uint32	_fps = 0;
};

