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
	/// �e�N�X�`���̓ǂݍ���
	/// </summary>
	/// <param name="a_fimename">�t�@�C���p�X</param>
	/// <returns></returns>
	sf::Texture* GetTexture(const std::string& a_fimename);


private:
	/// <summary>
	/// �ۑ����Ă���e�N�X�`���̃��\�[�X�̃R���N�V����
	/// </summary>
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;

};
