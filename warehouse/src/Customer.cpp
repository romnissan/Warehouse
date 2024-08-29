#include "../include/Customer.h"

// Customer constructor
Customer:: Customer(int id, const std::string& name, int locationDistance, int maxOrders) :
    id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders), ordersId() {}

const std::string& Customer:: getName() const {
    return name;
}

int Customer:: getId() const {
    return id;
}

int Customer:: getCustomerDistance() const {
    return locationDistance;
}

int Customer:: getMaxOrders() const {
    return maxOrders;
}

int Customer:: getNumOrders() const {
    return ordersId.size();
}

bool Customer:: canMakeOrder() const {
    return ordersId.size() < static_cast<std::vector<int>::size_type>(maxOrders);
}

const std::vector<int>& Customer:: getOrdersids() const {
    return ordersId;
}

int Customer:: addOrder(int orderId) {
    if (canMakeOrder()) {
        ordersId.push_back(orderId);
        return orderId;
    } else {
        return -1;
    }
}

