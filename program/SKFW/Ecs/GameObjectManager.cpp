#include<cassert>

#include<SKFW/Ecs/GameObjectManager.hpp>
#include<SKFW/Ecs/TagManager.hpp>

GameObjectManager::GameObjectManager()
    :m_shortLivedPool(100,true)
    , m_mediumLivedPool(50,true)
    , m_longLivedPool(10,true)
    , m_nextID(0)
{

}

/// <summary>
/// �v�[������GameObject�̎擾�����ď��������ڂ����������Ă���Q�Ƃ�Ԃ��B
/// </summary>
/// <param name="a_type"></param>
/// <param name="a_tag"></param>
/// <returns>�Q��</returns>
PoolHandle<GameObject>& GameObjectManager::Create(eObjectLivedType a_type, const std::string& a_tag)
{

    PoolHandle<GameObject> handle;

    //  �^�C�v���Ƃ̏�����ς���
    switch (a_type)
    {
    case eObjectLivedType::Short:
        handle = m_shortLivedPool.Acquire();
        break;
    case eObjectLivedType::Medium:
        handle = m_mediumLivedPool.Acquire();
        break;
    case eObjectLivedType::Long:
        handle = m_longLivedPool.Acquire();
        break;
    }



    //  �^�O�擾
    auto tagID = TagManager::Instance().GetTagId(a_tag);
    assert(tagID != -1);

    //  �Q�Ɨp�|�C���^�擾
    //  ������
    GameObject* obj = handle.GetObj();
    obj->SetID(m_nextID);
    obj->SetTagID(tagID);

    //  �n���h���̕ێ�
    m_activeHandles.push_back(std::move(handle));

    //  �����p�ɒǉ�
    m_idIndex.insert({m_nextID,obj});
    m_tagIndexs[tagID].insert(obj);

    //  �ԍ��̃C���N�������g
    m_nextID++;

    //  �Ō�ɒǉ������n���h���̎Q�Ƃ�Ԃ��B
    //  �ǐ��̂��߂ɂ�������󂯂Ă���Ԃ��ˁB���ӂ��Ă�H
    auto& lastHandle = m_activeHandles.back();
    return lastHandle;
}

/// <summary>
/// ID����Y������GameObject�̎Q�Ƃ��擾�B
/// </summary>
/// <param name="a_id"></param>
/// <returns></returns>
GameObject* GameObjectManager::FindByID(uint32_t a_id)
{
    auto it = m_idIndex.find(a_id);
    if (it != m_idIndex.end())
    {
        return it->second;
    }

    return nullptr;
}

/// <summary>
/// �^�O����Y������GameObject�̎Q�ƒB��Ԃ�
/// </summary>
/// <param name="a_tag"></param>
/// <returns></returns>
const std::unordered_set<GameObject*>& GameObjectManager::FindByTag(const std::string& a_tag)
{
    // ��̃Z�b�g��Ԃ�
    static const std::unordered_set<GameObject*> emptySet;

    //  �^�O�����݂��邩���肵�đ��݂��Ă�����ID��Ԃ�
    auto tag_id = TagManager::Instance().GetTagId(a_tag);
    if (tag_id == -1)
    {
        return emptySet;
    }

    //  �^�O���猟��
    auto it = m_tagIndexs.find(tag_id);
    if (it != m_tagIndexs.end())
    {
        return it->second;
    }

    return emptySet;
}

/// <summary>
/// �폜�t���O�������Ă���I�u�W�F�N�g���܂Ƃ߂ĕԋp����B
/// </summary>
void GameObjectManager::CleanupDestroyedObjects()
{
    std::erase_if(m_activeHandles,
        [this](PoolHandle<GameObject>& handle)
        {
            GameObject* obj = handle.GetObj();

            // �폜�t���O�������Ă��Ȃ���΂��̂܂�
            if (!obj->IsDestroy()) return false;

            // ID�C���f�b�N�X����폜
            m_idIndex.erase(obj->GetID());

            // �^�O�C���f�b�N�X����폜
            auto tagIt = m_tagIndexs.find(obj->GetTagID());
            if (tagIt != m_tagIndexs.end())
            {
                tagIt->second.erase(obj);

                // �����^�O�ɉ����c���Ă��Ȃ���� map ������폜
                if (tagIt->second.empty())
                    m_tagIndexs.erase(tagIt);
            }

            //  ���g�̏�����
            //  �����ŊǗ����Ă���R���|�[�l���g�̍폜��
            obj->Reset();

            // erase �̑Ώۂɂ���
            return true;
        });
}

/// <summary>
/// ���A�N�e�B�u��GameOBject�̐�
/// </summary>
/// <returns></returns>
int GameObjectManager::GetActiveCount() const
{
    return m_activeHandles.size();
}

