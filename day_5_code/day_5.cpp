#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
using namespace std;

tuple<map<int,vector<int>>,vector<vector<int>>> read_data(string file_name){
    map<int,vector<int>> rules;
    vector<vector<int>> orderings;
    string data_line;
    ifstream textFile(file_name);

    if (!textFile.is_open()){
        cerr  << "Error opening files!" << endl;
    }
    while (getline(textFile, data_line)){
        if (data_line == ""){
            break;
        }
        if (rules.find(stoi(data_line.substr(0,2))) == rules.end()){
            rules[stoi(data_line.substr(0,2))] = {stoi(data_line.substr(3,2))};
        } else {
            rules[stoi(data_line.substr(0,2))].push_back(stoi(data_line.substr(3,2)));
        }
        cout << rules.size() << endl;
    }
    while (getline(textFile, data_line)){
        vector<int> current_ordering;
        while (data_line.find(",") != string::npos){
            current_ordering.push_back(stoi(data_line.substr(0, data_line.find(","))));
            data_line.erase(0, data_line.find(",") + 1);
        }
        current_ordering.push_back(stoi(data_line));
        orderings.push_back(current_ordering);
    }
    return {rules, orderings};
}

int sum_middle_numbers(vector<vector<int>> orderings){
    int middle_element_index;
    int sum_of_middle_numbers = 0;

    for (vector<int> ordering: orderings){
        middle_element_index = static_cast<int>(ordering.size() / 2);
        sum_of_middle_numbers += ordering[middle_element_index];
    }
    return sum_of_middle_numbers;
}

tuple<int,int> find_incorrect_ordering_index(map<int,vector<int>> rules, vector<int> ordering){
    int incorrect_ordering_index_1 = -1;
    int incorrect_ordering_index_2 = -1;
    for (int i = 0; i < ordering.size(); i++){
        for (int j = i + 1; j < ordering.size(); j++){
            // Check that all j are in the rules for i
            if (rules.find(ordering[i]) != rules.end()){
                if (find(rules[ordering[i]].begin(), rules[ordering[i]].end(), ordering[j]) == rules[ordering[i]].end()){
                    incorrect_ordering_index_1 = i;
                    incorrect_ordering_index_2 = j;
                    break;
                }
            } else {
                incorrect_ordering_index_1 = i; // If the rule is not found and this is not the last element in the I array, this is the incorrect ordering
                incorrect_ordering_index_2 = j;
                break;
            }
        }
        if (incorrect_ordering_index_2 != -1 || incorrect_ordering_index_1 != -1){
            break;
        }
    }
    return {incorrect_ordering_index_1, incorrect_ordering_index_2};
}

vector<vector<int>> find_applicable_orderings(map<int,vector<int>> rules, vector<vector<int>> orderings, bool correct_orderings_only = true){
    vector<vector<int>> output_orderings;
    int incorrect_ordering_index_1, incorrect_ordering_index_2;
    for (vector<int> ordering: orderings){
        tie(incorrect_ordering_index_1, incorrect_ordering_index_2) = find_incorrect_ordering_index(rules, ordering);
        if ((correct_orderings_only && incorrect_ordering_index_1 == -1) || (!correct_orderings_only && incorrect_ordering_index_1 != -1)){
            output_orderings.push_back(ordering);
        }
    }
    return output_orderings;
}

vector<int> construct_valid_ordering(map<int,vector<int>> rules, vector<int> ordering){
    int current_incorrect_index_1, current_incorrect_index_2;
    int temp_int_store;
    tie(current_incorrect_index_1, current_incorrect_index_2) = find_incorrect_ordering_index(rules, ordering);
    while (current_incorrect_index_1 != -1){
        temp_int_store = ordering[current_incorrect_index_1];
        ordering[current_incorrect_index_1] = ordering[current_incorrect_index_2];
        ordering[current_incorrect_index_2] = temp_int_store;
        tie(current_incorrect_index_1, current_incorrect_index_2) = find_incorrect_ordering_index(rules, ordering);
    }
    return ordering;
}

vector<vector<int>> correct_invalid_ordering(map<int,vector<int>> rules, vector<vector<int>> orderings){
    vector<vector<int>> corrected_orderings;
    for (vector<int> ordering: orderings){
        corrected_orderings.push_back(construct_valid_ordering(rules, ordering));
    }
    return corrected_orderings;
}

int main() {
    string file_name = "day_5_input.txt";
    map<int,vector<int>> rules;
    vector<vector<int>> orderings;
    vector<vector<int>> valid_orderings, invalid_orderings;
    int sum_of_middle_numbers;
    tie(rules, orderings) = read_data(file_name);

    cout << orderings.size() << endl;

    valid_orderings = find_applicable_orderings(rules, orderings);

    cout << valid_orderings.size() << endl;

    sum_of_middle_numbers = sum_middle_numbers(valid_orderings);

    cout << sum_of_middle_numbers << endl;  

    // Part 2
    invalid_orderings = find_applicable_orderings(rules, orderings, false);

    valid_orderings = correct_invalid_ordering(rules, invalid_orderings);

    sum_of_middle_numbers = sum_middle_numbers(valid_orderings);

    cout << sum_of_middle_numbers << endl;

}