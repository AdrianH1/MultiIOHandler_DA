#include "stdafx.h"
#include "CFileHandler.h"


CFileHandler::CFileHandler(std::string path)
    : m_Path(path)
{
    m_id = ++m_idCounter;
}

CFileHandler::~CFileHandler()
{
}

void CFileHandler::run()
{

}

void CFileHandler::stop()
{

}

void CFileHandler::init()
{

}

void CFileHandler::write()
{

}

void CFileHandler::read()
{

}

void CFileHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | Path: " << m_Path << std::endl;
}