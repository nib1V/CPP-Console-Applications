#include "Library.h"

enum Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, octo, nov, dece
};

enum Dd {
    sun = 1, mon, tue, wen, thu, fri, sat = 0
};

class Date {
public:
    Date(int yy, Month mm, int dd);

    int   day()   {return d;}
    Month month() {return m;}
    int   year()  {return y;}
    Dd   day_name();

    bool leap_year();
    int  month_code(int month);
    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
    void daytoday();
    void next_workday();
    void week_of_year();
    bool has_30d();
    bool has_31d();
private:
    int   y;
    Month m;
    int   d;
};

bool Date::has_30d()
{
    if (m == apr || m == jun || m == sep || m == nov)
    {
        return true;
    }
    return false;
}

bool Date::has_31d()
{
    if (m == jan || m == mar || m == may || m == jul || m == aug || m == octo || m == dece)
    {
        return true;
    }
    return false;
}

bool Date::leap_year()
{
    if ((y/4 == 0 && (!(y/100 == 0))) || y/400 == 0)
    {
        return true;
    }
    return false;
}

Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd)
{
    if (mm < 1 || mm > 12) error("Invalid Input");
    if (dd < 1) error("Invalid Input");
    if (dd > 30 && has_30d()) error("Invalid Input");
    if (dd > 31 && has_31d()) error("Invalid Input");
    if (mm == 2 && leap_year() && dd > 29) error("Invalid Input");
    if (mm == 2 && !leap_year() && dd > 28) error("Invalid Input");
    if (yy < 1600 || yy > 2299) error("Invalid Input");
}

int year_code(int year)
{
    if (year > 2000) return year - 2000;
    if (year > 1900) return year - 1900;
    if (year > 1800) return year - 1800;
    if (year > 1700) return year - 1700;
    if (year > 1600) return year - 1600;
    return -1;
}

int Date::month_code(int month) 
{
    if (month == 1 && !leap_year()) return 1;
    if (month == 1 && leap_year()) return 4;
    if (month == 2 && !leap_year()) return 4;
    if (month == 2 && leap_year()) return 0;
    if (month == 3) return 4;
    if (month == 4) return 0;
    if (month == 5) return 2;
    if (month == 6) return 5;
    if (month == 7) return 0;
    if (month == 8) return 3;
    if (month == 9) return 6;
    if (month == 10) return 1;
    if (month == 11) return 4;
    if (month == 12) return 6;
    return -1;
}

int cent_code(int year)
{
    if (year < 1800) return 4;
    if (year < 1900) return 2;
    if (year < 2000) return 0;
    if (year < 2100) return 6;
    if (year < 2200) return 4;
    return -1;
}

Dd Date::day_name()
{
    //int day = ((d+m+y+21)%7) + 1;
    //return Dd(day);
    
    int Yy = year_code(y);
    int Mm = month_code(m);
    int Cc = cent_code(y);
    if (Yy == -1 || Mm == -1 || Cc == -1) error("SOmething went wrong!");
    int sum = Yy/4 + Yy + Mm + Cc + d;
    sum %= 7;
    return Dd(sum);
}

Month operator+(Month& mon, int n)
{
    int temp = mon;
    temp = temp + n;
    if(temp > 12)
    {
        temp -= 12;
        return Month(temp);
    }
    return Month(temp);
}

string day_select(int day_new)
{
    string Dy = " ";
    switch (day_new){
        case 0: Dy = "Saturday"; break;
        case 1: Dy = "Sunday"; break;
        case 2: Dy = "Monday"; break;
        case 3: Dy = "Tuesday"; break;
        case 4: Dy = "Wednesday"; break;
        case 5: Dy = "Thursday"; break;
        case 6: Dy = "Friday"; break;
    }
    return Dy;
}

string month_select(int month_new)
{
    string Mm = " ";
    switch (month_new) {
    case 1: Mm = "January"; break;
    case 2: Mm = "February"; break;
    case 3: Mm = "March"; break;
    case 4: Mm = "April"; break;
    case 5: Mm = "May"; break;
    case 6: Mm = "June"; break;
    case 7: Mm = "July"; break;
    case 8: Mm = "August"; break;
    case 9: Mm = "September"; break;
    case 10: Mm = "Octomber"; break;
    case 11: Mm = "November"; break;
    case 12: Mm = "December"; break;
    }
    return Mm;
    
}

void  Date::daytoday()
{
    string Mm = month_select(m);
    string Dy = day_select(day_name());
    cout << "Today is " << Dy << " the " << d << "th " << Mm << " of " << y << endl;
}

void Date::add_day(int n) 
{
    if (n < 0) error("Can't subtract days");
    if (has_30d()) 
    {
        int temp = 0;
        if (n > 31) error("Too big of a number of days to add!");
        temp = (d + n)/30;
        d = (d + n)%30;
        add_month(temp);
    }
    else if (has_31d()) 
    {
        int temp = 0;
        if (n > 30) error("Too big of a number of days to add!");
        temp = (d + n)/31;
        d = (d + n)%31;
        add_month(temp);
    }
    else
    {
        int temp = 0;
        if (n > 31) error("Too big of a number of days to add!");
        if (!leap_year())
        {
            temp = (d + n)/28;
            d = (d + n)%28;
            add_month(temp);
        }
        else
        {
            temp = (d + n)/29;
            d = (d + n)%29;
            add_month(temp);
        }  
    }
}

void Date::add_month(int n) //works
{
    int temp1 = m;
    m = m + n;
    int temp2 = m;
    if(temp1 > temp2)
    {
        add_year(1);
    }
}

void Date::add_year(int n) //works
{
    y = y + n;
}

void Date::next_workday()
{
    Dd day_new = day_name();
    Month month_new = m;
    int year_new = y;
    string Dy = " ";
    int offset = 0;
    if(day_name() == 0 || day_name() == 1 || day_name() == 6)
    {
        Dy = "Monday";
        if (day_name() == 0) offset = 2;
        if (day_name() == 1) offset = 1;
        if (day_name() == 6) offset = 3;
    }
    else
    {
        offset = 1;
        int temp = day_name();
        if(d + 1 > 30 && has_30d())
        {
            temp++;
            day_new = Dd(temp);
            month_new = m + 1;
            year_new = y;
        }
        else if (d + 1 > 31 && has_31d())
        {
            temp++;
            day_new = Dd(temp);
            month_new = m + 1;
            year_new = y;
            if (m == dece) year_new++;
        }
        else if ((d + 1) == 28 && !leap_year() || (d + 1) == 29 && leap_year())
        {
            temp++;
            day_new = Dd(temp);
            month_new = m + 1;
            year_new = y;
        }
        else
        {
            temp++;
            day_new = Dd(temp);
        }
        if (day_new == 1 || day_new == 0) error("Something went wrong...");
        Dy = day_select(day_new);
    }
    string Mm = month_select(month_new);
    cout << "The next workday is: " << Dy
         << " the " << d + offset << "th " << Mm 
         << " " << year_new <<  endl;
}

void Date::week_of_year()
{
    int n = d/7 + (m - 1)*4;
    int sum = 0;
    if (d%7 != 0) sum += d%7;
    for(int i = m; i; i--)
    {
        if (i == 4 || i == 6 || i == 9 || i == 11)
        {
            sum += 2;
        }
        else if(i != 2)
        {
            sum += 3;
        }
    }
    n = n + sum/7 + 1;
    cout << "It is week " << n << " of the year!" << endl;
}

int main()
{
    try{
        Date today(1643, jan, 3);
        today.daytoday();
	    today.week_of_year();
        today.next_workday();
        return 0;
    }
    catch(exception& e)
    {
        cerr << e.what() << endl;
    }
    catch(...)
    {
        cerr << "Something went wrong and the app had to be shut down.." << endl;
    }
}