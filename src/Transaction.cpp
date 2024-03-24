class Report
{
public:
    Date Start, End;
    int User_name, Book_code;
    bool Expire;
};

ostream &operator<<(ostream &o, Report a)
{
    o << "/" << a.Start << "/" << endl
      << "User(" << a.User_name << ")" << endl
      << "Book(" << a.Book_code << ")" << endl
      << "Expire(" << a.Expire << ")" << endl
      << "/" << a.End << "/" << endl;
    return o;
}