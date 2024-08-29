#include "../include/Action.h"
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;
extern WareHouse* backup;


        BaseAction:: BaseAction():
         errorMsg(""), status(ActionStatus::COMPLETED){
        }
        ActionStatus BaseAction:: getStatus() const{
            return status;
        }

        void BaseAction:: complete(){
            status = ActionStatus::COMPLETED;
        }
        void BaseAction:: error(string errorMsg){
            status = ActionStatus::ERROR;
            cout << getActionError(errorMsg) << endl;
        }
        string BaseAction:: getErrorMsg() const{
            return "Error: the action cannot be done";
        }
        string BaseAction:: getActionError(string errorMsg) const{
            return errorMsg;
        }
        



/////////////////////////////////////////  SIMULATE_STEP  //////////////////////////////////////////////////////////

        SimulateStep:: SimulateStep(int numOfSteps):
        numOfSteps(numOfSteps), ordersToErase(), volunteersToErase(){
        }
        void  SimulateStep:: act(WareHouse &wareHouse) {
            for(int i=0; i<numOfSteps; i++){
                //step 1
                for(Order *order: wareHouse.getPendingOrders()){
                    if(order->getStatus() == OrderStatus:: PENDING){
                        for(Volunteer* volunteer: wareHouse.getVolunteers()){
                            if (volunteer->getType() == "Collector" || volunteer->getType() == "limitedCollector"){
                                if(volunteer->canTakeOrder(*order)){
                                    volunteer->acceptOrder(*order);
                                    ordersToErase.push_back(order);
                                    wareHouse.addToInProcessOrders(order);
                                    order->setCollectorId(volunteer->getId());
                                    order->setStatus(OrderStatus::COLLECTING);
                                    break;
                                }
                            }
                        }
                    }
                    else {
                        for(Volunteer* volunteer: wareHouse.getVolunteers()){
                            if (volunteer->getType() == "Driver" || volunteer->getType() == "limitedDriver"){
                                if(volunteer->canTakeOrder(*order)){
                                    volunteer->acceptOrder(*order);
                                    ordersToErase.push_back(order);
                                    wareHouse.addToInProcessOrders(order);
                                    order->setDriverId(volunteer->getId());
                                    order->setStatus(OrderStatus::DELIVERING);
                                    break;
                                }
                            }
                        }
                    }
                }
                for (Order* order : ordersToErase) {
                    wareHouse.eraseFromPendingOrders(order);
                }
                //step 2
                for(Volunteer* volunteer: wareHouse.getVolunteers()){
                    if (volunteer->isBusy()){
                        Order* activeOrder = &wareHouse.getOrder(volunteer->getActiveOrderId());
                        volunteer->step();
                        //step 3
                        if(!(volunteer->isBusy())){     //volunteer just finished
                            if (volunteer->getType() == "Collector" || volunteer->getType() == "limitedCollector"){
                                wareHouse.eraseFromInProcessOrders(activeOrder);
                                wareHouse.addOrder(activeOrder);
                                if(volunteer->getType() == "limitedCollector"){
                                    if(!static_cast<LimitedCollectorVolunteer*>(volunteer)->hasOrdersLeft()){
                                        volunteersToErase.push_back(volunteer);
                                        delete volunteer;

                                    }
                                }
                            }
                            else{       // volunteer == driver/limitedDriver
                                wareHouse.eraseFromInProcessOrders(activeOrder);
                                activeOrder->setStatus(OrderStatus::COMPLETED);
                                wareHouse.addToCompletedOrders(activeOrder);
                                //step 4
                                if(volunteer->getType() == "limitedDriver"){       
                                    if(!static_cast<LimitedDriverVolunteer*>(volunteer)->hasOrdersLeft()){
                                        volunteersToErase.push_back(volunteer);
                                        delete volunteer;
                                    }
                                }
                            }
                        }
                    }
                }
            for (Volunteer* volunteer : volunteersToErase) {
                    wareHouse.eraseFromVolunteers(volunteer);
            }    
            complete();
            }
        }
        
        std::string  SimulateStep:: toString() const {
            return "simulateStep " + to_string(numOfSteps);
        }
        SimulateStep* SimulateStep:: clone() const {
            return new SimulateStep(*this);
        }

        

////////////////////////////////////////  ADD_ORDER  ///////////////////////////////////////////////////////////

        AddOrder:: AddOrder(int id)
        : customerId(id){
        }
        void AddOrder:: act(WareHouse &wareHouse) {
            if(wareHouse.isCustomerExist(customerId)){
                Customer& customer = wareHouse.getCustomer(customerId);
                if(customer.canMakeOrder()){
                    Order* order = new Order(wareHouse.getOrderCounter(), customerId, customer.getCustomerDistance());
                    wareHouse.setOrderCounter(wareHouse.getOrderCounter()+1);
                    wareHouse.addOrder(order);
                    customer.addOrder(order->getId());
                    complete();
                }
                 else error("Error: Cannot place this order");
            }
            else error("Error: Cannot place this order");
        }
        string AddOrder:: toString() const {
            return "order " + std::to_string(customerId);
        }
        AddOrder* AddOrder:: clone() const {
            return new AddOrder(*this);
        }
    


///////////////////////////////////  ADD_CUSTOMER  //////////////////////////////////////////////////////////////////

        AddCustomer:: AddCustomer(const string& customerName, const string& customerType, int distance, int maxOrders)
               : customerName(customerName),customerType(getCustomerTypeFromString(customerType)), distance(distance), maxOrders(maxOrders) {
            }
        void AddCustomer:: act(WareHouse &wareHouse) {
            Customer* customer;
            if(customerType == CustomerType::Civilian)
                customer = new CivilianCustomer(wareHouse.getCustomerCounter(),customerName, distance, maxOrders);
            else customer = new SoldierCustomer(wareHouse.getCustomerCounter(),customerName, distance, maxOrders);
            wareHouse.addCustomer(customer);
            wareHouse.setCustomerCounter(wareHouse.getCustomerCounter()+1);
            complete();
        }
        AddCustomer* AddCustomer:: clone() const {
            return new AddCustomer(*this);
        }
        string AddCustomer:: toString() const {
            if(customerType == (CustomerType::Soldier))
                return "customer " + customerName + " Soldier " + std::to_string(distance) + " " + std::to_string(maxOrders);
            else return "customer " + customerName + " Civilian " + std::to_string(distance) + " " + std::to_string(maxOrders);
        }
    CustomerType AddCustomer:: getCustomerTypeFromString(const string& type) const {
        if (type == "Soldier" || type == "Soldier") {
            return CustomerType::Soldier;
        } else {
            return CustomerType::Civilian;
        }
    }



////////////////////////////  PRINT_ORDER_STATUS  ///////////////////////////////////////////////////////////////////////

        PrintOrderStatus:: PrintOrderStatus(int id): orderId(id){
        }
        void PrintOrderStatus:: act(WareHouse &wareHouse) {
           if (!wareHouse.isOrderExist(orderId)) {
                error("Order doesn't exist");
            }
            else{
                Order& order = wareHouse.getOrder(orderId);
                std:: cout << "OrderId: " << order.getId() << endl;
                std:: cout << "OrderStatus: " << (order.getStatusString()) << endl;
                std:: cout << "CustomerID: " << order.getCustomerId() << endl;
                if(order.getCollectorId() != -1)
                    std:: cout << "Collector: " << order.getCollectorId() << endl;
                else std:: cout << "Collector: None" << endl;
                if(order.getDriverId() != -1)
                    std:: cout << "Driver: " << order.getDriverId() << endl;
                else std:: cout << "Driver: None" << endl;
                complete();
            }
        }
        PrintOrderStatus* PrintOrderStatus:: clone() const {
            return new PrintOrderStatus(*this);
        }
        string PrintOrderStatus:: toString() const {
            return "orderStatus " + std::to_string(orderId);
        }  



/////////////////////////////////  PRINT_CUSTOMER_STATUS  ////////////////////////////////////////////////////////////////////

        PrintCustomerStatus:: PrintCustomerStatus(int customerId): customerId(customerId){
        }
        void PrintCustomerStatus:: act(WareHouse &wareHouse) {
            if(!wareHouse.isCustomerExist(customerId))
                error("Customer doesn't exist");
            else{
                 Customer& customer = wareHouse.getCustomer(customerId); 
                 std:: cout << "CustomerID: " + std::to_string(customerId) << endl;
                 for(int orderId:customer.getOrdersids()){
                    Order* order = &wareHouse.getOrder(orderId);
                    cout << "OrderID: " + std::to_string(orderId) << endl;
                    cout << "OrderStatus: " + order->getStatusString() << endl;
                }
                int tmp = customer.getMaxOrders() - customer.getNumOrders();
                std::cout << "numOrdersLeft: " << tmp << endl;
                complete();
            }
        }
        PrintCustomerStatus* PrintCustomerStatus::clone() const {
            return new PrintCustomerStatus(*this);
        }
        string PrintCustomerStatus:: toString() const {
            return "customerStatus " + std::to_string(customerId);
        }



/////////////////////////////////  PRINT_VOLUNTEER_STATUS  //////////////////////////////////////////////////////////////////

        PrintVolunteerStatus:: PrintVolunteerStatus(int id): volunteerId(id){
        }
        void PrintVolunteerStatus:: act(WareHouse &wareHouse) {
            if(!wareHouse.isVolunteerExist(volunteerId))
                error("Volunteer doesn't exist");
            else {            
                Volunteer* volunteer = &wareHouse.getVolunteer(volunteerId);
                cout << volunteer->toString();
                complete();
            }
        }
        PrintVolunteerStatus *PrintVolunteerStatus:: clone() const {
            return new PrintVolunteerStatus(*this);
        }
        string PrintVolunteerStatus:: toString() const {
            return "volunteerStatus " + std::to_string(volunteerId);
        }



/////////////////////////////////  PRINT_ACTION_LOG  ////////////////////////////////////////////////////////////////////

        PrintActionsLog:: PrintActionsLog(): BaseAction(){
        }
        void PrintActionsLog:: act(WareHouse &wareHouse) {
            vector<BaseAction*> actions = wareHouse.getActions();
            for(BaseAction *action: actions){
                cout << action->toString() + " ";
                if(action->getStatus() == ActionStatus::COMPLETED)
                    cout << "COMPLETED\n";
                else cout << "ERROR\n";
            }
            complete();
        }
        PrintActionsLog* PrintActionsLog:: clone() const {
            return new PrintActionsLog(*this);
        }
        string PrintActionsLog:: toString() const {
            return "log";
        }



/////////////////////////////////  CLOSE  ////////////////////////////////////////////////////////////////////

        Close:: Close(){};
        void Close:: act(WareHouse &wareHouse) {
            wareHouse.close();
        }
        Close *Close:: clone() const {
            return new Close(*this);
        }
        string Close:: toString() const {
            return "close";
        }



/////////////////////////////////  BACK_UP  ////////////////////////////////////////////////////////////////////

        BackupWareHouse:: BackupWareHouse(){};
        void BackupWareHouse:: act(WareHouse &wareHouse) {
            if(backup != nullptr)
                delete backup;
            backup = new WareHouse(wareHouse);
            complete();
        }
        BackupWareHouse* BackupWareHouse:: clone() const {
            return new BackupWareHouse(*this);
        }
        string BackupWareHouse:: toString() const {
            return "backup";
        }



/////////////////////////////////  RESTORE  ////////////////////////////////////////////////////////////////////

        RestoreWareHouse:: RestoreWareHouse(){};
        void RestoreWareHouse:: act(WareHouse &wareHouse) {
            if(backup == nullptr)
                error("No backup available");
            else{
                wareHouse = *backup;
                complete();
            }
        }
        RestoreWareHouse* RestoreWareHouse:: clone() const {
            return new RestoreWareHouse(*this);
        }
        string RestoreWareHouse:: toString() const {
            return "restore";
        }