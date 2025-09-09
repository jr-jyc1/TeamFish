#include <iostream>
#include "test_board.h"

int main() {
    std::cout << "Running tests..." << std::endl;
    test_starting_position();
    test_checkmate();
    test_no_friendly_fire_check();
    test_stalemate();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
