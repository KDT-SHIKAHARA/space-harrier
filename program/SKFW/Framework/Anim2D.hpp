#pragma once

#include<vector>
#include<string>

#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>

#include<SKFW/Framework/Flag.h>

/// <summary>
/// Animation2D�̃C���^�[�t�F�[�X
/// </summary>
class IAnimation2D
{
public:
	enum class eMode
	{
		Once,
		Loop,
	};

	/// <summary>
	/// �ǂݍ��݌`���̎��
	/// </summary>
	enum class eType
	{
		Frame,
		Split,
	};


	IAnimation2D(IAnimation2D::eMode a_mode = IAnimation2D::eMode::Loop, float a_durationPerFrame = 0.2f)
		: m_playMode(a_mode), m_durationPerFrame(a_durationPerFrame)
	{
	}
	virtual ~IAnimation2D() = default;
	virtual void Update(double a_fixedDt) = 0;
	virtual void Reset() = 0;

	/// <summary>
	/// �e�N�X�`���̎擾
	/// </summary>
	/// <returns></returns>
	virtual const sf::Texture* GetTexture()const = 0;

	/// <summary>
	/// �t���[���̐؂�ւ����Ԃ̐ݒ�
	/// </summary>
	/// <param name="a_duration"></param>
	void SetDurationPerFrame(float a_duration)
	{
		//	�}�C�i�X�l�͕s��
		if (a_duration < 0.0)
		{
			a_duration = 0.1f;
		}

		m_durationPerFrame = a_duration;
	}

	eType GetType()const { return m_loadType; }
	void SetType(eType a_type)noexcept { m_loadType = a_type; }

protected:
	/// <summary>
	/// �Đ��̎�ނ̑I��
	/// </summary>
	eMode m_playMode{ eMode::Loop };

	/// <summary>
	/// �ǂݍ��݂̎��
	/// </summary>
	eType m_loadType{eType::Frame};

	/// <summary>
	/// ���݃t���[���̌o�ߎ���
	/// </summary>
	double m_elapsedTime = 0.0;

	/// <summary>
	/// �A�j���[�V������؂�ւ��鎞��
	/// </summary>
	float m_durationPerFrame = 0.1f;

	/// <summary>
	/// �\���{��
	/// </summary>
	float m_drawScale = 1.0f;



public:
	/// <summary>
	/// �Đ������ǂ����̃t���O
	/// </summary>
	Flag m_isPlaying{ Flag::On };

	/// <summary>
	/// �Đ����I�����Ă��邩�ǂ����̃t���O
	/// </summary>
	Flag m_isFinished{ Flag::Off };

	/// <summary>
	/// �e�N�X�`�����ύX���ꂽ���ǂ����̃t���O
	/// </summary>
	Flag m_hasChanged{ Flag::Off };

};

/// <summary>
/// �����̉摜�ŃA�j���[�V�������s���N���X
/// </summary>
class FrameAnimation2D : public IAnimation2D
{
public:
	/// <summary>
	/// �A�j���[�V�����Đ��ɕK�v�ȏ������̏�����
	/// �e�N�X�`���̓��\�[�X�Ǘ�������������Ă���B
	/// �A�j���[�V�����p�̉摜�̃t�H���_�p�X���A�ԂɂȂ��Ă��邱�Ƃ��O��B
	/// </summary>
	/// <param name="a_filepath">�����摜�̋��ʃp�X</param>
	/// <param name="a_firstFrame">�摜��1���ڂ̔ԍ�</param>
	/// <param name="a_lastFrame">�A�j���[�V�����̍Ō�̔ԍ�</param>
	/// <param name="a_mode">once:���[�v�Ȃ� loop:���[�v</param>
	FrameAnimation2D(const std::string& a_filepath, int a_firstFrame,int a_lastFrame
		, IAnimation2D::eMode a_mode = IAnimation2D::eMode::Loop,float a_durationPerFrame = 0.2f);

	/// <summary>
	/// �A�j���[�V�����̍X�V����
	/// </summary>
	/// <param name="a_fixedDt"></param>
	void Update(double a_fixedDt) override;

	/// <summary>
	/// �؂�ւ����̃��Z�b�g����
	/// </summary>
	void Reset() override;

	/// <summary>
	/// �e�N�X�`���̎擾
	/// </summary>
	/// <returns></returns>
	const sf::Texture* GetTexture()const override;

private:

	/// <summary>
	/// �A�j���[�V�����̃t���[����i�߂�
	/// </summary>
	void stepFrame();

private:
	/// <summary>
	/// �e�N�X�`���Q
	/// </summary>
	std::vector<const sf::Texture*> m_textures;

	/// <summary>
	/// �ŏ��̃t���[���̃C���f�b�N�X��ێ����鐮���ϐ��B
	/// </summary>
	int m_firstFrame = 0;

	/// <summary>
	/// �Ō�̃t���[���̃C���f�b�N�X��ێ����鐮���ϐ��B
	/// </summary>
	int m_lastFrame = 0;

	/// <summary>
	/// ���݂̃t���[���C���f�b�N�X��ێ����鐮���ϐ��B
	/// </summary>
	int m_currentFrame = 0;
};
