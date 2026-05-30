/*
Just a simple sieve. Runs in 1.15 seconds.
*/
#include <iostream>
using namespace std;

const int NMAX = 1e7;

int c[NMAX + 1];

int main()
{
    int i;
    for (i = 1; i <= NMAX; i++)
        for (int j = i; j <= NMAX; j += i)
            c[j]++;
    int ans = 0;
    for (i = 2; i < NMAX; i++)
        ans += (c[i] == c[i + 1]);
    cout << ans;
}
