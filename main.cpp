#include <chrono>
#include "Parser.h"
#include "SFML/Graphics.hpp"
#include "RadixSort.h"
#include "HeapSort.h"
#include "sortByRelevance.h"
#include <Windows.h>

using namespace std;

struct output_group 
{
	sf::Text heading;
	sf::Text piece_name;
	sf::Text artist_name;
	sf::Text period;
	sf::Text completed;
	sf::Text medium;
};

void GUI(vector<Piece> & gallery, int rduration, int hduration);
void init_result(output_group& text, int res, sf::Font& font);
int which_selected(int x, int y, int curr);

int main(int argc, char **argv)
{
	vector<Piece> gallery;

	gallery = parse_dataset(600000);
	
	vector<Piece> gallery2 = gallery; // Make a copy of gallery so that we can sort it 2 ways and compare the execution times of quick and heap sort
	
	// Radix sort
	auto rstart = std::chrono::high_resolution_clock::now();
	gallery = radixSort(gallery, 10);
	auto rstop = std::chrono::high_resolution_clock::now();
	auto rduration = std::chrono::duration_cast<std::chrono::microseconds>(rstop-rstart);
	
	// Heap sort
	auto hstart = std::chrono::high_resolution_clock::now();
	gallery2 = heap_sort(gallery2);
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

	// 0->piece_name, 1->artist_name, 2->period, 3->approx.data_completed, 4->medium

	sf::String user_input[5];
	sf::Text user_text[5];
	
	sf::Vertex vert_line[] =
	{
		sf::Vertex(sf::Vector2f(1000,50)),
		sf::Vertex(sf::Vector2f(1000,1000))
	};

	sf::Vertex horz_line1[] =
	{
		sf::Vertex(sf::Vector2f(0,50)),
		sf::Vertex(sf::Vector2f(2000,50))
	};

	sf::Vertex horz_line2[] =
	{
		sf::Vertex(sf::Vector2f(0,80)),
		sf::Vertex(sf::Vector2f(2000,80))
	};

	// Declare regions for text that is not effected by the user

	sf::Text const_text[12];

	const_text[0].setFont(font);
	const_text[0].setFillColor(sf::Color(255, 255, 255, 255));
	const_text[0].setOutlineColor(sf::Color(255, 255, 255, 255));
	const_text[0].setString(sf::String("Art Chart"));
	const_text[0].setCharacterSize(40);
	const_text[0].setPosition(1000 - (const_text[0].findCharacterPos(8).x / 2), 0);

	const_text[1].setFont(font);
	const_text[1].setFillColor(sf::Color(255, 255, 255, 255));
	const_text[1].setOutlineColor(sf::Color(255, 255, 255, 255));
	const_text[1].setString(sf::String("Input"));
	const_text[1].setPosition(500 - (const_text[1].findCharacterPos(4).x / 2), 45);

	const_text[2].setFont(font);
	const_text[2].setFillColor(sf::Color(255, 255, 255, 255));
	const_text[2].setOutlineColor(sf::Color(255, 255, 255, 255));
	const_text[2].setString(sf::String("Output"));
	const_text[2].setPosition(1500 - (const_text[2].findCharacterPos(5).x / 2), 45);

	const_text[3].setFont(font);
	const_text[3].setFillColor(sf::Color(255, 255, 255, 255));
	const_text[3].setOutlineColor(sf::Color(255, 255, 255, 255));
	const_text[3].setString(sf::String("Input the following parameters in the text correspondng text fields."));
	const_text[3].setPosition(25, 80);

	const_text[4].setFont(font);
	const_text[4].setFillColor(sf::Color(255, 255, 255, 255));
	const_text[4].setOutlineColor(sf::Color(255, 255, 255, 255));
	const_text[4].setString(sf::String("Click 'search' to search for a piece and get some similair pieces."));
	const_text[4].setPosition(25, 120);
	
	const_text[10].setFont(font);
	const_text[10].setFillColor(sf::Color(255, 255, 255, 255));
	const_text[10].setOutlineColor(sf::Color(255, 255, 255, 255));
	const_text[10].setString(sf::String("Radix sort sorted " + to_string(gallery.size()) + " elements in " + to_string(rduration) + " microseconds!"));
	const_text[10].setPosition(0, 0);

	const_text[11].setFont(font);
	const_text[11].setFillColor(sf::Color(255, 255, 255, 255));
	const_text[11].setOutlineColor(sf::Color(255, 255, 255, 255));
	const_text[11].setString(sf::String("Heap sort sorted " + to_string(gallery.size()) + " elements in " + to_string(hduration) + " microseconds!"));
	const_text[11].setPosition(2000 - const_text[11].findCharacterPos(const_text[11].getString().getSize()-1).x - 10, 0);


	// Text for handling/directing user input

	sf::String headings[5] =
	{
		"Piece Name:",
		"Artist Name:",
		"Period:",
		"Approx. Data Completed (enter a number):",
		"Medium:"
	};

	for (i = 0; i < 5; i++)
	{
		const_text[i+5].setFont(font);
		const_text[i+5].setFillColor(sf::Color(255, 255, 255, 255));
		const_text[i+5].setOutlineColor(sf::Color(255, 255, 255, 255));
		const_text[i+5].setString(sf::String(headings[i]));
		const_text[i+5].setPosition((float)25, (float)200+(120*i));
	}

	sf::RectangleShape text_box[5];

	for (i = 0; i < 5; i++)
	{
		text_box[i].setSize(sf::Vector2f(900, 50));
		text_box[i].setFillColor(sf::Color(255, 255, 255, 30));
		text_box[i].setPosition((float)50, (float)250 + (120 * i));

		user_text[i].setFont(font);
		user_text[i].setFillColor(sf::Color(225, 225, 20, 255));
		user_text[i].setOutlineColor(sf::Color(225, 225, 20, 255));
		user_text[i].setPosition((float)55, (float)250 + (120 * i));
	}
	
	// Sear

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

	output_group results[5];

	for (i = 0; i < 5; i++)
	{
		init_result(results[i], i, font);
	}

	int selected = 0;
	bool search_clicked = false;

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) window.close();

			if (e.type == sf::Event::TextEntered)
			{
				switch (e.text.unicode)
				{
				case 8: // backspace
					if (user_input[selected].getSize() > 0)
						user_input[selected].erase(user_input[selected].getSize() - 1, 1);
					// do nothing
					break;
				case 9: // tab
					selected = (selected + 1) % 5;
					break;
				case 13: // enter
					search_clicked = true;
					break;
				default:
					if (!(user_text[selected].findCharacterPos(user_input[selected].getSize() - 1).x > 930))
						user_input[selected] += e.text.unicode;
					break;
				}

				user_text[selected].setString(user_input[selected]);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				selected = which_selected(x, y, selected);
				if (x > 250 && x < 750 && y > 900 && y < 950) search_clicked = true;
			}
		}

		window.clear();

		if (search_clicked)
		{
			// Verify no empty input
			int count = 0;
			for (i = 0; i < 5; i++)
				if (user_input[i].toAnsiString() == "") count++;

			// Update text fields to result of searching for the specified value
			if (count == 0)
			{
				// Using the search parameters, make an object with them to generate the corresponding
				Piece p(user_input[0].toAnsiString(), user_input[1].toAnsiString(), user_input[2].toAnsiString(), user_input[4].toAnsiString(), stoi(user_input[3].toAnsiString()));

				vector<Piece> relevant = sortByRelevance(p, gallery);

				// Update each output field with the corresponding data from result
				for (i = 0; i < 5; i++)
				{
					results[i].artist_name.setString("Artist Name: " + relevant[i].artist_name);
					results[i].piece_name.setString("Piece Name: " + relevant[i].piece_name);
					results[i].period.setString("Period: " + relevant[i].time_period);
					results[i].completed.setString("Year Completed: " + to_string(relevant[i].year_finished));
					results[i].medium.setString("Medium: " + relevant[i].medium);
				}

			}
			search_clicked = false;

			

		}

		// Line partitions for formatting
		window.draw(vert_line, 2, sf::Lines);
		window.draw(horz_line1, 2, sf::Lines);
		window.draw(horz_line2, 2, sf::Lines);

		// Highlight the correct selected input field, draw each input field with the user inputted text over it
		for (i = 0; i < 5; i++) 
		{
			text_box[i].setFillColor(sf::Color(255, 255, 255, 30));
			if (i == selected) text_box[i].setFillColor(sf::Color(255, 255, 255, 120));
			window.draw(text_box[i]);
			window.draw(user_text[i]);
		}

		// Draw constant text fields (title, labels, headings, etc.)
		for (i = 0; i < 12; i++)
			window.draw(const_text[i]);

		// Draw the results
		for (i = 0; i < 5; i++)
		{
			window.draw(text_box[i]);
			window.draw(results[i].heading);
			window.draw(results[i].piece_name);
			window.draw(results[i].artist_name);
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

void init_result(output_group &text, int res, sf::Font &font)
{
	// Initializes result outgroup

	string str = "Result " + to_string(res + 1) + ":";
	text.heading.setFont(font);
	text.heading.setCharacterSize(25);
	text.heading.setFillColor(sf::Color(255, 255, 255, 255));
	text.heading.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.heading.setPosition((float)1055, (float)80 + (180 * res));
	text.heading.setString(sf::String(str));

	text.artist_name.setFont(font);
	text.artist_name.setCharacterSize(20);
	text.artist_name.setFillColor(sf::Color(255, 255, 255, 255));
	text.artist_name.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.artist_name.setPosition((float)1100, (float)85 + (180 * res) + 20);
	text.artist_name.setString("Artist Name: ");

	text.piece_name.setFont(font);
	text.piece_name.setCharacterSize(20);
	text.piece_name.setFillColor(sf::Color(255, 255, 255, 255));
	text.piece_name.setOutlineColor(sf::Color(255, 255, 255, 255));
	text.piece_name.setPosition((float)1100, (float)85 + (180 * res) + 40);
	text.piece_name.setString("Piece Name: ");

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

int which_selected(int x, int y, int curr)
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