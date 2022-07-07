#include "stdafx.h"
#include "Serial.h"


Serial::Serial(std::string Port, int Speed)
    : m_Port(Port), m_Speed(Speed)
{
    m_id = ++m_idCounter;
}

Serial::~Serial()
{
}

void Serial::init()
{

}

void Serial::send()
{

}

void Serial::recv()
{

}