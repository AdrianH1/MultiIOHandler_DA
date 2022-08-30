#pragma once

#include "stdafx.h"
#include "IIOModule.h"

class CServerSocketHandler : public IIOModule
{
public:
	CServerSocketHandler() = default;
	CServerSocketHandler(std::string ip, int unsigned port);
	~CServerSocketHandler();

};