#include "system_Transform.hpp"

/// <summary>
/// �V�X�e���ɓo�^����
/// </summary>
/// <param name="a_transform"></param>
void TransformSystem::Register(std::shared_ptr<TransformComponent> a_transform)
{
	m_transforms.push_back(a_transform);
}

/// <summary>
/// �O�̃t���[���̏�Ԃ�ۑ�����
/// </summary>
void TransformSystem::SavePrevious()
{
	for (auto& weakTransform : m_transforms)
	{
		if (auto transform = weakTransform.lock())
		{
			transform->SavePrevious();
		}
	}
}

/// <summary>
/// �폜�t���O�̗����Ă���I�u�W�F�N�g���폜����B
/// ���̏������Ă΂��̂̓t���[�������̂݁B
/// ������C���X�^���X���j������Ȃ��̂𗘗p���ăt���O�����āA�폜�t���O�������Ă�����폜������
/// </summary>
void TransformSystem::CleanupDestroyed()
{
	std::erase_if(m_transforms,
		[](const std::weak_ptr<TransformComponent>& weakTransform)
		{
			return weakTransform.expired();
		});
}