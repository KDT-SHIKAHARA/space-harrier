#pragma once

#include<memory>
#include<vector>

#include<SKFW/Ecs/base_Drawable.hpp>
#include<SKFW/Framework/Singleton.hpp>
#include<SFML/Graphics/RenderWindow.hpp>

/// <summary>
/// �`��R���|�[�l���g�̕`�揈����S��
/// </summary>
class RenderSystem : public Singleton<RenderSystem>
{
	friend class Singleton<RenderSystem>;
	RenderSystem() = default;
	virtual ~RenderSystem() = default;
public:

	/// <summary>
	/// �`��R���|�[�l���g�̎Q�Ɗi�[
	/// </summary>
	/// <param name="a_render"></param>
	void Register(std::shared_ptr<IDrawable> a_render);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Render(sf::RenderWindow& a_window,float a_alpha);

	/// <summary>
	/// �t���[�����ɍ폜����
	/// </summary>
	void ProcessExpired();

	/// <summary>
	///	��Ԃ̃��Z�b�g
	/// </summary>
	void Clear();

private:
	/// <summary>
	/// �`�悷��R���|�[�l���g�̎Q�ƃR���N�V����
	/// </summary>
	std::vector<std::vector<std::weak_ptr<IDrawable>>> m_renders;

};