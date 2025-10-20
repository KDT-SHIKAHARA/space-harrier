#pragma once

#include<memory>
#include<vector>

#include<SKFW/Framework/Singleton.hpp>
#include<SKFW/Ecs/comp_RigidBody.hpp>


class RigidBodySystem : public Singleton<RigidBodySystem>
{
	friend class Singleton<RigidBodySystem>;
	RigidBodySystem() = default;
	virtual ~RigidBodySystem() = default;
public:

	/// <summary>
	///	�A�N�e�B�u�A���X�g�ɒǉ�
	/// </summary>
	/// <param name="a_rigidbody"></param>
	void Register(std::shared_ptr<RigidBodyComponent> a_rigidbody);

	/// <summary>
	/// �Œ�X�V���Ăяo��
	/// </summary>
	/// <param name="fixedDt"></param>
	void FixedUpdate(float fixedDt);

	/// <summary>
	/// �t���[�����ɎQ�Ɛ؂���A�N�e�B�u���X�g����폜����
	/// </summary>
	void CleanupDestroyed();

private:
	/// <summary>
	/// �A�N�e�B�u�ȕ����̃R���N�V����
	/// </summary>
	std::vector<std::weak_ptr<RigidBodyComponent>> m_rigidbodys;
};

