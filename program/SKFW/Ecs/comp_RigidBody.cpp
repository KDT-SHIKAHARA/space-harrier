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
/// 外力の加算
/// </summary>
/// <param name="a_force"></param>
void RigidBodyComponent::AddForce(const sf::Vector2f& a_force) noexcept
{
	m_force += a_force;
}

/// <summary>
/// 入力の移動量を加算
/// </summary>
/// <param name="a_inputMove"></param>
void RigidBodyComponent::MoveInput(const sf::Vector2f& a_inputMove) noexcept
{
	sf::Vector2f move = a_inputMove * m_moveForce;
	AddForce(move);
}

/// <summary>
/// 再現性のために固定更新
/// </summary>
/// <param name="dt"></param>
void RigidBodyComponent::FixedUpdate(float fixedDt)
{
	//	座標のコンポーネントの取得
	auto transform = GetGameObject()->GetComponent<TransformComponent>();

	if (transform == nullptr)
	{
		return;
	}

	//	加速度 = 力 /  質量
	m_acceleration = m_force * (1.0f / m_mass);

	//	速度更新
	m_velociry += m_acceleration * fixedDt;


	//	空気抵抗（空中と地上の滑りやすさ）
	auto dragX = m_isGrounded == true ? m_drag_groundX : m_drag_airX;
	auto fps = 1.0f / fixedDt;
	m_velociry.x *= dragX;
	m_velociry.y *= m_dragY;

	//	位置の更新
	transform->Translate(m_velociry * fixedDt);


	//	力のリセット
	//m_force = {0,0};
}
