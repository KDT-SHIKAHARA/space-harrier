#pragma once
#include<memory>
#include <type_traits>


class GameObject;
class IComponent 
{
public:
	virtual ~IComponent() = default;
	virtual void Initialize(){}
	virtual void Update(float dt){}
	virtual void FixedUpdate(float fixedDt){}
	virtual void Reset(){}

	/// <summary>
	/// �A�^�b�`���Ă���I�u�W�F�N�g�ւ̎Q�Ƃ��擾
	/// </summary>
	/// <returns></returns>
	GameObject* GetGameObject() const noexcept
	{ 
		return m_gameObject;
	}
	
	/// <summary>
	/// �A�^�b�`���Ă���I�u�W�F�N�g�̎Q�Ƃ��Z�b�g
	/// </summary>
	/// <param name="a_gameObject"></param>
	void SetGameObject(GameObject* a_gameObject) noexcept
	{
		m_gameObject = a_gameObject;
	}

	//	�A�N�Z�T
	bool GetIsDestroy()const noexcept { return m_isDestory; }
	void Destory()noexcept { m_isDestory = true; }

protected:
	GameObject* m_gameObject;
	bool m_isDestory = false;
};

/// <summary>
/// ���O�ɃR���|�[�l���g���p�����Ă��Ȃ��Ɠn���Ȃ��悤�ɂ��Ă���
/// </summary>
template<typename T>
concept ComponentType = std::is_base_of_v<IComponent, T>;