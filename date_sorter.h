//
// Created by oscal on 10/17/2025.
//

#ifndef SITUACION_PROBLEMA_PARTE_2_DATE_SORTER_H
#define SITUACION_PROBLEMA_PARTE_2_DATE_SORTER_H

#include <iostream>
using namespace std;

class Order {
private:
    int sec, min, hr, day, month, n;
    string restaurant, name;
public:
    Order() : sec(0), min(0), hr(0), day(0), month(0), n(0), restaurant(""), name("") {}
    Order(int _s, int _min, int _h, int _d, int _m, int _n, const string& _r, const string& _nm)
       : sec(_s), min(_min), hr(_h), day(_d), month(_m), n(_n),
         restaurant(_r), name(_nm) {}
    Order(int _s, int _min, int _h, int _d, int _m)
        : sec(_s), min(_min), hr(_h), day(_d), month(_m),
          n(0), restaurant(""), name("") {}

    int getSec() const { return sec; }
    int getMin() const { return min; }
    int getHour() const { return hr; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getNumber() const { return n; }
    string getName() const { return name; }
    string getRestaurant() const { return restaurant; }

    int compareTime(const Order& other) const {

        if (month != other.month) {return (month < other.month) ? (-2) : (2);}
        if (day   != other.day)   {return (day   < other.day)   ? (-3) : (3);}
        if (hr    != other.hr)    {return (hr    < other.hr)    ? (-4) : (4);}
        if (min   != other.min)   {return (min   < other.min)   ? (-5) : (5);}
        if (sec   != other.sec)   {return (sec   < other.sec)   ? (-6) : (6);}
        return 0;
    }

    bool operator == (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) == 0);
        return restaurant == other.restaurant;
    }
    bool operator != (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) != 0);
        return restaurant != other.restaurant;
    }
    bool operator > (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) > 0);
        return restaurant > other.restaurant;
    }
    bool operator < (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) < 0);
        return restaurant < other.restaurant;
    }
    bool operator >= (const Order& other) const {
        if (restaurant == other.restaurant) return (compareTime(other) >= 0);
        return restaurant >= other.restaurant;
    }
    bool operator <= (const Order& other) const {
        if (restaurant == other.getRestaurant()) return (compareTime(other) <= 0);
        return restaurant <= other.getRestaurant();
    }

    string monthName() const {
        switch (month) {
            case 1:
                return "ENE";
            case 2:
                return "FEB";
            case 3:
                return "MAR";
            case 4:
                return "ABR";
            case 5:
                return "MAY";
            case 6:
                return "JUN";
            case 7:
                return "JUL";
            case 8:
                return "AGO";
            case 9:
                return "SEP";
            case 10:
                return "OCT";
            case 11:
                return "NOV";
            case 12:
                return "DIC";
            default:
                return "???";
        }
    }

    friend ostream& operator<<(ostream& os, const Order& order){

      os << order.monthName() << " " << order.getDay() << " " << order.getHour() << ":" << order.getMin() << ":" << order.getSec()
        << " R:" << order.getRestaurant() << " O:" << order.getName() << "(" << order.getNumber() << ")";

      return os;
    }

};

#endif //SITUACION_PROBLEMA_PARTE_2_DATE_SORTER_H
