#include<SKFW/Ecs/comp_Animation.hpp>
#include<SKFW/Framework/TextureResource.hpp>
#include<SKFW/Ecs/GameObject.hpp>
#include<SKFW/Ecs/comp_Transform.hpp>

void AnimationComponent::FlipAnimation()
{
}

AnimationComponent::AnimationComponent(uint32_t a_layer)
	:IDrawable(a_layer)
{

}

void AnimationComponent::Initialize()
{
}

void AnimationComponent::FixedUpdate(float fixedDt)
{
	//	���݂̃A�j���[�V�������X�V
	if(m_currentAnimationName.empty() == false)
	{
		auto it = m_animations.find(m_currentAnimationName);
		if (it != m_animations.end())
		{
			//	��ԍX�V
			it->second->Update(fixedDt);


			//	�e�N�X�`���𒣂�ւ��邩�ǂ����̓^�C�v�����Ĕ��肷��

			//	�e�N�X�`�����؂�ւ���ꂽ�Ȃ璣��ւ���
			if (it->second->m_hasChanged == true)
			{
				m_sprite->setTexture(*it->second->GetTexture());
			}
			
		}

	}
}

void AnimationComponent::Draw(sf::RenderWindow& a_window, float a_alpha)
{
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	if (transform == nullptr)
	{
		return;
	}
	
}

/// <summary>
/// �����摜�̃A�j���[�V�����̒ǉ�
/// </summary>
/// <param name="a_animKey">�A�j���[�V�����̖��O</param>
/// <param name="a_filePath">�t�@���_�p�X</param>
/// <param name="a_firstFrame">�ŏ��̃t���[��</param>
/// <param name="a_lastFrame">�Ō�̃t���[��</param>
/// <param name="a_move">���[�v�������肩</param>
void AnimationComponent::AddFrameAnimation(const std::string& a_animKey, const std::string& a_filePath, int a_firstFrame, int a_lastFrame, IAnimation2D::eMode a_move, float a_durationPerFrame)
{
	//	�������Ă���m�F���ăR���N�V�����ɒǉ�
	auto animation = std::make_unique<FrameAnimation2D>(a_filePath, a_firstFrame, a_lastFrame, a_move, a_durationPerFrame);

	//	����
	if (animation == nullptr)
	{
		return;
	}

	//	��̎��������݂̃A�j���[�V���������Z�b�g
	//	�f�t�H���g�ݒ肵�Ȃ��ƂˁB
	if(m_currentAnimationName.empty())
	{
		m_currentAnimationName = a_animKey;
	}

	//	�R���N�V�����ɒǉ�
	m_animations.emplace(a_animKey, std::move(animation));
}

/// <summary>
/// �A�j���[�V�����̏I������
/// </summary>
/// <returns></returns>
bool AnimationComponent::IsAnimationFinished() const noexcept
{
	if(m_currentAnimationName.empty())
	{
		return false;
	}

	return m_animations.at(m_currentAnimationName)->m_isFinished;
}

/// <summary>
/// ���̃A�j���[�V�������̃Z�b�g
/// </summary>
/// <param name="a_name"></param>
void AnimationComponent::SetAnimationKey(const std::string& a_name)
{
	auto it = m_animations.find(a_name);
	if(it != m_animations.end())
	{
		it->second->Reset();
		m_currentAnimationName = a_name;
	}
}
