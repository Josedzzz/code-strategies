#include <iostream>
#include <vector>
using namespace std;

// count the ocurrences of a number
int countOccurrences(const vector<int> &nums, int left, int right, int num) {
  int count = 0;
  for (int i = left; i <= right; i++) {
    if (nums[i] == num) {
      count++;
    }
  }
  return count;
}

// primary function to find the majority element
int majorityElementDivideConquer(const vector<int> &nums, int left, int right) {
  if (left == right) {
    return nums[left];
  }
  int mid = left + (right - left) / 2;
  int leftCandidate = majorityElementDivideConquer(nums, left, mid);
  int rightCandidate = majorityElementDivideConquer(nums, mid + 1, right);
  if (leftCandidate == rightCandidate) {
    return leftCandidate;
  }
  int leftCount = countOccurrences(nums, left, right, leftCandidate);
  int rightCount = countOccurrences(nums, left, right, rightCandidate);
  int majorityThreshold = (right - left + 1) / 2 + 1;
  if (leftCount >= majorityThreshold) {
    return leftCandidate;
  } else if (rightCount >= majorityThreshold) {
    return rightCandidate;
  } else {
    return -1;
  }
}

// wrapper function to call the recursive solution
int majorityElement(vector<int> &nums) {
  if (nums.empty())
    return -1;
  return majorityElementDivideConquer(nums, 0, nums.size() - 1);
}

int main() {
  vector<int> arr = {2, 2, 1, 1, 1, 2, 2};
  int result = majorityElement(arr);
  cout << "Result: " << result << endl;
  return 0;
}
