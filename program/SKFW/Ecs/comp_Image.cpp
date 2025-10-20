#include<SKFW/Ecs/comp_Image.hpp>
#include<SKFW/Ecs/GameObject.hpp>
#include<SKFW/Ecs/comp_Transform.hpp>

ImageComponent::ImageComponent(sf::Texture* a_texture, int a_layer)
	:IDrawable(a_layer), m_texture(a_texture), m_sprite(*m_texture)
{

}

/// <summary>
/// �摜�̕`��
/// </summary>
/// <param name="a_alpha"></param>
void ImageComponent::Draw(sf::RenderWindow& a_window, float a_alpha)
{
	//	���W�n���擾���Ĕ��f
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	if (transform != nullptr)
	{
		auto trans = transform->GetInterpolatedPosition(a_alpha);
		m_sprite.setPosition(trans);
		m_sprite.setRotation(transform->GetInterpolatedAngle(a_alpha));
		m_sprite.setScale(transform->GetScale());
	}

	//	�\��
	a_window.draw(m_sprite);
}