#include "Voice.h"

void TTS_Say(const std::wstring& input)
{
	try
	{
		using namespace std;

		ISpVoice* pVoice = NULL;      
		HRESULT hr;
		auto a = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		if (FAILED(a))
		{
			logErr("TTS_Say: ERROR 404 FAILED INITIALIZING COM");
			return;
		}
		HRESULT CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit);
		hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);            

		if (SUCCEEDED(hr))
		{
			try
			{
				hr = pVoice->Speak(input.c_str(), 0, NULL);
				pVoice->Release();
				pVoice = NULL;   
			}
			catch (const std::exception& ex)
			{
				logErr("TTS_Say exception 1: %s ", ex.what());
			}
		}
		return;
	}
	catch (const std::exception& ex)
	{
		logErr("TTS_Say exception 2: %s ", ex.what());

	}
	
}





std::queue<std::wstring> TTS::m_wstrsQueue{};

void TTS::addToQueue(std::wstring wstr)
{
	m_wstrsQueue.push(wstr);
}

void TTS::sayAllInQueue()
{
	while (!m_wstrsQueue.empty())
	{
		TTS_Say(m_wstrsQueue.front());
		m_wstrsQueue.pop();
	}
}
