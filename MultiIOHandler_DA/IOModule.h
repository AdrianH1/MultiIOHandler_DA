#pragma once

#include <vector>


class IOModule
{
public:
	IOModule() = default;

	virtual void init() = 0;
	virtual void send() = 0;
	virtual void recv() = 0;

	int getId();
	void setId(int id);

private:
	std::vector<IOModule> ListenerTable;
	static int m_id;
};