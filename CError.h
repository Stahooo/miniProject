#pragma once
#include <stdexcept>
using namespace std;

static const int NO_ERROR = 0;
static const int INVALID_DIMENSION = -1;
static const int INVALID_SIZE = -2;
static const int INVALID_VALUE = -3;
static const int INVALID_FILE = -4;

class CError
{
public:
	CError() { iCode = NO_ERROR; }
	string sGetError() { return "Kod bledu " + iCode; }
	int getError() { return iCode; }
	void setError(int newCode) { iCode = newCode; };
	void check() {
		if (iCode == NO_ERROR) return;
		throw invalid_argument(sGetError());
	}
private:
	int iCode;
};

