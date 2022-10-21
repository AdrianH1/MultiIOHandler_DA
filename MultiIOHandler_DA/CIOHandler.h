#pragma once

#include "stdafx.h"
#include "IIOModule.h"
#include "IDataFilter.h"

/**
 * This class is the central hub for all actions
 * It contains the main() function  
 */

class CIOHandler
{
public:
	CIOHandler();
	~CIOHandler();

	/**
	 * Calls the individual functions based on the user input
	 *
	 * @param input - Vector of the individual command strings
	 */
	void callFunction(std::vector<std::string>* input);

private:
	std::vector<IIOModule*> modules;
	std::vector<IDataFilter*> filter;

	/**
	 * All createXYZ functions create an instance of a module handler
	 * Every instance will be saved in a list of IIOModule* 
	 *
	 * @params - Different parameter apply for every specific module type
	 */
	void createConsole();
	void createFilter();
	void createClientSocket(std::string ip, int unsigned port);
	void createServerSocket(std::string ip, int unsigned port);
	void createSerial(std::string port, int bauderate);
	void createFile(std::string path);

	/**
	 * Connects to modules with each other to forward traffic
	 * ListenerTable of id1 will get a pointer to id2
	 *
	 * @params - ID of each module. Id1 will forward traffic to id2
	 */
	void connectModules(int id1, int id2);

	/**
	 * Display all currently created modules and filter
	 */
	void showModules();
	void showFilter();

	/**
	 * Writes all traffic to the console 
	 * Adds the console module as a listener to the specified id
	 * 
	 * @params - ID of module to output traffic to console
	 */
	void outputToConsole(int id);

	/**
	 * Initializes the module if it is not already connected to a device
	 * Tries to connect to device and starts reading from it if successfull
	 *
	 * @params - ID of module to initialize
	 */
	void initModules(int id);

	/**
	 * Delete module and remove it from modules list
	 *
	 * @params - ID of module to remove
	 */
	void removeModule(int id);

	/**
	 * Adds a content filter to a module.
	 * The module will filter all data it recieves before writing it to the device
	 *
	 * @params - ID of module and ID of filter
	 */
	void addFilter(int moduleId, int filterId);

	/**
	 * Save and load all created modules to or from a json file
	 * Each module will be saved with it's connection information for later use
	 * Every module will be initialized when loaded
	 *
	 * @params - Path to json file
	 */
	void saveJSON(std::string path);
	void loadJSON(std::string path);

	/**
	 * Stopps a module an all actions releated to it
	 * The module is in an unitialized state after stopping and has no connection to it's backend device
	 *
	 * @params - ID of module
	 */
	void stopModule(int id);

	/**
	 * Stopps all running threads and exits the application
	 */
	void exitApp();
};