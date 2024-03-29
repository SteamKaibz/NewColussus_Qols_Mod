#include "ClassDefV2.h"






std::string ClassDefV2::getInheritanceListStr()
{
	if (m_inheritanceStrVec.size() <= 0) {
		return std::string();
	}
	std::string result;

	for (size_t i = 0; i < m_inheritanceStrVec.size(); i++) {
		result += m_inheritanceStrVec[i];

		if (i < m_inheritanceStrVec.size() - 1) {
			result += " : ";
		}
	}
	return result;
}

bool ClassDefV2::hasInheritance()
{
	return (m_inheritanceStrVec.size() > 0);

}
