#pragma once
#include<SFML/Graphics.hpp>
#include<SKFW/Framework/Singleton.hpp>

/// <summary>
/// �Q�[�����[�t��t���[�����[�N���Ǘ�����B
/// </summary>
class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

	GameManager();
	virtual ~GameManager() = default;

	/// <summary>
	/// �σt���[���̍X�V����
	/// ���͂�UI�Ȃǂ͂����ɁB
	/// </summary>
	/// <param name="dt"></param>
	void Update(float a_dt);

	/// <summary>
	/// �Œ�t���[���̍X�V����
	/// �Œ�X�V�̍X�V�p�x�͕ύX����Ȃ��B
	/// �����AAI�Ȃǂ������Ɂ@
	/// </summary>
	/// <param name="a_fixedDt"></param>
	void FixedUpdate(float a_fixedDt);

	/// <summary>
	/// �`�揈��
	/// ��Ԑ��l��n���ČŒ�X�V�ƕ`��̂�����C������B
	/// �Œ肪60fps�ƕ`��120fps�͂��񂺂�Ⴄ����ˁB
	/// </summary>
	/// <param name="a_alpha"></param>
	void Render(float a_alpha);

	/// <summary>
	/// �E�B���h�E�̃C�x���g�n�̏���
	/// </summary>
	void HandleEvents();

	/// <summary>
	/// �ڕW��fps
	/// </summary>
	/// <param name="a_fps"></param>
	void SetFps(float a_fps);
public:
	/// <summary>
	/// �E�B���h�E�̍쐬�A�e�V�X�e���̐����A������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �Q�[�����[�v�A�e�V�X�e���̏�ԍX�V�A�`��X�V���s���B
	/// </summary>
	void Run();

	/// <summary>
	/// �I�������A�E�B���h�E�̔j���A�t���[�����[�N�̍폜���䂪�K�v�Ȃ�s��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �Q�[�����[�v�̏I��
	/// </summary>
	void Stop();

private:
	/// <summary>
	///	�E�B���h�E��Window�f�o�C�X�֌W�̑���
	/// </summary>
	sf::RenderWindow m_window;

	/// <summary>
	/// �Œ肵�����t���[�����[�g�̐��l
	/// </summary>
	float m_fps;

	/// <summary>
	/// �Œ菈���p�̃t���[�����[�g
	/// </summary>
	float m_fixedFps;


	/// <summary>
	/// ���[�v�̎��s�t���O
	/// true: ���s���@false: �I��
	/// </summary>
	bool m_running;


};
