#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Piece.h"

std::vector<Piece> parse_dataset(); // Final version of the parser, does the entire dataset
std::vector<Piece> parse_dataset(int count); // temp param = lines to get, so we arent reading all 600,000 lines each trial

int main(int argc, char **argv)
{
	std::vector<Piece> gallery = parse_dataset(std::stoi(argv[1]));
    return 0;
}

std::vector<Piece> parse_dataset() 
{
	std::vector<Piece> gallery;
	// TODO
	return gallery;
}

std::vector<Piece> parse_dataset(int count) 
{
	int i, iter, index;
	std::string in, temp, piece, period, artist, medium;
	std::ifstream dataset;
	std::vector<Piece> gallery;
	
	dataset.open("MetObjects.txt");
	getline(dataset, in); // get rid of first line which is information about the following rows of data
	
	
	for (i = 0; i < count; i++)
	{
		std::getline(dataset, in);
		std::cout << "Line " << i << ":\t" << in << std::endl;
		iter = 1;
		while (in.length() > 0)
		{
			index = 0;
			while (in.at(index) != ',' && index < in.length()-1) 
			{
				if (in.at(index) == '\"') // need to look for next quote then comma
				{
					index++;
					while (in.at(index) != '\"')
						index++;
					index += 1;
					break;
				}
				index++;
			}
			
			if (in.length()-1 != index) 
				temp = in.substr(0,index);
			else
				temp = in;
			if (i == 36) std::cout << temp << std::endl;
			in = in.substr(index+1, in.length()-index);
			//std::cout << "iteration" << iter << ":\t" << temp << "\t" << in << std::endl;
			
			if (temp == "") temp = "unknown";
			switch (iter)
			{
				case 10:
					std::cout << "Piece name: " << temp << std::endl;
					piece = temp;
					break;
				case 12:
					std::cout << "Period: " << temp << std::endl;
					period = temp;
					break;
				case 19:
					std::cout << "Artist name: " << temp << std::endl;
					artist = temp;
					break;
				case 32:
					std::cout << "Medium: " << temp << std::endl;
					medium = temp;
					break;
				default:
					break;
			}
			
			if (iter == 32) break;
			iter++;
		}
		// check if any unknown, continue
		gallery.push_back(Piece(piece, period, artist, medium));
		std::cout << std::endl;
		
	}		
	dataset.close();
	return gallery;
}
