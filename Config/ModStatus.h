#pragma once


class ModStatus
{
private:
	bool m_isError = false;


public:



	

	bool isAllGood() {
		return !m_isError;
	}

	void setError() {
		m_isError = true;
	}


	void logModStatus() {
		if (m_isError) {
			logErr("ModStatus: ERROR, mod can not start");
		}
		else {
			logInfo("ModStatus: All good so far");
		}
	}

};



