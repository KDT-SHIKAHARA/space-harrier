#pragma once

#include<unordered_map>
#include<typeindex>
#include<type_traits>
#include<memory>
#include<vector>
#include<stdexcept>

#include<SKFW/Ecs/base_component.hpp>
#include<SKFW/Framework/ObjectPool.hpp>
#include<SKFW/Ecs/base_Monobehaviour.hpp>

/// <summary>
/// �G���e�B�e�B�P�ʂŊ����ł���悤�Ɏ����̗v�f�͒��Ŏ���
/// </summary>
class GameObject
{
public:

	GameObject()
		:m_tag(0), m_enable(true), m_destory(false), m_id(std::numeric_limits<uint32_t>::max())
	{ 
	}

	virtual ~GameObject()
	{

	}

	/// <summary>
	/// ��Ԃ̏��������s��
	/// </summary>
	void Reset()
	{
		m_tag = 0;
		m_enable = true;
		m_destory = false;
		m_id = -1;
		m_components.clear();
	} 

	/// <summary>
	/// �R���|�[�l���g�̒ǉ�
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<typename T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args);

	/// <summary>
	/// �R���|�[�l���g�̎擾
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>����:�C���X�^���X ���s:nullptr</returns>
	template<typename T>
	std::shared_ptr<T> GetComponent();

	/// <summary>
	/// ���N���X�^�ŃR���|�[�l���g���擾����
	/// </summary>
	/// <typeparam name="BASE"></typeparam>
	/// <returns></returns>
	template<typename BASE>
	std::shared_ptr<BASE> GetComponentAsBase();

	template<typename T>
	[[nodiscard]] bool HasComponent()const;


	//	�A�N�Z�T
	void SetTagID(uint32_t id) { m_tag = id; }
	uint32_t GetTagID() const { return m_tag; }

	void SetEnable(bool enable) { m_enable = enable; }
	bool GetEnable() const { return m_enable; }

	void SetDestroy() { m_destory = true; }
	bool IsDestroy() const { return m_destory; }

	void SetID(uint32_t id) { m_id = id; }
	uint32_t GetID() const { return m_id; }

private:

	/// <summary>
	/// �������Ă���R���|�[�l���g�Q
	/// </summary>
	std::unordered_map<std::type_index, std::shared_ptr<IComponent>> m_components;

	/// <summary>
	/// ���[�U�[�X�N���v�g�̃R���N�V����
	/// </summary>
	std::vector<IMonoBehaviour*> m_monobehaviours;

	/// <summary>
	/// ���ʗp�̌�ID
	/// </summary>
	uint32_t m_id;

	/// <summary>
	/// �^�O�����͕�����ŕR�Â��Ă���ID(TagID)������������Ă���B
	/// </summary>
	uint32_t m_tag;

	/// <summary>
	/// �L���t���O
	/// true: �L��
	/// </summary>
	bool m_enable;

	/// <summary>
	/// �j��t���O
	/// true: �t���[�����Ŕj��
	/// </summary>
	bool m_destory;
};

template<typename T, typename ...Args>
inline std::shared_ptr<T> GameObject::AddComponent(Args && ...args)
{
	auto comp = std::make_shared<T>(std::forward<Args>(args)...);
	comp->SetGameObject(this);
	comp->Initialize();
	m_components[std::type_index(typeid(T))] = comp;

	//	����MonoBehaviour�p���Ȃ烊�X�g�ɒǉ�
	if (auto mb = dynamic_cast<IMonoBehaviour*>(comp.get()))
	{
		m_monobehaviours.push_back(mb);
	}

	return comp;
}

template<typename T>
inline std::shared_ptr<T> GameObject::GetComponent()
{
	auto it = m_components.find(std::type_index(typeid(T)));
	if (it != m_components.end())
	{
		return std::static_pointer_cast<T>(it->second);
	}

	return nullptr;
}

template<typename BASE>
inline std::shared_ptr<BASE> GameObject::GetComponentAsBase()
{
	for (auto& [type, comp] : m_components)
	{
		if(auto casted = std::dynamic_pointer_cast<BASE>(comp))
		{
			return casted;
		}
	}

	return nullptr;
}

template<typename T>
inline bool GameObject::HasComponent() const
{
	auto it = m_components.find(std::type_index(typeid(T)));
	if(it != m_components.end())
	{
		return true;
	}

	return false;
}
