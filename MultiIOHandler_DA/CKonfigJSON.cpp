#include "CKonfigJSON.h"
#include "CClientSocketHandler.h"
#include "CServerSocketHandler.h"
#include "CFileHandler.h"
#include "CSerialHandler.h"

using json = nlohmann::json;

static const std::string sModule = "Module";
static const std::string sId = "id";
static const std::string sType = "type";
static const std::string sIp = "ip";
static const std::string sPort = "port";
static const std::string sPath = "path";
static const std::string sBaudrate = "baudrate";


void CKonfigJSON::save(std::string path, std::vector<IIOModule*> &modules)
{
	std::vector<std::string> info;
	//JSON object to store all data in 
	std::ofstream file(path);
	if (file)
	{
		json json;
		std::cout << "Saving..." << std::endl;
		for (int i = 0; i < modules.size(); i++)
		{
			//Connection infos are different for each module type
			switch (modules.at(i)->getModuleType())
			{
			//Add alle infos recieved from getInfo() to the json object
			case IIOModule::tModule::clientSocket:
				info = modules.at(i)->getInfo();
				json[sModule + std::to_string(i)] = { {sId, stoi(info.at(0))}, {sType, stoi(info.at(1))}, {sIp, info.at(2)}, {sPort, stoi(info.at(3))}};
				break;
			case IIOModule::tModule::serverSocket:
				info = modules.at(i)->getInfo();
				json[sModule + std::to_string(i)] = { {sId, stoi(info.at(0))}, {sType, stoi(info.at(1))}, {sIp, info.at(2)}, {sPort, stoi(info.at(3))} };
				break;
			case IIOModule::tModule::file:
				info = modules.at(i)->getInfo();
				json[sModule + std::to_string(i)] = { {sId, stoi(info.at(0))}, {sType, stoi(info.at(1))}, {sPath, info.at(2)} };
				break;
			case IIOModule::tModule::serial:
				info = modules.at(i)->getInfo();
				json[sModule + std::to_string(i)] = { {sId, stoi(info.at(0))}, {sType, stoi(info.at(1))}, {sPort, info.at(2)}, {sBaudrate, stoi(info.at(3))} };
			default:
				break;
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
	//Check if file exists and has a correct format
	if (file && json::accept(file)) 
	{
		file.seekg(0);
		//json object to load data into from file
		json data = json::parse(file);
		std::cout << "Loading..." << std::endl;
		for (int i = 0; i < data.size(); i++)
		{
			//Connection infos are different for each module type
			//Read module type from json format and compare to enum module type
			if (data[sModule + std::to_string(i)][sType] == IIOModule::tModule::serverSocket)
			{
				//Convert json data to needed type for module consturctor
				std::string ip = data[sModule + std::to_string(i)][sIp].get<std::string>();
				int port = data[sModule + std::to_string(i)][sPort].get<int>();
				//Create module, initialize and add it to the modules list of the IOHandler 
				CServerSocketHandler* socket = new CServerSocketHandler(ip, port);
				socket->init();
				modules.push_back(socket);
			}
			else if (data[sModule + std::to_string(i)][sType] == IIOModule::tModule::clientSocket)
			{
				//Convert json data to needed type for module consturctor
				std::string ip = data[sModule + std::to_string(i)][sIp].get<std::string>();
				int port = data[sModule + std::to_string(i)][sPort].get<int>();
				//Create module, initialize and add it to the modules list of the IOHandler 
				CClientSocketHandler* socket = new CClientSocketHandler(ip, port);
				socket->init();
				modules.push_back(socket);
			}
			else if (data[sModule + std::to_string(i)][sType] == IIOModule::tModule::file)
			{
				//Convert json data to needed type for module consturctor
				std::string path = data[sModule + std::to_string(i)][sPath].get<std::string>();
				//Create module, initialize and add it to the modules list of the IOHandler 
				CFileHandler* file = new CFileHandler(path);
				file->init();
				modules.push_back(file);
			}
			else if (data[sModule + std::to_string(i)][sType] == IIOModule::tModule::serial)
			{
				//Convert json data to needed type for module consturctor
				std::string port = data[sModule + std::to_string(i)][sPort].get<std::string>();
				int baudrate = data[sModule + std::to_string(i)][sBaudrate].get<int>();
				//Create module, initialize and add it to the modules list of the IOHandler 
				CSerialHandler* serial = new CSerialHandler(port, baudrate);
				serial->init();
				modules.push_back(serial);
			}
		}
		std::cout << "Loading finished!" << std::endl;
	}
	else
	{
		std::cout << "File not found or wrong format!" << std::endl;
	}
}
