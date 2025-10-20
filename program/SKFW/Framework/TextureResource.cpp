#include<SKFW/Framework/TextureResource.hpp>

/// <summary>
/// デフォルトのテクスチャの読み込み
/// </summary>
TextureResourceManager::TextureResourceManager()
{
	this->GetTexture(DEFAULT_TEXTURE_PATH);
}

/// <summary>
/// テクスチャの読み込み
/// </summary>
/// <param name="a_fimename">ファイルパス</param>
/// <returns></returns>
sf::Texture* TextureResourceManager::GetTexture(const std::string& a_fimename)
{
    //  あれば返す
    auto it = m_textures.find(a_fimename);
    if (it != m_textures.end())
    {
        return it->second.get();
    }

    //  なければ生成する。
    auto texture = std::make_unique<sf::Texture>();

    //  読み込み
    auto result = texture->loadFromFile(a_fimename);
    assert(result == true);

    //  ポインタの取得
    auto ptr = texture.get();

    //  Resourceの保管
    m_textures[a_fimename] = std::move(texture);

    return ptr;

}
