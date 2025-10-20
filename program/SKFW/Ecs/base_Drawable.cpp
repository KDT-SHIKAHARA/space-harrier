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
/// システムに自身を登録
/// </summary>
void IDrawable::Initialize()
{
	//	描画システムに自身を追加
	RenderSystem::Instance().Register(shared_from_this());
}

