#include "stdafx.h"
#include "CFile.h"


CFile::CFile(std::string path)
    : m_Path(path)
{
    m_id = ++m_idCounter;
}

CFile::~CFile()
{
}

void CFile::init()
{

}

void CFile::send()
{

}

void CFile::recv()
{

}

void CFile::printInfo()
{
    std::cout << "ID: " << m_id << " | Path: " << m_Path << std::endl;
}