/*
Pretty lazy approach; One first cuts the 3d cuboid and gets a 2d opened shape of it. Then, the F point now is duplicated 
and the distance between S and F becomes a straight line. If one does this considering (L, l) as a base of the cuboid and 
then (l, h), one gets that the distance is min(sqrt((l+L)^2 + h^2), sqrt((l+h)^2+L^2), sqrt((h+L)^2 + l^2))

We now order them and start calling them a <= b <= c. Then, the smallest is sqrt((a+b)^2+c^2) and we want this to be an
integer. So (a+b)^2 + c^2 = d^2

If you decide to call a + b = x, then x^2 + c^2 = d^2. d^2 <= (m+m)^2 + m^2 = 5m^2, so d <= m sqrt 5, which is O(m). 
Thus you fix (c, d) and find x and then count the pairs (a, b) s.t. a + b = x and 1 <= a <= b <= c

Complexity becomes O(m^2) to count how many triples work with a <= b <= c <= m. To find the answer, binary search it 
on [1, 2000] (2000 was found empirically, the intuition being that 1000 is almost 400000, so it will probably spike 
pretty quickly; also, I needed to test that 2000 works in time) 

Complexity O(m^2 log mmax). It runs in 0.5 - 1s, which is pretty bad, but that's life. 
Turns out you can compute the number of triples in O(m log m) using primitive pythagorean triples, which makes sense because
you can generate them using (a^2 + b^2, 2ab, a^2 - b^2), with 2ab <= m, so the count of (a, b) with 2ab <= m is O(m log m). 
*/
#include <iostream>
#include <cassert>
#include <cmath>
#define ll long long
using namespace std;

int no_sols_m3(int m)
{
    int ans = 0;
    int i, j, k;
    for (i = 1; i <= m; i++)
        for (j = i; j <= m; j++)
            for (k = j; k <= m; k++)
            {
                int val = (i + j) * (i + j) + k * k;
                int rad = sqrt(val);
                if (rad * rad == val)
                {
                    ans++;
                }
            }
    return ans;
}

int no_sols_m2(int m)
{
    int c, d;
    int ans = 0;
    for (c = 1; c <= m; c++)
    {
        int cont = 0;
        for (d = c; d * d <= m * m * 5; d++)
        {
            int val = d * d - c * c;
            int rad = sqrt(val);
            if (rad * rad == val)
            {
                int st = max(rad - c, 1);
                int dr = min(rad / 2, c);
                if (st <= dr)
                    cont += dr - st + 1;
            }
        }
        ans += cont;
    }
    return ans;
}

int main()
{
    int st = 1, dr = 2000;
    while (st <= dr)
    {
        int med = ((st + dr) >> 1);
        if (no_sols_m2(med) >= 1e6)
            dr = med - 1;
        else
            st = med + 1;
    }
    cout << dr + 1;
}
