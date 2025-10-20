#pragma once
#include<SKFW/Framework/ObjectPool.hpp>
#include<SKFW/Ecs/comp_Transform.hpp>
#include<SKFW/Framework/Singleton.hpp>

#include<vector>


class TransformSystem : public Singleton<TransformSystem>
{
	friend class Singleton<TransformSystem>;
	TransformSystem() = default;

public:

	/// <summary>
	/// �V�X�e���ɓo�^����
	/// </summary>
	/// <param name="a_transform"></param>
	void Register(std::shared_ptr<TransformComponent> a_transform);

	/// <summary>
	/// �O�̃t���[���̏�Ԃ�ۑ�����
	/// </summary>
	void SavePrevious();

	/// <summary>
	/// �폜�t���O�̗����Ă���I�u�W�F�N�g���폜����B
	/// ���̏������Ă΂��̂̓t���[�������̂݁B
	/// ������C���X�^���X���j������Ȃ��̂𗘗p���ăt���O�����āA�폜�t���O�������Ă�����폜������
	/// </summary>
	void CleanupDestroyed();

private:
	/// <summary>
	/// ���A�N�e�B�u��t�����X�t�H�[���̎Q��
	/// </summary>
	std::vector<std::weak_ptr<TransformComponent>> m_transforms;

};