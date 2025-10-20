#pragma once
#include<SKFW/Framework/TagManager.hpp>
#include<SKFW/Debug/DebugTab.hpp>

class DebugTagManager : public DebugTabBase
{
public:
	DebugTagManager()
		:DebugTabBase("Tags"){ }

	void Draw()override
	{
		TagManager::Instance().DrawImGui();
	}
};
