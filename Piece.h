#pragma once
#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>

#define NAME_WEIGHT 1
#define PERIOD_WEIGHT 1
#define ARTIST_WEIGHT 1
#define MEDIUM_WEIGHT 1
#define FINISHED_WEIGHT 6

class Piece 
{
    private:
        int hash(std::string input, int characterLimit);

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
	if (_piece_name == "" && _time_period == "" && _artist_name == "" && _medium == "")
		value = _year_finished + 1000000;
	else
		valueGen();
}

//26^characterLimit needs to be less than INT_MAX
int Piece::hash(std::string s, int characterLimit = 5)
{
    int pieceValue = 0;
    int size = 0;

    if(s.size() == 0) return 0;

    if(s.size() > characterLimit)
        size = characterLimit;
    else
        size = s.size();

    for(int i = 0; i < size; i++) //Closest character gets highest priority / exponent
    {
        int c = tolower(s[i]) - 96;
        if(c > 0 && c < 26)
            pieceValue += pow(c, size - i); //97 is the first value of a. I want a = 1.
    }

    return pieceValue;
}

void Piece::valueGen() 
{
    //int yearValue = yearFinished + 1000000; //((int)(sqrt(yearPercentage) * 10000) % 1000) * 100000; //Flat buffer + range.

	//int nameValue = 0; //hash(pieceName, 5) * 0.0001;
	//int timeValue = 0; //hash(timePeriod, 5) * 0.00001;
	//int artistValue = 0; //hash(artistName, 5) * 0.00001;

    //value = yearValue + nameValue + timeValue + artistValue;
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