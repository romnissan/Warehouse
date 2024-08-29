#include <string>
#include <vector>
#include "../include/Order.h"
#include "../include/Volunteer.h"

using std::string;
using std::vector;

#define NO_ORDER -1


        LimitedCollectorVolunteer:: LimitedCollectorVolunteer(int id, const string& name, int coolDown ,int maxOrders)
        : CollectorVolunteer (id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders){};
        LimitedCollectorVolunteer* LimitedCollectorVolunteer:: clone() const{
            return new LimitedCollectorVolunteer (*this);
        }
        void LimitedCollectorVolunteer:: step(){
            if(isBusy()){
                if(CollectorVolunteer:: decreaseCoolDown()){
                    completedOrderId = activeOrderId;
                    activeOrderId = NO_ORDER;
                }            
            }
        }
        bool LimitedCollectorVolunteer:: hasOrdersLeft() const{
            return ordersLeft > 0;
        }
        bool LimitedCollectorVolunteer:: canTakeOrder(const Order &order) const{
            return (hasOrdersLeft() && !isBusy());
        }
        void LimitedCollectorVolunteer:: acceptOrder(const Order &order){
            CollectorVolunteer::acceptOrder(order);
            ordersLeft--;
        }
        int LimitedCollectorVolunteer:: getMaxOrders() const{
            return maxOrders;
        }
        int LimitedCollectorVolunteer:: getNumOrdersLeft() const{
            return ordersLeft;
        }
        string LimitedCollectorVolunteer:: toString() const{
            string s1 =  "VolunteerID: " + std::to_string(getId()) + "\n";
            string s5 = "OrdersLeft: " + std::to_string(ordersLeft) + "\n";
            if(isBusy()){
                string s2 = "isBusy: True\n";
                string s3 = "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
                string s4 = "timeLeft: " + std::to_string(getTimeLeft()) + "\n";
                return s1 + s2 + s3 + s4 + s5; 
            }
            return s1 + "isBusy: False\n" + "OrderID: None\n" + "timeLeft: None\n" + s5;
        }
        string LimitedCollectorVolunteer:: getType() const{
            return "limitedCollector";
        }
        LimitedCollectorVolunteer* LimitedCollectorVolunteer:: nullVolunteer() const{
            return new LimitedCollectorVolunteer(-1, "nullVolunteer", 0, 0);
        }
    