#include<iostream>
#include<fstream>
#include<sstream>
#include<filesystem>

#include<imgui.h>
#include<SKFW/Ecs/TagManager.hpp>
#include<cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/unordered_map.hpp>

TagManager::TagManager()
{
	this->Load(FILE_PATH);
}

TagManager::~TagManager()
{
	this->Save(FILE_PATH);
}

/// /// <summary>
/// �^�O�o�^
/// ���ɂ���Δԍ���Ԃ�
/// </summary>
/// <param name="a_tagName"></param>
/// <returns></returns>
uint32_t TagManager::Register(const std::string& a_tagName)
{
	//	����
	auto it = m_nameToID.find(a_tagName);
	if (it != m_nameToID.end())
	{
		return it->second;
	}

	//	�V������������
	uint32_t newID = static_cast<uint32_t>(m_idToName.size());
	m_nameToID[a_tagName] = newID;
	m_idToName.push_back(a_tagName);
	return newID;
}

/// <summary>
/// �^�O����ID���擾����
/// </summary>
/// <param name="a_tagName"></param>
/// <returns></returns>
uint32_t TagManager::GetTagId(const std::string& a_tagName) const
{
	auto it = m_nameToID.find(a_tagName);
	if (it == m_nameToID.end())
	{
		//	�Ȃ��������̏����͂ǂ����邩��ŕύX���悤
		std::cerr << a_tagName << "�����݂��܂���" << std::endl;
		return -1;
	}
	return it->second;
}

/// <summary>
/// ID����^�O�̎擾
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
const std::string& TagManager::GetTagName(uint32_t a_id) const
{
	if (a_id >= m_idToName.size())
	{
		//	�ő吔���z���Ă�����̏�������Œǉ�
		std::cerr << a_id << "�͓o�^����Ă���ID���z���Ă��܂�" << std::endl;
		return "";
	}
	return m_idToName[a_id];
}

/// <summary>
/// �^�O�����݂��Ă��邩�ǂ���
/// </summary>
/// <param name="tagName"></param>
/// <returns></returns>
bool TagManager::Exists(const std::string& a_tagName) const
{
	return m_nameToID.contains(a_tagName);
}

/// <summary>
/// �^�O�̃Z�b�g�Ȃǂ�ImGui�ł������悤��
/// </summary>
void TagManager::DrawImGui()
{
	ImGui::Text("Registered Tags: ");
	ImGui::Separator();

	//	�ۑ��{�^��
	if (ImGui::Button("Save"))
	{
		this->Save(FILE_PATH);
	}

	ImGui::Separator();

	//	�����^�O�̈ꗗ
	for (uint32_t id = 0; id < m_idToName.size();)
	{
		ImGui::PushID(static_cast<int>(id));

		char buffer[64];
		std::snprintf(buffer, sizeof(buffer), "%s", m_idToName[id].c_str());

		//	���O�ҏW
		if (ImGui::InputText("##TagName", buffer, IM_ARRAYSIZE(buffer)))
		{
			//	�ύX��̖��O
			std::string newName(buffer);

			//	���O���ύX���ꂽ�ꍇ�d���`�F�b�N�����čX�V
			if (newName != m_idToName[id] && !Exists(newName))
			{
				//	�Â����O�̍폜
				m_nameToID.erase(m_idToName[id]);
				//	�V�������O��o�^
				m_nameToID[newName] = id;
				m_idToName[id] = std::move(newName);
			}	// if

		}	//	if

		ImGui::SameLine();
		ImGui::Text("ID: %u", id);

		//	�폜����
		ImGui::SameLine();
		if (ImGui::Button("Delete"))
		{
			//	�폜����
			 // �폜����
			m_nameToID.erase(m_idToName[id]);
			m_idToName.erase(m_idToName.begin() + id);
			// ID�Ċ��蓖��
			for (uint32_t newId = 0; newId < m_idToName.size(); ++newId)
				m_nameToID[m_idToName[newId]] = newId;

			ImGui::PopID();
			continue; // �폜�����̂Ŏ���ID�ɐi��
		}


		ImGui::PopID();
		id++;

	}	// for

	ImGui::Separator();

	//	�V�K�ǉ�
	static char newTagName[64] = "";
	ImGui::InputText("New Tag", newTagName, IM_ARRAYSIZE(newTagName));
	ImGui::SameLine();
	if (ImGui::Button("Add Tag"))
	{
		//	�����������ĂĊ����̃^�O�ł͖������
		if (strlen(newTagName) > 0 && !Exists(newTagName))
		{
			this->Register(newTagName);
			//	���s�q
			newTagName[0] = '\0';
		}
	}
}

/// <summary>
/// �ۑ�
/// cereal�g�p
/// </summary>
/// <param name="a_filePath"></param>
void TagManager::Save(const std::string& a_filePath)
{
	// �f�B���N�g����������
	std::filesystem::create_directories(std::filesystem::path(a_filePath).parent_path());

	std::ofstream os(a_filePath);
	if (!os.is_open())
	{
		std::cerr << "TagManager: �t�@�C�����J���܂���: " << a_filePath << std::endl;
		return;
	}

	cereal::JSONOutputArchive archive(os);
	archive(cereal::make_nvp("name_to_id", m_nameToID),
		cereal::make_nvp("id_to_name", m_idToName));
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <param name="a_filePath"></param>
void TagManager::Load(const std::string& a_filePath)
{
	if (!std::filesystem::exists(a_filePath))
	{
		// �t�@�C�������݂��Ȃ� �� �f�t�H���g�쐬
		m_nameToID.clear();
		m_idToName.clear();
		Register("Default");
		Save(a_filePath);
		return;
	}

	std::ifstream is(a_filePath);
	if (!is.is_open())
	{
		std::cerr << "TagManager: �ǂݍ��݂Ɏ��s���܂���: " << a_filePath << std::endl;
		return;
	}

	cereal::JSONInputArchive archive(is);
	archive(cereal::make_nvp("name_to_id", m_nameToID),
		cereal::make_nvp("id_to_name", m_idToName));
}
