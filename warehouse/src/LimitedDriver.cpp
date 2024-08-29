#include <string>
#include <vector>
#include "../include/Volunteer.h"

using std::string;
using std::vector;

#define NO_ORDER -1

        LimitedDriverVolunteer:: LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders)
        : DriverVolunteer(id,name,maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders){
        }
        void LimitedDriverVolunteer:: step(){
            if(isBusy()){
                if(DriverVolunteer:: decreaseDistanceLeft()){
                    completedOrderId = activeOrderId;
                    activeOrderId = NO_ORDER;
                }            
            }
        }
        LimitedDriverVolunteer *LimitedDriverVolunteer:: clone() const{
            return new LimitedDriverVolunteer(*this);
        }
        int LimitedDriverVolunteer:: getMaxOrders() const{
            return maxOrders;
        }
        int LimitedDriverVolunteer:: getNumOrdersLeft() const{
            return ordersLeft;
        }
        bool LimitedDriverVolunteer:: hasOrdersLeft() const{
            return ordersLeft > 0;
        }
        bool LimitedDriverVolunteer:: canTakeOrder(const Order &order) const{
            return (DriverVolunteer::canTakeOrder(order) && hasOrdersLeft());
        } // Signal if the volunteer is not busy, the order is within the maxDistance.
        void LimitedDriverVolunteer:: acceptOrder(const Order &order){
            DriverVolunteer::acceptOrder(order);
            ordersLeft--;
        } // Assign distanceLeft to order's distance and decrease ordersLeft
        string LimitedDriverVolunteer:: toString() const{
            string s1 =  "VolunteerID: " + std::to_string(getId()) + "\n";
            string s5 = "OrdersLeft: " + std::to_string(ordersLeft) + "\n";
            if(isBusy()){
                string s2 = "isBusy: True\n";
                string s3 = "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
                string s4 = "distanceLeft: " + std::to_string(getDistanceLeft()) + "\n";
                return s1 + s2 + s3 + s4 + s5;
            }
            return s1 + "isBusy: False\n" + "OrderID: None\n" + "distanceLeft: None\n" + s5;
        }

        string LimitedDriverVolunteer:: getType() const{
            return "LimitedDriver";
        }
        LimitedDriverVolunteer* LimitedDriverVolunteer:: nullVolunteer() const{
            return new LimitedDriverVolunteer(-1, "nullVolunteer", 0, 0, 0);
        }
