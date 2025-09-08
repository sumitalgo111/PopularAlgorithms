#include "TokenBucket.h"

void TokenBucket::RunRefiller()
{
	//if (!toStopRefiller)
		//cout << "\nStarting Refiller.......\n";

	while (!toStopRefiller)
	{
		{
			//locking this portion by using mutexTokens
			lock_guard<mutex> lock(mutexTokens);

			if (NumberOfTokens == BucketSize)
			{
				//cout << "Bucket Overflow" << endl;
			}
			else
			{
				// Update number of tokens
				NumberOfTokens = std::min(BucketSize, NumberOfTokens + RefillRatePerSecond);

				//cout << "Number of Tokens : " << NumberOfTokens << endl;
			}
		}
		this_thread::sleep_for(chrono::seconds(1));
	}

	//cout << "\nStopping Refiller.......\n";
}


TokenBucket::TokenBucket(long bucketSize, int refillRatePerSecond){
	BucketSize = bucketSize;
	RefillRatePerSecond = refillRatePerSecond;
	NumberOfTokens = 0;
	toStopRefiller = false;

	// start refiller as separate thread in background
	threadRefiller = thread(&TokenBucket::RunRefiller, this);
}

TokenBucket::~TokenBucket()
{
	// stop refiller thread which running in background
	toStopRefiller = true;
	if (threadRefiller.joinable())
		threadRefiller.join();

	cout << "\nTokenBucket Object destoryed\n";
}

bool TokenBucket::allowRequest(int tokensRequired)
{
	//locking this portion by using mutexTokens
	lock_guard<mutex> lock(mutexTokens);

	if (tokensRequired > NumberOfTokens)
	{
		cout << "Not enough tokens" << endl;
		return false;
	}
	NumberOfTokens -= tokensRequired;

	return true;
}