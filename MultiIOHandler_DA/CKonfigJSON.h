#include "stdafx.h"
#include "IIOModule.h"
#include <nlohmann/json.hpp>

/**
 * This class contains the saving and loading to json function 
 * It uses the third-party library "JSON for Modern C++" by nlohmann
 */

class CKonfigJSON
{
public:
	/**
	 * Saves all currently created modules to a json file
	 * Every module is saved with all connection informations
	 * Module infos are recieved via getInfo() function
	 *
	 * @params - Path to the json file
	 * @params - Pointer to the list of currently created modules
	 */
	void save(std::string path, std::vector<IIOModule*> &modules);

	/**
	 * Loads all modules previously saved to a json file
	 * Every module is loaded with all connection informations
	 * Modules are being created and initialized
	 *
	 * @params - Path to the json file
	 * @params - Pointer to the list of currently created modules
	 */
	void load(std::string path, std::vector<IIOModule*> &modules);
};