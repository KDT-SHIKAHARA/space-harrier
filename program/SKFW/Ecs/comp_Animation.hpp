#pragma once
#include<memory>
#include<string>
#include<vector>
#include<unordered_map>

#include<SKFW/Ecs/base_Drawable.hpp>
#include<SKFW/Framework/Anim2D.hpp>
#include<SFML/Graphics/Sprite.hpp>
#include<SKFW/Framework/Flag.h>

class AnimationComponent : public IDrawable
{
	/// <summary>
	/// �A�j���[�V�����̔��]����
	/// �X�P�[���𔽓]�����Ē��S�ʒu���ς��Ȃ��悤�ɂ���B
	/// </summary>
	void FlipAnimation();

public:
	AnimationComponent(uint32_t a_layer = 0);
	void Initialize() override;
	void FixedUpdate(float fixedDt) override;
	void Draw(sf::RenderWindow& a_window, float a_alpha) override;


	/// <summary>
	/// �����摜�̃A�j���[�V�����̒ǉ�
	/// </summary>
	/// <param name="a_animKey">�A�j���[�V�����̖��O</param>
	/// <param name="a_filePath">�t�@���_�p�X</param>
	/// <param name="a_firstFrame">�ŏ��̃t���[��</param>
	/// <param name="a_lastFrame">�Ō�̃t���[��</param>
	/// <param name="a_move">���[�v�������肩</param>
	void AddFrameAnimation(const std::string& a_animKey, const std::string& a_filePath
		, int a_firstFrame, int a_lastFrame, IAnimation2D::eMode a_move, float a_durationPerFrame = 0.2f);

	//	�����摜�̃A�j���[�V�����̒ǉ�
	//void AddSpriteSheetAnimation();

	/// <summary>
	/// �A�j���[�V�����̏I������
	/// </summary>
	/// <returns>true: �Đ��I�����Ă���</returns>
	bool IsAnimationFinished()const noexcept;

	/// <summary>
	/// ���̃A�j���[�V�������̃Z�b�g
	/// </summary>
	/// <param name="a_name"></param>
	void SetAnimationKey(const std::string& a_name);

private:
	/// <summary>
	/// �\������X�v���C�g
	/// </summary>
	std::unique_ptr<sf::Sprite> m_sprite;

	/// <summary>
	///	�A�j���[�V�������ɊǗ�����R���N�V����
	/// </summary>
	std::unordered_map<std::string, std::unique_ptr<IAnimation2D>> m_animations;

	/// <summary>
	/// ���̃A�j���[�V�����̖��O
	/// </summary>
	std::string m_currentAnimationName;


public:

	/// <summary>
	/// �A�j���[�V�����̔���t���O
	/// </summary>
	Flag m_hasChanged{ Flag::Off };
};

