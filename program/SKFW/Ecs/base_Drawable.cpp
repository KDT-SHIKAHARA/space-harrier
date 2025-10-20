#include<SKFW/Ecs/base_Drawable.hpp>
#include<SKFW/Ecs/system_Render.hpp>

IDrawable::IDrawable(uint32_t a_layer)
	:m_layer(a_layer), m_isVisible(true)
{
}

IDrawable::~IDrawable()
{
}

/// <summary>
/// �V�X�e���Ɏ��g��o�^
/// </summary>
void IDrawable::Initialize()
{
	//	�`��V�X�e���Ɏ��g��ǉ�
	RenderSystem::Instance().Register(shared_from_this());
}

