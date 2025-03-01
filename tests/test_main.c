#include <greatest.h>

/* Declare the test suites */
SUITE(entity_manager_suite);
SUITE(movement_system_suite);

/* Required by the testing framework */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line arguments, initialization */

    RUN_SUITE(entity_manager_suite);
    RUN_SUITE(movement_system_suite);

    GREATEST_MAIN_END();        /* display results */
}
