#include "CKonfigJSON.h"

using json = nlohmann::ordered_json;

static const std::string sModule = "Module";
static const std::string sOpen = "open";

CKonfigJSON::CKonfigJSON(CIOHandler* ioHandler)
	: m_ioHandler(ioHandler)
{
}

void CKonfigJSON::save(std::string path, std::vector<IIOModule*> &modules)
{
	std::vector<std::vector<std::string>> info;
	std::ofstream file(path);
	if (file)
	{
		//json object to store all data in 
		json json;
		std::cout << "Saving..." << std::endl;

		for (int i = 0; i < modules.size(); i++)
		{
			info = modules.at(i)->getInfo();
			for (std::vector<std::string> v : info)
			{
				json[sModule + std::to_string(i)][v.at(0)] = v.at(1);
			}
		}

		//Write json object to file
		file << std::setw(4) << json << std::endl;
		file.close();
		std::cout << "Saving finished!" << std::endl;
	}
	else
	{
		std::cout << "File not found!" << std::endl;
	}

}


void CKonfigJSON::load(std::string path, std::vector<IIOModule*>& modules)
{
	std::fstream file(path);
	std::vector<std::string> moduleInfos;
	//Check if file exists and has a correct format
	if (file && json::accept(file)) 
	{
		file.seekg(0);
		//json object to load data into from file
		json data = json::parse(file);
		std::cout << "Loading..." << std::endl;

		for (auto& element : data) {
			moduleInfos.push_back(sOpen);
			for (auto& info : element)
			{
				moduleInfos.push_back(info);
			}
			m_ioHandler->callFunction(&moduleInfos);
			moduleInfos.clear();
		}
		std::cout << "Loading finished!" << std::endl;
	}
	else
	{
		std::cout << "File not found or wrong format!" << std::endl;
	}
}
