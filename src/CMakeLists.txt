add_executable( chef CListGenerator.cpp CListGenerator.h CMealDB.cpp CMealDB.h CMealGenerator.cpp CMealGenerator.h COptionsHandler.cpp COptionsHandler.h json-forwards.h json.h jsoncpp.cpp main.cpp Print.h ConsoleMenuPrinter.cpp ConsoleMenuPrinter.h MenuFilePrinter.cpp MenuFilePrinter.h )

install (TARGETS chef DESTINATION bin)
