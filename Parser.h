#pragma once
#include <fstream> 
#include <vector>
#include <iostream>
#include "Piece.h"

std::vector<Piece> parse_dataset()
{
	std::vector<Piece> gallery;
	// TODO
	return gallery;
}

std::vector<Piece> parse_dataset(int count)
{
	int i, iter, index, unknown_count, quote_count, true_length, finished;
	std::string in, temp, piece, period, artist, medium;
	std::ifstream dataset;
	std::vector<Piece> gallery;
	
	dataset.open("MetObjects.txt");
	getline(dataset, in); // get rid of first line which is information about the following rows of data
	
	for (i = 0; i < count; i++)
	{
		std::getline(dataset, in);
		quote_count = 0;
		true_length = 0;
		unknown_count = 0;
		
		for (int j = 0; j < in.length(); j++) {
			if (in.at(j) == '\"') quote_count++;
			if (in.at(j) != '\"' && in.at(j) != ' ') true_length++;
		}
		
		/*
			Some rationalization of the following:
				1. We have 600,000 entries to start
				2. Some of them have mismatching quotation marks which make them very tough to parse correctly
				3. Some of them are so short they can't possibly have all of the required information		
		*/
		
		if (quote_count % 2 == 1 || quote_count > 6 || true_length < 70) continue;
		
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
			
			in = in.substr(index+1, in.length()-index);
			//std::cout << "iteration" << iter << ":\t" << temp << "\t" << in << std::endl;
			
			if (temp == "" && (iter == 10 || iter == 12 || iter == 19 || iter == 31 || iter == 32)) {
				temp = "unknown"; 
				unknown_count++;
			}
			
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
				case 31:
					std::cout << "Year finished: " << temp << std::endl;
					finished = std::stoi(temp);
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
		std::cout << "Unknown count: " << unknown_count << std::endl;
		if(unknown_count < 4) gallery.push_back(Piece(piece, period, artist, medium, finished));
		std::cout << std::endl;
		
	}		
	dataset.close();
	return gallery;
}
