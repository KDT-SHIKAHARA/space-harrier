#pragma once
#include<memory>

#include<SKFW/Ecs/base_component.hpp>
#include<SFML/System/Vector2.hpp>

class RigidBodyComponent : public IComponent , public std::enable_shared_from_this<RigidBodyComponent>
{
public:

	/// <summary>
	/// ���W�X�^�[�o�^
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �O�͂̉��Z
	/// </summary>
	/// <param name="a_force"></param>
	void AddForce(const sf::Vector2f& a_force) noexcept;

	/// <summary>
	/// ���͂̈ړ��ʂ����Z
	/// </summary>
	/// <param name="a_inputMove"></param>
	void MoveInput(const sf::Vector2f& a_inputMove)noexcept;

	/// <summary>
	/// �Č����̂��߂ɌŒ�X�V
	/// </summary>
	/// <param name="dt"></param>
	void FixedUpdate(float fixedDt)override;

private:
	/// <summary>
	/// �ړ���
	/// </summary>
	sf::Vector2f m_velociry;

	/// <summary>
	/// �����x
	/// </summary>
	sf::Vector2f m_acceleration;

	/// <summary>
	/// �O��
	/// </summary>
	sf::Vector2f m_force;

	/// <summary>
	/// ����
	/// </summary>
	float m_mass = 1.0f;

	/// <summary>
	/// �d�͉����x
	/// </summary>
	float m_gravity = 980.0f;

	/// <summary>
	/// ��C��R
	/// </summary>
	float m_drag_groundX = 0.98f;
	float m_drag_airX = 0.85f; 
	float m_dragY = 0.99f;

	/// <summary>
	/// �ړ����͎��ɉ������
	/// </summary>
	float m_moveForce = 4000.0f;

	/// <summary>
	/// �ݒu����
	/// </summary>
	bool m_isGrounded = false;
};