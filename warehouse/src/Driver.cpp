#include <string>
#include <vector>
#include "../include/Volunteer.h"

using std::string;
using std::vector;

#define NO_ORDER -1

        DriverVolunteer:: DriverVolunteer(int id, const string& name, int maxDistance, int distancePerStep)
        : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(0){
        }

        DriverVolunteer* DriverVolunteer:: clone() const {
            return new DriverVolunteer(*this);
        }

        int DriverVolunteer:: getDistanceLeft() const{
            return distanceLeft;
        }

        int DriverVolunteer:: getMaxDistance() const{
            return maxDistance;
        }
        int DriverVolunteer:: getDistancePerStep() const{
            return distancePerStep;
        }  
        bool DriverVolunteer:: decreaseDistanceLeft(){
           if(distanceLeft==0)
                return false;
            else{
                distanceLeft = distanceLeft - distancePerStep;
                if(distanceLeft < 0)
                    distanceLeft = 0;
                return distanceLeft == 0;
            }
        } //Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
        bool DriverVolunteer:: hasOrdersLeft() const {
            return true;
        }
        bool DriverVolunteer:: canTakeOrder(const Order &order) const {
            if(!isBusy() && maxDistance >= order.getOrderDistance())
                return true;
            return false;
        } // Signal if the volunteer is not busy and the order is within the maxDistance
        void DriverVolunteer:: acceptOrder(const Order &order) {
            distanceLeft = order.getOrderDistance();
            activeOrderId = order.getId();
        } // Assign distanceLeft to order's distance
        void DriverVolunteer:: step() {
            if (isBusy()) {
                if (decreaseDistanceLeft()) {
                    // Finish the order
                    completedOrderId = activeOrderId;
                    activeOrderId = NO_ORDER;
                }
            }
        }
        string DriverVolunteer:: toString() const {
            string s1 =  "VolunteerID: " + std::to_string(getId()) + "\n";
            if(isBusy()){
                string s2 = "isBusy: True\n";
                string s3 = "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
                string s4 = "distanceLeft: " + std::to_string(getDistanceLeft()) + "\n";
                return s1 + s2 + s3 + s4 + "OrdersLeft: No Limit\n";
            }
            return s1 + "isBusy: False\n" + "OrderID: None\n" + "distanceLeft: None\n" + "OrdersLeft: No Limit\n"; 
        }
        string DriverVolunteer:: getType() const {
            return "Driver";
        }
        DriverVolunteer* DriverVolunteer:: nullVolunteer() const{
            return new DriverVolunteer(-1, "nullVolunteer", 0, 0);
        }