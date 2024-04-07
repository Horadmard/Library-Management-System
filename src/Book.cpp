

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

istream &operator>>(istream &x, Book &Book)
{
    cout << "------<Add Book>------" << endl; //<<"Enter ID:";

    cout << "Enter Title:";
    x >> Book.Title;

    cout << "Enter Authers:";
    x >> Book.Authors;

    cout << "Enter category:";
    x >> Book.Cat;

    cout << "Enter Numbers:";
    x >> Book.Numbers;

    return x;
}
