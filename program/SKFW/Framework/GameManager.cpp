#include<SKFW/Framework/GameManager.hpp>
#include<SKFW/Framework/Time.hpp>
#include<SKFW/Framework/InputManager.hpp>
#include<SKFW/Debug/DebugUi.hpp>

#include<SKFW/Ecs/GameObjectManager.hpp>

#include<SKFW/Ecs/system_Transform.hpp>
#include<SKFW/Ecs/system_Render.hpp>
#include<SKFW/Ecs/system_RigidBody.hpp>

#include<SKFW/Debug/Logger.hpp>

GameManager::GameManager()
	:m_running(true), m_fps(240.0f), m_fixedFps(60.0f)
{

}

void GameManager::Update(float a_dt)
{
}

void GameManager::FixedUpdate(float a_fixedDt)
{




	//	�ړ�����
	RigidBodySystem::Instance().FixedUpdate(a_fixedDt);
}

void GameManager::Render(float a_alpha)
{
	RenderSystem::Instance().Render(m_window, a_alpha);
}

void GameManager::HandleEvents()
{
	while (auto event = m_window.pollEvent())
	{
		DebugUI::ProcessEvent(m_window, *event);
		InputManager::Instance().ProcessEvent(*event);

		//	�I������
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}
	}
}

/// <summary>
/// �ڕW��fps
/// </summary>
/// <param name="a_fps"></param>
void GameManager::SetFps(float a_fps)
{
	if (a_fps < 30)
	{
		a_fps = 30;
	}

	m_fps = a_fps;
}

/// <summary>
/// �E�B���h�E�̍쐬�A�e�V�X�e���̐����A������
/// </summary>
void GameManager::Initialize()
{
	//	�J�n���O���o��
	Logger::Info("�Q�[���N��");

	//	�f�[�^�ǂݍ���

	//	�E�B���h�E������
	//	�K�v��������E�B���h�E�p��config�t�@�C����ǉ����ăf�[�^���擾���Ă���쐬���Ă�����
	{
		sf::VideoMode size({ 800,600 });
		std::string title = "sk-framework";
		sf::State mode = sf::State::Windowed;
		m_window = sf::RenderWindow(size, title, sf::Style::Default | sf::Style::Resize, mode);
		m_window.setFramerateLimit(m_fps);
		DebugUI::Initialize(m_window);
	}

	//	���ԊǗ�������
	Time::Instance().Initialize(m_fixedFps);

	//	���O�̏�����
	Logger::Initialize();

	//	�J�n���O���o��
	Logger::Info("�Q�[���J�n���̃t���[�����[�g�ݒ� FPS: %.2f, Fixed FPS: %.2f", m_fps, m_fixedFps);

}

/// <summary>
/// �Q�[�����[�v�A�e�V�X�e���̏�ԍX�V�A�`��X�V���s���B
/// </summary>
void GameManager::Run()
{
	auto& time = Time::Instance();

	//	���[�v
	while (m_window.isOpen() && m_running == true)
	{
		//	�E�B���h�E�̃C�x���g�֌W
		HandleEvents();

		//	��Ƀt���[���J�n�n�_�Ŏ��Ԍo�߂��Ȃ��Ƃ����Ȃ��̂�
		time.Update();


		//	ImGui�̓�����ԍX�V
		DebugUI::Update(m_window, sf::seconds(time.DeltaTime()));


		//	�ύX�V
		this->Update(time.DeltaTime());

		while (time.ShouldFixedUpdate())
		{

			//	���W�n�̑S�̂̏�Ԃ�ۑ�
			TransformSystem::Instance().SavePrevious();

			//	�Œ�X�V
			this->FixedUpdate(time.FixedDelta());
	
			//	�Œ�X�V�̎��Ԍo��
			time.ConsumeFixedDelta();
		}

		Time::Instance().UpdateAlpha();
		
		m_window.clear(sf::Color(64,64,64));

		//	��Ԃ�n���Ċ��炩�ɂ��ĕ`�悷��
		Render(time.Alpha());


		//	ImGui�`��
		DebugUI::Instance().Draw();
		DebugUI::Render(m_window);

		m_window.display();

		InputManager::Instance().Update();

		//	�폜���[�v
		GameObjectManager::Instance().CleanupDestroyedObjects();
		TransformSystem::Instance().CleanupDestroyed();
		RenderSystem::Instance().ProcessExpired();
		RigidBodySystem::Instance().CleanupDestroyed();
	}

}

/// <summary>
/// �I�������A�E�B���h�E�̔j���A�t���[�����[�N�̍폜���䂪�K�v�Ȃ�s��
/// </summary>
void GameManager::Finalize()
{
	DebugUI::Shutdown();
	Logger::Info("�Q�[���̐���I��");
}

/// <summary>
/// �Q�[�����[�v�̏I��
/// </summary>
void GameManager::Stop()
{
	m_running = false;
}
