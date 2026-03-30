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
    Date(){};

    int   day()   {return d;}
    Month month() {return m;}
    int   year()  {return y;}
    Dd   day_name();

    void operator=(Date& d2);

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

void interface(Date&);

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

string label_select(int day)
{
    string label = " ";
    switch (day)
    {
        case 1: label = "st "; break;
        case 2: label = "nd "; break;
        case 3: label = "rd "; break;
        default: label = "th "; break;
    }
    return label;
}

Dd Date::day_name()
{
    int Yy = year_code(y);
    int Mm = month_code(m);
    int Cc = cent_code(y);
    if (Yy == -1 || Mm == -1 || Cc == -1) error("Something went wrong!");
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

void Date::operator=(Date& date)
{
    d = date.day();
    m = date.month();
    y = date.year();
}

Date operator>>(istream& ist, Date& date)
{
    char symb1, symb2;
    int y, temp, d;
    ist >> y >> symb1 >> temp >> symb2 >> d;
    if (symb1 != '/' || symb2 != '/') error("Wrong input layout, try again...");
    Month m = Month(temp);
    Date dtemp(y, m, d);
    date = dtemp;
    return date;
}

void Date::daytoday()
{
    string Mm = month_select(m);
    string Dy = day_select(day_name());
    string label = label_select(d);
    cout << "Today is " << Dy << " the " << d << label << "of " << Mm << " " << y << endl;
}

void Date::add_day(int n) 
{
    if (n < 0) error("Can't subtract days");
    if (has_30d()) 
    {
        int temp = 0;
        if (n > 31) error("Too big of a number of days to add!");
        temp = (d + n)/30;
        d = ((d + n)%30 ? (d + n)%30 : 1);
        add_month(temp);
    }
    else if (has_31d()) 
    {
        int temp = 0;
        if (n > 30) error("Too big of a number of days to add!");
        temp = (d + n)/31;
        d = ((d + n)%31 ? (d + n)%31 : 1);
        add_month(temp);
    }
    else
    {
        int temp = 0;
        if (n > 31) error("Too big of a number of days to add!");
        if (!leap_year())
        {
            temp = (d + n)/28;
            d = ((d + n)%28 ? (d + n)%28 : 1);
            add_month(temp);
        }
        else
        {
            temp = (d + n)/29;
            d = ((d + n)%29 ? (d + n)%29 : 1);
            add_month(temp);
        }  
    }
}

void Date::add_month(int n)
{
    int temp1 = m;
    m = m + n;
    int temp2 = m;
    if(temp1 > temp2)
    {
        add_year(1);
    }
}

void Date::add_year(int n)
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
    Date temp(y, m, d);
    temp.add_day(offset);
    string Mm = month_select(month_new);
    string label = " ";
    label = label_select(temp.day());
    if ((d + offset < 31 && has_30d()) || (d + offset < 32 && has_31d()))
    {
        cout << "The next workday is: " << Dy
         << " the " << d + offset << label << "of " << Mm 
         << " " << year_new <<  endl;
    }
    else
    {
        cout << "The next workday is: " << Dy
         << " the " << temp.day() << label << "of " << Mm 
         << " " << year_new <<  endl;
    }
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

void input()
{
    cout << "Input the date you want below" << endl
         << "(The correct format is yy/mm/dd): ";
    Date date;
    cin >> date;
    if (cin.fail() || cin.bad()) error("Somthing went wrong while inputting the date...");
    interface(date);
}

void interface(Date& date)
{
    while(1)
    {
        int sel;
        cout << "Select what you want to do with your date:" << endl
            << "1. Print the current Date" << endl
            << "2. Print the week of the year" << endl
            << "3. Print the Date of the next workday" << endl
            << "4. Enter new date" << endl
            << "5. Add n days to your current date" << endl
            << "6. Add n months to your current date" << endl
            << "7. Add n years to your current date" << endl
            << "8. Exit" << endl
            << "Enter an interger followed by ENTER: ";
        cin >> sel;
        cout << endl;
        if (sel == 1) 
        {
            date.daytoday();
            cout << endl;
        }
        else if (sel == 2)
        {
            date.week_of_year();
            cout << endl;
        }
        else if (sel == 3)
        {
            date.next_workday();
            cout << endl;

        } 
        else if (sel == 4)
        {
            input();
        }
        else if (sel == 5)
        {
            int n = 0;
            cout << endl << "Enter the ammount of days you want to add" << endl
                 << "(It has to be a number between 1 and 31 according to the month): ";
            cin >> n;
            date.add_day(n);
            cout << endl;
        }
        else if (sel == 6)
        {
            int n = 0;
            cout << endl << "Enter the ammount of months you want to add: ";
            cin >> n;
            cout << endl;
            date.add_month(n);
            cout << endl;
        }
        else if (sel == 7)
        {
            int n = 0;
            cout << endl << "Enter the ammount of years you want to add ";
            cin >> n;
            cout << endl;
            date.add_year(n);
            cout << endl;
        }
        else if (sel == 8)
        {
            exit(0);
        }
        else
        {
            error("Unexpected input, try again...");
        }
    }
}

int main()
{
    try
    {
        input();
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

//Adding comments soon...