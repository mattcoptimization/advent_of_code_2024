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

bool simulate_timestep(int number_of_rows, int number_of_columns, vector<vector<char>>& data, map<array<int, 2>, array<bool, 4>>& directions_at_location, array<int, 2>& current_location, int& current_direction){

    if (update_direction(current_direction, current_location, data)){
        current_direction = next_direction(current_direction);
    } else {
        current_location = move_character(current_direction, current_location);
    }

    if (!check_out_of_bounds(number_of_rows, number_of_columns, current_location)){
        return false;
    }

    return true;
}

map<array<int, 2>, array<bool, 4>> count_number_of_visited_locations(vector<vector<char>> data, array<int, 2> starting_location){
    
    map<array<int, 2>, array<bool, 4>> directions_at_location;
    bool continue_traversing;

    int current_direction = 0;
    array<int, 2> current_position = starting_location;
    int number_of_rows = data.size();
    int number_of_columns = data[0].size();
    directions_at_location[current_position] = {true, false, false, false};
    while (check_out_of_bounds(number_of_rows, number_of_columns, current_position)){
        // Update the direction
        if (!simulate_timestep(number_of_rows, number_of_columns, data, directions_at_location, current_position, current_direction)){
            break;
        }
        if(directions_at_location[current_position][current_direction]){
            directions_at_location.clear();
            return directions_at_location;
        }
        if (directions_at_location.find(current_position) == directions_at_location.end()){
            // Add current location and direction to the map
            directions_at_location[current_position] = {false, false, false, false};
            directions_at_location[current_position][current_direction] = true;
        } else {
            directions_at_location[current_position][current_direction] = true;
        }
        
    }
    return directions_at_location;
}

int count_valid_obstacles(vector<vector<char>> data, array<int, 2> starting_location){
    vector<vector<char>> obstacle_added_data;
    map<array<int, 2>, array<bool, 4>> visited_locations;
    int valid_obstacles = 0;
    for(int i = 0; i < data.size(); i++){
        for (int j = 0; j < data[0].size(); j++){
            array<int, 2> obstacle_location = {i, j};
            if (obstacle_location != starting_location && data[i][j] == '.'){
                obstacle_added_data = data;
                obstacle_added_data[i][j] = '#';
                visited_locations = count_number_of_visited_locations(obstacle_added_data, starting_location);
                if (visited_locations.size() == 0){
                    valid_obstacles++;
                    cout << valid_obstacles << endl;
                }
            }
        }
    }
    return valid_obstacles;
}

int main() {
    vector<vector<char>> data;
    array<int, 2> starting_position;
    string file_name = "day_6_input.txt";
    tie(starting_position, data) = read_data(file_name);

    map<array<int, 2>, array<bool, 4>> locations_visited = count_number_of_visited_locations(data, starting_position);

    int valid_obstacle_count = count_valid_obstacles(data, starting_position);

    cout << locations_visited.size() << endl;

    cout << valid_obstacle_count << endl;
}