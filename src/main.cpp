#include <iostream>
#include <fstream>
#include <string.h>

#include "Book.cpp"
#include "Date.cpp"
#include "User.cpp"
#include "Functions.cpp"
#include "Transaction.cpp"
#include "time.cpp"

//------------------------------------------
using namespace std;
char File_Name[] = "../data/UserData.Dat", File_Name2[] = "../data/BookData.Dat", File_Name3[] = "../data/ReportlendData.Dat", File_Name4[] = "../data/ReportReserveData.Dat";
int _FileSize(char a[]);
int main();
int User_Name;
//------------------------------------------

bool Log_In(User U);
void _AddUser(User new_User)
{
    fstream X(File_Name, ios::app | ios::binary);
    if (!X.is_open())
    {
        cout << "Faild!" << endl;
        return;
    }
    cin >> new_User;
    new_User.Ultimate_Access = false;
    new_User.User_name = (_FileSize(File_Name) / sizeof(User)) + 1;
    X.write((char *)&new_User, sizeof(User));
    X.close();
    system("cls");
    cout << "Done!" << endl;
    return;
}
void Admin_AddUser(User new_User)
{
    fstream X(File_Name, ios::app | ios::binary);
    if (!X.is_open())
    {
        cout << "Faild!" << endl;
        return;
    }
    cin >> new_User;
    new_User.Ultimate_Access = true;
    new_User.User_name = (_FileSize(File_Name) / sizeof(User)) + 1;
    X.write((char *)&new_User, sizeof(User));
    X.close();
    system("cls");
    cout << "Done!" << endl;
    return;
}
void _AddBook(Book new_Book)
{
    fstream X(File_Name2, ios::app | ios::binary);
    if (!X.is_open())
    {
        cout << "Faild!" << endl;
        return;
    }
    cin >> new_Book;
    new_Book.Code = (_FileSize(File_Name2) / sizeof(Book)) + 1;
    new_Book.Status = true;
    X.write((char *)&new_Book, sizeof(Book));
    X.close();
    system("cls");
    cout << "Done!" << endl;
    return;
}
void _PrintUser(User user)
{
    fstream Y(File_Name, ios::in | ios::binary);
    while (Y.read((char *)&user, sizeof(User)))
    {
        if (user.Active == true)
            cout << user << endl
                 << "-----------" << endl;
    }
    Y.close();
}

void _RemoveUser(User RUser, Report R)
{
    fstream X(File_Name, ios::out | ios::in | ios::binary);
    fstream Y(File_Name3, ios::out | ios::in | ios::binary);
    fstream Z(File_Name4, ios::out | ios::in | ios::binary);
    cout << "\nEnter the Username: ";
    int code, j = 0;
    cin >> code;
    if (code == 0)
    {
        X.close();
        system("cls");
        return;
    }
    if (code > _FileSize(File_Name) / sizeof(User))
    {
        system("cls");
        cout << "Not Exist!" << endl;
        return;
    }
    X.seekg((code - 1) * sizeof(User), ios::beg);
    X.read((char *)&RUser, sizeof(User));
    RUser.Active = false;
    X.seekg((code - 1) * sizeof(User), ios::beg);
    X.write((char *)&RUser, sizeof(User));
    // dar daste tamir---------------------------

    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.User_name == RUser.User_name && R.Expire == false)
        {
            R.Expire = true;
            Y.seekg(j * sizeof(Report), ios::beg);
            Y.write((char *)&R, sizeof(Report));
        }
        j++;
    }
    j = 0;
    while (Z.read((char *)&R, sizeof(Report)))
    {
        if (R.User_name == RUser.User_name && R.Expire == false)
        {
            R.Expire = true;
            Z.seekg(j * sizeof(Report), ios::beg);
            Z.write((char *)&R, sizeof(Report));
        }
        j++;
    }
    //-------------------------------------------
    X.close();
    Y.close();
    Z.close();
    system("cls");
    cout << "Done!" << endl;
    return;
}
void _EditUser(User RUser)
{
    fstream X(File_Name, ios::out | ios::in | ios::binary);
    int Swich, newN;
    char newT[31];
    int code;
    Date date;
    if (!X.is_open())
    {
        cout << "Faild!" << endl;
        return;
    }
    cout << "Enter the Username: ";
    cin >> code;
    if (code == 0)
    {
        X.close();
        system("cls");
        return;
    }
    if (code > _FileSize(File_Name) / sizeof(User))
    {
        system("cls");
        cout << "Not Exist!" << endl;
        X.close();
        return;
    }
    X.seekg((code - 1) * sizeof(User), ios::beg);
    X.read((char *)&RUser, sizeof(User));

    if (!RUser.Active)
    {
        system("cls");
        cout << "This User is removed!\n";
        X.close();
        return;
    }

    cout << "1 - Name\n2 - Family\n3 - Father Name\n4 - Birthday\n5 - Back\n";
    cin >> Swich;
    switch (Swich)
    {
    case 1:
        cout << "(" << RUser.Name << ")Enter the new Name:";
        cin >> newT;
        strcpy(RUser.Name, newT);
        system("cls");
        cout << "Done!" << endl;
        break;
    case 2:
        cout << "(" << RUser.Family << ")Enter the new Family:";
        cin >> newT;
        strcpy(RUser.Family, newT);
        system("cls");
        cout << "Done!" << endl;
        break;
    case 3:
        cout << "(" << RUser.Fname << ")Enter the new Father Name:";
        cin >> newT;
        strcpy(RUser.Fname, newT);
        system("cls");
        cout << "Done!" << endl;
        break;
    case 4:
        cout << "(" << RUser.BD << ")Enter the new Birthday:";
        cin >> date;
        RUser.BD = date;
        system("cls");
        cout << "Done!" << endl;
        break;
    case 5:
        system("cls");
        break;
    }
    X.seekg((code - 1) * sizeof(User), ios::beg);
    X.write((char *)&RUser, sizeof(User));
    X.close();
    return;
}
void _EditBook(Book RBook)
{
    fstream X(File_Name2, ios::out | ios::in | ios::binary);
    int Swich, newN, Code;
    char newT[31];
    if (!X.is_open())
    {
        system("cls");
        cout << "Faild!" << endl;
        return;
    }
    cout << "Enter the Book code: ";
    cin >> Code;
    if (Code == 0)
    {
        X.close();
        system("cls");
        return;
    }
    if (Code > _FileSize(File_Name2) / sizeof(Book))
    {
        system("cls");
        cout << "Not Exist!" << endl;
        X.close();
        return;
    }
    X.seekg((Code - 1) * sizeof(Book), ios::beg);
    X.read((char *)&RBook, sizeof(Book));
    if (!RBook.Status)
    {
        system("cls");
        cout << "This Book is removed!\n";
        X.close();
        return;
    }
    cout << "1 - Title\n2 - Authors\n3 - Category\n4 - Numbers\n0 - Back\n";
    cin >> Swich;
    switch (Swich)
    {
    case 1:
        cout << "(" << RBook.Title << ")Enter the new Title:";
        cin >> newT;
        strcpy(RBook.Title, newT);
        system("cls");
        cout << "Done!" << endl;
        break;
    case 2:
        cout << "(" << RBook.Authors << ")Enter the new Authors:";
        cin >> newT;
        strcpy(RBook.Authors, newT);
        system("cls");
        cout << "Done!" << endl;
        break;
    case 3:
        cout << "(" << RBook.Cat << ")Enter the new Category:";
        cin >> newT;
        strcpy(RBook.Cat, newT);
        system("cls");
        cout << "Done!" << endl;
        break;
    case 4:
        cout << "(" << RBook.Numbers << ")Enter the new Numbers:";
        cin >> newN;
        RBook.Numbers = newN;
        system("cls");
        cout << "Done!" << endl;
        break;
    case 0:
        system("cls");
        break;
    default:
        system("cls");
        cout << "Input Error" << endl;
        break;
    }
    X.seekg((Code - 1) * sizeof(Book), ios::beg);
    X.write((char *)&RBook, sizeof(Book));
    X.close();
}
void _SearchUser(User user)
{
    fstream X(File_Name, ios::in | ios::binary);
    if (!X.is_open())
    {
        cout << "Faild!" << endl;
        return;
    }
    system("cls");
    cout << "1 - Search a Name\n2 - Search Family\n";
    int Swich;
    char T[31];
    cin >> Swich;
    cout << "Enter the Text: ";
    cin >> T;
    switch (Swich)
    {
    case 1:
        system("cls");
        while (X.read((char *)&user, sizeof(User)))
        {
            if (strcmp(user.Name, T) == 0)
            {
                cout << endl
                     << user << endl
                     << "---------------" << endl;
                X.close();
                return;
            }
        }
        cout << "Not Found" << endl;
        break;
    case 2:
        system("cls");
        while (X.read((char *)&user, sizeof(User)))
        {
            if (strcmp(user.Family, T) == 0)
            {
                cout << user << endl
                     << "---------------" << endl;
                X.close();
                return;
            }
        }
        cout << "Not Found" << endl;
        break;
    default:
        system("cls");
        cout << "Input Error" << endl;
        break;
    }
    X.close();
    return;
}

void _RemoveBook(Book RBook, Report R)
{
    fstream X(File_Name2, ios::in | ios::out | ios::binary);
    fstream Y(File_Name3, ios::in | ios::out | ios::binary);
    fstream Z(File_Name4, ios::in | ios::out | ios::binary);
    if (!X.is_open())
    {
        cout << "Faild!" << endl;
        return;
    }
    int code, j = 0;
    cout << "Enter your Book code: ";
    cin >> code;
    if (code == 0)
    {
        X.close();
        system("cls");
        return;
    }
    if (code > _FileSize(File_Name2) / sizeof(Book))
    {
        system("cls");
        cout << "Not Exist!" << endl;
        return;
    }
    X.seekg((code - 1) * sizeof(Book), ios::beg);
    X.read((char *)&RBook, sizeof(Book));
    if (RBook.Status)
        RBook.Status = !RBook.Status;
    else
        RBook.Status = true;
    X.seekg((code - 1) * sizeof(Book), ios::beg);
    X.write((char *)&RBook, sizeof(Book));

    // to be fixed---------------------------
    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.Book_code == RBook.Code && R.Expire == false)
        {
            R.Expire = true;
            Y.seekg(j * sizeof(Report), ios::beg);
            Y.write((char *)&R, sizeof(Report));
        }
        j++;
    }
    j = 0;
    while (Z.read((char *)&R, sizeof(Report)))
    {
        if (R.Book_code == RBook.Code && R.Expire == false)
        {
            R.Expire = true;
            Z.seekg(j * sizeof(Report), ios::beg);
            Z.write((char *)&R, sizeof(Report));
        }
        j++;
    }
    //-------------------------------------------
    X.close();
    Y.close();
    Z.close();
    system("cls");
    cout << "Done!" << endl;
    return;
}
void _SearchBook(Book book)
{
    fstream X(File_Name2, ios::in | ios::binary);
    if (!X.is_open())
    {
        cout << "Faild!" << endl;
        return;
    }
    system("cls");
    cout << "1 - Search a Title\n2 - Search Authors\n0 - Back\n";
    int Swich;
    char T[31];
    cin >> Swich;
    cout << "Enter the Text: ";
    switch (Swich)
    {
    case 1:
        cin >> T;
        system("cls");
        while (X.read((char *)&book, sizeof(Book)))
        {
            if (strcmp(book.Title, T) == 0)
            {
                cout << endl
                     << book << "---------------" << endl;
                X.close();
                return;
            }
        }
        cout << "Not Found" << endl;
        break;
    case 2:
        cin >> T;
        system("cls");
        while (X.read((char *)&book, sizeof(Book)))
        {
            if (strcmp(book.Authors, T) == 0)
            {
                cout << book << "---------------" << endl;
                X.close();
                return;
            }
        }
        cout << "Not Found" << endl;
        break;
    case 0:
        system("cls");
        break;
    default:
        system("cls");
        cout << "Input Error" << endl;
        break;
    }
    X.close();
    return;
}

bool Log_In(User U)
{
    fstream X(File_Name, ios::in | ios::binary);
    if (!X.is_open() || _FileSize(File_Name) == 0)
    {
        Admin_AddUser(U);
        main();
    }
    int UserI, PassI;
    char Access[10];
    while (1)
    {
        cout << "Username: ";
        cin >> UserI;
        if (UserI <= _FileSize(File_Name) / sizeof(User))
        {
            X.seekg((UserI - 1) * sizeof(User), ios::beg);
            X.read((char *)&U, sizeof(User));
            if (U.Active == false)
            {
                system("cls");
                cout << "This User is Removed!" << endl;
                X.close();
                main();
            }
            cout << "Password: ";
            cin >> PassI;
            if (U.Pass == PassI)
            {
                system("cls");
                if (U.Ultimate_Access)
                    strcpy(Access, "Admin");
                else
                    strcpy(Access, "Member");
                cout << "Welcome " << U.Name << "(" << Access << ")" << endl;
                User_Name = UserI;
                X.close();
                if (U.Ultimate_Access)
                    return true;
                else
                    return false;
            }
            else
            {
                system("cls");
                cout << "Wrong Password" << endl;
            }
        }
        else
        {
            system("cls");
            cout << "Not Found!" << endl;
        }
    }
    X.close();
}

int _FileSize(char a[])
{
    fstream Y(a, ios::in | ios::binary);
    Y.seekg(0, ios::end);
    int n = Y.tellg();
    Y.seekg(0, ios::beg);
    Y.close();
    return n;
}
void _PrintBooKs(Book book)
{
    fstream Y(File_Name2, ios::in | ios::binary);
    if (_FileSize(File_Name2) / sizeof(Book) == 0 || !Y.is_open())
    {
        cout << "No Book!" << endl;
        Y.close();
        return;
    }
    while (Y.read((char *)&book, sizeof(Book)))
    {
        if (book.Status)
        {
            cout << book << "---------------" << endl;
        }
    }
    Y.close();
}
//--------------------------------------------------
void _Record(Report R, char File_Name[])
{
    fstream X(File_Name, ios::app | ios::binary);
    if (!X.is_open())
    {
        cout << "Faild!" << endl;
        return;
    }
    R.Expire = false;
    X.write((char *)&R, sizeof(Report));
    X.close();
    return;
}

void _Reserve(User U, Book B, Date D, Report R, int Book_code, int User_name)
{
    R.Book_code = Book_code;
    R.User_name = User_name;
    R.Start = Today;
    R.End.Day = 0;
    R.End.Month = 0;
    R.End.Year = 0;
    R.Expire = false;

    _Record(R, File_Name4);
}

void _Lend(User U, Book B, Date D, Report R)
{
    fstream X(File_Name2, ios::out | ios::in | ios::binary);
    fstream Y(File_Name3, ios::out | ios::in | ios::binary);
    bool s;
    int Book_code;
    if (!X.is_open() || _FileSize(File_Name2) / sizeof(Book) == 0)
    {
        system("cls");
        cout << "No Book!\n";
        X.close();
        Y.close();
        return;
    }
    _PrintBooKs(B);
    cout << "Enter a Bookcode: ";
    cin >> Book_code;
    if (Book_code == 0)
    {
        X.close();
        Y.close();
        system("cls");
        return;
    }
    if (_FileSize(File_Name2) / sizeof(Book) < Book_code)
    {
        system("cls");
        cout << "Not Exist!\n";
        X.close();
        Y.close();
        return;
    }

    X.seekg((Book_code - 1) * sizeof(Book), ios::beg);
    X.read((char *)&B, sizeof(Book));

    if (B.Status == false)
    {
        cout << "This Book is Removed\n";
        X.close();
        Y.close();
        return;
    }

    if (B.Numbers <= 0 && B.Status == true)
    {
        system("cls");
        cout << "Not Available!" << endl
             << "Do you want to Reserve?\n1 - Yes\t0 - No\n";
        cin >> s;
        if (s)
        {
            system("cls");
            _Reserve(U, B, D, R, B.Code, User_Name);
            cout << "Done!" << endl;
        }

        X.close();
        Y.close();
        return;
    }

    B.Numbers = B.Numbers - 1;

    X.seekg((Book_code - 1) * sizeof(Book), ios::beg);
    X.write((char *)&B, sizeof(Book));

    R.User_name = User_Name;
    R.Book_code = Book_code;
    R.Start = Today;
    R.End = Today;
    R.End = R.End + 5;
    R.Expire = false;

    _Record(R, File_Name3);

    X.close();
    Y.close();
}
void Admin_Lend(Book B, Report R, Date D, User U)
{
    fstream X(File_Name2, ios::out | ios::in | ios::binary);
    fstream Y(File_Name3, ios::out | ios::in | ios::binary);
    fstream Z(File_Name, ios::in | ios::binary);

    bool s;
    int Book_code, User_code;

    if (_FileSize(File_Name2) / sizeof(Book) == 0 || !X.is_open())
    {
        system("cls");
        cout << "No Book!\n";
        X.close();
        Y.close();
        return;
    }
    if (_FileSize(File_Name) / sizeof(User) == 0 || !Z.is_open())
    {
        system("cls");
        cout << "No User!\n";
        X.close();
        Y.close();
        return;
    }

    cout << "Enter a Username: ";
    cin >> User_code;
    if (User_code == 0)
    {
        X.close();
        Y.close();
        system("cls");
        return;
    }
    if (_FileSize(File_Name) / sizeof(User) < User_code)
    {
        system("cls");
        cout << "Not Exist!\n";
        X.close();
        Y.close();
        return;
    }

    _PrintBooKs(B);

    cout << "Enter a Bookcode: ";
    cin >> Book_code;
    if (Book_code == 0)
    {
        X.close();
        Y.close();
        system("cls");
        return;
    }
    if (_FileSize(File_Name2) / sizeof(Book) < Book_code)
    {
        system("cls");
        cout << "Not Exist!\n";
        X.close();
        Y.close();
        return;
    }

    X.seekg((Book_code - 1) * sizeof(Book), ios::beg);
    X.read((char *)&B, sizeof(Book));

    if (B.Numbers <= 0)
    {
        system("cls");
        cout << "Not Available!" << endl
             << "Do you want to Reserve?\n1 - Yes\t0 - No\n";
        cin >> s;
        if (s)
        {
            system("cls");
            _Reserve(U, B, D, R, B.Code, User_code);
            cout << "Done!" << endl;
        }

        X.close();
        Y.close();
        Z.close();
        return;
    }

    B.Numbers = B.Numbers - 1;

    X.seekg((Book_code - 1) * sizeof(Book), ios::beg);
    X.write((char *)&B, sizeof(Book));

    R.User_name = User_code;
    R.Book_code = Book_code;
    R.Start = Today;
    R.End = Today;
    R.End = R.End + 5;
    R.Expire = false;

    _Record(R, File_Name3);

    X.close();
    Y.close();
    return;
}
void Reserve_Lend(User U, Book B, Date D, Report R, int Book_code, int User_name)
{
    fstream X(File_Name2, ios::out | ios::in | ios::binary);

    X.seekg((Book_code - 1) * sizeof(Book), ios::beg);
    X.read((char *)&B, sizeof(Book));

    B.Numbers = B.Numbers - 1;

    X.seekg((Book_code - 1) * sizeof(Book), ios::beg);
    X.write((char *)&B, sizeof(Book));

    R.User_name = User_name;
    R.Book_code = Book_code;
    R.Start = Today;
    R.End = Today;
    R.End = R.End + 5;
    R.Expire = false;

    _Record(R, File_Name3);

    X.close();
}

void _PrintMyReturnedBooks(User U, Book B, Date D, Report R)
{
    fstream X(File_Name2, ios::in | ios::binary);
    fstream Y(File_Name3, ios::in | ios::binary);
    int i = 1;

    if (_FileSize(File_Name2) / sizeof(Book) == 0 || !Y.is_open())
    {
        system("cls");
        cout << "No Book!";
        X.close();
        Y.close();
        return;
    }
    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.User_name == User_Name && R.Expire == true)
        {
            X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
            X.read((char *)&B, sizeof(Book));
            cout << i << " - " << B.Title << endl;
            i++;
        }
    }

    X.close();
    Y.close();
}
void _PrintMyBooks(User U, Book B, Date D, Report R)
{
    fstream X(File_Name2, ios::in | ios::binary);
    fstream Y(File_Name3, ios::in | ios::binary);
    int i = 1;

    cout << "------<My Books>------\n";
    if (_FileSize(File_Name2) / sizeof(Book) == 0 || !Y.is_open() || !X.is_open())
    {
        system("cls");
        cout << "No Book!";
        X.close();
        Y.close();
        return;
    }
    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.User_name == User_Name && R.Expire == false)
        {
            X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
            X.read((char *)&B, sizeof(Book));
            cout << i << " - " << B.Title << "\t" << R.End << endl;
            i++;
        }
    }

    X.close();
    Y.close();
}
void Admin_PrintMyBooks(User U, Book B, Date D, Report R, int User_code)
{
    fstream X(File_Name2, ios::in | ios::binary);
    fstream Y(File_Name3, ios::in | ios::binary);
    int i = 1;
    if (_FileSize(File_Name) / sizeof(User) < User_code)
    {
        system("cls");
        cout << "Not Exist!";
        X.close();
        Y.close();
        return;
    }
    if (_FileSize(File_Name2) / sizeof(Book) == 0 || !Y.is_open())
    {
        system("cls");
        cout << "No Book!";
        X.close();
        Y.close();
        return;
    }

    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.User_name == User_code && R.Expire == false)
        {
            X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
            X.read((char *)&B, sizeof(Book));
            cout << i << " - " << B.Title << "\t" << R.End << endl;
            i++;
        }
    }

    X.close();
    Y.close();
}
void Admin_PrintLendedBooks(User U, Book B, Date D, Report R)
{
    fstream X(File_Name2, ios::in | ios::binary);
    fstream Y(File_Name3, ios::in | ios::binary);
    int i = 0;

    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.Expire == false)
        {
            X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
            X.read((char *)&B, sizeof(Book));
            i++;
            cout << i << " - " << B.Title << "\tUser(" << R.User_name << ")\t" << R.End << endl;
        }
    }
    if (i == 0)
    {
        cout << "No Book Lend!\n";
    }

    X.close();
    Y.close();
    return;
}

void Admin_PrintReports(Report R, char File_Name[])
{
    fstream Z(File_Name, ios::in | ios::binary);
    while (Z.read((char *)&R, sizeof(Report)))
    {
        cout << R << "---------------" << endl;
    }
    Z.close();
    return;
}
void Admin_PrintReportsinPeriod(Report R)
{
    fstream Z(File_Name3, ios::in | ios::binary);
    Date S, E;
    cout << "From: ";
    cin >> S;
    cout << "To: ";
    cin >> E;
    cout << endl;
    while (Z.read((char *)&R, sizeof(Report)))
    {
        if (R.Start >= S && R.End <= E)
        {
            cout << "User(" << R.User_name << ") Lend Book(" << R.Book_code << ")";
            if (R.Expire == 1)
                cout << " and Return it.";
            cout << endl
                 << "---------------" << endl;
        }
    }
    Z.close();
    return;
}

void Admin_PrintLateBooks(User U, Book B, Date D, Report R)
{
    fstream X(File_Name2, ios::in | ios::binary);
    fstream Y(File_Name3, ios::in | ios::binary);
    int i = 1;

    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.Expire == false && R.End < Today)
        {
            X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
            X.read((char *)&B, sizeof(Book));
            cout << i << " - " << B.Title << "\tUser(" << R.User_name << ")\t" << R.End << endl;
            i++;
        }
    }

    X.close();
    Y.close();
    return;
}
void Admin_PrintPopularBooks(Book B, Report R)
{
    fstream Z(File_Name3, ios::in | ios::binary);
    fstream Y(File_Name2, ios::in | ios::binary);
    int a[_FileSize(File_Name2) / sizeof(Book)] = {0}, m = 0;

    for (int i = 0; i < _FileSize(File_Name2) / sizeof(Book); i++)
    {
        while (Z.read((char *)&R, sizeof(Report)))
        {
            if (R.Book_code == i + 1)
            {
                a[i]++;
            }
        }
        Z.close();
        Z.open(File_Name3, ios::in | ios::binary);
    }
    for (int i = 0; i < _FileSize(File_Name2) / sizeof(Book); i++)
    {
        m += a[i];
    }
    m /= (_FileSize(File_Name2) / sizeof(Book));
    cout << "------<Popular Books>------\n";
    for (int i = 0; i < _FileSize(File_Name2) / sizeof(Book); i++)
    {
        if (a[i] > m)
        {
            Y.seekg(i * sizeof(Book), ios::beg);
            Y.read((char *)&B, sizeof(Book));
            cout << B.Title << "\t" << B.Authors << "\t" << B.Cat << endl
                 << "---------------" << endl;
        }
    }
    Z.close();
    return;
}
void Admin_PrintActiveUsers(User U, Report R)
{
    fstream Z(File_Name3, ios::in | ios::binary);
    fstream X(File_Name, ios::in | ios::binary);
    int a[_FileSize(File_Name) / sizeof(User)] = {0}, m = 0;

    for (int i = 0; i < _FileSize(File_Name) / sizeof(User); i++)
    {
        while (Z.read((char *)&R, sizeof(Report)))
        {
            if (R.User_name == i + 1)
            {
                a[i]++;
            }
        }
        Z.close();
        Z.open(File_Name3, ios::in | ios::binary);
    }
    for (int i = 0; i < _FileSize(File_Name) / sizeof(User); i++)
    {
        m += a[i];
    }
    m /= (_FileSize(File_Name) / sizeof(User));
    cout << "------<Active Users>------\n";
    for (int i = 0; i < _FileSize(File_Name) / sizeof(User); i++)
    {
        if (a[i] > m)
        {
            X.seekg(i * sizeof(User), ios::beg);
            X.read((char *)&U, sizeof(User));
            cout << U.Name << " " << U.Family << "\t" << endl
                 << "---------------" << endl;
        }
    }
    Z.close();
    X.close();
    return;
}
bool _CheckReserve(User U, Book B, Date D, Report R)
{
    fstream X(File_Name4, ios::out | ios::in | ios::binary);
    int o = 0;
    while (X.read((char *)&R, sizeof(Report)))
    {
        if (R.Book_code == B.Code && R.Expire == false)
        {
            R.Expire = true;
            X.seekg((o) * sizeof(Report), ios::beg);
            X.write((char *)&R, sizeof(Report));
            Reserve_Lend(U, B, D, R, R.Book_code, R.User_name);
            return true;
            break;
        }
        o++;
    }
    X.close();
    return false;
}
void _Return(User U, Book B, Date D, Report R)
{
    fstream X(File_Name2, ios::out | ios::in | ios::binary);
    fstream Y(File_Name3, ios::out | ios::in | ios::binary);
    int c, i = 0, j = 0, o = 0, T = 0;

    _PrintMyBooks(U, B, D, R);
    cout << endl
         << "Choose a Book to Return: ";
    cin >> c;

    if (c == 0)
    {
        X.close();
        Y.close();
        return;
    }

    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.User_name == User_Name && R.Expire == false)
        {
            i++;
            if (i == c)
            {
                R.Expire = true;
                Y.seekg((j) * sizeof(Report), ios::beg);
                Y.write((char *)&R, sizeof(Report));

                X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
                X.read((char *)&B, sizeof(Book));
                B.Numbers = B.Numbers + 1;
                X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
                X.write((char *)&B, sizeof(Book));

                if (_CheckReserve(U, B, D, R))
                {
                    X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
                    X.read((char *)&B, sizeof(Book));

                    B.Numbers = B.Numbers - 1;

                    X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
                    X.write((char *)&B, sizeof(Book));
                }

                break;
            }
        }
        j++;
    }

    X.close();
    Y.close();
    return;
}
void Admin_Return(User U, Book B, Date D, Report R)
{
    fstream X(File_Name2, ios::out | ios::in | ios::binary);
    fstream Y(File_Name3, ios::out | ios::in | ios::binary);
    int c, i = 0, j = 0, User_code;

    cout << "Enter a Username: ";
    cin >> User_code;
    if (_FileSize(File_Name) / sizeof(User) < User_code)
    {
        system("cls");
        cout << "Not Exist!";
        X.close();
        Y.close();
        return;
    }
    Admin_PrintMyBooks(U, B, D, R, User_code);

    cout << endl
         << "Choose a Book to Return: ";
    cin >> c;

    if (c == 0)
    {
        X.close();
        Y.close();
        return;
    }

    while (Y.read((char *)&R, sizeof(Report)))
    {
        if (R.User_name == User_code && R.Expire == false)
        {
            i++;
            if (i == c)
            {
                R.Expire = true;
                Y.seekg((j) * sizeof(Report), ios::beg);
                Y.write((char *)&R, sizeof(Report));

                X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
                X.read((char *)&B, sizeof(Book));

                B.Numbers = B.Numbers + 1;

                X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
                X.write((char *)&B, sizeof(Book));

                if (_CheckReserve(U, B, D, R))
                {
                    X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
                    X.read((char *)&B, sizeof(Book));

                    B.Numbers = B.Numbers - 1;

                    X.seekg((R.Book_code - 1) * sizeof(Book), ios::beg);
                    X.write((char *)&B, sizeof(Book));
                }

                break;
            }
        }
        j++;
    }
    X.close();
    Y.close();
    return;
}

//----------------------------------------------------------------------
int main()
{
    Date D;
    Book B;
    User U;
    Report R;

    int Switch;
lable1:
    if (!Log_In(U))
        goto labble2;
    do
    {
        cout << "Today: " << Today << endl
             << "1 - Book List\n2 - Add new Book" << endl;
        cout << "3 - Remove / Edit / Search a Book\n4 - Print Lended Books\n5 - Add / Remove / Edit / Search / Print a User" << endl;
        cout << "6 - Lend / Return / Reserve a Book\n7 - Reports\n0 - Log_out" << endl;
        cin >> Switch;
        switch (Switch)
        {
        case 1:
            system("cls");
            _PrintBooKs(B);
            break;
        case 2:
            system("cls");
            _AddBook(B);
            break;
        case 3:
            system("cls");
            cout << "1 - Remove\n2 - Edit\n3 - Search\n0 - Back\n";
            cin >> Switch;
            switch (Switch)
            {
            case 1:
                _PrintBooKs(B);
                _RemoveBook(B, R);
                break;
            case 2:
                _PrintBooKs(B);
                _EditBook(B);
                break;
            case 3:
                _SearchBook(B);
                break;
            case 0:
                system("cls");
                break;
            }
            break;
        case 4:
            system("cls");
            Admin_PrintLendedBooks(U, B, D, R);
            break;
        case 5:
            system("cls");
            cout << "1 - Add\n2 - Remove\n3 - Edit\n4 - Search\n5 - Print all Users\n0 - Back\n";
            cin >> Switch;
            switch (Switch)
            {
            case 1:
                system("cls");
                _AddUser(U);
                break;
            case 2:
                system("cls");
                _PrintUser(U);
                _RemoveUser(U, R);
                break;
            case 3:
                system("cls");
                _EditUser(U);
                break;
            case 4:
                system("cls");
                _SearchUser(U);
                break;
            case 5:
                system("cls");
                _PrintUser(U);
                break;
            case 0:
                system("cls");
                break;
            }
            break;
        case 6:
            system("cls");
            cout << "1 - Lend\n2 - Return\n0 - Back\n";
            cin >> Switch;
            switch (Switch)
            {
            case 1:
                system("cls");
                Admin_Lend(B, R, D, U);
                break;
            case 2:
                system("cls");
                Admin_Return(U, B, D, R);
                break;
            case 3:
                system("cls");
                break;
            case 0:
                system("cls");
                break;
            }
            break;
        case 7:
            system("cls");
            cout << "1 - Print all Reports\n2 - Print late Books\n3 - Papular Books\n4 - Active Users\n5 - Reports In a period of time\n0 - Back\n";
            cin >> Switch;
            switch (Switch)
            {
            case 1:
                system("cls");
                cout << "------<Lend Reports>-------\n";
                Admin_PrintReports(R, File_Name3);
                cout << "-----<Reserve Reports>-----\n";
                Admin_PrintReports(R, File_Name4);
                break;
            case 2:
                system("cls");
                Admin_PrintLateBooks(U, B, D, R);
                break;
            case 3:
                system("cls");
                Admin_PrintPopularBooks(B, R);
                break;
            case 4:
                system("cls");
                Admin_PrintActiveUsers(U, R);
                break;
            case 5:
                system("cls");
                Admin_PrintReportsinPeriod(R);
                break;
            case 0:
                system("cls");
                break;
            }
            break;
        case 8:
            system("cls");
            _AddUser(U); //*
            system("cls");
            break;
        case 0:
            system("cls");
            cout << "Goodbye " << endl; //<<U.Name<<endl
            goto lable1;
            break;
        default:
            cout << "Input Error" << endl;
            break;
        }
    } while (1);
labble2:
    do
    {
        cout << "Today: " << Today << endl
             << "1 - Search a Book\n2 - Take a Book\n3 - My Returned Books" << endl;
        cout << "4 - My Books\n5 - Return a Book\n0 - Log_out\n"
             << endl;
        cin >> Switch;
        switch (Switch)
        {
        case 1:
            system("cls");
            _SearchBook(B); //*
            break;
        case 2:
            system("cls");
            _Lend(U, B, D, R);
            break;
        case 3:
            system("cls");
            _PrintMyReturnedBooks(U, B, D, R);
            break;
        case 4:
            system("cls");
            _PrintMyBooks(U, B, D, R);
            break;
        case 5:
            system("cls");
            _Return(U, B, D, R);
            break;
        case 0:
            system("cls");
            cout << "Goodbye " << endl;
            goto lable1;
            break;
        default:
            system("cls");
            cout << "Input Error" << endl;
            break;
        }
    } while (1);
    //------------------------------------------*/
}
