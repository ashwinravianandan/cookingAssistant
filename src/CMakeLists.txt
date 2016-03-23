add_executable( chef CListGenerator.cpp CListGenerator.h CMealDB.cpp CMealDB.h CMealGenerator.cpp CMealGenerator.h COptionsHandler.cpp COptionsHandler.h json-forwards.h json.h jsoncpp.cpp main.cpp Print.h  MealMenuPrinter.cpp MealMenuPrinter.h GroceryListPrinter.cpp GroceryListPrinter.h MealBuilder.cpp MealBuilder.h TagDB.cpp TagDB.h Database.cpp Database.h Meal.h Meal.cpp )


install (TARGETS chef DESTINATION bin)
