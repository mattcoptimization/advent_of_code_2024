#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
using namespace std;

tuple< vector<int>, vector<int> > read_data(string file_name, string delimiter){
    vector<int> left_tokens, right_tokens;
    string data_line;
    ifstream textFile(file_name);
    int pos_of_delimiter;

    if (!textFile.is_open()){
        cerr  << "Error opening files!" << endl;
    }
    while (getline(textFile, data_line)){
        pos_of_delimiter = data_line.find(delimiter);
        left_tokens.push_back(stoi(data_line.substr(0, pos_of_delimiter)));
        data_line.erase(0, pos_of_delimiter + delimiter.length());
        right_tokens.push_back(stoi(data_line));
    }
    return {left_tokens, right_tokens};
}

int find_diff(vector<int> left_tokens, vector<int> right_tokens){
    int total_diff;
    for(int i = 0; i<left_tokens.size(); i++){
        total_diff += abs(left_tokens[i] - right_tokens[i]);
    }
    return total_diff;
}

int find_sim_score(vector<int> left_tokens, vector<int> right_tokens){
    set<int> uniqueValues(left_tokens.begin(), left_tokens.end());
    int left_instances, right_instances;

    int total_similarity = 0;

    for (int val: uniqueValues){
        left_instances = count(left_tokens.begin(), left_tokens.end(), val);
        right_instances = count(right_tokens.begin(), right_tokens.end(), val);
        total_similarity += val*right_instances*left_instances;
        
    }

    return total_similarity;
}

int main(){
    string file_name = "day_1_input.txt";
    vector<int> left_tokens, right_tokens, differences;
    string delimiter = "   ";
    int total_diff = 0;
    
    tie(left_tokens, right_tokens) = read_data(file_name, delimiter);

    sort(left_tokens.begin(), left_tokens.end());
    sort(right_tokens.begin(), right_tokens.end());

    cout << find_diff(left_tokens, right_tokens) << endl;

    cout << find_sim_score(left_tokens, right_tokens) << endl;


}