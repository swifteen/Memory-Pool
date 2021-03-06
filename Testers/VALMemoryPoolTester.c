/**
 * @file   VALMemoryPoolTester.c
 *
 * @date   Oct 25, 2011
 * @author WangLiang
 * @email  WangLiangCN@live.com
 *
 * @brief  Test program for VALMemoryPool.
 */

#include "../VALMemoryPool/MemoryPool.h"
#include "../MemoryPoolTester.h"
#include <time.h>
#include <sys/time.h>

#ifdef ENABLE_VALMemoryPool

/**
 * @brief Tester for VALMemoryPool.
 */
int VALMemoryPoolTester()
{
	// To compute used time.
	struct timeval startTime, endTime;
	unsigned long long costTime = 0ULL;

	// To store available memory address got from system or pool.
	char **pStrings = (char **)malloc(sizeof(char *) * TEST_MALLOC_TIMES);
	// Generate variable length of string.
	int aStrLen[TEST_MALLOC_TIMES];
	srand((unsigned int)time(NULL) + rand());
	for (int i=0; i<TEST_MALLOC_TIMES; ++i)
	{
		aStrLen[i] = rand() % MALLOC_MAX_LEN;
		srand(aStrLen[i]);
	}

	// Memory pool Malloc/Free test.
	PrintLog("Now testing memory pool Malloc/Free, VAL memory pool.");
	gettimeofday(&startTime, NULL);

	MemoryPool_t *pPool = CreateMemoryPool(MALLOC_MAX_LEN);
	for (int i=0; i<TEST_RETRY_TIMES; ++i)
	{
		for (int j=0; j<TEST_MALLOC_TIMES; ++j)
		{
			pStrings[j] = Malloc(pPool, sizeof(char) * (aStrLen[j] + 1));
			//GenerateRandStr(pStrings[j], aStrLen[j]);
			*pStrings[j] = '\0';
			Free(pPool, pStrings[j]);
		}
	}
	/*
	 * The following code tests when wants to allocate a big block memory than pool can do, then deliver
	 * action to system, and record this memory, when destroy memory pool, all allocated big block will
	 * be release.
	 */
	/*for (int i=0; i<TEST_MALLOC_TIMES; ++i)
	{
		pStrings[i] = Malloc(pPool, sizeof(char) * (aStrLen[i] + MALLOC_MAX_LEN));
	}*/
	DestroyMemoryPool(&pPool);

	gettimeofday(&endTime, NULL);
	costTime = 1000 * 1000 * (endTime.tv_sec - startTime.tv_sec) + endTime.tv_usec - startTime.tv_usec;
	printf("Memory pool Malloc/Free tested, malloc and free %d strings for %d times, cost %llu us.\n",
			TEST_MALLOC_TIMES, TEST_RETRY_TIMES, costTime);

	free(pStrings);
	return 0;
}

#endif /* ENABLE_VALMemoryPool */
