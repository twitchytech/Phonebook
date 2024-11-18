#include "../include/app.h"

int main(void) {
    int r = setup_db();
    if (r) {
        log_error(get_errMsg(r));
        return EXIT_FAILURE;
    }
    login();

    return EXIT_SUCCESS;
}
