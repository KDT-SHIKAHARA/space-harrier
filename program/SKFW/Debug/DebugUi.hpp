#pragma once
#include<memory>

#include<SKFW/Debug/DebugTab.hpp>
#include<SKFW/Framework/Singleton.hpp>
#include<SFML/Graphics.hpp>

class DebugUI : public Singleton<DebugUI>
{
	friend class Singleton<DebugUI>;
	DebugUI();
	virtual~DebugUI() = default;
public:
	/// <summary>
	///	ImGui�̃E�B���h�E����
	/// </summary>
	/// <param name="window"></param>
	static void Initialize(sf::RenderWindow& window);

	/// <summary>
	/// ImGui�̃C���X�^���X�j��
	/// </summary>
	static void Shutdown();

	/// <summary>
	/// �E�B���h�E�̃C�x���g���擾
	/// </summary>
	/// <param name="window"></param>
	/// <param name="event"></param>
	static void ProcessEvent(sf::Window& window, sf::Event& event);

	/// <summary>
	/// ��ԍX�V
	/// </summary>
	/// <param name="window"></param>
	/// <param name="dt"></param>
	static void Update(sf::RenderWindow& window, sf::Time dt);

	/// <summary>
	/// �`��X�V
	/// </summary>
	/// <param name="window"></param>
	static void Render(sf::RenderWindow& window);

	/// <summary>
	/// �^�u�̒ǉ�
	/// </summary>
	/// <param name="tab"></param>
	void RegisterTab(std::unique_ptr<DebugTabBase> tab);

	/// <summary>
	///	�ǉ�����Ă���^�u�̕\��
	/// </summary>
	void Draw();



private:
	std::vector<std::unique_ptr<DebugTabBase>> m_tabs;
	bool m_isShowDebugUi = true;

};

