#pragma once
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>

#include<SKFW/Framework/Singleton.hpp>
#include<SKFW/Framework/ObjectPool.hpp>
#include<SKFW/Ecs/GameObject.hpp>

/// <summary>
/// ���C�t�^�C���̎��
/// �Z�������Ԃ�������
/// </summary>
enum class eObjectLivedType
{
	Short,
	Medium,
	Long,
};

class GameObjectManager : public Singleton<GameObjectManager>
{
	friend class Singleton<GameObjectManager>;
	GameObjectManager();

public:
	/// <summary>
	/// �v�[������GameObject�̎擾�����ď��������ڂ����������Ă���Q�Ƃ�Ԃ��B
	/// </summary>
	/// <param name="a_type"></param>
	/// <param name="a_tag"></param>
	/// <returns></returns>
	PoolHandle<GameObject>& Create(eObjectLivedType a_type, const std::string& a_tag);

	/// <summary>
	/// ID����Y������GameObject�̎Q�Ƃ��擾�B
	/// </summary>
	/// <param name="a_id"></param>
	/// <returns></returns>
	GameObject* FindByID(uint32_t a_id);

	/// <summary>
	/// �^�O����Y������GameObject�̎Q�ƒB��Ԃ�
	/// </summary>
	/// <param name="a_tag"></param>
	/// <returns></returns>
	const std::unordered_set<GameObject*>& FindByTag(const std::string& a_tag);

	/// <summary>
	/// �폜�t���O�������Ă���I�u�W�F�N�g���܂Ƃ߂ĕԋp����B
	/// </summary>
	void CleanupDestroyedObjects();

	/// <summary>
	/// ���A�N�e�B�u��GameOBject�̐�
	/// </summary>
	/// <returns></returns>
	int GetActiveCount()const;


private:
	/// <summary>
	/// �e�Ȃǂ̒Z���I�u�W�F�N�g�p�̃v�[��
	/// </summary>
	ObjectPool<GameObject> m_shortLivedPool;

	/// <summary>
	/// �G��A�C�e���Ȃǂ̒Z���ł͂Ȃ����ǃv���C���[�قǒ����ł��Ȃ�����
	/// </summary>
	ObjectPool<GameObject> m_mediumLivedPool;

	/// <summary>
	/// �v���C���[�̓{�X�Ȃǂ̒����I�u�W�F�N�g�p�v�[��
	/// </summary>
	ObjectPool<GameObject> m_longLivedPool;

	/// <summary>
	/// �A�N�e�B�u��GameObject�̃n���h���̃C���X�^���X
	/// </summary>
	std::vector<PoolHandle<GameObject>> m_activeHandles;

	/// <summary>
	/// ID����C���X�^���X�̌����p
	/// </summary>
	std::unordered_map<uint32_t, GameObject*> m_idIndex;

	/// <summary>
	/// �^�O����Y������C���X�^���X�B�̌����p
	/// </summary>
	std::unordered_map<uint32_t, std::unordered_set<GameObject*>> m_tagIndexs;

	/// <summary>
	/// �Z�b�g����ŗL�ԍ���ID
	/// </summary>
	uint32_t m_nextID;
};