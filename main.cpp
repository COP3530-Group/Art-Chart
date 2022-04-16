#include "Parser.h"

using namespace std;

int main(int argc, char **argv)
{
	vector<Piece> gallery;
	if (argc == 1) {
		gallery = parse_dataset(600000);
		cout << "Gallery size after parsing 600,000 entries: " << gallery.size() << endl;
	}
	else {
		gallery = parse_dataset(stoi(argv[1]));
		cout << "Gallery size after parsing " << argv[1] << " entries: " << gallery.size() << endl;
	}
	
    return 0;
}
