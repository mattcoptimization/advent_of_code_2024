#include <regex>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

string read_data(string file_name){
    string result;
    string data_line;
    ifstream textFile(file_name);
    int pos_of_delimiter;

    if (!textFile.is_open()){
        cerr  << "Error opening files!" << endl;
    }
    while (getline(textFile, data_line)){
        result += data_line;
    }
    return result;
}

int match_result(string data, string pattern) {
    regex multiplier_pattern(pattern);
    regex number_pattern("[0-9]{1,3}");
    sregex_iterator multiplier_results(data.begin(), data.end(), multiplier_pattern);
    sregex_iterator end;
    bool mul_enabled = true;
    int inner_mul;
    int result = 0;
    while (multiplier_results != end){
        string multiplier_match = (*multiplier_results)[0];
        if (multiplier_match == "don't()"){
            mul_enabled = false;
            ++ multiplier_results;
            continue;
        } else if (multiplier_match == "do()"){
            mul_enabled = true;
            ++ multiplier_results;
            continue;
        }
        sregex_iterator inner_matches(multiplier_match.begin(), multiplier_match.end(), number_pattern);
        if (mul_enabled){
            inner_mul = 1;
            while (inner_matches != end){
                string inner_number = (*inner_matches)[0];
                inner_mul *= stoi(inner_number);
                ++ inner_matches;
            }
            result += inner_mul;
        }
        ++ multiplier_results;
    }

    return result;
    
}

int main(){
    string file_name = "day_3_input.txt";

    string full_data = read_data(file_name);

    int result = match_result(full_data, "mul\\([0-9]{1,3},[0-9]{1,3}\\)");

    int result_2 = match_result(full_data, "mul\\([0-9]{1,3},[0-9]{1,3}\\)|don't\\(\\)|do\\(\\)");

    cout << result << endl;

    cout << result_2 << endl;

    
    return 0;
}