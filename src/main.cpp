#include <iostream>
#include <fstream>
#include <cstring>

#include "Book.cpp"
#include "Date.cpp"
#include "User.cpp"
#include "Functions.cpp"
#include "Transaction.cpp"
#include "time.cpp"

using namespace std;


char File_Name[] = "../data/UserData.Dat", File_Name2[] = "../data/BookData.Dat", File_Name3[] = "../data/ReportlendData.Dat", File_Name4[] = "../data/ReportReserveData.Dat";
int _FileSize(char a[]);
int main();
int User_Name;


bool Log_In();


int main()
{

    int Switch;

    if (!Log_In()){

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
                _PrintBooKs();
                break;
            case 2:
                system("cls");
                _AddBook();
                break;
            case 3:
                system("cls");
                cout << "1 - Remove\n2 - Edit\n3 - Search\n0 - Back\n";
                cin >> Switch;
                switch (Switch)
                {
                case 1:
                    _PrintBooKs();
                    _RemoveBook();
                    break;
                case 2:
                    _PrintBooKs();
                    _EditBook();
                    break;
                case 3:
                    _SearchBook();
                    break;
                case 0:
                    system("cls");
                    break;
                }
                break;
            case 4:
                system("cls");
                Admin_PrintLendedBooks();
                break;
            case 5:
                system("cls");
                cout << "1 - Add\n2 - Remove\n3 - Edit\n4 - Search\n5 - Print all Users\n0 - Back\n";
                cin >> Switch;
                switch (Switch)
                {
                case 1:
                    system("cls");
                    _AddUser();
                    break;
                case 2:
                    system("cls");
                    _PrintUser();
                    _RemoveUser();
                    break;
                case 3:
                    system("cls");
                    _EditUser();
                    break;
                case 4:
                    system("cls");
                    _SearchUser();
                    break;
                case 5:
                    system("cls");
                    _PrintUser();
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
                    Admin_Lend();
                    break;
                case 2:
                    system("cls");
                    Admin_Return();
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
                    Admin_PrintReports(File_Name3);
                    cout << "-----<Reserve Reports>-----\n";
                    Admin_PrintReports(File_Name4);
                    break;
                case 2:
                    system("cls");
                    Admin_PrintLateBooks();
                    break;
                case 3:
                    system("cls");
                    Admin_PrintPopularBooks();
                    break;
                case 4:
                    system("cls");
                    Admin_PrintActiveUsers();
                    break;
                case 5:
                    system("cls");
                    Admin_PrintReportsinPeriod();
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
                User_Name = -1;
                main();
                break;
            default:
                cout << "Input Error" << endl;
                break;
            }
        } while (1);

    }else{

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
                _SearchBook();
                break;
            case 2:
                system("cls");
                _Lend();
                break;
            case 3:
                system("cls");
                _PrintMyReturnedBooks();
                break;
            case 4:
                system("cls");
                _PrintMyBooks();
                break;
            case 5:
                system("cls");
                _Return();
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

    }
}
