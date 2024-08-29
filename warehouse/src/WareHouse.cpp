#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
#include "../include/WareHouse.h"



class BaseAction;
class Volunteer;

        WareHouse:: WareHouse(const string &configFilePath)
        :   isOpen(true), 
            volunteerCounter(0),
            customerCounter(0), 
            orderCounter(0),
            actionsLog(),
            volunteers(),
            pendingOrders(),
            inProcessOrders(),
            completedOrders(),
            customers(){
            std::ifstream inputFile(configFilePath);
            if(!inputFile.is_open()){
                std::cout <<"File opening error" << std::endl;
            }
            
            string line;
            while(getline(inputFile,line)){
                istringstream iss(line);
                string role;
                if(iss >> role){
                    if(role == "customer" || role == "Customer"){
                        string name,type;
                        int distance,maxorders;
                        Customer* customer;
                        if(iss >> name >> type >> distance >> maxorders){
                            if(type == "Civilian" || type == "civilian"){
                                customer = new CivilianCustomer(customerCounter,name,distance,maxorders);
                                customerCounter++;
                                customers.push_back(customer);
                            }
                            else if(type == "Soldier" || type == "soldier"){
                                customer = new SoldierCustomer(customerCounter,name,distance,maxorders);
                                customerCounter++;
                                customers.push_back(customer);
                            }
                            else std::cout<< "illegal customer type "<< type <<std::endl ;
                        }
                    }
                    else if(role == "volunteer" || role == "Volunteer"){
                        std::string name,type;
                        if(iss >> name >> type){
                            if(type == "collector" || type == "Collector"){
                                int cooldown;
                                if(iss >> cooldown){
                                    CollectorVolunteer* cvol = new CollectorVolunteer(volunteerCounter,name,cooldown);
                                    volunteerCounter++;
                                    volunteers.push_back(cvol);
                                }
                            }
                            else if(type == "limited_collector"|| type == "Limited_Collector"){
                                int cooldown,maxorders;
                                if(iss >> cooldown >> maxorders){
                                    LimitedCollectorVolunteer* lcvol = new LimitedCollectorVolunteer(volunteerCounter,name,cooldown,maxorders);
                                    volunteerCounter++;
                                    volunteers.push_back(lcvol);
                                }
                            }
                            else if(type == "driver"||type == "Driver"){
                                int maxdistance,distanceperstep;
                                if(iss >> maxdistance >> distanceperstep){
                                    DriverVolunteer* driverVolunteer = new DriverVolunteer(volunteerCounter,name,maxdistance,distanceperstep);
                                    volunteerCounter++;
                                    volunteers.push_back(driverVolunteer);
                                }
                            }
                            else if(type == "limited_driver"|| type == "Limited_Driver"){
                                int maxdistance,distanceperstep,maxorders;
                                if(iss >> maxdistance >> distanceperstep >> maxorders){
                                    LimitedDriverVolunteer* limitedDriverVolunteer = new LimitedDriverVolunteer(volunteerCounter,name,maxdistance,distanceperstep,maxorders);
                                    volunteerCounter++;
                                    volunteers.push_back(limitedDriverVolunteer);
                                }
                            }
                        }
                    }
                }
            }
            inputFile.close();
        }
        void WareHouse:: start(){
            open();
            while(isOpen){
                string sentence;
                getline(cin, sentence);
                istringstream iss(sentence);
                string firstWord;
                string secondWord;
                if(iss >> firstWord){
                    if(firstWord == "close"){
                        Close* close = new Close();
                        close->act(*this);
                        delete close;
                    }
                    else if(firstWord == "log"){
                            PrintActionsLog* log = new PrintActionsLog();
                            log->act(*this);
                            actionsLog.push_back(log);
                        }
                        else if(firstWord == "backup"){
                            BackupWareHouse* backup = new BackupWareHouse();
                            backup->act(*this);
                            actionsLog.push_back(backup);
                        }
                        else if(firstWord == "restore"){
                            RestoreWareHouse* restore = new RestoreWareHouse();
                            restore->act(*this);
                            actionsLog.push_back(restore);
                        }
                        else if(iss >> secondWord){
                        if(firstWord == "step"){
                            SimulateStep* action = new SimulateStep(stoi(secondWord));
                            action->act(*this);
                            actionsLog.push_back(action);
                        }
                        else if(firstWord == "order"){
                            AddOrder* order = new AddOrder(stoi(secondWord));
                            order->act(*this);
                            actionsLog.push_back(order);
                        }
                        else if(firstWord == "orderStatus"){
                            PrintOrderStatus* orderStatus = new PrintOrderStatus(stoi(secondWord));
                            orderStatus->act(*this);
                            actionsLog.push_back(orderStatus);
                        }
                        else if(firstWord == "customerStatus"){
                            PrintCustomerStatus* customerStatus = new PrintCustomerStatus(stoi(secondWord));
                            customerStatus->act(*this);
                            actionsLog.push_back(customerStatus);
                        }
                        else if(firstWord == "volunteerStatus"){
                            PrintVolunteerStatus* volunteerStatus = new PrintVolunteerStatus(stoi(secondWord));
                            volunteerStatus->act(*this);
                            actionsLog.push_back(volunteerStatus);
                        }
                        
                        else if(firstWord == "customer"){
                            string thirdWord;
                            string forthWord;
                            string fifthWord;
                            iss >> thirdWord;
                            iss >> forthWord;
                            iss >> fifthWord;
                            AddCustomer* addCustomer = new AddCustomer(secondWord, thirdWord, stoi(forthWord), stoi(fifthWord));
                            addCustomer->act(*this);
                            actionsLog.push_back(addCustomer);
                        }
                    }
                }
            }
        }
        void WareHouse:: addOrder(Order* order){
            pendingOrders.push_back(order);
        }

        vector<Volunteer*> WareHouse:: getVolunteers(){
            return volunteers;
        }
        const vector<BaseAction*>& WareHouse:: getActions() const{
            return actionsLog;
        }
        void WareHouse:: close(){
            for(Order* order: pendingOrders){
                cout << order->toString();
                cout << "\n";
            }
            for(Order* order: inProcessOrders){
                cout << order->toString();
                cout << "\n";
            }
            for(Order* order: completedOrders){
                cout << order->toString();
                cout << "\n";
            }
            isOpen = false;
        }
        void WareHouse:: open(){
            isOpen = true;
            cout << "Warehouse is open!" << endl;
        }
        void WareHouse:: addCustomer(Customer* customer){
            customers.push_back(customer);
        }
        void WareHouse:: setCustomerCounter(int num){
            customerCounter = num;
        }
        int WareHouse:: getCustomerCounter(){
            return customerCounter;
        }
        int WareHouse:: getVolunteerCounter(){
            return volunteerCounter;
        }
        void WareHouse:: setVolunteerCounter(int num){
            volunteerCounter = num;
        }
        int WareHouse:: getOrderCounter(){
            return orderCounter;
        }
        void WareHouse:: setOrderCounter(int num){
            orderCounter = num;
        }
        vector<Order*>& WareHouse:: getPendingOrders(){
            return pendingOrders;
        }
        bool WareHouse:: isCustomerExist(int customerId){
            for(Customer* customer: customers){
                if(customer->getId() == customerId)
                    return true;
            }
            return false;
        }
        Customer& WareHouse:: getCustomer(int customerId) const{
            for(Customer* customer: customers){
                if(customer->getId() == customerId)
                    return *customer;
            }
            return *customers.front();
        }

        Order& WareHouse:: getOrder(int orderId) const{
            for(Order* order: pendingOrders)
                if(order->getId() == orderId)
                    return *order;
            for(Order* order: inProcessOrders)
                if(order->getId() == orderId)
                    return *order;
            for(Order* order: completedOrders)
                if(order->getId() == orderId)
                    return *order;
            return *pendingOrders.front();
        }
        bool WareHouse:: isOrderExist(int orderId){
            for(Order* order: pendingOrders)
                if(order->getId() == orderId)
                    return true;
            for(Order* order: inProcessOrders)
                if(order->getId() == orderId)
                    return true;
            for(Order* order: completedOrders)
                if(order->getId() == orderId)
                    return true;
            return false;
        }
        Volunteer& WareHouse:: getVolunteer(int volunteerId) const{
            for(Volunteer* volunteer: volunteers){
                if(volunteer->getId() == volunteerId)
                    return *volunteer;
            }
            return *volunteers.front();
        }
        void WareHouse:: eraseFromPendingOrders(Order* order){
            auto it = find(pendingOrders.begin(), pendingOrders.end(), order);
                // If found, erase the element
                if (it != pendingOrders.end()) {
                    pendingOrders.erase(it); 
                }
            }
        void WareHouse:: eraseFromInProcessOrders(Order* order){
            auto it = find(inProcessOrders.begin(), inProcessOrders.end(), order);
                // If found, erase the element
                if (it != inProcessOrders.end()) {
                    inProcessOrders.erase(it); 
                }
            }
        void WareHouse:: eraseFromCompletedOrders(Order* order){
            auto it = find(completedOrders.begin(), completedOrders.end(), order);
                // If found, erase the element
                if (it != completedOrders.end()) {
                    completedOrders.erase(it); 
                }
            }

        void WareHouse:: eraseFromVolunteers(Volunteer* volunteer){
            auto it = find(volunteers.begin(), volunteers.end(), volunteer);
                // If found, erase the element
                if (it != volunteers.end()) {
                    volunteers.erase(it); 
                }
        }

        void WareHouse:: addToInProcessOrders(Order* order){
            inProcessOrders.push_back(order);
        }
        void WareHouse:: addToCompletedOrders(Order* order){
            completedOrders.push_back(order);
        }
        bool WareHouse:: isVolunteerExist(int volunteerId){
            for(Volunteer* volunteer: volunteers){
                if(volunteer->getId() == volunteerId)
                    return true;
            }
            return false;
        }

        // Destructor
        WareHouse::~WareHouse() {
            for (BaseAction* action : actionsLog) {
                delete action;
            }
            for (Volunteer* volunteer : volunteers) {
                delete volunteer;
            }
            for (Order* order : pendingOrders) {
                delete order;
            }
            for (Order* order : inProcessOrders) {
                delete order;
            }
            for (Order* order : completedOrders) {
                delete order;
            }
            for (Customer* customer : customers) {
                delete customer;
            }
        }

        // Copy Constructor
        WareHouse::WareHouse(const WareHouse& other)
        :   isOpen(other.isOpen), 
            volunteerCounter(other.volunteerCounter),
            customerCounter(other.customerCounter), 
            orderCounter(other.orderCounter),
            actionsLog(),
            volunteers(),
            pendingOrders(),
            inProcessOrders(),
            completedOrders(),
            customers()
            {
            for (BaseAction* action : other.actionsLog) {
                actionsLog.push_back(action->clone());
            }
            for (Volunteer* volunteer : other.volunteers) {
                volunteers.push_back(volunteer->clone());
            }
            for (Order* order : other.pendingOrders) {
                pendingOrders.push_back(new Order(*order));
            }
            for (Order* order : other.inProcessOrders) {
                inProcessOrders.push_back(new Order(*order));
            }
            for (Order* order : other.completedOrders) {
                completedOrders.push_back(new Order(*order));
            }
            for (Customer* customer : other.customers) {
                customers.push_back(customer->clone());
            }
        }

        // Copy Assignment Operator
        WareHouse& WareHouse::operator=(const WareHouse& other) {
            if (this != &other) {
                for (auto action : actionsLog) {
                    delete action;
                }
                actionsLog.clear();
                for (auto order : pendingOrders) {
                    delete order;
                }
                pendingOrders.clear();
                for (auto order : inProcessOrders) {
                    delete order;
                }
                inProcessOrders.clear();
                for (auto order : completedOrders) {
                    delete order;
                }
                completedOrders.clear();
                for (auto customer : customers) {
                    delete customer;
                }
                customers.clear();
                isOpen = other.isOpen;
                customerCounter = other.customerCounter;
                volunteerCounter = other.volunteerCounter;
                orderCounter = other.orderCounter;
                for (auto action : other.actionsLog) {
                    actionsLog.push_back(action->clone());
                }
                for (auto order : other.pendingOrders) {
                    pendingOrders.push_back(new Order(*order));
                }
                for (auto order : other.inProcessOrders) {
                    inProcessOrders.push_back(new Order(*order));
                }
                for (auto order : other.completedOrders) {
                    completedOrders.push_back(new Order(*order));
                }

                for (auto volunteer : volunteers) {
                    delete volunteer;
                }
                volunteers.clear();
                for (auto volunteer : other.volunteers) {
                    volunteers.push_back(volunteer->clone());
                }

                for (auto customer : customers) {
                    delete customer;
                }
                customers.clear();
                for (auto customer : other.customers) {
                    customers.push_back(customer->clone());
                }
            }
            return *this;
        }


        // Move Constructor
        WareHouse::WareHouse(WareHouse&& other) noexcept
            : isOpen(std::move(other.isOpen)),
            volunteerCounter(std::move(other.volunteerCounter)),
            customerCounter(std::move(other.customerCounter)),
            orderCounter(std::move(other.orderCounter)),
            actionsLog(std::move(other.actionsLog)),
            volunteers(std::move(other.volunteers)),
            pendingOrders(std::move(other.pendingOrders)),
            inProcessOrders(std::move(other.inProcessOrders)),
            completedOrders(std::move(other.completedOrders)),
            customers(std::move(other.customers)) {
            other.isOpen = false;
            other.volunteerCounter = 0;
            other.customerCounter = 0;
            other.orderCounter = 0;
            for (BaseAction* action : other.actionsLog) {
                delete action; 
            }
            other.actionsLog.clear();
            for (Volunteer* volunteer : other.volunteers) {
                delete volunteer; 
            }
            other.volunteers.clear();
            for (Order* order : other.pendingOrders) {
                delete order; 
            }
            other.pendingOrders.clear();
            for (Order* order : other.inProcessOrders) {
                delete order; 
            }
            other.inProcessOrders.clear();
            for (Order* order : other.completedOrders) {
                delete order; 
            }
            other.completedOrders.clear();
            for (Customer* customer : other.customers) {
                delete customer; 
            }
            other.customers.clear();
        }

        // Move Assignment Operator
        WareHouse& WareHouse::operator=(WareHouse&& other) noexcept {
            if (this != &other) {
                isOpen = std::move(other.isOpen);
                customerCounter = std::move(other.customerCounter);
                volunteerCounter = std::move(other.volunteerCounter);
                orderCounter = std::move(other.orderCounter);
                actionsLog = std::move(other.actionsLog);
                volunteers = std::move(other.volunteers);
                pendingOrders = std::move(other.pendingOrders);
                inProcessOrders = std::move(other.inProcessOrders);
                completedOrders = std::move(other.completedOrders);
                customers = std::move(other.customers);
                other.isOpen = false;
                other.customerCounter = 0;
                other.volunteerCounter = 0;
                other.orderCounter = 0;
                other.actionsLog.clear();
                other.volunteers.clear();
                other.pendingOrders.clear();
                other.inProcessOrders.clear();
                other.completedOrders.clear();
                other.customers.clear();
            }
            return *this;
        }