#include"Library.h"

void input();

class RatNum{
    int numerator;
    int denominator;
public:
    RatNum():numerator(0), denominator(1){}
    RatNum(int, int);
    int num(){return numerator;}
    int den(){return denominator;}
    void print_d();
    void print_r();
};

RatNum::RatNum(int num, int den):numerator(num)
{
    if (den == 0) error("Can't Divide by zero! Try Again...");
    denominator = den;
}

void RatNum::print_d()
{
    double result = (double)numerator/denominator;
    cout << endl << "The result of the rational number is:" << endl;
    cout << setprecision(8) << result << endl;
}

void RatNum::print_r()
{
    int flag = 0;
    if (numerator < 0)
    {
        flag = 1;
    }
    if (denominator < 0)
    {
        if (flag == 1) 
        {
            flag = 0;
        }
        else
        {
            flag = 1;
        }
    }
    cout << endl << "Your Rational Number is:" << endl;
    if (flag == 1)
    {
        cout << "  " << abs(numerator) << endl
             << "- " << "--" << endl
             << "  " << abs(denominator) << endl;
    }
    else
    {
        cout << abs(numerator) << endl
             << "--" << endl
             << abs(denominator) << endl;
    }
    
}

int find_gcd(int num, int den)
{
    while(den != 0)
    {
        int temp = den;
        den = num % den;
        num = temp;
    }
    return num;
}

RatNum operator+(RatNum& num1, RatNum& num2)
{
    if (num1.den() == num2.den())
    {
        int nnum = num1.num() + num2.num();
        int nden = num1.den();
        int gcd = find_gcd(nnum, nden);
        nnum /= gcd;
        nden /= gcd;
        RatNum result(nnum, nden);
        return result;
    }
    else 
    {
        int nnum = (num1.num() * num2.den()) + (num2.num() * num1.den());
        int nden = (num1.den() * num2.den());
        int gcd = find_gcd(nnum, nden);
        nnum /= gcd;
        nden /= gcd;
        RatNum result(nnum, nden);
        return result;
    }
}

RatNum operator-(RatNum& num1, RatNum& num2)
{
    if (num1.den() == num2.den())
    {
        int nnum = num1.num() - num2.num();
        int nden = num1.den();
        int gcd = find_gcd(nnum, nden);
        nnum /= gcd;
        nden /= gcd;
        RatNum result(nnum, nden);
        return result;
    }
    else
    {
        int nnum = (num1.num() * num2.den()) - (num2.num() * num1.den());
        int nden = (num1.den() * num2.den());
        int gcd = find_gcd(nnum, nden);
        nnum /= gcd;
        nden /= gcd;
        RatNum result(nnum, nden);
        return result;
    }
}

RatNum operator*(RatNum& num1, RatNum& num2)
{
    int nres = num1.num() * num2.num();
    int dres = num1.den() * num2.den();
    int gcd = find_gcd(nres, dres);
    nres /= gcd;
    dres /= gcd;
    RatNum result(nres, dres);
    return result;
}

RatNum operator/(RatNum& num1, RatNum& num2)
{
    int nres = num1.num() * num2.den();
    if(num2.num() == 0) error("\nCan't divide because the numerator of the second number is 0");
    int dres = num1.den() * num2.num();
    int gcd = find_gcd(nres, dres);
    nres /= gcd;
    dres /= gcd;
    RatNum result(nres, dres);
    return result;
}

bool operator==(RatNum& num1, RatNum& num2)
{
    if (num1.num() == num2.num() && num1.den() == num2.den()) return true;
    return false;
}

vector<RatNum>nums;

void select(RatNum& num1, RatNum& num2)
{
    int res = 0;
    RatNum number;
    while(1)
    {   
        cout << endl << "What do you want to do with your numbers (Choose one from the ones listed bellow):" << endl;
        cout << "1. Addition" << endl
             << "2. Subtraction" << endl
             << "3. Multiplication" << endl
             << "4. Division" << endl
             << "5. Print Result" << endl
             << "6. Print Rational as Double" << endl
             << "7. Check if they are the same" << endl
             << "8. Input new numbers" << endl
             << "9. Exit" << endl;
        if(res == 1) 
        {
            cout << "10. Save oparation result" << endl;
            cout << "Type your answer by typing a number (1 - 10): ";
        }
        else 
        {
            cout << "Type your answer by typing a number (1 - 9): ";
        }
        int sel = 0;
        cin >> sel;
        if (sel == 1)
        {
            number = num1 + num2;
            res = 1;
        }
        else if(sel == 2)
        {
            number = num1 - num2;
            res = 1;
        }
        else if(sel == 3)
        {
            number = num1 * num2;
            res = 1;
        }  
        else if(sel == 4)
        {  
            number = num1 / num2;
            res = 1;
        }  
        else if(sel == 5)
        {
            if (res == 0) error("No oparation has been done to print the result");
            number.print_r();
            res = 0;
        }
        else if(sel == 6)
        {
            cout << endl << "What do you want to print:" << endl
                 << "1. The First Rational" << endl
                 << "2. The Second Rational" << endl;
            if(res == 1) cout << "3. The Result of the Computation" << endl;
            int print = 0;
            cout << endl << "Type your choice here (It has to be a number between 1-3): ";
            cin >> print;
            if(print == 1)
            {
                num1.print_d();
            }
            else if(print == 2)
            {
                num2.print_d();
            }
            else if (print == 3)
            {
                number.print_d();
            }
            else
            {
                error("Incorrect input!");
            }

        }
        else if(sel == 7)
        {
            if (num1 == num2)
            {
                cout << endl << "The two rationals are the same!" << endl;
            }
            else
            {
                cout << endl << "The two rationals aren't the same" << endl;
            }
        }
        else if(sel == 8)
        {
            input();
        }
        else if(sel == 9)
        {
            exit(0);
        }
        else if(sel == 10) 
        {
            nums.push_back(number);
        }
        else
        {
            error("Incorrect input!");
        }
    }
}

void input() {
    cout << endl << "Number No.1:" << endl;
    cout << "Enter your numerator and denominator:" << endl;
    cout << ">  ";
    int num1 = 0;
    int den1 = 0;
    cin >> num1;
    if (cin.fail()) error("Wrong Input");
    cout << ">  ";
    cin >> den1;
    if (cin.fail()) error("Wrong Input");
    RatNum rnumber1(num1, den1);
    cout << endl;
    cout << "Number No.2:" << endl;
    cout << "Enter your numerator and denominator:" << endl;
    cout << ">  ";
    int num2 = 0;
    int den2 = 0;
    cin >> num2;
    if (cin.fail()) error("Wrong Input");
    cout << ">  ";
    cin >> den2;
    if (cin.fail()) error("Wrong Input");
    RatNum rnumber2(num2, den2);
    cout << endl;
    select(rnumber1, rnumber2);
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
        cerr << "Oops something went wrong!" << endl;
    }
}