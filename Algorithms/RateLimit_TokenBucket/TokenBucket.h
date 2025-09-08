#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

class TokenBucket
{
private:
	long BucketSize;
	long NumberOfTokens;
	int RefillRatePerSecond;

	bool toStopRefiller;
	thread threadRefiller;
	std::mutex mutexTokens;

	void RunRefiller();

	static std::unique_ptr<TokenBucket> instance;

	friend class TokenBucketBuilder;

public:
	// stop to create object directry
	TokenBucket(long bucketSize, int refillRatePerSecond);

	~TokenBucket();

	bool allowRequest(int tokensRequired = 1);

	long getNumberOfTokens()
	{
		return NumberOfTokens;
	}
};
