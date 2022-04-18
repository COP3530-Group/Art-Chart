#pragma once
#include <iostream>
#include <string>
#include <iostream>
#include <vector>

#define NAME_WEIGHT 1
#define PERIOD_WEIGHT 1
#define ARTIST_WEIGHT 1
#define MEDIUM_WEIGHT 1
#define FINISHED_WEIGHT 6

class Piece 
{
	public:
		std::string timePeriod = "";
		std::string medium = "";
		std::string artistName = "";
		std::string pieceName = "";
		int yearFinished = 0;
		
		int value; // What it will be sorted by for each algorithm
	
		Piece(std::string _time_period, std::string _medium, std::string _artist_name, std::string _piece_name, int _year_finished);	
		void valueGen();
		void print();
};

Piece::Piece(std::string _piece_name, std::string _time_period, std::string _artist_name, std::string _medium, int _year_finished) 
{
	pieceName = _piece_name;
	timePeriod = _time_period;
	artistName = _artist_name;
	medium = _medium;
	yearFinished = _year_finished;
	valueGen();
}

void Piece::valueGen() 
{
	value = (pieceName.length()*NAME_WEIGHT) + (timePeriod.length()*PERIOD_WEIGHT) + (artistName.length()*ARTIST_WEIGHT) + (medium.length()*MEDIUM_WEIGHT) + (yearFinished*FINISHED_WEIGHT);
}

void Piece::print()
{
	std::cout << "Time period: " << timePeriod << std::endl;
	std::cout << "Medium: " << medium << std::endl;
	std::cout << "Artist name: " << artistName << std::endl;
	std::cout << "Piece name: " << pieceName << std::endl;
	std::cout << "Year finished: " << yearFinished << std::endl;
	std::cout << "Value: " << value << std::endl;
}