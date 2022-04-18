/*
#include <chrono>
#include "SFML/Graphics.hpp"

#include "Parser.h"
#include "RadixSort.h"
#include "HeapSort.h"
#include "SortByRelevance.h"


using namespace std;

struct outputGroup 
{
	sf::Text heading;
	sf::Text pieceName;
	sf::Text artistName;
	sf::Text period;
	sf::Text completed;
	sf::Text medium;
	sf::Text link;
};

void GUI(vector<Piece> & gallery, int rduration, int hduration);
void initText(sf::Text& text, sf::Font& font, string str, int charSize, int xPos, int yPos);
void initResult(outputGroup& text, int res, sf::Font& font);
int whichSelected(int x, int y, int curr);

int main(int argc, char **argv)
{
	vector<Piece> gallery;

	gallery = parseDataset(600000);

	vector<Piece> gallery2 = gallery; // Make a copy of gallery so that we can sort it 2 ways and compare the execution times of quick and heap sort
	
	// Radix sort
	auto rstart = std::chrono::high_resolution_clock::now();
	gallery = radixSort(gallery, 10);
	auto rstop = std::chrono::high_resolution_clock::now();
	auto rduration = std::chrono::duration_cast<std::chrono::microseconds>(rstop-rstart);
	
	// Heap sort
	auto hstart = std::chrono::high_resolution_clock::now();
	gallery2 = heapSort(gallery2);
	auto hstop = std::chrono::high_resolution_clock::now();
	auto hduration = std::chrono::duration_cast<std::chrono::microseconds>(hstop-hstart);

	// cout << gallery.size() << " elements sorted in " << rduration.count() << " microseconds using radix sort" << endl;
	// cout << gallery2.size() << " elements sorted in " << hduration.count() << " microseconds using heap sort" << endl;

	GUI(gallery, (int)rduration.count(), (int)hduration.count());

    return 0;
}

void GUI(vector<Piece> & gallery, int rduration, int hduration)
{
	int i;

	sf::RenderWindow window(sf::VideoMode(2000, 1000), "Art Chart");
	window.setFramerateLimit(60);
	sf::Event e;

	sf::Font font;
	if (!font.loadFromFile("times new roman.ttf"))
	{
		std::cout << "font not loaded" << std::endl;
		return;
	}

	// Constant text
	sf::Text constText[12];

	// User inputed text
	sf::String userInput[5];
	sf::Text userText[5];
	
	// Screen partitions
	sf::Vertex vertLine[] = {sf::Vertex(sf::Vector2f(1000,50)), sf::Vertex(sf::Vector2f(1000,1000))};
	sf::Vertex horzLine1[] = {sf::Vertex(sf::Vector2f(0,50)), sf::Vertex(sf::Vector2f(2000,50))};
	sf::Vertex horzLine2[] = {sf::Vertex(sf::Vector2f(0,80)), sf::Vertex(sf::Vector2f(2000,80))};

	// Headings and info text
	initText(constText[0], font, "Art Chart", 40, 1000 - (constText[0].findCharacterPos(8).x / 2), 0);
	initText(constText[1], font, "Input", 30, 500 - (constText[1].findCharacterPos(4).x / 2), 45);
	initText(constText[2], font, "Output", 30, 1500 - (constText[2].findCharacterPos(5).x / 2), 45);
	initText(constText[3], font, "Input the following parameters in the corresponding text fields.", 30, 25, 80);
	initText(constText[4], font, "Click 'Search' to search for a piece and get some similair pieces.", 30, 25, 120);
	initText(constText[10], font, "Radix sort sorted " + to_string(gallery.size()) + " elements in " + to_string(rduration) + " microseconds!", 30, 0, 0);
	initText(constText[11], font, "Heap sort sorted " + to_string(gallery.size()) + " elements in " + to_string(hduration) + " microseconds!", 30, 1249, 0);

	// Text for directing user input
	sf::String headings[5] = {"Piece Name:", "Artist Name:", "Period:", "Approx. Data Completed (enter a number):", "Medium:"};

	//sf::String headings[5] = { "Year (enter a number):", "Artist Name:", "Period:", "Piece Name:", "Medium:" };

	for (i = 0; i < 5; i++)
	{
		constText[i+5].setFont(font);
		constText[i+5].setFillColor(sf::Color(255, 255, 255, 255));
		constText[i+5].setOutlineColor(sf::Color(255, 255, 255, 255));
		constText[i+5].setString(sf::String(headings[i]));
		constText[i+5].setPosition((float)25, (float)200+(120*i));
	}

	sf::RectangleShape text_box[5];

	for (i = 0; i < 5; i++)
	{
		text_box[i].setSize(sf::Vector2f(900, 50));
		text_box[i].setFillColor(sf::Color(255, 255, 255, 30));
		text_box[i].setPosition((float)50, (float)250 + (120 * i));

		userText[i].setFont(font);
		userText[i].setFillColor(sf::Color(225, 225, 20, 255));
		userText[i].setOutlineColor(sf::Color(225, 225, 20, 255));
		userText[i].setPosition((float)55, (float)250 + (120 * i));
	}
	
	// Search

	sf::RectangleShape search_field;
	search_field.setSize(sf::Vector2f(500, 80));
	search_field.setFillColor(sf::Color(0, 255, 0, 100));
	search_field.setPosition((float)250, (float)900);

	sf::Text search_text;
	search_text.setFont(font);
	search_text.setString(sf::String("Search"));
	search_text.setCharacterSize(50);
	search_text.setFillColor(sf::Color(255, 255, 255, 200));
	search_text.setOutlineColor(sf::Color(255, 255, 255, 200));
	search_text.setPosition((float)500 - (search_text.findCharacterPos(5).x / 2), (float)910);

	outputGroup results[5];

	for (i = 0; i < 5; i++)
	{
		initResult(results[i], i, font);
	}

	int selected = 0;
	bool search_clicked = false;

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			// Keyboard input
			if (e.type == sf::Event::TextEntered)
			{
				switch (e.text.unicode)
				{
				case 8: // backspace
					if (userInput[selected].getSize() > 0)
						userInput[selected].erase(userInput[selected].getSize() - 1, 1);
					// do nothing
					break;
				case 9: // tab
					selected = (selected + 1) % 5;
					break;
				case 13: // enter
					search_clicked = true;
					break;
				default:
					if (!(userText[selected].findCharacterPos(userInput[selected].getSize() - 1).x > 930))
						userInput[selected] += e.text.unicode;
					break;
				}

				userText[selected].setString(userInput[selected]);
			}

			// Mouse input
			if (e.type == sf::Event::Closed) window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				selected = whichSelected(x, y, selected);
				if (x > 250 && x < 750 && y > 900 && y < 950) search_clicked = true;
			}
		}

		window.clear();

		if (search_clicked)
		{
			// Verify no empty input
			int count = 0;
			for (i = 0; i < 5; i++)
				if (userInput[i].toAnsiString() == "") count++;

			// Update text fields to result of searching for the specified value
			if (count == 0)
			{
				// Using the search parameters, make an object with them to generate the corresponding
				Piece p(userInput[0].toAnsiString(), userInput[1].toAnsiString(), userInput[2].toAnsiString(), userInput[4].toAnsiString(), stoi(userInput[3].toAnsiString()));

				vector<Piece> relevant = sortByRelevance(p, gallery);

				// Update each output field with the corresponding data from result
				for (i = 0; i < 5; i++)
				{
					results[i].artistName.setString("Artist Name: " + relevant[i].artistName);
					results[i].pieceName.setString("Piece Name: " + relevant[i].pieceName);
					results[i].period.setString("Period: " + relevant[i].timePeriod);
					results[i].completed.setString("Year Completed: " + to_string(relevant[i].yearFinished));
					results[i].medium.setString("Medium: " + relevant[i].medium);
				}

			}
			search_clicked = false;
		}

		// Line partitions for formatting
		window.draw(vertLine, 2, sf::Lines);
		window.draw(horzLine1, 2, sf::Lines);
		window.draw(horzLine2, 2, sf::Lines);

		// Highlight the correct selected input field, draw each input field with the user inputted text over it
		for (i = 0; i < 5; i++) 
		{
			text_box[i].setFillColor(sf::Color(255, 255, 255, 30));
			if (i == selected) text_box[i].setFillColor(sf::Color(255, 255, 255, 120));
			window.draw(text_box[i]);
			window.draw(userText[i]);
		}

		// Draw constant text fields (title, labels, headings, etc.)
		for (i = 0; i < 12; i++)
			window.draw(constText[i]);

		// Draw the results
		for (i = 0; i < 5; i++)
		{
			window.draw(text_box[i]);
			window.draw(results[i].heading);
			window.draw(results[i].pieceName);
			window.draw(results[i].artistName);
			window.draw(results[i].period);
			window.draw(results[i].completed);
			window.draw(results[i].medium);
		}

		// Draw search button
		window.draw(search_field);
		window.draw(search_text);

		window.display();
	}
}

void initText(sf::Text& text, sf::Font& font, string str, int charSize, int xPos, int yPos)
{
	text.setFont(font);
	text.setFillColor(sf::Color(255,255,255,255));
	text.setOutlineColor(sf::Color(255,255,255,255));
	text.setString(sf::String(str));
	text.setCharacterSize(charSize);
	text.setPosition(xPos, yPos);
}

void initResult(outputGroup &text, int res, sf::Font &font)
{
	// Initializes result outgroup

	string str = "Result " + to_string(res + 1) + ":";
	text.heading.setFont(font);
	text.heading.setCharacterSize(25);
	text.heading.setFillColor(sf::Color(255, 255, 255, 255));
	text.heading.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.heading.setPosition((float)1055, (float)80 + (180 * res));
	text.heading.setString(sf::String(str));

	text.artistName.setFont(font);
	text.artistName.setCharacterSize(20);
	text.artistName.setFillColor(sf::Color(255, 255, 255, 255));
	text.artistName.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.artistName.setPosition((float)1100, (float)85 + (180 * res) + 20);
	text.artistName.setString("Artist Name: ");

	text.pieceName.setFont(font);
	text.pieceName.setCharacterSize(20);
	text.pieceName.setFillColor(sf::Color(255, 255, 255, 255));
	text.pieceName.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.pieceName.setPosition((float)1100, (float)85 + (180 * res) + 40);
	text.pieceName.setString("Piece Name: ");

	text.period.setFont(font);
	text.period.setCharacterSize(20);
	text.period.setFillColor(sf::Color(255, 255, 255, 255));
	text.period.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.period.setPosition((float)1100, (float)85 + (180 * res) + 60);
	text.period.setString("Period: ");

	text.completed.setFont(font);
	text.completed.setCharacterSize(20);
	text.completed.setFillColor(sf::Color(255, 255, 255, 255));
	text.completed.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.completed.setPosition((float)1100, (float)85 + (180 * res) + 80);
	text.completed.setString("Year Completed: ");

	text.medium.setFont(font);
	text.medium.setCharacterSize(20);
	text.medium.setFillColor(sf::Color(255, 255, 255, 255));
	text.medium.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.medium.setPosition((float)1100, (float)85 + (180 * res) + 100);
	text.medium.setString("Medium: ");
}

int whichSelected(int x, int y, int curr)
{
	// Check whether x and y lie in any text box's region, if they do, return the text box's ID to become selected
	int lowerx = 50, upperx = 950, lowery, uppery;

	for (int i = 0; i < 5; i++)
	{
		lowery = 250 + (120 * i);
		uppery = 250 + (120 * i) + 50;
		if (x > lowerx && x < upperx && y > lowery && y < uppery) return i;
	}
	
	return curr;
}
 */