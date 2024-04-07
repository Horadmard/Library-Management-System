class User
{
public:

    char Name[31], Family[31], Fname[31], Email[31];
    Date BD;
    int User_name, Pass;
    bool Active = true, Ultimate_Access;
};

istream &operator>>(istream &i, User &User)
{
    cout << "<User Information>" << endl << "First Name:";
    i >> User.Name;

    cout << "Last Name:";
    i >> User.Family;

    cout << "Father's name:";
    i >> User.Fname;

    cout << "Birthday:";
    i >> User.BD;

    cout << "Password:";
    i >> User.Pass;

    return i;
}

ostream &operator<<(ostream &o, User User)
{
    char Ultimate[] = "Member";
    if (User.Ultimate_Access)
        strcpy(Ultimate, "Admin");

    o << User.User_name << "-" << User.Name << " " << User.Family << " <" << Ultimate << ">" << endl

      << "Birthday: " << User.BD << endl
      << "Father's name: " << User.Fname << endl
      << "Password: " << User.Pass;

    return o;
}
