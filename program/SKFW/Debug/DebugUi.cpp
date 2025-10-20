#include<SKFW/Debug/DebugUi.hpp>
#include<SKFW/Framework/InputManager.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#ifdef _DEBUG
#define DEBUGUI_ENABLED 1
#else
#define DEBUGUI_ENABLED 0
#endif // _DEBUG

#include<SKFW/Debug/debug_GameManager.hpp>
#include<SKFW/Debug/debug_TagManager.hpp>
#include<SKFW/Debug/debug_GameObjectManager.hpp>

DebugUI::DebugUI()
{
	this->RegisterTab(std::make_unique<DebugGameManager>());
	this->RegisterTab(std::make_unique<DebugTagManager>());
	this->RegisterTab(std::make_unique<DebugGameObjectManager>());
}

/// <summary>
///	ImGui�̃E�B���h�E����
/// </summary>
/// <param name="window"></param>
void DebugUI::Initialize(sf::RenderWindow& window)
{
#if DEBUGUI_ENABLED
	ImGui::SFML::Init(window);
#endif // DEBUGUI_ENABLED
}

/// <summary>
/// ImGui�̃C���X�^���X�j��
/// </summary>
void DebugUI::Shutdown()
{
#if DEBUGUI_ENABLED
	ImGui::SFML::Shutdown();
#endif // DEBUGUI_ENABLED
}

/// <summary>
/// �E�B���h�E�̃C�x���g���擾
/// </summary>
/// <param name="window"></param>
/// <param name="event"></param>
void DebugUI::ProcessEvent(sf::Window& window, sf::Event& event)
{
#if DEBUGUI_ENABLED
	ImGui::SFML::ProcessEvent(window, event);
#endif // DEBUGUI_ENABLED
}

/// <summary>
/// ��ԍX�V
/// </summary>
/// <param name="window"></param>
/// <param name="dt"></param>
void DebugUI::Update(sf::RenderWindow& window, sf::Time dt)
{
#if DEBUGUI_ENABLED
	ImGui::SFML::Update(window, dt);
#endif // DEBUGUI_ENABLED
}

/// <summary>
/// �`��X�V
/// </summary>
/// <param name="window"></param>
void DebugUI::Render(sf::RenderWindow& window)
{
#if DEBUGUI_ENABLED
	ImGui::SFML::Render(window);
#endif // DEBUGUI_ENABLED
}

/// <summary>
/// �^�u�̒ǉ�
/// </summary>
/// <param name="tab"></param>
void DebugUI::RegisterTab(std::unique_ptr<DebugTabBase> tab)
{
#if DEBUGUI_ENABLED
	m_tabs.push_back(std::move(tab));
#endif // DEBUGUI_ENABLED

}

/// <summary>
///	�ǉ�����Ă���^�u�̕\��
/// </summary>
void DebugUI::Draw()
{
#if DEBUGUI_ENABLED

	//	F1�ŕ\���t���O�̐؂�ւ�
	if (InputManager::Instance().IsKeyPressed(sf::Keyboard::Key::F1)) {
		m_isShowDebugUi = !m_isShowDebugUi;
	}

	//	�\���t���O�������Ă���Ƃ�����
	if (m_isShowDebugUi) {
		ImGui::Begin("debug");

		if (ImGui::BeginTabBar("debug tab", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_AutoSelectNewTabs)) {
			for (auto& tab : m_tabs) {
				if (ImGui::BeginTabItem(tab->GetName().c_str())) {
					tab->Draw();
					ImGui::EndTabItem();
				}
			}
			ImGui::EndTabBar();
		}

		ImGui::End();
	}

#endif // DEBUGUI_ENABLED
}
