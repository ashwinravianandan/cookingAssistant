add_executable( chef ListGenerator.cpp ListGenerator.h MealDB.cpp MealDB.h MealGenerator.cpp MealGenerator.h OptionsHandler.cpp OptionsHandler.h json-forwards.h json.h jsoncpp.cpp main.cpp Print.h  MealMenuPrinter.cpp MealMenuPrinter.h GroceryListPrinter.cpp GroceryListPrinter.h MealBuilder.cpp MealBuilder.h TagDB.cpp TagDB.h Database.cpp Database.h Meal.h Meal.cpp )


install (TARGETS chef DESTINATION bin)
