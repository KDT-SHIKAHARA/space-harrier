#pragma once

#include<memory>
#include<vector>

#include<SKFW/Ecs/base_Drawable.hpp>
#include<SKFW/Framework/Singleton.hpp>
#include<SFML/Graphics/RenderWindow.hpp>

/// <summary>
/// 描画コンポーネントの描画処理を担当
/// </summary>
class RenderSystem : public Singleton<RenderSystem>
{
	friend class Singleton<RenderSystem>;
	RenderSystem() = default;
	virtual ~RenderSystem() = default;
public:

	/// <summary>
	/// 描画コンポーネントの参照格納
	/// </summary>
	/// <param name="a_render"></param>
	void Register(std::shared_ptr<IDrawable> a_render);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render(sf::RenderWindow& a_window,float a_alpha);

	/// <summary>
	/// フレーム末に削除処理
	/// </summary>
	void ProcessExpired();

	/// <summary>
	///	状態のリセット
	/// </summary>
	void Clear();

private:
	/// <summary>
	/// 描画するコンポーネントの参照コレクション
	/// </summary>
	std::vector<std::vector<std::weak_ptr<IDrawable>>> m_renders;

};