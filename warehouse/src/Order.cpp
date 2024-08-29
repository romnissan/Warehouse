#include "../include/Order.h"
#include <string>



    Order:: Order(int id, int customerId, int distance):
         id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING), collectorId(-1), driverId(-1) {
    }

    int Order:: getId() const {
        return id;
    }

    int Order:: getCustomerId() const {
        return customerId;
    }

    int Order:: getCollectorId() const {
        return collectorId;
    }

    int Order:: getDriverId() const {
        return driverId;
    }

    OrderStatus Order:: getStatus() const {
        return status;
    }

    void Order:: setStatus(OrderStatus status) {
        this->status = status;
    }

    void Order:: setCollectorId(int collectorId) {
        this->collectorId = collectorId;
    }

    void Order:: setDriverId(int driverId) {
        this->driverId = driverId;
    }

    const std::string Order:: toString() const {
        return "OrderID: " + std::to_string(id) + " CustomerID: " + std::to_string(customerId) + " OrderStatus: " + getStatusString();
    }
    int Order:: getOrderDistance() const{
        return distance;
    }
    std::string Order:: getStatusString() const{
        if(status == OrderStatus::PENDING)
            return "PENDING";
        if(status == OrderStatus::COLLECTING)
            return "COLLECTING";
        if(status == OrderStatus::DELIVERING)
            return "DELIVERING";
        return "COMPLETED";
    }
    Order* Order:: nullOrder() const {
        return new Order(-1, -1, 0);
    }
