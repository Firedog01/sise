#ifndef ZAD1_FILE_START_STATE_H
#define ZAD1_FILE_START_STATE_H

#include <fstream>
#include <iostream>
#include "../includes.h"
#include "../puzzle/board.h"

// max rozmiar 255x255, chyba starczy
class file_start_state {
    uint8_t* state;

public:
    file_start_state(const std::string& file);
    ~file_start_state();
    board* getState();
};


#endif //ZAD1_FILE_START_STATE_H
