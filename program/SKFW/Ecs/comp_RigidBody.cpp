#include<SKFW/Ecs/comp_RigidBody.hpp>
#include<SKFW/Ecs/GameObject.hpp>
#include<SKFW/Ecs/comp_Transform.hpp>

#include<SKFW/Ecs/system_RigidBody.hpp>

#include<algorithm>
#include<cmath>

void RigidBodyComponent::Initialize()
{
	RigidBodySystem::Instance().Register(shared_from_this());
}

/// <summary>
/// �O�͂̉��Z
/// </summary>
/// <param name="a_force"></param>
void RigidBodyComponent::AddForce(const sf::Vector2f& a_force) noexcept
{
	m_force += a_force;
}

/// <summary>
/// ���͂̈ړ��ʂ����Z
/// </summary>
/// <param name="a_inputMove"></param>
void RigidBodyComponent::MoveInput(const sf::Vector2f& a_inputMove) noexcept
{
	sf::Vector2f move = a_inputMove * m_moveForce;
	AddForce(move);
}

/// <summary>
/// �Č����̂��߂ɌŒ�X�V
/// </summary>
/// <param name="dt"></param>
void RigidBodyComponent::FixedUpdate(float fixedDt)
{
	//	���W�̃R���|�[�l���g�̎擾
	auto transform = GetGameObject()->GetComponent<TransformComponent>();

	if (transform == nullptr)
	{
		return;
	}

	//	�����x = �� /  ����
	m_acceleration = m_force * (1.0f / m_mass);

	//	���x�X�V
	m_velociry += m_acceleration * fixedDt;


	//	��C��R�i�󒆂ƒn��̊���₷���j
	auto dragX = m_isGrounded == true ? m_drag_groundX : m_drag_airX;
	auto fps = 1.0f / fixedDt;
	m_velociry.x *= dragX;
	m_velociry.y *= m_dragY;

	//	�ʒu�̍X�V
	transform->Translate(m_velociry * fixedDt);


	//	�͂̃��Z�b�g
	//m_force = {0,0};
}
