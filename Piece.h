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
		std::string time_period = "";
		std::string medium = "";
		std::string artist_name = "";
		std::string piece_name = "";
		int year_finished = 0;
		
		int value; // What it will be sorted by for each algorithm
	
		Piece(std::string _time_period, std::string _medium, std::string _artist_name, std::string _piece_name, int _year_finished);	
		void Value_gen(); // tbd
		void print();
};

Piece::Piece(std::string _piece_name, std::string _time_period, std::string _artist_name, std::string _medium, int _year_finished) 
{
	piece_name = _piece_name;
	time_period = _time_period;
	artist_name = _artist_name;
	medium = _medium;
	year_finished = _year_finished;
	Value_gen();
}

void Piece::Value_gen() 
{
	value = (piece_name.length()*NAME_WEIGHT) + (time_period.length()*PERIOD_WEIGHT) + (artist_name.length()*ARTIST_WEIGHT) + (medium.length()*MEDIUM_WEIGHT) + (year_finished*FINISHED_WEIGHT);
}

void Piece::print()
{
	std::cout << "Time period: " << time_period << std::endl;
	std::cout << "Medium: " << medium << std::endl;
	std::cout << "Artist name: " << artist_name << std::endl;
	std::cout << "Piece name: " << piece_name << std::endl;
	std::cout << "Year finished: " << year_finished << std::endl;
	std::cout << "Value: " << value << std::endl;
}