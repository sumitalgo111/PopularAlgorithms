// RateLimit_TokenBucket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\RateLimit_TokenBucket\TokenBucket.h"

class TokenBucket;

class RateLimiter
{
private:
	std::unique_ptr<TokenBucket> upTokenBucket;

public:
	RateLimiter(long bucketSize, int refillRatePerSecond)
	{
		upTokenBucket = std::make_unique<TokenBucket>(bucketSize, refillRatePerSecond);
	}

	bool allowRequest(int tokens = 1)
	{
		if (!upTokenBucket)
			return false;

		if (upTokenBucket->allowRequest(tokens))
		{
			cout << "allowed\n";
			cout << "Available Tokens: " << upTokenBucket->getNumberOfTokens() << endl;
			return true;
		}
		else
		{
			cout << "Not Allowed\n";
			cout << "Available Tokens: " << upTokenBucket->getNumberOfTokens() << endl;
			return false;
		}
	}
};

	int main()
	{
		cout << "Creating Rate Limiter\n";
		cout << "Starting..........\n";
		RateLimiter limiter(15, 3);

		while (true)
		{
			cout << "Enter no of token you need: ";
			int tokens;
			cin >> tokens;

			if (tokens == 0)
				break;

			limiter.allowRequest(tokens);
		}
	}
