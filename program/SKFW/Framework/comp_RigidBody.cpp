#include "comp_RigidBody.h"

#include<algorithm>
#include<cmath>

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
	auto transform = GetGameObject();

	//	�����x = �� /  ����
	m_acceleration = m_force * (1.0f / m_mass);

	//	���x�X�V
	m_velociry += m_acceleration * fixedDt;

	//	��C��R�i�󒆂ƒn��̊���₷���j
	auto dragX = m_isGrounded == true ? m_drag_groundX : m_drag_airX;
	auto fps = 1.0f / fixedDt;
	m_velociry.x *= std::pow(dragX, fixedDt * fps);
	m_velociry.y *= std::pow(m_dragY, fixedDt * fps);

	//	�ʒu�̍X�V

	//	�͂̃��Z�b�g
}
