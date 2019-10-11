#include<iostream>
using namespace std;

int kub_broja(int a)
{
return a*a*a;
}

int main()
{
int b;
cout << "Upišite neki broj: ";
cin >> b;
cout << endl;
cout << "Kub unešenog broja: " << kub_broja(b) << endl;
return 0;
}
