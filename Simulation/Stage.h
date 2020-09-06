#pragma once

class Stage
{
public:
	Stage();
	~Stage();

	void Init();

	void PlayShow();

private:
	void PackDown();

	bool mInitialised;


};

