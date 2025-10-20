#pragma once
#include<SKFW/Ecs/base_Drawable.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Sprite.hpp>

class ImageComponent : public IDrawable
{
public:

	ImageComponent(sf::Texture* a_texture, int a_layer = 0);

	/// <summary>
	/// �摜�̕`��
	/// </summary>
	/// <param name="a_alpha"></param>
	void Draw(sf::RenderWindow& a_window, float a_alpha)override;

	//	�ʒu
	void SetPosition(const sf::Vector2f& a_pos) { m_sprite.setPosition(a_pos); }
	const sf::Vector2f& GetPosition()const noexcept { return m_sprite.getPosition(); };

	//	�X�P�[��
	void SetScale(const sf::Vector2f& a_scale) noexcept { m_sprite.setScale(a_scale); }
	const sf::Vector2f& GetScale()noexcept { return m_sprite.getScale(); }

	//	��]
	void SetRotation(sf::Angle a_angle)noexcept { m_sprite.setRotation(a_angle); }
	const sf::Angle& GetRotation()const noexcept { return m_sprite.getRotation(); }

	//	�F�E�����x
	void SetColor(const sf::Color& a_color)noexcept { m_sprite.setColor(a_color); }
	const sf::Color& GetColor()const { return m_sprite.getColor(); }

	//	�e�N�X�`���̈ꕔ�\��
	void SetTextureRect(const sf::IntRect& a_rect) { m_sprite.setTextureRect(a_rect); }

	//	���_
	void SetOrigin(const sf::Vector2f& a_origin)noexcept { m_sprite.setOrigin(a_origin); }

	/// <summary>
	/// �f�o�b�N����p�ɃX�v���C�g��n���B
	/// </summary>
	/// <returns></returns>
	sf::Sprite& GetSprite() { return m_sprite; }

private:
	/// <summary>
	/// ���\�[�X�Ǘ����炷�łɓǂݍ���ł��������\�[�X���Ǘ�����
	/// </summary>
	sf::Texture* m_texture;

	/// <summary>
	/// �\������X�v���C�g
	/// </summary>
	sf::Sprite m_sprite;

};