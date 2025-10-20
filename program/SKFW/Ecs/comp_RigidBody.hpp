#pragma once
#include<memory>

#include<SKFW/Ecs/base_component.hpp>
#include<SFML/System/Vector2.hpp>

class RigidBodyComponent : public IComponent , public std::enable_shared_from_this<RigidBodyComponent>
{
public:

	/// <summary>
	/// レジスター登録
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// 外力の加算
	/// </summary>
	/// <param name="a_force"></param>
	void AddForce(const sf::Vector2f& a_force) noexcept;

	/// <summary>
	/// 入力の移動量を加算
	/// </summary>
	/// <param name="a_inputMove"></param>
	void MoveInput(const sf::Vector2f& a_inputMove)noexcept;

	/// <summary>
	/// 再現性のために固定更新
	/// </summary>
	/// <param name="dt"></param>
	void FixedUpdate(float fixedDt)override;

private:
	/// <summary>
	/// 移動量
	/// </summary>
	sf::Vector2f m_velociry;

	/// <summary>
	/// 加速度
	/// </summary>
	sf::Vector2f m_acceleration;

	/// <summary>
	/// 外力
	/// </summary>
	sf::Vector2f m_force;

	/// <summary>
	/// 質量
	/// </summary>
	float m_mass = 1.0f;

	/// <summary>
	/// 重力加速度
	/// </summary>
	float m_gravity = 980.0f;

	/// <summary>
	/// 空気抵抗
	/// </summary>
	float m_drag_groundX = 0.98f;
	float m_drag_airX = 0.85f; 
	float m_dragY = 0.99f;

	/// <summary>
	/// 移動入力時に加える力
	/// </summary>
	float m_moveForce = 4000.0f;

	/// <summary>
	/// 設置判定
	/// </summary>
	bool m_isGrounded = false;
};