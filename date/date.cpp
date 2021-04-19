// date.cpp
// version 2
#include "date.h"

// days of month in a common year
const int calendar::Mdays[12]={31,28,31,30,31,30,31,31,30,31,30,31};

bool calendar::valid(int y,int m,int d)const{
    m--,d--;
    if(m<0||m>11||d<0) return false;
    else if(d<Mdays[m]) return true;
    else if(m==1&&(y%4==0&&y%100!=0||y%400==0)&&d==28) return true;// for 2.29
    return false;
}

bool calendar::bissextile(int y)const{return y%4==0&&y%100!=0||y%400==0;}

const int calendar::yday(int y,int m,int d)const{
    if(!valid(y,m,d)) throw dateNS::Invalid_date;
    int cnt=d;
    for(int i=0;i<m-1;i++)cnt+=Mdays[i];                // add days of the month before this month(m)
    if((y%4==0&&y%100!=0||y%400==0)&&m>2)cnt++;         // if include bissextile month, add 1
    return cnt;
}

// days counted from 2000.1.1: 1 is 2000.1.1 and 0 is 1999.12.31
const int calendar::days(int y,int m,int d)const{
    if(!valid(y,m,d)) throw dateNS::Invalid_date;
    int cnt=yday(y,m,d);
    if(y<2000) while(y++<2000) cnt-=bissextile(y-1)?366:365;
    else while(y-->2000) cnt+=bissextile(y)?366:365;
    return cnt;
}

// 1 repesents Monday and 7 for Sunday
const int calendar::wday(int y,int m,int d)const{
    int cnt=(days(y,m,d)-3)%7+7;                          // 2000.1.1 is Saturday
    return cnt%7+1;
}


const int calendar::week(int y,int m,int d)const{
    int temp=wday(y,1,1);
    if(temp<5){
        int n=yday(y,m,d)-(8-temp);
        if(n<0)return 1;
        if(n%7)n+=7;
        return n/7+1;
    }
    else{
        int n=yday(y,m,d)-(8-temp);
        if(n<0)
            return -week(y-1,12,31);
        if(n%7)n+=7;
        return n/7;
    }
}


const dateNS::DATE calendar::days2DATE(int n)const{
    int y=2000,m=1;

    while(n>(bissextile(y)?366:365)){
        n-=(bissextile(y)?366:365);
        y++;
    }

    if(n<=0)n--;
    while(n<=0){
        n+=(bissextile(y)?366:365);
        y--;
    }

    while(n>Mdays[m-1]){
        if(m==2&&bissextile(y)){if(n>29)n-=29,m++;else break;}
        else n-=Mdays[m-1],m++;;
    }
    return dateNS::DATE({y,m,n});
}


// ---not include error log
// --------may not include
/*
string calendar::fmtout(int y,int m,int d,string fmt){
    ostringstream buff;
    buff<<y<<"/"
        <<m<<"/"
        <<d;
    return buff.str();
}
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
date::date(dateNS::sday s){
    time_t t=time(NULL);tm*T=localtime(&t);
    switch(s){
        case dateNS::today:
            year=T->tm_year+1900;
            month=T->tm_mon+1;
            day=T->tm_mday;
        break;
    }
}
date::date(int y,int m,int d):year(y),month(m),day(d){}
date::date(int m,int d):year(0),month(m),day(d){}

date& date::set(int y,int m,int d){year=y,month=m,day=d;return *this;}

//------------------------------------------------------------

const int& date::operator[](dateNS::element ele)const{
    switch(ele){
        case dateNS::Y:return year;
        case dateNS::M:return month;
        case dateNS::D:return day;
        default:throw dateNS::Invalid_parameter;
    }
}

const int date::operator[](dateNS::info inf)const{
    switch(inf){
        case dateNS::WK:return calendar::week(year,month,day);
        case dateNS::WD:return calendar::wday(year,month,day);
        case dateNS::YD:return calendar::yday(year,month,day);
        case dateNS::DS:return calendar::days(year,month,day);
        default:throw dateNS::Invalid_parameter;
    }
}

//------------------------------------------------------------

date& date::operator++(){
    if(!valid())return validated();
    day++;
    if(!valid()){if(month==12){month=1;year++;}else month++;day=1;}
    return *this;
}

const date date::operator++(int){
    date temp(*this);
    ++(*this);
    return temp;
}

date& date::operator--(){
    if(!valid())return validated();
    day--;
    if(!valid()){
        if(month==1){month=12;year--;}else month--;
        day=Mdays[month-1];if(month==2&&bissextile(year))day++;
    }
    return *this;
}

const date date::operator--(int){
    date temp(*this);
    --(*this);
    return temp;
}

//------------------------------------------------------------

const date date::days2date(int n){
    dateNS::DATE temp=calendar::days2DATE(n);
    return date(temp.y,temp.m,temp.d);
}


const date date::operator+(int n){
    if(!valid())throw dateNS::Invalid_date;
    return days2date((*this)[dateNS::DS]+n);
}

const date date::operator-(int n){
    if(!valid())throw dateNS::Invalid_date;
    return days2date((*this)[dateNS::DS]-n);
}

const int date::operator-(const date that){
    if(!valid()||!that.valid())throw dateNS::Invalid_date;
    return (*this)[dateNS::DS]-that[dateNS::DS];
}

//------------------------------------------------------------

const date&date::operator+=(int n){
    *this=(*this)+n;
    return *this;
}

const date&date::operator-=(int n){
    *this=(*this)-n;
    return *this;
}

//------------------------------------------------------------

bool date::valid()const{return calendar::valid(year,month,day);}

date& date::validated(){
    if(month>12)month=12;else if(month<1)month=1;
    if(day<1)day=1;else if(day>Mdays[month-1]){
        day=Mdays[month-1];if(month==2&&bissextile(year))day++;
    }
    return *this;
}

//------------------------------------------------------------

string date::fmtout(string fmt)const{
    if(!valid()) throw dateNS::Invalid_date;
    ostringstream buff;
    buff<<year<<"-"
        <<setfill('0')
        <<setw(2)<<month<<"-"
        <<setw(2)<<day;
    return buff.str();
}

string date::state()const{
    ostringstream buff;
    buff<<"\e[36myear: "  <<"\e[93m"<<setw(4)   <<year <<"\e[0m | "
        <<"\e[36mmonth: " <<"\e[93m"<<setw(2)   <<month<<"\e[0m | "
        <<"\e[36mday: "   <<"\e[93m"<<setw(2)   <<day  <<"\e[0m | "
        <<"\e[36mvalid: " <<"\e[93m"            <<(valid()?"\e[92mTrue":"\e[91mFalse")<<"\e[0m";
    return buff.str();
}

//------------------------------------------------------------

ostream& operator<<(ostream& out,const date t){
    if(!t.valid()) throw dateNS::Invalid_date;
    out <<t.year<<"-"<<setfill('0')<<setw(2)<<t.month<<"-"<<setw(2)<<t.day;
    return out;
}

ofstream& operator<<(ofstream& out,const date t){
    if(!t.valid()) throw dateNS::Invalid_date;
    out <<t.year<<"-"<<setfill('0')<<setw(2)<<t.month<<"-"<<setw(2)<<t.day;
    return out;
}

istream& operator>>(istream& in,date& t){
    in>>t.year>>t.month>>t.day;
    return in;
}

ifstream& operator>>(ifstream& in,date& t){
    in>>t.year>>t.month>>t.day;
    return in;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

calendar dateNS::rule;