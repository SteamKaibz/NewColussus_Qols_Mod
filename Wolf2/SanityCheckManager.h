#pragma once


class SanityCheckManager
{
public:

	//! making sure dev menu in enabled so user can acces the mod settings, even if user disabled the dev menu through the console.
	void forceDevMenuOn();
	void update();
};

