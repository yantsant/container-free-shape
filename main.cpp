#include "container.h"


void container_unit_test()
{
	for (size_t i = 0; i < 10000000; i++)
	{
		std::vector<size_t> dims;
		dims.push_back(2);
		dims.push_back(3);
		dims.push_back(40);
		dims.push_back(5);
		dims.push_back(3);
		auto cc = new container<int>(dims);
		//auto bb = *cc;// new containerN<int>(dims);
		delete cc;
		//delete bb;
	}
};

int main()
{
	container_unit_test();

	return 0;
}