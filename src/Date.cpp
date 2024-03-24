class Date{
    public:
        int Year,Month,Day;
        bool operator<=(Date y);
        bool operator>=(Date y);
        bool operator<(Date y);
        bool operator>(Date y);
};

bool Date::operator<=(Date y)
{
    if (Year < y.Year)
        return true;
    if (Year = y.Year)
    {
        if (Month < y.Month)
            return true;
        if (Month = y.Month)
        {
            if (Day <= y.Day)
                return true;
        }
    }
    return false;
}

bool Date::operator>=(Date y)
{
    if (Year > y.Year)
        return true;
    if (Year = y.Year)
    {
        if (Month > y.Month)
            return true;
        if (Month = y.Month)
        {
            if (Day >= y.Day)
                return true;
        }
    }
    return false;
}

bool Date::operator<(Date y)
{
    if (Year < y.Year)
        return true;
    if (Year = y.Year)
    {
        if (Month < y.Month)
            return true;
        if (Month = y.Month)
        {
            if (Day < y.Day)
                return true;
        }
    }
    return false;
}

bool Date::operator>(Date y)
{
    if (Year > y.Year)
        return true;
    if (Year = y.Year)
    {
        if (Month > y.Month)
            return true;
        if (Month = y.Month)
        {
            if (Day > y.Day)
                return true;
        }
    }
    return false;
}

Date operator+(Date x, int y)
{
    Date z;
    z.Day = x.Day;
    z.Month = x.Month;
    z.Year = x.Year;
    z.Day = z.Day + y;
    if (z.Day > 30)
    {
        z.Day = 1;
        z.Month + 1;
        if (z.Month > 12)
        {
            z.Month = 1;
            z.Year + 1;
        }
    }
    return z;
}

ostream &operator<<(ostream &o, Date a)
{
    o << a.Year << "-" << a.Month << "-" << a.Day;
    return o;
}

istream &operator>>(istream &i, Date &a)
{
    while (1)
    {
        cout << "\nDay: ";
        i >> a.Day;
        if (a.Day <= 30 && a.Day > 0)
            break;
        else
            cout << "\nInvalid Date!";
    }
    while (1)
    {
        cout << "Month: ";
        i >> a.Month;
        if (a.Month <= 12 && a.Month > 0)
            break;
        else
            cout << "\nInvalid Date!";
    }
    cout << "Year: ";
    i >> a.Year;
    return i;
}

Date Today;