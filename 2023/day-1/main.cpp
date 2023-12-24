#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
	std::fstream file("in.txt");
	if(file.is_open())
	{
		std::string line;
		int sum = 0;
		while(file)
		{
			int nums;
			std::getline(file, line);
			
			if(line.empty())
			{
				break;
			}

			std::string nums_string;
			size_t first_number = line.find_first_of("0123456789");
			if(first_number != std::string::npos)
			{
				nums_string += line[first_number];
			}
			size_t last_numer = line.find_last_of("0123456789");
			if(last_numer != std::string::npos)
			{
				nums_string += line[last_numer];
			}
			
			std::stringstream ss;
			ss << nums_string;
			ss >> nums;
			sum += nums;
		}

		std::cout << sum << '\n';
	}
    
	return 0;
}