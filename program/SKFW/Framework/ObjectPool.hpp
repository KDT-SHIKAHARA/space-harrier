#pragma once
#include<stack>
#include<vector>
#include<stdexcept>
#include<memory>
#include<algorithm>

//	����̓��C���X���b�h���炵���Ă΂Ȃ��z��̐݌v�ɂȂ��Ă��܂��B
//	�����ʃX���b�h������Ăԉ\��������̂Ȃ�X���b�h�̌Œ��std::mutex�ōs����Bby 2025/10/7 ����

template<typename T>
class PoolHandle;


//	�v�[���N���X
//	�e���v���[�g�^�̃n���h���̃C���X�^���X�Ǘ�
//	N�̃C���X�^���X���ŏ��ɐ������đS�̃��X�g�Ɩ��g�p���X�g�ɕ����ĕێ����A�擾�ƊǗ�������
template<typename T>
class ObjectPool {
	friend class PoolHandle<T>;
public:
	//	�w�萔����
	explicit ObjectPool(size_t capacity, bool allowDynamic = true)
		:m_allowDynamic(allowDynamic), m_initializeCapaciry(capacity)
	{
		m_objects.reserve(capacity);
		for (size_t i = 0; i < capacity; i++) {
			m_objects.emplace_back(std::make_unique<T>());
			m_free.push(m_objects.back().get());
		}
	}

	/// <summary>
	/// �Ǘ����Ă���C���X�^���X�̖��g�p���X�g����Q�Ɨp�̃|�C���^�Ƃ��̃v�[���ɕԂ��Ă���p�̎��|�C���^���܂Ƃ߂��N���X�𐶐�����B
	/// </summary>
	/// <returns></returns>
	PoolHandle<T> Acquire()
	{
		if (m_free.empty())
		{
			if (m_allowDynamic == true)
			{
				ExpandPool();
			}
			else
			{
				throw std::runtime_error("object pool is empty (dynamic = false)");		//	�擾�s�̏ꍇ
			}
		}
		T* obj = m_free.top();										//	���ɂ���I�u�W�F�N�g���擾
		m_free.pop();												//	�X�^�b�N����폜�i���p�\�g���珜�O�j
		return PoolHandle<T>(obj, this);							//	�C���X�^���X�쐬
	}

private:
	/// <summary>
	/// �n���h�����疢�g�p���X�g�ɕԋp
	/// </summary>
	/// <param name="obj"></param>
	void Release(T* obj)
	{
		//	�}���`�X���b�h�Ή��Ȃ炱���ŌŒ�
		m_free.push(obj);
	}

	/// <summary>
	/// �v�[���T�C�Y���z���ăn���h���̎擾����Ƃ��Ɋ����T�C�Y�{�����̃T�C�Y�ɕύX����B
	/// </summary>
	void ExpandPool()
	{
		//	�ǉ���������T�C�Y�̔����̎擾
		size_t expandCount = std::max<size_t>(1, m_objects.size() / 2);
		m_objects.reserve(m_objects.size() + expandCount);
		for (size_t i = 0; i < expandCount; i++)
		{
			m_objects.emplace_back(std::make_unique<T>());
			m_free.push(m_objects.back().get());
		}
	}


	std::vector<std::unique_ptr<T>> m_objects;	//	T�^�̃C���X�^���X�̃R���N�V����
	std::stack<T*> m_free;	//	���g�p��T�^�̎Q�Ƃ̃R���N�V����
	size_t m_initializeCapaciry = 0;	//	���������̃T�C�Y
	bool m_allowDynamic = true;			//	���I�g�����\���ǂ����̔���

};

//	�n���h���N���X
//	�e���v���[�g�^�̎Q�Ƃƃv�[���̎Q�Ƃ����B
//	�f�X�g���N�^�Ŏ����ԋp�@�\��S���B
template<typename T>
class PoolHandle {
	friend class ObjectPool<T>;

	//	pool���炵���ĂׂȂ�
	PoolHandle(T* obj, ObjectPool<T>* pool)
		: obj_(obj), pool_(pool) {
	}



public:
	PoolHandle() = default;


	//	�R�s�[�̋֎~
	PoolHandle(const PoolHandle&) = delete;

	//	���[�u�R���X�g���N�^
	PoolHandle(PoolHandle&& other)noexcept
		:obj_(other.obj_), pool_(other.pool_) {
		other.obj_ = nullptr;
		other.pool_ = nullptr;
	}

	// ���[�u������Z�q
	PoolHandle& operator=(PoolHandle&& other) noexcept {
		if (this != &other) {
			// ���g�����łɉ�����ێ����Ă�����ԋp
			if (obj_ && pool_) {
				pool_->Release(obj_);
			}
			obj_ = other.obj_;
			pool_ = other.pool_;
			other.obj_ = nullptr;
			other.pool_ = nullptr;
		}
		return *this;
	}

	//	�����ԋp
	virtual ~PoolHandle() {
		if (obj_ && pool_) {
			pool_->Release(obj_);
			obj_ = nullptr;
			pool_ = nullptr;
		}
	}

	//	�A�N�Z�X���Z�q
	T* operator->() { return obj_; }
	T& operator*() { return *obj_; }
	const T& operator*() const { return *obj_; }
	const T* operator->() const { return obj_; }

	// �L�����`�F�b�N
	bool IsValid() const { return obj_ != nullptr; }

	//	�����I�Ɏ擾
	T* GetObj()const { return obj_; }

private:
	T* obj_;	//	T�^�N���X�̎Q�Ɓi�|�C���^�j
	ObjectPool<T>* pool_;	//	�ԋp��̎Q�Ɓi�|�C���^�j

};

