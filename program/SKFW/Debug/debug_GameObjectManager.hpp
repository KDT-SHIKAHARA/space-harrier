#pragma once
#include<SKFW/Debug/DebugTab.hpp>
#include<SKFW/Ecs/GameObjectManager.hpp>

#include<SKFW/Ecs/comp_Transform.hpp>
#include<SKFW/Ecs/comp_Image.hpp>
#include<SKFW/Framework/TextureResource.hpp>
#include<SKFW/Ecs/comp_RigidBody.hpp>


class DebugGameObjectManager : public DebugTabBase
{
public:
	DebugGameObjectManager()
		:DebugTabBase("GameObjects")
	{ }

	void Draw()override
	{
		ImGui::Text("GameObjects:");
		ImGui::Separator();

		ImGui::Text("Active Count: %5d", GameObjectManager::Instance().GetActiveCount());

		ImGui::Separator();

		//	プレイヤー追加ボタン
		if (ImGui::Button("Player Add"))
		{
			auto& obj =  GameObjectManager::Instance().Create(eObjectLivedType::Long,"Player");
			auto trans = obj->AddComponent<TransformComponent>();
			trans->SetPosition({000,000});
			auto texture = TextureResourceManager::Instance().GetTexture(DEFAULT_TEXTURE_PATH);
			obj->AddComponent<ImageComponent>(texture, 0);
			auto rigid = obj->AddComponent<RigidBodyComponent>();
			rigid->MoveInput({1,0});
		}

	}
};
