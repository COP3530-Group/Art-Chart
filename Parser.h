#pragma once
#include <fstream> 
#include <vector>
#include <iostream>
#include "Piece.h"

std::vector<Piece> parseDataset(int count)
{
	int i, iter, index, unknown_count, quoteCount, trueLength, finished;
	std::string in, temp, piece, period, artist, medium;
	std::ifstream dataset;
	
	std::vector<Piece> gallery;
	
	dataset.open("MetObjects.txt");
	std::getline(dataset, in); // get rid of first line which is information about the following rows of data
	
	for (i = 0; i < count; i++)
	{
		std::getline(dataset, in);
		quoteCount = 0;
		trueLength = 0;
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
			if (in.at(j) == '\"') quoteCount++;
			if (in.at(j) != '\"' && in.at(j) != ' ') trueLength++;
		}
	
		if (quoteCount % 2 == 1 || quoteCount > 6 || trueLength < 70) continue;
		
		iter = 1;
		
		while (in.length() > 0)
		{		
			index = 0;
			while (in.at(index) != ',' && index < (int)in.length()-1) 
			{
				if (in.at(index) == '\"')
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

		if (unknown_count < 4)
			gallery.push_back(Piece(piece, period, artist, medium, finished));
	}		
	dataset.close();
	return gallery;
}
