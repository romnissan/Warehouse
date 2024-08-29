#include <string>
#include <vector>
#include "../include/Volunteer.h"

using std::string;
using std::vector;

#define NO_ORDER -1

        CollectorVolunteer:: CollectorVolunteer(int id, const string& name, int coolDown):
        Volunteer(id, name), coolDown(coolDown), timeLeft(0) {
        }

        CollectorVolunteer *CollectorVolunteer::clone() const {
            return new CollectorVolunteer(*this);
        }
        void CollectorVolunteer:: step()  {
            if(isBusy()){
                if(decreaseCoolDown()){
                    completedOrderId = activeOrderId;
                    activeOrderId = NO_ORDER;
                }
            }
        }
        int CollectorVolunteer:: getCoolDown() const{
            return coolDown;
        }
        int CollectorVolunteer:: getTimeLeft() const{
            return timeLeft;
        }
        bool CollectorVolunteer:: decreaseCoolDown(){//Decrease timeLeft by 1,return true if timeLeft=0,false otherwise
            if(timeLeft==0)
                return false;
            else{
                timeLeft--;
                return timeLeft==0;
            }
        }
        bool CollectorVolunteer:: hasOrdersLeft() const {
            return true;
        }
        bool CollectorVolunteer:: canTakeOrder(const Order &order) const {
            return !isBusy();
        }
        void CollectorVolunteer:: acceptOrder(const Order &order) {
            if(!isBusy() && hasOrdersLeft()){
                activeOrderId = order.getId();
                timeLeft = coolDown;
            }
        }
        string CollectorVolunteer:: toString() const {
            string s1 =  "VolunteerID: " + std::to_string(getId()) + "\n";
            if(isBusy()){
                string s2 = "isBusy: True\n";
                string s3 = "OrderID: " + std::to_string(getActiveOrderId())  + "\n";
                string s4 = "timeLeft: " + std::to_string(getTimeLeft()) + "\n";
                return s1 + s2 + s3 + s4 + "OrdersLeft: No Limit\n";
            }
            return s1 + "isBusy: False\n" + "OrderID: None\n" + "timeLeft: None\n" + "OrdersLeft: No Limit\n";
        }
        string CollectorVolunteer:: getType() const {
            return "Collector";
        }
        CollectorVolunteer* CollectorVolunteer:: nullVolunteer() const{
            return new CollectorVolunteer(-1, "nullVolunteer", 0);
        }