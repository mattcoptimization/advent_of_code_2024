#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
using namespace std;

vector<vector<int>> read_data(string file_name){
    vector<vector<int>> result;
    string data_line;
    ifstream textFile(file_name);
    int pos_of_delimiter;

    if (!textFile.is_open()){
        cerr  << "Error opening files!" << endl;
    }
    while (getline(textFile, data_line)){
        vector<int> interior_line;
        std::istringstream interior_stream(data_line);
        int number;
        
        while (interior_stream >> number) {
            interior_line.push_back(number);
        }
        
        if (!interior_line.empty()) {
            result.push_back(interior_line);
        }
    }
    return result;
}


int find_validity(vector<int> sequence, bool allow_removal){
    int prev_element, difference;
    bool decreasing;
    vector<int> n_minus_2_element_removed, prev_element_removed, current_element_removed;


    if ((sequence[0] - sequence[1]) > 0){
        decreasing = true;
    } else if ((sequence[0] - sequence[1]) < 0){
        decreasing = false;
    } else{
        if (allow_removal){
            prev_element_removed = sequence;
            prev_element_removed.erase(prev_element_removed.begin());
            current_element_removed = sequence;
            current_element_removed.erase(current_element_removed.begin() + 1);
            int result = find_validity(prev_element_removed, false) | find_validity(current_element_removed, false);
            return result;
        } else{
            return 0;
        }
    }
    prev_element = sequence[0];
    if (decreasing){
        for(int i = 1; i< sequence.size(); i++){
            if (((prev_element - sequence[i]) < 1) || ((prev_element - sequence[i]) > 3)){
                if (allow_removal){
                    n_minus_2_element_removed = sequence;
                    if (i > 1){
                        n_minus_2_element_removed.erase(n_minus_2_element_removed.begin() + i - 2);
                    }
                    prev_element_removed = sequence;
                    prev_element_removed.erase(prev_element_removed.begin() + i - 1);
                    current_element_removed = sequence;
                    current_element_removed.erase(current_element_removed.begin() + i);
                    int result = find_validity(prev_element_removed, false) | find_validity(current_element_removed, false) | find_validity(n_minus_2_element_removed, false);
                    return result;
                } else{
                    return 0;
                }

            }
            prev_element = sequence[i];
        }
    } else{
        for(int i = 1; i< sequence.size(); i++){
            if (((sequence[i] - prev_element) < 1) || ((sequence[i] - prev_element) > 3)){
                if (allow_removal){
                    n_minus_2_element_removed = sequence;
                    if (i  > 1){
                        n_minus_2_element_removed.erase(n_minus_2_element_removed.begin() + i - 2);
                    }
                    prev_element_removed = sequence;
                    prev_element_removed.erase(prev_element_removed.begin() + i - 1);
                    current_element_removed = sequence;
                    current_element_removed.erase(current_element_removed.begin() + i);
                    int result = find_validity(prev_element_removed, false) | find_validity(current_element_removed, false) | find_validity(n_minus_2_element_removed, false);
                    return result;
                } else{
                    return 0;
                }
            }
            prev_element = sequence[i];
        }
    }
    return 1;
}

int main(){
    string file_name = "day_2_input.txt";

    vector<vector<int>> full_data = read_data(file_name);

    int safe_reports_strict = 0;
    int safe_reports_loose = 0;
    
    for(vector<int> inner_vector: full_data){
        safe_reports_strict += find_validity(inner_vector, false);
        safe_reports_loose += find_validity(inner_vector, true);
    }

    cout << safe_reports_strict << endl;
    cout << safe_reports_loose << endl;

    

}
