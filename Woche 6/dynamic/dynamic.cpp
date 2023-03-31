#include <iostream>
#include <vector>
#include <algorithm>

// Test cases
std::vector<std::vector<int>> testCases = {
    {10, 22, 9, 33, 21, 50, 41, 60, 80},
    {3, 4, -1, 0, 6, 2, 3},
    {5, 4, 3, 2, 1},
    {1, 2, 3, 4, 5},
    {10, 9, 2, 5, 3, 7, 101, 18},
};

// Expected results
std::vector<int> expectedResults = {6, 4, 1, 5, 4};

void testLISIterative();
void testLISRecursive();
int lisIterative(const std::vector<int> &arr);
int lisRecursive(const std::vector<int> &arr);
int lisRecursiveHelper(const std::vector<int> &arr, int prev, int cur);

int main()
{
    testLISIterative();
    testLISRecursive();
    return 0;
}

// Iterative solution to find the length of the longest increasing subsequence (LIS)
int lisIterative(const std::vector<int> &arr)
{
    int n = arr.size();
    // Create a vector dp of length n, initialized with 1s
    std::vector<int> dp(n, 1);

    // Iterate through the array and update the dp vector
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            // If arr[i] > arr[j], update the dp[i] value
            if (arr[i] > arr[j])
            {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }

    // Return the maximum value from the dp vector as the LIS length
    return *std::max_element(dp.begin(), dp.end());
}

// Test function for the iterative LIS solution
void testLISIterative()
{
    for (size_t i = 0; i < testCases.size(); ++i)
    {
        int result = lisIterative(testCases[i]);
        // Compare the result with the expected result and print the outcome
        if (result == expectedResults[i])
        {
            std::cout << "Test case " << i + 1 << " (iterative) PASSED." << std::endl;
        }
        else
        {
            std::cout << "Test case " << i + 1 << " (iterative) FAILED. Expected "
                      << expectedResults[i] << ", but got " << result << std::endl;
        }
    }
}

// Recursive solution to find the length of the longest increasing subsequence (LIS)
int lisRecursive(const std::vector<int> &arr)
{
    return lisRecursiveHelper(arr, INT32_MIN, 0);
}

// Recursive helper function for the LIS solution
int lisRecursiveHelper(const std::vector<int> &arr, int prev, int cur)
{
    // Base case: when the current index is equal to the array size
    if (cur == arr.size())
    {
        return 0;
    }

    // If arr[cur] > prev, we can include the current element in the LIS
    int includeCur = 0;
    if (arr[cur] > prev)
    {
        includeCur = 1 + lisRecursiveHelper(arr, arr[cur], cur + 1);
    }
    // Calculate the LIS length by excluding the current element
    int excludeCur = lisRecursiveHelper(arr, prev, cur + 1);

    // Return the maximum of including and excluding the current element
    return std::max(includeCur, excludeCur);
}

// Test function for the recursive LIS solution
void testLISRecursive()
{
    // Iterate through the test cases
    for (size_t i = 0; i < testCases.size(); ++i)
    {
        // Calculate the LIS length using the recursive solution
        int result = lisRecursive(testCases[i]);

        // Compare the result with the expected result and print the outcome
        if (result == expectedResults[i])
        {
            std::cout << "Test case " << i + 1 << " (recursive) PASSED." << std::endl;
        }
        else
        {
            std::cout << "Test case " << i + 1 << " (recursive) FAILED. Expected "
                      << expectedResults[i] << ", but got " << result << std::endl;
        }
    }
}
