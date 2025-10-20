#pragma once
#include<SKFW/Ecs/base_component.hpp>
#include<SFML/System/Vector2.hpp>
#include<SFML/System/Angle.hpp>

class TransformComponent : public IComponent, public std::enable_shared_from_this<TransformComponent>
{
public:
    /// <summary>
    /// ���W�
    /// </summary>
    enum class ePivot
    {
        TopLeft,
        Center,
    };

    void Reset() override
    {
        m_currentPosition = sf::Vector2f(0.f, 0.f);
        m_previousPosition = sf::Vector2f(0.f, 0.f);
        m_currentAngle = sf::Angle::Zero;
        m_previousAngle = sf::Angle::Zero;
        m_currentScale = sf::Vector2f(1.f, 1.f);
        m_previousScale = sf::Vector2f(1.f, 1.f);
		m_gameObject = nullptr;
        m_isDestory = false;
	}

    /// <summary>
    /// ������
    /// </summary>
    TransformComponent();

    /// <summary>
    /// 
    /// </summary>
    void Initialize()override;

    /// <summary>
    /// �O�̏�Ԃ�ۑ�����ˁB
    /// �X�V�����̑O�ɌĂ�
    /// </summary>
    void SavePrevious()
    {
        m_previousPosition = m_currentPosition;
        m_previousAngle = m_currentAngle;
        m_previousScale = m_currentScale;
    }

    // �ʒu����
    void SetPosition(const sf::Vector2f& pos) {
        m_currentPosition = pos; 
        //m_previousPosition = pos;
    }
    const sf::Vector2f& GetPosition() const { return m_currentPosition; }

    // ��]����
    void SetAngle(const sf::Angle& angle) { m_currentAngle = angle; }
    const sf::Angle& GetAngle() const { return m_currentAngle; }

    // �X�P�[������
    void SetScale(const sf::Vector2f& scale) { m_currentScale = scale; }
    const sf::Vector2f& GetScale() const { return m_currentScale; }

    //  ����
    void Translate(const sf::Vector2f& delta)
    {
        m_currentPosition += delta;
	}

    void Rotate(const sf::Angle& delta)
    {
        m_currentAngle += delta;
	}

    //  ���W�
	ePivot GetPivot()const noexcept 
    {
        return m_pivot; 
    }
    void SetPivot(ePivot pivot) noexcept 
    { 
        m_pivot = pivot; 
	}

    // �`��p���
    sf::Vector2f GetInterpolatedPosition(float alpha) const
    {
        return m_previousPosition * (1.0f - alpha) + m_currentPosition * alpha;
    }

    sf::Angle GetInterpolatedAngle(float alpha) const
    {
        return m_previousAngle * (1.0f - alpha) + m_currentAngle * alpha;
    }

    sf::Vector2f GetInterpolatedScale(float alpha) const
    {
        return m_previousScale * (1.0f - alpha) + m_currentScale * alpha;
    }

private:

    //  ���W
    sf::Vector2f m_currentPosition;
    sf::Vector2f m_previousPosition;

    //  ��]
    sf::Angle m_currentAngle;
    sf::Angle m_previousAngle;

	//  �X�P�[��
    sf::Vector2f m_currentScale;
    sf::Vector2f m_previousScale;

    //  ���W�
	ePivot m_pivot{ ePivot::TopLeft };
};