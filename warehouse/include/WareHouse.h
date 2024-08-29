#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"
class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        //rule of 5
        ~WareHouse();
        WareHouse(const WareHouse& other);
        WareHouse& operator=(const WareHouse& other);
        WareHouse(WareHouse&& other) noexcept;
        WareHouse& operator=(WareHouse&& other) noexcept;

        void start();
        void addOrder(Order* order);
        // addAction(BaseAction& action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();
        void addCustomer(Customer* customer);
        void setCustomerCounter(int num);
        int getCustomerCounter();
        int getVolunteerCounter();
        void setVolunteerCounter(int num);
        vector<Order*>& getPendingOrders();
        vector<Order*>& getInProcessOrders();
        vector<Order*>& getCompletedOrders();
        vector<Volunteer*> getVolunteers();
        bool isCustomerExist(int customerId);
        bool isOrderExist(int orderId);
        int getOrderCounter();
        void setOrderCounter(int num);
        void eraseFromPendingOrders(Order* order);
        void eraseFromInProcessOrders(Order* order);
        void eraseFromCompletedOrders(Order* order);
        void eraseFromVolunteers(Volunteer* volunteer);
        void addToInProcessOrders(Order* order);
        void addToCompletedOrders(Order* order);
        bool isVolunteerExist(int IDvolunteer);


    private:
        bool isOpen;
        int volunteerCounter; //For assigning unique volunteer IDs
        int customerCounter; //For assigning unique customer IDs 
        int orderCounter; //For assigning unique order IDs
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;

};