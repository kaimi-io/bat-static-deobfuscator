#include <map>
#include <regex>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: batch_deobfuscate.exe batch_file" << std::endl;
		return 0;
	}

	std::string ifile, ofile;

	try
	{
		ifile = argv[1];
		ofile = ifile + ".decrypted";

		std::ifstream ifs(ifile);
		if (!ifs.is_open())
			throw std::runtime_error("Can't open " + ifile + " for reading");

		std::ofstream ofs(ofile);
		if (!ofs.is_open())
			throw std::runtime_error("Can't open " + ofile + " for writing");


		std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		ifs.close();

		std::smatch found;
		std::regex search_pattern("^set\\s([^\\s%]+?)=(.+)$"), replace_pattern;
		std::map<std::string, std::string> env_variables;

		size_t offset = 0;
		std::string search_substring = content.substr(offset);

		while (std::regex_search(search_substring, found, search_pattern))
		{
			if (found.size() < 3)
				break;

			offset += found.position(2);

			env_variables[found[1]] = found[2];

			for (auto it = env_variables.cbegin(); it != env_variables.cend(); ++it)
			{
				replace_pattern.assign("%" + (*it).first + "%");
				content = std::regex_replace(content, replace_pattern, (*it).second);
			}

			search_substring = content.substr(offset);
		}

		ofs << content;
		ofs.close();

		std::cout << "Done! Check " << ofile << std::endl;
		std::getchar();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::getchar();

		return -1;
	}

	return 0;
}
