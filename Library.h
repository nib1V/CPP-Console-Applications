#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <cmath>

using namespace std;


inline void error(const string& errormessage)
{
    throw runtime_error(errormessage);
}