//quite a lazy one, but to me the number of computations is insignificant, as 
//sqrt(5e7) was quite small, let alone the number of primes less than that
//It was approx. 1.6 million numbers to sort, which, with the quite bad 3 for loops, 
//took 0.439s, which is not the best
//
//So I decided to change it with a bitset and it surprisingly runs in approx. 0.080ms,
//which is insane. I knew C++ should've been better than what I initially did
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

inline int _4(int n)
{
	return n * n * n * n;
}

inline int _3(int n)
{
	return n * n * n;
}

inline int _2(int n)
{
	return n * n;
}

std::vector <int> primes(int n)
{
	std::vector <bool> composite(n + 1);
	for (int i = 2; i <= n; i++)
		if (!composite[i])
			for (int j = i * 2; j <= n; j += i)
				composite[j] = true;
	std::vector <int> ans;
	for (int i = 2; i <= n; i++)
		if (composite[i] == false)
			ans.push_back(i);
	return ans;
}

const int N = 5e7;
const int BBOUND = 7071; //sqrt(N)

std::bitset <N + 1> cold;  
int main()
{
	std::vector <int> ps = primes(BBOUND); 
	std::vector <int> candidates;
	for (int p1 : ps)
		if (_4(p1) <= N)
		{
			for (int p2 : ps)
			{
				if (_4(p1) + _3(p2) <= N)
					for (int p3 : ps)
					{
						int val = _4(p1) + _3(p2) + _2(p3);
						if (val <= N)
							cold[val] = 1;
						else 
							break;
					}
				else 
					break;
			}
		}
		else 
			break;
	std::cout << cold.count();
}
