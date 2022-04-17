#pragma once
#include <fstream> 
#include <vector>
#include <iostream>
#include <map>
#include "Piece.h"

std::pair<std::vector<Piece>, std::map<std::string, int>> parse_dataset(int count = 600000)
{
	int i, iter, index, unknown_count, quote_count, true_length, finished;
	std::string in, temp, piece, period, artist, medium;
	std::ifstream dataset;
	
	std::vector<Piece> gallery;
	std::map<std::string, int> periods;
	
	dataset.open("MetObjects.txt");
	std::getline(dataset, in); // get rid of first line which is information about the following rows of data
	
	for (i = 0; i < count; i++)
	{
		std::getline(dataset, in);
		quote_count = 0;
		true_length = 0;
		unknown_count = 0;
		
		
		/*
			Some rationalization of the following:
				1. We have 600,000 entries to start
				2. Some of them have mismatching quotation marks which make them very tough to parse correctly
				3. Some of them are so short they can't possibly have all of the required information		
		*/
		
		if (in.length() < 70 || i == 439647) continue;		
		if (in.at(0) == '\"' && in.at(in.length()-1) == '\"' || in.at(0) == '(' && in.at(in.length()-1) == ')' ) continue;
		
		for (unsigned int j = 0; j < in.length(); j++) {
			if (in.at(j) == '\"') quote_count++;
			if (in.at(j) != '\"' && in.at(j) != ' ') true_length++;
		}
	
		if (quote_count % 2 == 1 || quote_count > 6 || true_length < 70) continue;
		
		// std::cout << "Line " << i << ":\t" << in << std::endl;
		iter = 1;
		
		while (in.length() > 0)
		{		
			index = 0;
			while (in.at(index) != ',' && index < (int)in.length()-1) 
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
			
			in = in.substr(index+1, in.length()-index);
			//std::cout << "iteration" << iter << ":\t" << temp << "\t" << in << std::endl;
			
			if (temp == "") temp = "unknown";
			if (temp == "unknown" && (iter == 10 || iter == 12 || iter == 19 || iter == 31 || iter == 32)) unknown_count++;
			
			switch (iter)
			{
				case 10:
					piece = temp;
					break;
				case 12:
					period = temp;
					break;
				case 19:
					artist = temp;
					break;
				case 31:
					finished = std::stoi(temp);
					break;
				case 32:
					medium = temp;
					break;
				default:
					break;
			}
			
			if (iter == 32) break;
			iter++;
		}
		
		// check if any unknown, continue
		// std::cout << "Unknown count: " << unknown_count << std::endl;	
		// std::cout << std::endl;
		
		if (unknown_count < 4) {
			/*
			std::cout << "Piece name: " << piece << std::endl;
			std::cout << "Period: " << period << std::endl;
			std::cout << "Artist name: " << artist << std::endl;
			std::cout << "Year finished: " << finished << std::endl;
			std::cout << "Medium: " << medium << std::endl << std::endl;
			*/
			
			gallery.push_back(Piece(piece, period, artist, medium, finished));
			periods[period] = finished;
		}
		
	}		
	dataset.close();
	return {gallery, periods};
}
