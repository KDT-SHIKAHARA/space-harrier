#pragma once
#include<SFML/System.hpp>
#include<SKFW/Framework/Singleton.hpp>


class Time : public Singleton<Time>
{
	friend class Singleton<Time>;
public:

	//	������
	void Initialize(float fps = 60.0f) {
		if (fps <= 0.0f) fps = 60.0f; // fallback
		m_clock.restart();
		m_fpsClock.restart();
		m_accumulator = 0.f;
		m_fixedDelta = 1.0f / fps;
		m_deltaTime = 0.0f;
		m_fps = 0.0f;
		m_frameCount = 0;
	}

	void Update()
	{

		//	1�t���[���Ԃ̌o�ߎ���
		double frameTime = m_clock.restart().asSeconds();

		const double MAX_ACCUMULATED_TIME = 0.25;
		m_accumulator = std::min(m_accumulator + frameTime, MAX_ACCUMULATED_TIME);

		static float smoothedDelta = 1.0f / 60.0f; // �����l��60FPS
		const float SMOOTHING_FACTOR = 0.9f;       // 0.0f�ɋ߂��قǗh��ɋ������������x��
		smoothedDelta = smoothedDelta * SMOOTHING_FACTOR + frameTime * (1.0f - SMOOTHING_FACTOR);
		m_deltaTime = smoothedDelta;

		//	FPS����
		m_frameCount++;
		float elapsed = m_fpsClock.getElapsedTime().asSeconds();
		if (elapsed >= 1.0f)
		{
			//	1�t���o�ߌ�̃��Z�b�g����
			m_fps = static_cast<float>(m_frameCount) / elapsed;
			m_frameCount = 0;
			m_fpsClock.restart();
		}
	}

	void UpdateAlpha()
	{
		m_alpha = std::clamp(m_accumulator / m_fixedDelta, 0.0, 1.0);
	}

	/// <summary>
	/// �Œ�X�V���s�����ǂ����̔���
	/// </summary>
	/// <returns></returns>
	bool ShouldFixedUpdate()
	{
		return m_accumulator >= m_fixedDelta;
	}

	/// <summary>
	/// �Œ�X�V�������
	/// </summary>
	void ConsumeFixedDelta()
	{
		m_accumulator -= m_fixedDelta;
	}

	double FixedDelta() const { return m_fixedDelta; }
	double DeltaTime() const { return m_deltaTime; }
	double Alpha() const { 
		return m_alpha; 
	}
	float Fps()const { return m_fps; }

	sf::Clock& GetClock()
	{
		return m_clock;
	}

private:

	/// <summary>
	/// ���t���[���̌o�ߎ���
	/// </summary>
	sf::Clock m_clock;

	/// <summary>
	/// FSP�̑���p
	/// </summary>
	sf::Clock m_fpsClock;

	/// <summary>
	/// �Œ�t���[���̃X�e�b�v���f�p�b��
	/// </summary>
	double m_fixedDelta;

	/// <summary>
	/// 1�t���[���Ԃ̌o�ߎ���
	/// </summary>
	double m_deltaTime;

	/// <summary>
	/// ���ۂ̃t���[�����[�g
	/// </summary>
	float m_fps;

	/// <summary>
	/// �t���[�����̃J�E���g
	/// </summary>
	unsigned int m_frameCount;

	/// <summary>
	/// �o�ߎ��Ԓ~�ϗp
	/// </summary>
	double m_accumulator;

	/// <summary>
	/// �`��⊮�p
	/// </summary>
	double m_alpha = 0.0f;
};
