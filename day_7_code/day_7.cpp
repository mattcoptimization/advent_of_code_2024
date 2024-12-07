#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <sstream>
using namespace std;
// Read the data into a tuple of int, vector<int>

tuple<vector<long long>, vector<vector<int>>> read_data(string file_name){
    vector<vector<int>> numbers;
    vector<long long> sums;
    string data_line;
    ifstream textFile(file_name);

    if (!textFile.is_open()){
        cerr  << "Error opening files!" << endl;
    }

    while (getline(textFile, data_line)){
        int col_loc = data_line.find(':');
        sums.push_back(stoll(data_line.substr(0, col_loc)));
        stringstream ss(data_line.substr(col_loc+1));
        int num;
        vector<int> current_numbers;
        while (ss >> num){
            current_numbers.push_back(num);
        }
        numbers.push_back(current_numbers);
    }
    return {sums, numbers};
}

vector<int> convert_to_base_n(int num, int base, int length) {
    vector<int> result(length, 0); 
    
    int idx = length - 1;
    while (num > 0 && idx >= 0) {
        result[idx] = num % base;
        num /= base;
        idx--;
    }
    
    return result;
}

vector<vector<int>> generate_all_combinations(int length_of_numbers, int base) {
    vector<vector<int>> result;
    int total_combinations = pow(base, (length_of_numbers-1)); 
    
    // Generate all combinations from 0 to base^length - 1
    for (int i = 0; i < total_combinations; i++) {
        result.push_back(convert_to_base_n(i, base, length_of_numbers-1));
    }
    
    return result;
}


// Function to loop over all of the rows
long long valid_summations(vector<long long> sums, vector<vector<int>> inputs, int base){
    long long test_sum;
    long long current_sum;
    long long valid_summations = 0;
    vector<int> current_inputs, current_combination;
    vector<vector<int>> current_combinations;
    for (int i = 0; i < sums.size(); i++){
        test_sum = sums[i];
        current_inputs = inputs[i];
        current_combinations = generate_all_combinations(current_inputs.size(), base);
        for (int j = 0; j < current_combinations.size(); j++){
            current_sum = current_inputs[0];
            current_combination = current_combinations[j];
            for (int k = 1; k < current_inputs.size(); k++){
                if (current_combination[k-1] == 0){
                    current_sum += current_inputs[k];
                } else if(current_combination[k-1] == 1){
                    current_sum *= current_inputs[k];
                } else if (current_combination[k-1] == 2){
                    current_sum = stoll(to_string(current_sum) + to_string(current_inputs[k]));
                }
            }
            if (current_sum == test_sum){
                valid_summations += test_sum;
                cout << valid_summations << endl;
                break;
            }
        }
    }
    return valid_summations;
}

int main(){
    string file_name = "day_7_input.txt";
    vector<long long> sums;
    vector<vector<int>> numbers;

    tie(sums, numbers) = read_data(file_name);

    long long valid_summation = valid_summations(sums, numbers, 2);

    cout << valid_summation << endl;

    valid_summation = valid_summations(sums, numbers, 3);

    cout <<valid_summation << endl;
}