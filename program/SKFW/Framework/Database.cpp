#include<SKFW/Framework/Database.hpp>

void GameDatabase::loadData(const sf::path& dataRoot, LoadMode mode)
{
	//	���f�B���N�g�����A�Ǎ����\�b�h���łǂ̃f�B���N�g���ɑ΂��Ăǂ̏������s�����̃e�[�u���쐬
	std::unordered_map<std::string, std::function<void(const sf::path&)>> typeLoaders;

	//	�^���Ƃ̓ǂݍ��ݏ���
	//	�f�o�b�N�� csv�Ǎ��A�o�C�i�������o��
	//	�����[�X�� �o�C�i���Ǎ�

	// ================== �e�X�g�f�[�^ ===================
	//typeLoaders["Test"] = [this, debugMode](const sf::path& filepath) {
	//	auto binpath = filepath;
	//	binpath.replace_extension(".bin");
	//	if (debugMode) {
	//		auto list = CSVLoader::Load<TestData>(filepath.string());
	//		for (auto& d : list) this->add<TestData>(d.id, d);
	//		BinarySerializer::Save(list, binpath.string());
	//	}
	//	else {
	//		auto list = BinarySerializer::Load<TestData>(binpath.string());
	//		for (auto d : list) this->add<TestData>(d.id, d);
	//	}
	//};



	//	========== �f�B���N�g���{�� ==========
	for (const auto& entry : sf::recursive_directory_iterator(dataRoot)) {
		if (!entry.is_regular_file())continue;	//	�ʏ�t�@�C���ȊO(�f�B���N�g���A�����N�Ȃ�)�̓X�L�b�v
		if (entry.path().extension() != ".csv") continue;	//	csv�g���q�ȊO�̓X�L�b�v

		//	�e�f�B���N�g�����Ō^�𔻕�
		std::string typeName = entry.path().parent_path().filename().string();

		//	�f�B���N�g�����Ō���
		auto it = typeLoaders.find(typeName);
		if (it != typeLoaders.end()) {
			//	�Ǎ����\�b�h���s
			it->second(entry.path());

#ifdef _DEBUG
			std::ostringstream oss;
			oss << "[GameDatabase] ���[�h����; " << entry.path().string() << std::endl;
			std::cout << oss.str();
#endif // !_DEBUG

			//	�R���\�[���Ƀ��O�\��

		}
	}

}

/// <summary>
/// ��������
/// �w�肵���f�B���N�g����.csv�g���q��
/// </summary>
/// <param name="dataRooot"></param>
/// <param name="debugMove"></param>
void GameDatabase::Initialize(const sf::path& dataRoot, LoadMode mode)
{
	loadData(dataRoot, mode);
	isLoaded_ = true;
}

void GameDatabase::InitializeAsync(const sf::path& dataRoot, LoadMode mode)
{

}

