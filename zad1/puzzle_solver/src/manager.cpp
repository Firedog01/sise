#include "../lib/manager.h"


manager::manager(char **argv) : info() {
    std::string strategy(argv[1]);
    file_start_state startStateHandler(argv[3]);

    board* start_state = startStateHandler.getState();
    uint8_t* solved_table = board_handler::getSolvedTable();

    if(strategy == "bfs") {
        ops::operators* order = getOrder(argv[2]); // ops::operators[4]
        std::queue<board*> q_to_process; // queue is silent
        std::vector<board*> visited; //
        q_to_process.emplace(start_state);

        // same is function pointer. There are different functions depending on table_length
        bool (*same)(uint8_t* first, uint8_t* second);
        if(board::len % 8 == 0) {
            same = &board_handler::sameMod16;
        } else if(board::len % 4 == 0) {
            same = &board_handler::sameMod4;
        } else {
            same = &board_handler::sameAny;
        }
        int iterations = 0;
        while(true) {
            if(q_to_process.empty()) {
                std::cout << "no solution found!\n";
                // todo
                break;
            }
            board* cur_state = q_to_process.front();
//            auto cursor = cur_state->path;
//            for(int i = 0; i < cur_state->pathLen; i++, cursor++) {
//                std::cout << *cursor;
//            }
//            std::cout << "\n";
            if(iterations % 100000 == 0) {
                std::cout << iterations << '\n';
            }



            if(same(solved_table, cur_state->table)) {
                std::cout << "solution found!\n";
                // todo
                break;
            } else {
                ops::operators* op = order;
                for(int i = 0; i < 4; i++, op++) {
                    auto new_board = board_handler::createMoved(cur_state, *op);
                    if(new_board == nullptr) {
                        continue;
                    }
                    auto found = std::find_if(
                            visited.begin(),
                            visited.end(),
                            [same, new_board](board* cur) {
                                return same(cur->table, new_board->table);
                            });
                    if(found == visited.end()) { // not found
                        q_to_process.push(new_board);
                    }
                }
            }
            q_to_process.pop();
            delete(cur_state);
            iterations++;
        }


    } else if(strategy == "dfs") {
        auto order = getOrder(argv[2]);

    } else if(strategy == "astr") {
        auto heuristic = getHeuristic(argv[2]);
    }
    delete(start_state);
    auto execTime = info.getExecutionTime();
    std::cout << execTime << '\n';

    std::ofstream solutionFile(argv[4]);

    solutionFile.close();

    std::ofstream infoFile(argv[5]);
    infoFile << info.getLength() << '\n'
             << info.getStatesVisited() << '\n'
             << info.getStatesProcessed() << '\n'
             << info.getMaxDepth() << '\n'
             << std::setprecision(3) << std::fixed << execTime << '\n';
    infoFile.close();

}

/**
 * Creates new table that needs to be deleted.
 *
 * @param s input string
 * @return table of operators, table_len exactly 4 or nullptr
 */
ops::operators* manager::getOrder(std::string s) {
    if(s.size() == 4) {
        auto order = new ops::operators[4];
        for(int i = 0; i < 4; i++) {
            switch(s[i]) {
                case 'L':
                case 'l':
                    order[i] = ops::L;
                    break;
                case 'R':
                case 'r':
                    order[i] = ops::R;
                    break;
                case 'U':
                case 'u':
                    order[i] = ops::U;
                    break;
                case 'D':
                case 'd':
                    order[i] = ops::D;
                    break;
                default:
                    throw std::logic_error("illegal operators, must be permutation of L, R, U, D");
            }
        }
        return order;
    }
    throw std::logic_error("incorrect operators count");
}

ops::heuristics manager::getHeuristic(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if(s == "hamm") {
        return ops::hamm;
    }
    if(s == "manh") {
        return ops::manh;
    }
    return ops::error;
}
