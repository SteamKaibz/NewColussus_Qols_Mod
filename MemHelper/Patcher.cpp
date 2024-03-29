#include "Patcher.h"




bool Patcher::patch(std::string patchNameStr, uintptr_t addr, const std::vector<unsigned char>& newInstructionVec) {
	std::string vecString = "";

	for (unsigned char byte : newInstructionVec) {
		vecString += " " + std::to_string(byte);
	}

	logInfo("patch: name: %s addr: %p with newInstructionVec: %s", patchNameStr.c_str(), (void*)addr, vecString.c_str());

	return MemHelper::overwriteInstruction(patchNameStr, addr, newInstructionVec);
}

bool Patcher::patchIfNeeded(std::string patchNameStr, uintptr_t addr, const std::vector<unsigned char>& newInstructionVec) {
	

	if (!patchNameStr.empty()) {
		std::string vecString = "";
		for (unsigned char byte : newInstructionVec) {
			vecString += " " + std::to_string(byte);
		}
		logInfo("patch: name: %s addr: %p with newInstructionVec: %s", patchNameStr.c_str(), (void*)addr, vecString.c_str());
	}

	return MemHelper::overwriteInstructionIfNotEqual(patchNameStr, addr, newInstructionVec);
}