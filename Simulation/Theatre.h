#pragma once

class Theatre
{
public:
	Theatre();
	~Theatre();

	void Init();

	void PlayShows();

private:
	bool Shutdown();

	bool mInitialised;
};

