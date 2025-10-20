#pragma once
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<typeindex>
#include<type_traits>
#include<functional>
#include<tuple>
#include<filesystem>
#include<stdexcept>
#include<mutex>


#include<cereal/archives/binary.hpp>
#include<cereal/types/string.hpp>
#include<cereal/types/vector.hpp>

#include<SKFW/Framework/Singleton.hpp>

template<typename T>
struct StructMeta;

//  csv�ɓǂݏ���������t�B�[���h�̐ݒ�p
#define REFLECT(TYPE,...)\
template<>\
struct StructMeta<TYPE>{\
    using Type = TYPE;\
    static constexpr auto fields = std::make_tuple(__VA_ARGS__); \
};

/// <summary>
/// csv����̓Ǎ��ƃo�C�i���ϊ��ƓǍ�������B
/// </summary>
class CSVLoader {
public:
    /// <summary>
    /// csv����f�[�^��ǂݍ���
    /// </summary>
    /// <typeparam name="T"> �ǂݍ��݂����\���� </typeparam>
    /// <param name="filepath"> csv�̃t�H���_�p�X </param>
    /// <param name="skipHeader"> �w�b�_�[�s���X�L�b�v���邩�ǂ����̃t���O </param>
    /// <returns> �ǂݍ��񂾍\���̂�vector </returns>
    template<typename T>
    static std::vector<T> Load(const std::string& filepath, bool skipHeader = true) {
        //  �t�@�C���W�J
        std::ifstream file(filepath);
        //  �Ǎ����s����
        if (!file.is_open()) throw std::runtime_error("CSV�t�@�C�����J���܂���ł����B" + filepath);

        std::vector<T> result;  //  �ǂݍ��񂾍\���̂̃R���N�V������ۊ�
        std::string line;   //  csv1�s��buf
        bool skip = skipHeader; //  �w�b�_�[�s��ǂݔ�΂����ǂ���

        //  �ǂݍ��ݏ���
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            if (skip) { skip = false; continue; }    //  �w�b�_�[�s�A���Ȃ�1�񂾂��X�L�b�v����B
            //  �ǉ�����ۂ�1�s�P�ʂœǂݍ���ŕϊ��������̂�n���B
            result.push_back(parseLine<T>(line));
        }

        return result;
    }

private:
    /// <summary>
    /// csv��1�s���\���̂ɕϊ����ĕԂ�
    /// </summary>
    /// <typeparam name="T"> �ǂݍ��݂����\���� </typeparam>
    /// <param name="line"> csv��1�s </param>
    /// <returns> �ǂݍ���csv��1�s </returns>
    template<typename T>
    static T parseLine(const std::string& line) {
        T obj{};    //  ��̃C���X�^���X����

        std::stringstream ss(line);
        std::string cell;   //  �P�Z�����̕����̕ۊ�
        auto fields = StructMeta<T>::fields;    //  �o�^����csv�ɓǂݍ��ރt�B�[���h (std::tuple -> std::pair<FieldPtr, "���O">);

        //  tuple��W�J���ă����_�ɓn���B
        //  ��:(id, name, damage, cost) �� �����_���� flds...
        std::apply([&](auto&&... flds) {
            //  tuple�̊e�t�B�[���h���Ƃ�csv��ǂݍ���ő��
            ((std::getline(ss, cell, ','), assignField(obj, flds.first, cell)), ...);
            }, fields); // apply

        return obj;

    } // parseLine


    /// <summary>
    /// �ǂݍ��񂾕������Ή������^�ɕϊ�����B
    /// </summary>
    /// <typeparam name="T"> �ǂݍ��݂����C�ӂ̍\���� </typeparam>
    /// <typeparam name="FieldPtr"> �e�t�B�[���h�̃|�C���^�^ </typeparam>
    /// <param name="obj"> �l��������\���̂̃C���X�^���X </param>
    /// <param name="field"> �����o�|�C���^�Ŏw�肷��t�B�[���h </param>
    /// <param name="value"> csv����ǂݍ���cell�P�ʂ̕��� </param>
    template<typename T, typename FieldPtr>
    static void assignField(T& obj, FieldPtr field, const std::string& value) {
        //  decltype�͌^�̎擾 decay_t�͕��ʂ̌^�ɕϊ�����B
        using FieldType = std::decay_t<decltype(obj.*field)>;
        //  �R���p�C�����Ɍ^����A�Y�����Ȃ���΍폜�B�S�Ăɂ��Ă͂Ȃ�Ȃ��������O
        if constexpr (std::is_same_v<FieldType, int>) obj.*field = std::stoi(value);
        else if constexpr (std::is_same_v<FieldType, float>) obj.*field = std::stof(value);
        else if constexpr (std::is_same_v<FieldType, double>)obj.*field = std::stod(value);
        else if constexpr (std::is_same_v <FieldType, std::string >) obj.*field = value;
        else static_assert(always_false<FieldType>::value, "�ϊ��ł��Ȃ��l�ł��B");
    }

    //  �^���̂��̂��g����true:false (c++ template���炢)
    template<typename>
    struct always_false : std::false_type {};

};  //  class


/// <summary>
/// c++ cereal���g���č\���̂��o�C�i���f�[�^�ɃV���A���C�Y�A�Ǎ��B
/// </summary>
class BinarySerializer {
public:
    /// <summary>
    /// �\���̂��o�C�i���ɕۑ�����B
    /// bin�t�@�C���ɂ��ăt�H���_�쐬�������ŁB
    /// </summary>
    /// <typeparam name="T"> �ۑ��������\���̂̌^ </typeparam>
    /// <param name="data"> �ۑ��������\���̂̎Q�� </param>
    /// <param name="path"> �ۑ�����t�H���_�̃p�X </param>
    template<typename T>
    static void Save(const std::vector<T>& data, const std::string& path) {
        //  ���̑���f�B���N�g���Ƀo�C�i���t�@�C�����쐬����B
        std::filesystem::create_directories(std::filesystem::path(path).parent_path());
        std::ofstream os(path, std::ios::binary);
        cereal::BinaryOutputArchive archive(os);
        archive(data);
        std::cout << "[OK] " << path << " �ɕۑ����܂��� (" << data.size() << " ��)" << std::endl;
    }

    /// <summary>
    /// �o�C�i���t�@�C������f�[�^���\���̂ɃV���A���C�Y
    /// </summary>
    /// <typeparam name="T"> �ǂݍ��݂����\���̂̌^ </typeparam>
    /// <param name="path"> �ǂݍ��ރo�C�i���f�[�^�̃p�X </param>
    /// <returns> �ǂݍ��񂾃f�[�^�̃R���N�V���� </returns>
    template<typename T>
    static std::vector<T> Load(const std::string& path) {
        std::ifstream is(path, std::ios::binary);
        cereal::BinaryInputArchive archive(is);
        std::vector<T> data;
        archive(data);
        return data;
    }
};


//	�ǂݍ��ރf�[�^���
enum class LoadMode {
    CSV,
    Binary
};

namespace sf = std::filesystem;
/// <summary>
/// csv�f�[�^��ǂݍ���ŕۊǂ���B
/// ���������Ɣ񓯊�������؂�ւ�����悤�ɂ���B
/// </summary>
class GameDatabase : public Singleton<GameDatabase> {
    friend class Singleton<GameDatabase>;

    //	�ǂݍ��ݏ����iCSV���ǂ����𔻒肵�āACSV�Ȃ�ǂݍ��ށj
    void loadData(const sf::path& dataRoot, LoadMode mode);

    //	�f�[�^���R���N�V�����ɒǉ�
    template<typename T>
    void add(int id, const T& data) {
        std::lock_guard<std::mutex> lock(mutex_);	//	�X���b�h�Œ�
        GetTable<T>()[id] = data;
    }

public:

    //	�X���b�h�̏I�����m����
    virtual ~GameDatabase() {
        if (loadthread_.joinable()) loadthread_.join();
    }

    //	�������i���������j
    void Initialize(const sf::path& dataRoot, LoadMode mode);

    //	�������i�񓯊������j
    void InitializeAsync(const sf::path& dataRoot, LoadMode mode);

    //�@�����@�\���ē���̃f�[�^���擾
    //	�^�ɂ���ĕʁX�̃��\�b�h�Ƃ��Ĉ����邩��f�[�^��ނ̍��݂͂Ȃ��B
    template<typename T>
    std::unordered_map<int, T>& GetTable() {
        static std::unordered_map<int, T> table;
        return table;
    }	//	gettable

    //	����̌^�̃R���N�V������Ԃ�
    //	std::optional������const�����ĂȂ��̂�std::reference_wrapper�Ń��b�v���܂��B
    template<typename T>
    std::optional<std::reference_wrapper<const T>> Get(int id) {
        //	�v���C���[�̃C���x���g���Ȃǂł͂Ȃ��������ȍ~�ɓǂݍ��񂾂珑�������邱�Ƃ��Ȃ��̂�
        //	�X���b�h�Œ�͂��邾���R�X�g�̖��ʁB
        //	�ǐ����I����Ă��܂��̂ŋ��ʏ������f�o�b�N�����[�X�ŏ��������Ă܂����ǐ��̂��߂Ȃ̂ŃR�[�h�ǂ񂾐l�͓˂����܂Ȃ��ł��������B
#ifdef _DEBUG
            //	�e�[�u���̎擾
        auto& table = GetTable<T>();
        auto it = table.find(id);
        //	�f�o�b�N���͒��g�Ȃ��������O�𓊂��܂��B
        if (it == table.end()) {
            throw std::out_of_range("[GameDatabase] �͈͊O�A�N�Z�X: ID " + std::to_string(id) + "�^�F" + typeid(T).name());
        }	//	if

#else 

        auto& table = GetTable<T>();
        auto it = table.find(id);
        //	�����[�X�͒��g���Ȃ����Ƃ𖾎��I�ɂ��܂��B
        if (it == table.end()) {
            return std::nullopt;
        } // if

#endif // _DEBUG

            //	�߂�
        return it->second;
    }	//	Get

private:
    //	�ǂݍ��ݗp�X���b�h
    std::thread loadthread_;

    //	�X���b�h�Œ�iconst���\�b�h�ŃX���b�h�Œ�ł���悤��mutable�j
    mutable std::mutex mutex_;

    //	�ǂݍ��ݏI���t���O
    bool isLoaded_ = false;

};	//	class 

