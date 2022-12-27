#include "rcf_basic.h"




int rcf_fetch_ivalue(std::string data, const char* variable_name) {
    // checking if the variable exists.
    size_t variable_name_position = data.find(variable_name, 0);
    if (variable_name_position == -1) {
        printf("rcf_fetch_ivalue error: Variable '%s' was not found. Config file either doesn't contain such variable or there was a misspelling.\n", variable_name);
        return 0;
    }

    // checking how much to copy.
    size_t equal_pos = data.find('=', variable_name_position);
    if (equal_pos == -1) {
        printf("rcf_fetch_ivalue error: Variable \"%s\" is incorrectly formatted. Equal sign not found.\n", variable_name);
        return 0;
    }
    
    size_t newline_pos = data.find('\n', equal_pos); // NOTE: Right now we are requiring the file to have a \n.
    if (newline_pos == -1) {
        printf("rcf_fetch_ivalue error: Variable \"%s\" is incorrectly formatted. Newline character not found.\n", variable_name);
        return 0;
    }
    
    size_t value_size  = newline_pos - equal_pos;
    if ((value_size - 1) == 0) { // Checking if there is no space between the equal sign and the newline character
        printf("rcf_fetch_ivalue error: The value of %s is empty or incorrectly formatted.\n", variable_name);
        return 0;
    }

    std::string copied_string_value;
    copied_string_value = data.substr(equal_pos + 1, value_size-1); // basically slicing the string
    for (int i = 0; i < copied_string_value.length(); i++) { // erasing blank characters.
        if (isblank(copied_string_value[i])) {
            copied_string_value.erase(i, 1);
        }
    }

    if (copied_string_value.empty()) {
        printf("rcf_fetch_ivalue error: The value of %s is empty or incorrectly formatted.\n", variable_name);
        return 0;
    }
    
    int bad_value = 0;
    for (int i = 0; i < copied_string_value.length(); i++) {
        if (isalpha(copied_string_value[i])) {
            printf("rcf_fetch_ivalue error: Variable \"%s\" contains invalid value. Letters were detected.\n", variable_name);
            bad_value = 1;
            break;
        }
    }
    if (!bad_value) {
        int value_as_int = std::stoi(copied_string_value);
        return value_as_int;   
    }
    return 0;
}


float  rcf_fetch_fvalue(std::string data, const char* variable_name) {
    size_t variable_name_position = data.find(variable_name, 0);
    if (variable_name_position == -1) {
        printf("rcf_fetch_fvalue error: Variable '%s' was not found. Config file either doesn't contain such variable or there was a misspelling.\n", variable_name);
        return 0;
    }

    // checking how much to copy.
    size_t equal_pos = data.find('=', variable_name_position);
    if (equal_pos == -1) {
        printf("rcf_fetch_fvalue error: Variable \"%s\" is incorrectly formatted. Equal sign not found.\n", variable_name);
        return 0;
    }
    
    size_t newline_pos = data.find('\n', equal_pos); // NOTE: Right now we are requiring the file to have a \n.
    if (newline_pos == -1) {
        printf("rcf_fetch_fvalue error: Variable \"%s\" is incorrectly formatted. Newline character not found.\n", variable_name);
        return 0;
    }
    
    size_t value_size  = newline_pos - equal_pos;
    if ((value_size - 1) == 0) { // Checking if there is no space between the equal sign and the newline character
        printf("rcf_fetch_fvalue error: The value of %s is empty or incorrectly formatted.\n", variable_name);
        return 0;
    }
    
    std::string copied_string_value;
    copied_string_value = data.substr(equal_pos + 1, value_size-1); // basically slicing the string
    for (int i = 0; i < copied_string_value.length(); i++) { // erasing blank characters.
        if (isblank(copied_string_value[i])) {
            copied_string_value.erase(i, 1);
        }
    }
    
    if (copied_string_value.empty()) {
        printf("rcf_fetch_fvalue error: The value of %s is empty or incorrectly formatted.\n", variable_name);
        return 0;
    }
    
    int bad_value = 0;
    for (int i = 0; i < copied_string_value.length(); i++) {
        if (isalpha(copied_string_value[i])) {
            printf("rcf_fetch_fvalue error: Variable \"%s\" contains invalid value. Letters were detected.\n", variable_name);
            bad_value = 1;
            break;
        }
    }
    if (!bad_value) {
        float value_as_int = std::stof(copied_string_value);
        return value_as_int;   
    }
    return 0;
}


std::string rcf_fetch_svalue(std::string data, const char* variable_name) {
    // checking if the variable exists.
    size_t variable_name_position = data.find(variable_name, 0);
    if (variable_name_position == -1) {
        printf("rcf_fetch_svalue error: Variable '%s' was not found. Config file either doesn't contain such variable or there was a misspelling.\n", variable_name);
        return 0;
    }

    // checking how much to copy.
    size_t equal_pos = data.find('=', variable_name_position);
    if (equal_pos == -1) {
        printf("rcf_fetch_svalue error: Variable \"%s\" is incorrectly formatted. Equal sign not found.\n", variable_name);
        return 0;
    }
    
    size_t newline_pos = data.find('\n', equal_pos); // NOTE: Right now we are requiring the file to have a \n.
    if (newline_pos == -1) {
        printf("rcf_fetch_svalue error: Variable \"%s\" is incorrectly formatted. Newline character not found.\n", variable_name);
        return 0;
    }
    
    size_t value_size  = newline_pos - equal_pos;
    if ((value_size - 1) == 0) { // Checking if there is no space between the equal sign and the newline character
        printf("rcf_fetch_svalue error: The value of %s is empty or incorrectly formatted.\n", variable_name);
        return 0;
    }

    std::string copied_string_value;
    copied_string_value = data.substr(equal_pos + 1, value_size-1); // basically slicing the string
    for (int i = 0; i < copied_string_value.length(); i++) { // erasing blank characters.
        if (isblank(copied_string_value[i])) {
            copied_string_value.erase(i, 1);
        }
    }

    if (copied_string_value.empty()) {
        printf("rcf_fetch_svalue error: The value of %s is empty or incorrectly formatted.\n", variable_name);
        return 0;
    }
    return copied_string_value;
}
