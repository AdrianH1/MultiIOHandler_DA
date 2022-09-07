#include "stdafx.h"
#include "IIOModule.h"
#include <fstream>
#include <nlohmann/json.hpp>

class CKonfigJSON
{
public:
	void save(std::string path, std::vector<IIOModule*> &modules);
	void load(std::string path, std::vector<IIOModule*> &modules);

private:

};