#pragma once
#include "stdafx.h"
#include "IDataFilter.h"

/**
 * This interface gives every module a default structure, functions and variables
 * Every module handler has to inherit this interface
 */

class IIOModule
{
public:

	/**
	* Virtual destructor so that every module must specify a destructor
	* Child desctructor will be called when object is destroyed and stop all running tasks
	*/
	virtual ~IIOModule() {};

	/**
	* Virtual methods that have to be overriden by all modules
	* Details to each override is described in the handler classes
	*/
	virtual void init() = 0;
	virtual void stop() = 0;
	virtual void write(std::vector<char> message) = 0;
	virtual void read() = 0;
	virtual void connect() = 0;
	virtual void output() = 0;
	virtual std::vector<std::string> getInfo() = 0;
	virtual void printInfo() = 0;

	//Enum for the module type
	typedef enum
	{
		none,
		console,
		serverSocket,
		clientSocket,
		serverSocketUDP,
		clientSocketUDP,
		file,
		serial,
		endOfType
	} tModule;

	//Setters and Getters for all private member variables
	void setId(int id) { m_id = id; };
	const int getId() { return m_id; };
	void setModuleType(tModule tModule) { m_tModule = tModule; };
	const int getModuleType() { return m_tModule; };
	void setWriteToListener(bool state) { m_writeToListener = state; };
	const int getWriteToListener() { return m_writeToListener; };
	void setConnectedState(bool state) { m_connected = state; };
	const int getConnectedState() { return m_connected; };
	void setFilter(IDataFilter* filter) { m_dataFilter = filter; m_filterActive = true; };
	IDataFilter* getFilter() { return m_dataFilter; };
	bool filterIsSet() { return m_filterActive; };
	void removeFilter() { m_dataFilter = nullptr; m_filterActive = false; };
	
	//Listener table for storing pointer to other io modules
	std::vector<IIOModule*> listenerTable;

	//Id counter to ensure a unique id for every module
	static int m_idCounter;

	//Buffer max size for read buffer (used to store already read data)
	static const size_t bufferMax = 50;
	//Buffer size for a single async read
	static const size_t vBufferSize = 1 * 512;
	//Mutex used for locking the write method
	std::mutex writeMutex;
			
private:
	//Id for unique identifier
	int m_id;
	//Enum for module type
	tModule m_tModule;
	//Boolean to activate writing to a modules listeners
	bool m_writeToListener = false;
	//Boolean to track a modules connection status with its device, file or serial port
	bool m_connected = false;
	//Boolean to check if a module has an acitve filter
	bool m_filterActive = false;
	//Pointer to the active filter
	IDataFilter* m_dataFilter;
	
};