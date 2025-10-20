#pragma once
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdarg>
#include <mutex>
#include<iostream>

class Logger {
public:
    enum class Level { Info, Warn, Error };

    /// <summary>
    /// ������
    /// ���O�t�@�C���̃N���A
    /// </summary>
    static void Initialize() {
#if _DEBUG
        std::lock_guard<std::mutex> lock(m_mtx);
        std::ofstream ofs("log.txt", std::ios::trunc); // �����Ńt�@�C�����N���A
        ofs << "[" << GetCurrentTimeString() << "] [INFO] ���O�o�͂̏����� .\n";
#endif // _DEBUG
    }

    /// <summary>
	/// �W���̃��O�o��
    /// </summary>
    /// <param name="fmt"></param>
    /// <param name=""></param>
    static void Info(const char* fmt, ...) {
#if _DEBUG
        va_list args;
        va_start(args, fmt);
        Log(Level::Info, fmt, args);
        va_end(args);
#endif // _DEBUG
    }

    /// <summary>
	/// �x�����O�o��
	/// �d��ȃG���[�ł͂Ȃ������ӂ��K�v�ȏꍇ�Ɏg�p
    /// </summary>
    /// <param name="fmt"></param>
    /// <param name=""></param>
    static void Warn(const char* fmt, ...) {
#if _DEBUG
        va_list args;
        va_start(args, fmt);
        Log(Level::Warn, fmt, args);
        va_end(args);
#endif // _DEBUG
    }

    /// <summary>
	/// �d��ȃG���[���O�o��
	/// ���Ƃ������͊܂܂Ȃ����A�����Ή����K�v�ȏꍇ�Ɏg�p
    /// </summary>
    /// <param name="fmt"></param>
    /// <param name=""></param>
    static void Error(const char* fmt, ...) {
#if _DEBUG
        va_list args;
        va_start(args, fmt);
        Log(Level::Error, fmt, args);
        va_end(args);
#endif // _DEBUG
    }

private:
    /// <summary>
	/// ���O�t�@�C���ɏ�������
    /// </summary>
    /// <param name="level"></param>
    /// <param name="fmt"></param>
    /// <param name="args"></param>
    static void Log(Level level, const char* fmt, va_list args) {
#if _DEBUG
        std::lock_guard<std::mutex> lock(m_mtx);

        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), fmt, args);

        std::ofstream logFile(m_logFileName, std::ios::app);
        if (!logFile) return;

        logFile << "[" << GetCurrentTimeString() << "] "
            << "[" << LevelToString(level) << "] "
            << buffer << "\n";

        std::cout << buffer << std::endl;
#endif // _DEBUG
    }

    /// <summary>
	/// ���̎��Ԃ𕶎���Ŏ擾
    /// </summary>
    /// <returns></returns>
    static std::string GetCurrentTimeString() {
#if _DEBUG
        std::time_t t = std::time(nullptr);
        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
#endif // _DEBUG
        return std::string();
    }

    /// <summary>
	/// ���̃��O���x���𕶎���Ŏ擾
    /// </summary>
    /// <param name="level"></param>
    /// <returns></returns>
    static const char* LevelToString(Level level) {
#if _DEBUG
        switch (level) {
        case Level::Info:  return "INFO";
        case Level::Warn:  return "WARN";
        case Level::Error: return "ERROR";
        }
        return "UNKNOWN";
#endif // _DEBUG
    }

    static inline std::string m_logFileName = "Log/log.txt";
    static inline std::mutex m_mtx;
};
