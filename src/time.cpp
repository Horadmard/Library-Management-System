#include <ctime>

time_t t = time(0); // get current time from your system
tm *now = localtime(&t);
Today.Year = (now->tm_year + 1900);
Today.Month = (now->tm_mon + 1);
Today.Day = (now->tm_mday);
// cin>>Today;