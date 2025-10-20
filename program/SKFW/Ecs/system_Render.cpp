#include<SKFW/Ecs/system_Render.hpp>

#include<SKFW/Ecs/GameObject.hpp>

/// <summary>
/// �`��R���|�[�l���g�̎Q�Ɗi�[
/// </summary>
/// <param name="a_render"></param>
void RenderSystem::Register(std::shared_ptr<IDrawable> a_render)
{
	if (!a_render)
	{
		return;
	}

	//	���C���[�ԍ����R���N�V�������������Ȃ�g��
	int layer = a_render->GetLayer();
	if (layer >= m_renders.size())
	{
		m_renders.resize(layer + 1);
	}

	//	�ǉ�
	m_renders[layer].push_back(a_render);
}


/// <summary>
/// �`�揈��
/// </summary>
void RenderSystem::Render(sf::RenderWindow& a_window, float a_alpha)
{
	for (auto& layer : m_renders)
	{
		for (auto& render : layer)
		{
			//	���g�Ȃ���Ύ���
			if (render.expired() == true)
			{
				continue;
			}

			//	�|�C���^�擾
			auto ptr = render.lock();

			//	GameObject���Ȃ��Ƃ� or �����̎���
			//	�������s�킸�Ɏ���
			if (ptr->GetGameObject() == nullptr ||
				ptr->GetGameObject()->GetEnable() == false)
			{
				continue;
			}

			//	�\���\��ԂȂ�`�悷��
			if (ptr->IsVisible() == true)
			{
				ptr->Draw(a_window,a_alpha);
			}
		} // for 2
	}	//	for 1
}


/// <summary>
/// �t���[�����ɍ폜����
/// </summary>
void RenderSystem::ProcessExpired()
{


	//	���C���[�ԍ����ƂɎQ�Ɛ؂ꂪ�Ȃ���������
	for (auto& layer : m_renders)
	{
		std::erase_if(layer,
			[](const std::weak_ptr<IDrawable>& render)
			{
				return render.expired();
		});
	}
}

/// <summary>
///	��Ԃ̃��Z�b�g
/// </summary>
void RenderSystem::Clear()
{
	m_renders.clear();
}