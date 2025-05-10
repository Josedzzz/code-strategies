#include <iostream>
#include <vector>
using namespace std;

// merge and count all the right elements
void mergeAndCount(vector<pair<int, int>> &numsWithIndex, int left, int mid,
                   int right, vector<int> &counts) {
  vector<pair<int, int>> temp(right - left + 1);
  int i = left, j = mid + 1, k = 0;
  int rightCount = 0;
  while (i <= mid && j <= right) {
    if (numsWithIndex[i].first <= numsWithIndex[j].first) {
      counts[numsWithIndex[i].second] += rightCount;
      temp[k++] = numsWithIndex[i++];
    } else {
      rightCount++;
      temp[k++] = numsWithIndex[j++];
    }
  }
  while (i <= mid) {
    counts[numsWithIndex[i].second] += rightCount;
    temp[k++] = numsWithIndex[i++];
  }
  while (j <= right) {
    temp[k++] = numsWithIndex[j++];
  }
  for (int idx = 0; idx < k; idx++) {
    numsWithIndex[left + idx] = temp[idx];
  }
}

// primary function to count the smaller numbers
void countSmallerDivideConquer(vector<pair<int, int>> &numsWithIndex, int left,
                               int right, vector<int> &counts) {
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;
  countSmallerDivideConquer(numsWithIndex, left, mid, counts);
  countSmallerDivideConquer(numsWithIndex, mid + 1, right, counts);
  mergeAndCount(numsWithIndex, left, mid, right, counts);
}

// wrapper function to call the solution
vector<int> countSmaller(vector<int> &nums) {
  int n = nums.size();
  vector<int> counts(n, 0);
  vector<pair<int, int>> numsWithIndex(n);
  for (int i = 0; i < n; i++) {
    numsWithIndex[i] = {nums[i], i};
  }
  countSmallerDivideConquer(numsWithIndex, 0, n - 1, counts);
  return counts;
}

int main() {
  vector<int> arr = {5, 2, 6, 1, 3};
  vector<int> result = countSmaller(arr);
  cout << "Result: [ ";
  for (int num : result) {
    cout << num << " ";
  }
  cout << "]" << endl;
  return 0;
}
