#pragma once

#include<memory>
#include<string>
#include<unordered_map>

#include<SFML/Graphics/Texture.hpp>
#include<SKFW/Framework/Singleton.hpp>

#ifndef DEFAULT_TEXTURE_PATH
#define DEFAULT_TEXTURE_PATH "assets/default/default.jpg"
#endif // !DEFAULT_TEXTURE_PATH


class TextureResourceManager : public Singleton<TextureResourceManager>
{
	friend class Singleton<TextureResourceManager>;
	TextureResourceManager();
	virtual ~TextureResourceManager() = default;

public:

	/// <summary>
	/// テクスチャの読み込み
	/// </summary>
	/// <param name="a_fimename">ファイルパス</param>
	/// <returns></returns>
	sf::Texture* GetTexture(const std::string& a_fimename);


private:
	/// <summary>
	/// 保存しているテクスチャのリソースのコレクション
	/// </summary>
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;

};
