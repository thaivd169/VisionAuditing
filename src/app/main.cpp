#include <QApplication>
#include <iostream>

#include "session.h"

#ifndef VISION_AUDITING_VERSION_STRING
#define VISION_AUDITING_VERSION_STRING "unknown"
#endif

int main(int argc, char* argv[]) {
    if (argc > 1 &&
        (std::string(argv[1]) == "--version" ||
         std::string(argv[1]) == "-v")) {
        std::cout << VISION_AUDITING_VERSION_STRING << std::endl;
        return 0;
    }

    QApplication app(argc, argv);
    QApplication::setApplicationVersion(VISION_AUDITING_VERSION_STRING);
    Session session(&app);
    return app.exec();
}
