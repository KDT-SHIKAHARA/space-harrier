#pragma once
#include<unordered_map>
#include<vector>
#include<string>
#include<stdexcept>

#include<SKFW/Framework/Singleton.hpp>

/// <summary>
/// �^�O�̕������ID(���l)�������N������B
/// </summary>
class TagManager : public Singleton<TagManager>
{
	friend class Singleton<TagManager>;
	TagManager();
	virtual ~TagManager();
public:
	/// <summary>
	/// �^�O�o�^
	/// ���ɂ���Δԍ���Ԃ�
	/// </summary>
	/// <param name="a_tagName"></param>
	/// <returns></returns>
	uint32_t Register(const std::string& a_tagName);

	/// <summary>
	/// �^�O����ID���擾����
	/// </summary>
	/// <param name="a_tagName"></param>
	/// <returns></returns>
	uint32_t GetTagId(const std::string& a_tagName)const;

	/// <summary>
	/// ID����^�O�̎擾
	/// </summary>
	/// <param name="id"></param>
	/// <returns></returns>
	const std::string& GetTagName(uint32_t a_id) const;

	/// <summary>
	/// �^�O�����݂��Ă��邩�ǂ���
	/// </summary>
	/// <param name="tagName"></param>
	/// <returns></returns>
	bool Exists(const std::string& a_tagName) const;

	/// <summary>
	/// �^�O�̃Z�b�g�Ȃǂ�ImGui�ł������悤��
	/// </summary>
	void DrawImGui();

	/// <summary>
	/// �ۑ�
	/// cereal�g�p
	/// </summary>
	/// <param name="a_filePath"></param>
	void Save(const std::string& a_filePath);

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <param name="a_filePath"></param>
	void Load(const std::string& a_filePath);


private:
	/// <summary>
	/// ���O���琔�l
	/// </summary>
	std::unordered_map<std::string, uint32_t> m_nameToID;

	/// <summary>
	/// ���l���疼�O
	/// </summary>
	std::vector<std::string> m_idToName;

	/// <summary>
	/// �ۑ�����t�H���_�p�X
	/// </summary>
	const std::string FILE_PATH = "bin/config/debug/tags.json";
};