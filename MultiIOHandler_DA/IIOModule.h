#pragma once
#include "stdafx.h"
#include "IDataFilter.h"



class IIOModule
{
public:
	virtual void init() = 0;
	virtual void stop() = 0;
	virtual void write(std::string message) = 0; //@@@semaphore
	virtual void read() = 0;
	virtual void connect() = 0;
	virtual void output() = 0;
	virtual std::vector<std::string> getInfo() = 0;
	virtual void printInfo() = 0;

	typedef enum
	{
		none,
		console,
		serverSocket,
		clientSocket,
		file,
		serial,
		endOfType
	} tModule;

	void setId(int id) { m_id = id; };
	const int getId() { return m_id; };
	void setModuleType(tModule tModule) { m_tModule = tModule; };
	const int getModuleType() { return m_tModule; };
	void setConnectedState(bool state) { m_connected = state; };
	const int getConnectedState() { return m_connected; };
	void setFilter(IDataFilter* filter) { m_dataFilter = filter; filterActive = true; };
	IDataFilter* getFilter() { return m_dataFilter; };
	bool filterIsSet() { return filterActive; };
	
	std::vector<IIOModule*> listenerTable;

	static int m_idCounter;
	static const size_t bufferMax = 50;
	static const size_t vBufferSize = 1 * 512;
	std::mutex writeMutex;
			
private:
	int m_id;
	tModule m_tModule;
	bool m_connected;
	bool filterActive = false;
	IDataFilter* m_dataFilter;
	
};
