#include "Parser.h"

using namespace std;

int main(int argc, char **argv)
{
	vector<Piece> gallery = parse_dataset(std::stoi(argv[1]));
	cout << "Gallery size after parsing " << argv[1] << " entries: " << gallery.size() << endl;
    return 0;
}
