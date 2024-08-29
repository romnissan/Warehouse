#include <string>
#include <vector>
using std::string;
using std::vector;
#include "../include/Customer.h"

        SoldierCustomer:: SoldierCustomer(int id, const string& name, int locationDistance, int maxOrders):
        Customer(id, name, locationDistance, maxOrders) {}
        SoldierCustomer *SoldierCustomer:: clone() const{
                return new SoldierCustomer(*this);
        }
        SoldierCustomer *SoldierCustomer:: nullCustomer() const{
                return new SoldierCustomer(-1, "Default Customer", 0, 0);
        }