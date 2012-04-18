#include<iostream>
using namespace std;

void test2  ();
void test1  ();
double  c = 1000;
double  a=0;
int main()
{


do
{
 a = a + c;
if ( c > 500 )
 test1  ();
if ( c < 100 )
 test2   ();
 c = c - 1;
}
while( c < 1 );
cout<<"final numeric value for a = "<<a;
}

void test1  ()
{
 a = a + 11  ;
if ( c > 750 )

{
 test2  ();
 a = a + 1  ;
}
}

void test2  ()
{
 a = a + 22;
}

