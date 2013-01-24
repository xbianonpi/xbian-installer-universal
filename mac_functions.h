#ifndef MAC_FUNCTIONS_H
#define MAC_FUNCTIONS_H

#include "mac_disk.h"
#include "vector"

using namespace std;

class mac_functions
{
public:
    mac_functions();
    vector<mac_disk> mac_GetDisks();
};

#endif // MAC_FUNCTIONS_H
