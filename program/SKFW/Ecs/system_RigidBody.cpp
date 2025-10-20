#include "system_RigidBody.hpp"

/// <summary>
///	�A�N�e�B�u�A���X�g�ɒǉ�
/// </summary>
/// <param name="a_rigidbody"></param>
void RigidBodySystem::Register(std::shared_ptr<RigidBodyComponent> a_rigidbody)
{
	if (a_rigidbody != nullptr)
	{
		m_rigidbodys.push_back(a_rigidbody);
	}
}

/// <summary>
/// �Œ�X�V���Ăяo��
/// </summary>
/// <param name="fixedDt"></param>
void RigidBodySystem::FixedUpdate(float fixedDt)
{
	for (auto& weak_rigid : m_rigidbodys) {
		if (auto shared_rigid = weak_rigid.lock())
		{
			shared_rigid->FixedUpdate(fixedDt);
		}
	}
}

/// <summary>
/// �t���[�����ɎQ�Ɛ؂���A�N�e�B�u���X�g����폜����
/// </summary>
void RigidBodySystem::CleanupDestroyed()
{
	m_rigidbodys.erase(
		std::remove_if(
			m_rigidbodys.begin(),
			m_rigidbodys.end(),
			[](const std::weak_ptr<RigidBodyComponent>& a_weakrigid)
			{
				return a_weakrigid.expired();
			}),
			m_rigidbodys.end());
}
