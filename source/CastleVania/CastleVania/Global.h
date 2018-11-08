#pragma once
class Global
{
	static Global * __instance;
	int SIMON_WALKING_TEST;
public:

	void Set(int a) { SIMON_WALKING_TEST = a; }
	int Get() { return SIMON_WALKING_TEST; }
	static Global * GetInstance();
	Global();
	~Global();
};

