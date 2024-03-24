class Book
{
public:
    char Title[31], Authors[31], Cat[31];
    int Code, Numbers;
    bool Status;
};

ostream &operator<<(ostream &x, Book a)
{
    x << a.Code << "-" << a.Title << endl
      << "Authors: " << a.Authors << endl
      << "Category: " << a.Cat << endl
      << "Numbers: " << a.Numbers << endl;
    return x;
}

istream &operator>>(istream &x, Book &a)
{
    cout << "------<Add Book>------" << endl; //<<"Enter ID:";
    // x>>a.Code;
    cout << "Enter Title:";
    x >> a.Title;
    cout << "Enter Authers:";
    x >> a.Authors;
    cout << "Enter category:";
    x >> a.Cat;
    cout << "Enter Numbers:";
    x >> a.Numbers;
    return x;
}
