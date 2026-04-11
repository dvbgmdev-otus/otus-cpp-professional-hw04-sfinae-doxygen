#include <string>

#include "app.h"
#include "debug_log.h"

int main(int argc, char* argv[]) {
    DEBUG_LOG("Application started");
    if (argc > 1 && std::string(argv[1]) == "--test") {
        return runTestMode();
    }

    return runTaskMode();
}
