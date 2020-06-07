// Build suffix array of the string text in nlogn time. Return a vector result
// of the same length as the text such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest suffix of text starts.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cctype>
#include <stdexcept>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

#define MAX_CHARS_SIZE 53

// Helper function to print vector
template<typename T>
void PrintVector(vector<T> vec) {

  for (T el : vec) {
      std::cout << el << " ";
  }

  std::cout << std::endl;
}

// Helper function that returns 0 for $, 1-26 for upper case alphabets, 27-53 for lower case
int GetCharIndex(char c) {

  int idx {0};

  if (std::isupper(c)) {
    idx = c - 'A' + 1;
  }
  else if (std::islower(c)) {
    idx = c - 'a' + 27;
  }

  return idx;
}

// Sorts the characters of the text using counting sort
vector<int> SortCharacters(const string& text) {

  vector<int> order(text.size(), 0);

  // Create an array of 53 - 0-25 for upper case alphabets, 26-52 for lower case, 53 for $
  vector<int> count_array(MAX_CHARS_SIZE, 0);

  for(auto c : text) {
    if (!std::isalpha(c) && c != '$') {
      throw std::runtime_error("Text character should be an english alphabet or $");
    }
    auto idx = GetCharIndex(c);
    count_array[idx] += 1;
  }

  // Cummulative sum of count array
  std::partial_sum(count_array.begin(), count_array.end(), count_array.begin());

  for (int i = text.size() - 1; i >= 0; --i) {
    auto idx = GetCharIndex(text[i]);
    auto& count = count_array[idx];
    // count will contain the ith+1 position where the last occurence of the character
    // would go in the sorted array
    order[--count] = i;
  }

  return order;
}

// Compute equivalence group of the characters of the text
vector<int> ComputeCharGroup(const string& text, const vector<int>& order) {

  vector<int> group(text.size(), 0);

  for(int i = 1; i < text.size(); ++i) {

    if (text[order[i]] != text[order[i-1]]) {
      group[order[i]] = group[order[i-1]] + 1;
    }
    else {
      group[order[i]] = group[order[i-1]];
    }

  }

  return group;
}

// Sort doubled cyclic shifts of len L
vector<int> SortDoubled(const string& text, int len, const vector<int>& order, const vector<int>& group) {

  vector<int> new_order(text.size(), 0);
  vector<int> count_array(text.size(), 0);

  for(auto group_num : group) {
    count_array[group_num] += 1;
  }

  std::partial_sum(count_array.begin(), count_array.end(), count_array.begin());

  for(int i = text.size()-1; i >= 0; --i) {
    auto doubled_suffix_idx = (order[i] - len + text.size()) % text.size();
    auto group_num = group[doubled_suffix_idx];
    auto& count = count_array[group_num];
    new_order[--count] = doubled_suffix_idx;
  }

  return new_order;
}

// Compute equivalence groups of the double cyclic shifts of len L
vector<int> UpdateGroup(int len, const vector<int>& order, const vector<int>& group) {

  auto text_len = order.size();
  vector<int> new_group(text_len, 0);

  for(int i = 1; i < order.size(); ++i) {

    auto p_i = make_pair(group[order[i]], group[(order[i]+len)%text_len]);
    auto p_j = make_pair(group[order[i-1]], group[(order[i-1]+len)%text_len]);

    if (p_i != p_j) {
      new_group[order[i]] = new_group[order[i-1]] + 1;
    }
    else {
      new_group[order[i]] = new_group[order[i-1]];
    }

  }

  return new_group;
}

// Driver function
vector<int> BuildSuffixArray(const string& text) {

  auto order = SortCharacters(text);
  //PrintVector<int>(order);
  auto group = ComputeCharGroup(text, order);
  //PrintVector<int>(group);
  int len = 1;

  while (len < text.size()) {
    order = SortDoubled(text, len, order, group);
    //PrintVector<int>(order);
    group = UpdateGroup(len, order, group);
    //PrintVector<int>(group);
    len *= 2;
  }

  return order;

}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  PrintVector<int>(suffix_array);
  return 0;
}
