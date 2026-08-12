//
// Created by Pavan Durga Nivas Maddarapu on 12/08/26.
//

#ifndef UNTITLED1_ORDER_H
#define UNTITLED1_ORDER_H
#include <chrono>

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock,std::chrono::nanoseconds>;

enum side{buy,sell};
enum type{limit,market};
enum market_type{time_in_force,ioc,fok}; // Immediate Or Cancel , Fill Or Kill

class Order {
    int order_id;
    int owner_id;
    side order_side;
    type order_type;
    market_type m_type;
    int price;
    int quantity;
    int remain_quantity;
    TimePoint timestamp;
public:
    Order(int order_id,int owner_id, int price, int quantity, side order_side, type order_type, market_type m_type = time_in_force) {
        this->order_id = order_id;
        this->owner_id = owner_id;
        this->price = price;
        this->quantity = this->remain_quantity = quantity;
        this->order_side = order_side;
        this->order_type = order_type;
        this->m_type = m_type;
        this->timestamp = Clock::now();
    }

    Order(Order&&) = delete;
    Order& operator=(const Order&) = delete;
    Order(const Order&) = delete;
    ~Order() = default;

};


#endif //UNTITLED1_ORDER_H