#include "../../lib/puzzle/board_handler.h"

void board_handler::move(board *board, ops::operators op) {

}

bool board_handler::notSame16(uint8_t* solved, uint8_t* state) {
    auto solvedPtr = (uint64_t *)solved,
         statePtr = (uint64_t *)state;
    uint64_t x = (*solvedPtr ^ *statePtr);
    solvedPtr++;
    statePtr++;
    x += (*solvedPtr ^ *statePtr);
    return !!x;
}

bool board_handler::notSolvedMod4(uint8_t* solved, uint8_t* state, uint8_t length) {
    auto solvedPtr = (uint32_t *)solved,
         statePtr = (uint32_t *)state;
    uint8_t steps = length >> 2;
    for(uint8_t i = 0; i < steps; i++) {
        if(*solvedPtr ^ *statePtr) {
            return true;
        }
    }
    return false;
}

bool board_handler::notSolvedAny(uint8_t* solved, uint8_t* state, uint8_t length) {
    uint8_t *solvedPtr = solved,
            *statePtr = state;

    for(uint8_t i = 0; i < length; i++, solvedPtr++, statePtr++) {
        if(*solvedPtr ^ *statePtr) {
            return true;
        }
    }
    return false;
}