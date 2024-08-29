#include <string>
#include <vector>
using std::string;
using std::vector;
#include "../include/Customer.h"


        CivilianCustomer:: CivilianCustomer(int id, const string& name, int locationDistance, int maxOrders):
        Customer(id, name, locationDistance, maxOrders) {}
                CivilianCustomer *CivilianCustomer:: clone() const{
                return new CivilianCustomer(*this);
        }
        CivilianCustomer *CivilianCustomer:: nullCustomer() const{
                return new CivilianCustomer(-1, "Default Customer", 0, 0);
        }