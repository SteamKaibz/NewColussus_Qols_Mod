#include "K_Utils.h"




 std::set<std::string> K_Utils::uniqueAppNames;



bool K_Utils::IsBitSet(int value, int bitPosition) {
	if (bitPosition < 0 || bitPosition > 31) {
		logErr("IsBitSet: Bit position %d is out of range (0-31). ", bitPosition);
		return false;
	}
	return (value & (1 << bitPosition)) != 0;
}


uint64_t K_Utils::EpochMillis()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

std::string K_Utils::unicode_to_utf8(wchar_t* wide_string)
{
	if (wide_string == nullptr)

		return std::string();

	int buffer_size = WideCharToMultiByte(CP_UTF8, 0, wide_string, -1, nullptr, 0, nullptr, nullptr);
	if (buffer_size == 0)
	{
		throw std::runtime_error("Failed to convert wide string to UTF-8.");
	}

	std::string utf8_string(buffer_size, '\0');

	if (WideCharToMultiByte(CP_UTF8, 0, wide_string, -1, utf8_string.data(), buffer_size, nullptr, nullptr) == 0)
	{
		throw std::runtime_error("Failed to convert wide string to UTF-8.");
	}

	utf8_string.resize(buffer_size - 1);

	return utf8_string;
}

std::string K_Utils::getBuildDate()
{
	std::string date = __DATE__;
	std::string time = __TIME__;
	return date + " " + time;
}

void K_Utils::PlayModLoadSuccesBeeps()
{
	Beep(558, 100);
	Beep(837, 100);
}

void K_Utils::PlayModUnloadedBeeps()
{

	Beep(837, 100);
	Beep(558, 100);
}

std::wstring K_Utils::StandardKeyToStringW(DWORD VKey)
{
	static WCHAR name[32] = L"";
	static BYTE kbState[256] = { 0 };
	DWORD idThread;
	idThread = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);
	long code = MapVirtualKeyExW(VKey, MAPVK_VK_TO_VSC,
		GetKeyboardLayout(idThread)) << 16;
	ToUnicodeEx(VKey, MapVirtualKey(VKey, MAPVK_VK_TO_VSC), kbState, name,
		32, 0, GetKeyboardLayout(idThread));
	return name;
}

std::string K_Utils::wide_to_narrow(const std::wstring& wide_str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
	return convert.to_bytes(wide_str);
}


std::wstring K_Utils::WstrtoLower(const std::wstring& input) {
	std::wstringstream wss;
	const std::ctype<wchar_t>& facet = std::use_facet<std::ctype<wchar_t>>(wss.getloc());

	for (wchar_t ch : input) {
		wss << facet.tolower(ch);
	}

	return wss.str();
}


std::string K_Utils::intToHexString(__int64 decimalValue) {
	std::stringstream ss;
	ss << "0x" << std::uppercase << std::hex << decimalValue;
	return ss.str();
}

bool K_Utils::saveSetToFile(std::string fileName, std::set<std::string> StrSet)
{
	int counter = 0;
	std::ofstream outputFile(fileName);
	if (!outputFile.is_open()) {
		logErr("saveSetToFile: Error opening file %s for writing returning", fileName.c_str());
		return false;
	}
	for (const auto& entity : StrSet) {
		outputFile << entity << std::endl;
		counter++;
	}
	outputFile.close();
	logInfo("saveSetToFile: %d elements were saved to file: %s ", counter, fileName.c_str());
	return true;
}

bool K_Utils::saveVecToFile(std::string fileName, std::vector<std::string> StrVec)
{
	int counter = 0;
	std::ofstream outputFile(fileName);
	if (!outputFile.is_open()) {
		logErr("saveVecToFile: Error opening file %s for writing returning", fileName.c_str());
		return false;
	}
	for (const auto& entity : StrVec) {
		outputFile << entity << std::endl;
		counter++;
	}
	outputFile.close();
	logInfo("saveVecToFile: %d elements were saved to file: %s ", counter, fileName.c_str());
	return true;
}




void K_Utils::removeDuplicates(const std::string& inputFilePath, const std::string& outputFilePath) {
	std::ifstream inputFile(inputFilePath);
	if (!inputFile.is_open()) {
		logErr("Error opening input file : %s returning", inputFilePath.c_str());
		return;
	}

	std::set<std::string> uniqueLines;
	std::string line;
	while (std::getline(inputFile, line)) {
		uniqueLines.insert(line);
	}

	inputFile.close();

	std::ofstream outputFile(outputFilePath);
	if (!outputFile.is_open()) {
		logErr("Error opening output file : %s returning", outputFilePath.c_str());
		return;
	}

	for (const auto& uniqueLine : uniqueLines) {
		outputFile << uniqueLine << '\n';
	}

	outputFile.close();

	logErr("Duplicates removed. Unique lines saved to:: %s ", outputFilePath.c_str());
}

std::set<std::string> K_Utils::loadFileToSet(std::string inputFilePath)
{
	int counter = 0;
	std::set<std::string> uniqueStrsSet;

	std::ifstream inputFile(inputFilePath);

	if (!inputFile.is_open()) {
		logErr("loadFileToSet: Error opening file: %s returning", inputFilePath.c_str());
		return uniqueStrsSet;
	}
		
	
	std::string line;
	while (std::getline(inputFile, line)) {
		uniqueStrsSet.insert(line);           
		counter++;
	}
	inputFile.close();

	logInfo("loadFileToSet: found %d elements in file: %s ", counter, inputFilePath.c_str());
	return uniqueStrsSet;
}
