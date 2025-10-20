#pragma once
#include<memory>

#include<SKFW/Ecs/base_Monobehaviour.hpp>
#include<SFML/Graphics/RenderWindow.hpp>

/// <summary>
/// �`��\�ȃR���|�[�l���g
/// </summary>
class IDrawable : public IMonoBehaviour,public std::enable_shared_from_this<IDrawable>
{
public:
	IDrawable(uint32_t a_layer = 0);
	virtual ~IDrawable();

	/// <summary>
	/// �V�X�e���Ɏ��g��o�^
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �`�惁�\�b�h
	/// </summary>
	/// <param name="a_alpha"></param>
	virtual void Draw(sf::RenderWindow& a_window,float a_alpha) = 0;

	//	�A�N�Z�T
	uint32_t GetLayer()const { return m_layer; }
	void SetLayer(uint32_t a_layer) { m_layer = a_layer; }
	bool IsVisible()const noexcept { return m_isVisible; }
	void SetVisible(bool a_isVisible) { m_isVisible = a_isVisible; }

	//	���ʃC���^�[�t�F�[�X
	virtual void Update(float dt) {}
	virtual void FixedUpdate(float fixedDt) {}
	virtual void Reset() {}

protected:
	uint32_t m_layer;
	bool m_isVisible;
};