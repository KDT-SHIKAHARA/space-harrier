#include<SKFW/Framework/TextureResource.hpp>

/// <summary>
/// �f�t�H���g�̃e�N�X�`���̓ǂݍ���
/// </summary>
TextureResourceManager::TextureResourceManager()
{
	this->GetTexture(DEFAULT_TEXTURE_PATH);
}

/// <summary>
/// �e�N�X�`���̓ǂݍ���
/// </summary>
/// <param name="a_fimename">�t�@�C���p�X</param>
/// <returns></returns>
sf::Texture* TextureResourceManager::GetTexture(const std::string& a_fimename)
{
    //  ����ΕԂ�
    auto it = m_textures.find(a_fimename);
    if (it != m_textures.end())
    {
        return it->second.get();
    }

    //  �Ȃ���ΐ�������B
    auto texture = std::make_unique<sf::Texture>();

    //  �ǂݍ���
    auto result = texture->loadFromFile(a_fimename);
    assert(result == true);

    //  �|�C���^�̎擾
    auto ptr = texture.get();

    //  Resource�̕ۊ�
    m_textures[a_fimename] = std::move(texture);

    return ptr;

}
