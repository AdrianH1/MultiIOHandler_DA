#include "stdafx.h"
#include "CFileHandler.h"


CFileHandler::CFileHandler(std::string path)
    : m_path(path)
{
    setId(++m_idCounter);
    setModuleType(file);
    setConnectedState(false);
    std::cout << "Created File Module: " << std::endl;
    printInfo();
}

CFileHandler::~CFileHandler()
{
    stop();
}

void CFileHandler::stop()
{
    writeToListener = false;
    reading = false;
    setConnectedState(false);
    listenerTable.clear();
    m_fs.close();
    if (m_thrRead.joinable()) m_thrRead.join();
}

void CFileHandler::init()
{
    std::ifstream file(m_path);
    if (file)
    {
        file.close();
        reading = true;
        setConnectedState(true);
        std::cout << "Connected!" << std::endl;
        m_thrRead = std::thread([this]() {read(); });
    }
    else
    {
        file.close();
        std::cout << "File doesn't exist!" << std::endl;
    }
}

void CFileHandler::write(std::string message)
{
    m_fs.open(m_path, std::ios::app);

    if (filterIsSet())
    {
        std::string filteredMessage = getFilter()->filterData(message);
        m_fs << filteredMessage << std::endl;
    }
    else
    {
        m_fs << message << std::endl;
    }
    
    m_fs.close();
}

void CFileHandler::read()
{
    m_fs.open(m_path, std::ios::in);
    std::string message;
    while (reading)
    {
        if (std::getline(m_fs, message))
        {
            if (writeToListener)
            {
                for (IIOModule* m : listenerTable)
                {
                    m->write(message);
                }
            }
        }
        else
        {
            //Set file pointer to the start of the file
            m_fs.clear();
            m_fs.seekg(0);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    m_fs.close();
}

void CFileHandler::output()
{
    writeToListener = true;
}

void CFileHandler::connect()
{
    //activate write to listener
    for (IIOModule* m : listenerTable)
    {
        writeToListener = true;
    }
}

std::vector<std::string> CFileHandler::getInfo()
{
    std::vector<std::string> info;
    info.push_back(std::to_string(getId()));
    info.push_back(std::to_string(getModuleType()));
    info.push_back(m_path);
    return info;
}

void CFileHandler::printInfo()
{
    std::cout << "ID: " << getId() << " | Type: " << "file" << " | Path: " << m_path << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;
}