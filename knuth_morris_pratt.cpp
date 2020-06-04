// Knuth-Morris-Pratt algorithm to find pattern in a text

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

vector<int> ComputePrefixFunction(const string& str) {

	vector<int> prefix(str.size(), 0);
	int border = 0;

	for (int i = 1; i < prefix.size(); ++i) {

		while(border > 0 && str[i] != str[border]){
		    border = prefix[border - 1];
		}

		if (str[i] == str[border]) {
		    border = border + 1;
		}

		prefix[i] = border;

	}

	return prefix;
}

vector<int> FindPattern(const string& pattern, const string& text) {

	vector<int> result;

	if (pattern.size() > text.size()) {
		return result;
	}

	string new_str = pattern + "$" + text;
	auto prefix = ComputePrefixFunction(new_str);

	for (int i = pattern.size()+1; i < new_str.size(); ++i) {

		if (prefix[i] == pattern.size()){
		    result.push_back(i-2*pattern.size());
		}

	}

  return result;

}

int main() {

  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);

  for (int i = 0; i < result.size(); ++i) {
    std::cout << result[i] << " ";
  }

  std::cout << std::endl;

  return 0;
}
