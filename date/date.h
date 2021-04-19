// date.h
// version 2
#ifndef _DATE_
#define _DATE_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
using std::string;
using std::ostringstream;

using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;

using std::setw;
using std::setfill;
// currently not support locale setting

namespace dateNS{
    enum error{Invalid_date,Invalid_parameter};
    enum sday{today,yesterday,tomorrow};
    enum element{Y,M,D};
    enum info{WK,WD,YD,DS};
    struct DATE{int y;int m;int d;};
}

class calendar{
    protected:
    static const int Mdays[12];
    public:
    virtual bool valid(int y,int m,int d)const;
    virtual bool bissextile(int y)const;

    virtual const int days(int y,int m,int d)const;
    virtual const int yday(int y,int m,int d)const;
    virtual const int wday(int y,int m,int d)const;
    virtual const int week(int y,int m,int d)const;

    virtual const dateNS::DATE days2DATE(int n)const;
};

class date:public calendar{
    int year;
    int month;
    int day;
    public:
    date(dateNS::sday s=dateNS::today);
    date(int y,int m,int d);
    date(int m,int d);
    date& set(int y,int m,int d);

    const int& operator[](dateNS::element ele)const;
    const int operator[](dateNS::info inf)const;

    date& operator++();
    const date operator++(int);
    date& operator--();
    const date operator--(int);

    const date days2date(int d);
    const date operator+(int n);
    const date operator-(int n);
    const int operator-(const date that);

    const date& operator+=(int n);
    const date& operator-=(int n);

    virtual bool valid()const;
    date& validated();

    string fmtout(string fmt="yyyy/mm/dd")const;// not completed
    string state()const;

    friend ostream& operator<<(ostream& out,const date t);
    friend ofstream& operator<<(ofstream& out,const date t);
    friend istream& operator>>(istream& in,date& t);
    friend ifstream& operator>>(ifstream& in,date& t);

};

namespace dateNS{
    extern calendar rule;
}

#endif