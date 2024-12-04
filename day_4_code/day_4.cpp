#include <regex>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
string read_data(string file_name){
    string result;
    string data_line;
    ifstream textFile(file_name);

    if (!textFile.is_open()){
        cerr  << "Error opening files!" << endl;
    }
    while (getline(textFile, data_line)){
        result += data_line + "\n";
    }
    return result;
}

int line_length(string file_name){
    int result;
    string data_line;
    ifstream textFile(file_name);

    if (!textFile.is_open()){
        cerr  << "Error opening files!" << endl;
    }
    while (getline(textFile, data_line)){
        result = data_line.length();
        break;
    }
    return result;
}


int pattern_counter(string data, string pattern){
    regex word_pattern(pattern);
    sregex_iterator pattern_results(data.begin(), data.end(), word_pattern);
    sregex_iterator pattern_end;
    int result = distance(pattern_results, pattern_end);
    cout << result << endl;
    return result;
}



int main(){
    string file_name = "day_4_input.txt";

    string full_data = read_data(file_name);


    int length_of_line = line_length(file_name);

    // Part 1

    // Right
    int pattern_count = pattern_counter(full_data, "XMAS");

    // Left
    pattern_count += pattern_counter(full_data, "SAMX");
    
    // Up
    pattern_count += pattern_counter(full_data, "(?=(S[\\s\\S]{" + to_string(length_of_line) + "}A[\\s\\S]{" + to_string(length_of_line) + "}M[\\s\\S]{" + to_string(length_of_line) + "}X))");
    
    // Down
    pattern_count += pattern_counter(full_data, "(?=(X[\\s\\S]{" + to_string(length_of_line) + "}M[\\s\\S]{" + to_string(length_of_line) + "}A[\\s\\S]{" + to_string(length_of_line) + "}S))");

    // Left down diagonal
    pattern_count += pattern_counter(full_data, "(?=(X[\\s\\S]{" + to_string(length_of_line-1) + "}M[\\s\\S]{" + to_string(length_of_line-1) + "}A[\\s\\S]{" + to_string(length_of_line-1) + "}S))");

    // Right down diagonal
    pattern_count += pattern_counter(full_data, "(?=(X[\\s\\S]{" + to_string(length_of_line+1) + "}M[\\s\\S]{" + to_string(length_of_line+1) + "}A[\\s\\S]{" + to_string(length_of_line+1) + "}S))");

    // Left up diagonal
    pattern_count += pattern_counter(full_data, "(?=(S[\\s\\S]{" + to_string(length_of_line-1) + "}A[\\s\\S]{" + to_string(length_of_line-1) + "}M[\\s\\S]{" + to_string(length_of_line-1) + "}X))");

    // Right up diagonal
    pattern_count += pattern_counter(full_data, "(?=(S[\\s\\S]{" + to_string(length_of_line+1) + "}A[\\s\\S]{" + to_string(length_of_line+1) + "}M[\\s\\S]{" + to_string(length_of_line+1) + "}X))");

    cout << pattern_count << endl;

    // Part 2

    // Pattern 1
    pattern_count = pattern_counter(full_data, "(?=(M.{1}S[\\s\\S]{" + to_string(length_of_line-1) + "}A[\\s\\S]{" + to_string(length_of_line-1) + "}M.{1}S))");

    // Pattern 2
    pattern_count += pattern_counter(full_data, "(?=(M.{1}M[\\s\\S]{" + to_string(length_of_line-1) + "}A[\\s\\S]{" + to_string(length_of_line-1) + "}S.{1}S))");

    // Pattern 3
    pattern_count += pattern_counter(full_data, "(?=(S.{1}M[\\s\\S]{" + to_string(length_of_line-1) + "}A[\\s\\S]{" + to_string(length_of_line-1) + "}S.{1}M))");

    // Pattern 4
    pattern_count += pattern_counter(full_data, "(?=(S.{1}S[\\s\\S]{" + to_string(length_of_line-1) + "}A[\\s\\S]{" + to_string(length_of_line-1) + "}M.{1}M))");

    cout << pattern_count << endl;

    return 0;
}
