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
    setWriteToListener(false);
    reading = false;
    setConnectedState(false);
    listenerTable.clear();
    removeFilter();
    m_fs.close();
    if (m_thrRead.joinable()) m_thrRead.join();
}

void CFileHandler::init()
{
    std::ifstream file(m_path);
    //Check if file exists
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

void CFileHandler::write(std::vector<char> message)
{
    //lock_guard to prevent simultaneous writing. Lock is released when block ends.
    const std::lock_guard<std::mutex> lock(writeMutex);
    m_fs.open(m_path, std::ios::app);

    if (filterIsSet())
    {
        std::vector<char> filteredMessage = getFilter()->filterData(message);
        m_fs.write((char*)&filteredMessage, sizeof(filteredMessage));
        m_fs << std::endl;
    }
    else
    {
        m_fs.write((char*)&message, sizeof(message));
        m_fs << std::endl;
    }
    
    m_fs.close();
}

void CFileHandler::read()
{
    m_fs.open(m_path, std::ios::in);
    std::vector<char> message;
    char c;

    while (reading)
    {
        while (m_fs.get(c))
        {
            message.push_back(c);
            if (c == '\n')
            {
                if (getWriteToListener())
                {
                    for (IIOModule* m : listenerTable)
                    {
                        m->write(message);
                    }
                }
                message.clear();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

        //Set file pointer to the start of the file
        m_fs.clear();
        m_fs.seekg(0);

    }
    m_fs.close();
}

void CFileHandler::output()
{
    setWriteToListener(true);
}

void CFileHandler::connect()
{
     setWriteToListener(true);
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