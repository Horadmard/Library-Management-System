class User
{
public:
    char Name[31], Family[31], Fname[31], Email[31];
    Date BD;
    int User_name, Pass;
    bool Active = true, Ultimate_Access;
};
istream &operator>>(istream &i, User &a)
{
    cout << "<User Information>" << endl;
    cout << "First Name:";
    i >> a.Name;
    cout << "Last Name:";
    i >> a.Family;
    cout << "Father's name:";
    i >> a.Fname;
    cout << "Birthday:";
    i >> a.BD;
    cout << "Password:";
    i >> a.Pass;
    return i;
}
ostream &operator<<(ostream &o, User a)
{
    char Ultimate[] = "Member";
    if (a.Ultimate_Access)
        strcpy(Ultimate, "Admin");
    o << a.User_name << "-" << a.Name << " " << a.Family << " <" << Ultimate << ">" << endl
      << "Birthday: " << a.BD << endl
      << "Father's name: " << a.Fname << endl
      << "Password: " << a.Pass;
    return o;
}
