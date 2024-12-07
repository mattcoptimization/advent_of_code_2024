#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <set>
#include <array>
using namespace std;

int directions[4][2] = {
    {-1, 0},
    {0, 1}, 
    {1, 0},
    {0, -1}
};


tuple<array<int, 2>, vector<vector<char>>> read_data(string file_name){
    vector<vector<char>> result;
    vector<char> current_line;
    string data_line;
    ifstream textFile(file_name);
    array<int, 2> starting_location = {-1, -1};
    int row, column;

    if (!textFile.is_open()){
        cerr  << "Error opening files!" << endl;
    }
    row = 0;

    while (getline(textFile, data_line)){
        column = 0;
        current_line = {};
        for (char c: data_line){
            if (c == '^'){
                starting_location.at(0) = row;
                starting_location.at(1) = column;
            }
            current_line.push_back(c);
            column ++;
        }
        result.push_back(current_line);
        row ++;
    }
    return {starting_location, result};
}

array<int, 2> move_character(int current_direction, array<int, 2> current_position){
    current_position.at(0) = current_position[0] + directions[current_direction][0];
    current_position.at(1) = current_position[1] + directions[current_direction][1];

    return current_position;
}

bool check_out_of_bounds(int number_of_rows, int number_of_columns, array<int, 2> position){
    return (position[0] < number_of_rows && position[1] < number_of_columns && position[0] >= 0 && position[1] >= 0);
}

bool update_direction(int current_direction, array<int, 2> current_position, vector<vector<char>>& data){
    array<int, 2> next_location = move_character(current_direction, current_position);
    if (check_out_of_bounds(data.size(), data[0].size(), next_location) && data[next_location[0]][next_location[1]] == '#'){
        return true;
    }
    return false;
}

int next_direction(int current_direction){
    if (current_direction == 3){
        return 0;
    } else {
        return current_direction + 1;
    }
}

bool find_loop_in_direction(array<int, 2> current_position, int current_direction, int number_of_rows, int number_of_columns, map<array<int, 2>, array<bool, 4>> directions_at_location){
    int next_dir = next_direction(current_direction);

    while (check_out_of_bounds(number_of_rows, number_of_columns, current_position)){
        if (directions_at_location.find(current_position) != directions_at_location.end()) {
            if (directions_at_location[current_position][next_dir]){
                return true;
            }
        }
        current_position = move_character(next_dir, current_position);
    }
    return false;

}

int count_number_of_visited_locations(vector<vector<char>> data, array<int, 2> starting_location){
    

    set<array<int, 2>> locations_visited, added_obstacles;
    map<array<int, 2>, array<bool, 4>> directions_at_location;

    int current_direction = 0;
    array<int, 2> current_position = starting_location;
    int number_of_rows = data.size();
    int number_of_columns = data[0].size();
    directions_at_location[current_position] = {true, false, false, false};
    locations_visited.insert(current_position);
    while (check_out_of_bounds(number_of_rows, number_of_columns, current_position)){
        current_position = move_character(current_direction, current_position);

        if (!check_out_of_bounds(number_of_rows, number_of_columns, current_position)){
            break;
        }

        locations_visited.insert(current_position);

        if (find_loop_in_direction(current_position, current_direction, number_of_rows, number_of_columns, directions_at_location)){
            array<int, 2> added_obstacle = move_character(current_direction, current_position);
            added_obstacles.insert(move_character(current_direction, current_position));
            cout << added_obstacles.size() << endl;
        } 

        if (directions_at_location.find(current_position) == directions_at_location.end()){
            // Add current location and direction to the map
            directions_at_location[current_position] = {false, false, false, false};
            directions_at_location[current_position][current_direction] = true;
        } else {
            directions_at_location[current_position][current_direction] = true;
        }
        
        // Update the direction
        if (update_direction(current_direction, current_position, data)){
            current_direction = next_direction(current_direction);
        }
    }
    cout << added_obstacles.size() << endl;
    return locations_visited.size();
}

int main() {
    vector<vector<char>> data;
    array<int, 2> starting_position;
    string file_name = "day_6_input.txt";
    tie(starting_position, data) = read_data(file_name);

    int visited_locations = count_number_of_visited_locations(data, starting_position);

    cout << visited_locations << endl;
}