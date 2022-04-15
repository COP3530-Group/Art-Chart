#pragma once
#include <string>

class Piece {
	public:
		std::string time_period = "";
		std::string medium = "";
		std::string artist_name = "";
		std::string piece_name = "";
		int index; // What it will be sorted by for each algorithm
		Piece(std::string _time_period, std::string _medium, std::string _artist_name, std::string _piece_name);	
		int Index_gen(); // tbd, 
};

Piece::Piece(std::string _piece_name, std::string _time_period, std::string _artist_name, std::string _medium ) {
	piece_name = _piece_name;
	time_period = _time_period;
	artist_name = _artist_name;
	medium = _medium;
	index = Index_gen();
}

int Piece::Index_gen() {
	// TODO
	return 0;
}