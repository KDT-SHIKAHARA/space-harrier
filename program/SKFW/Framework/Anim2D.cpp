#include<SKFW/Framework/TextureResource.hpp>
#include<SKFW/Framework/Anim2D.hpp>
#include<SKFW/Debug/Logger.hpp>

#include<cassert>

FrameAnimation2D::FrameAnimation2D(const std::string& a_filepath, int a_firstFrame, int a_lastFrame, IAnimation2D::eMode a_mode,float a_durationPerFrame)
	:IAnimation2D(a_mode, a_durationPerFrame)
	,m_firstFrame(a_firstFrame)
	, m_lastFrame(a_lastFrame)
	, m_currentFrame(a_firstFrame)
{
	// �e�N�X�`���Q�̎擾
	for (int i = a_firstFrame; i <= a_lastFrame; i++)
	{
		std::string filepath = a_filepath + std::to_string(i) + ".png";
		auto texture = TextureResourceManager::Instance().GetTexture(filepath);
		
		//	���s����
		if (texture == nullptr)
		{
			Logger::Info("2D�A�j���[�V�����p�e�N�X�`���Ǎ����s:", filepath.c_str());
		}
		assert(texture != nullptr && "2D�A�j���[�V�����Ńe�N�X�`���̓Ǎ��Ɏ��s");

		m_textures.push_back(texture);
	}
}

/// <summary>
/// �A�j���[�V�����̍X�V����
/// </summary>
/// <param name="a_fixedDt"></param>
void FrameAnimation2D::Update(double a_fixedDt)
{
	// �Đ����Ă��Ȃ��A�܂��̓e�N�X�`�����Ȃ��ꍇ�͏������Ȃ�
	if(m_isPlaying == Flag::Off || m_textures.empty())
	{ 
		return;
	}

	//	�e�N�X�`���ύX�t���O�̐ݒ�
	m_hasChanged.Set(Flag::Off);

	//	�o�ߎ��Ԃ̍X�V
	m_elapsedTime += a_fixedDt;

	while (m_elapsedTime >= m_durationPerFrame)
	{
		m_elapsedTime -= m_durationPerFrame;
		stepFrame();
		if(m_isPlaying == Flag::Off)
		{
			break;
		}
	}
}

/// <summary>
/// �؂�ւ����̃��Z�b�g����
/// </summary>
void FrameAnimation2D::Reset()
{
	m_elapsedTime = 0;
	m_currentFrame = 0;
	m_isPlaying.Set(Flag::On);
	m_isFinished.Set(Flag::Off);
	m_hasChanged.Set(Flag::Off);
}

/// <summary>
/// �e�N�X�`���̎擾
/// </summary>
/// <returns></returns>
const sf::Texture* FrameAnimation2D::GetTexture() const
{
	if (m_textures.empty())
	{
		Logger::Warn("�e�N�X�`���擾���Ƀe�N�X�`�������݂��܂���ł����B");
		return nullptr;
	}

	return m_textures[m_currentFrame];
}

/// <summary>
/// �A�j���[�V�����̃t���[����i�߂�
/// </summary>
void FrameAnimation2D::stepFrame()
{

	switch (m_playMode)
	{
	//	�P������
	//	�������͔͈͊O�ɂȂ�Ƃ��̂܂܂̂Ȃ̂ő��₷�O�ɔ��������
	case IAnimation2D::eMode::Once:
		//	���̃A�j���t���[�����T�C�Y���z���Ă�Ȃ�I��
		if (m_currentFrame + 1 >= m_textures.size())
		{
			m_isPlaying.Set(Flag::Off);
			m_isFinished.Set(Flag::On);
		}
		//	�z���ĂȂ��Ȃ�i�߂�
		else
		{
			m_currentFrame++;
			m_hasChanged.Set(Flag::On);
		}

		break;
	//	���[�v����
	//	��������Clamp���������Ă���̂ŏ�ɔ͈͓��Ȃ̂ŉ��Z���ɂ��܂�
	case IAnimation2D::eMode::Loop:
		m_currentFrame++;
		m_currentFrame = m_currentFrame % m_textures.size();	
		m_hasChanged.Set(Flag::On);
		break;
	}

}
