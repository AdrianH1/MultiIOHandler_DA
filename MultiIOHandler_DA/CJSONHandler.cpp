#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void test()
{
	std::ifstream f("example.json");
	json data = json::parse(f);
}