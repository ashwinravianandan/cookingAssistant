add_executable( chef CListGenerator.cpp CListGenerator.h CMealDB.cpp CMealDB.h CMealGenerator.cpp CMealGenerator.h COptionsHandler.cpp COptionsHandler.h json-forwards.h json.h jsoncpp.cpp main.cpp )

install (TARGETS chef DESTINATION bin)
