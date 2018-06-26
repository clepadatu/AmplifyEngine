#pragma once
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

	class FileUtils{
	public:

		static std::string read_file(const char* filepath)
		{
			FILE* file = fopen(filepath, "r");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char *data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		};

		static void write_score(std::string name, float score)
		{
			std::ofstream scorefile("private_libraries/_Running/score.txt", std::ofstream::app);
			if (scorefile.is_open())
			{
				scorefile << name<<","<<score<<"\n";				
				scorefile.close();
				std::cout << "success" << std::endl;
			}
			else
				std::cout << "not open" << std::endl;
			
		}
		static void read_score(std::vector<std::string> &scorelist)
		{
			std::string line;
			
			std::ifstream scorefile("private_libraries/_Running/score.txt");
			if (scorefile.is_open())
			{
				int k = 0; k++;
				while (getline(scorefile, line))
				{
					std::string _name = line.substr(0,line.length()-2);
					
					scorelist.push_back(line);
				}
				
				scorefile.close();
				std::cout << "success" << std::endl;
			}
			else
				std::cout << "not open" << std::endl;
			
		}



		/*static void read_score(std::map<int, std::string> &namelist, std::map<int, int> &scorelist)
		{
		std::string line;

		std::ifstream scorefile("private_libraries/_Running/score.txt");
		if (scorefile.is_open())
		{
		int k;
		k = 0; k++;
		while (getline(scorefile, line))
		{
		std::string _name = line.substr(0, line.find(",", 0));
		int _score = std::stoi(line.substr(line.find(",", 0) + 1, std::string::npos));
		scorelist.insert(std::pair<int, int>(k, _score));
		namelist.insert(std::pair<int, std::string>(k, _name));
		k++;
		}

		scorefile.close();
		std::cout << "success" << std::endl;
		}
		else
		std::cout << "not open" << std::endl;

		}*/
	
	};
