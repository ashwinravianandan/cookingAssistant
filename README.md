# Cooking Assistant

## Introduction
Cooking assistant, packaged as _chef_ is a list generator that processes a Json
meal database and generates a list of randomized meals. In addition to this, it
generates a grocery list needed to execute the menu. Very often one gets in to
the rut of cooking the same dishes over an over in spite of having a wide range
of recipes to choose from. This command line utility encourages you to prepare
something new everyday thereby ensuring a balanced diet and a refreshing meal.

## Installation
_chef_ would have to be built from sources but has not external dependencies. So
building a installing should be straight forward provided you have a modern c++
compiler. Please follow the below steps to build and install _chef_.

    git clone https://github.com/ashwinravianandan/cookingAssistant.git
    cd cookingAssistant
    ./configure && make
    sudo make install

Once installed, you should be able to invoke chef from the command line.

## Usage
In order to use chef you would have to construct a Json database of recipes. A
reference database is available as a part of this repository. The Json database
has three main sections. One dedicated for _recipe groups_, one for _meal items_
and one for _sides_. These categories are discussed in details in the next
section of the document.

Chef accepts a path to the database file as a command line argument. If not
command line argument is specified, chef would wait for the database on stdin.
So chef could be invoked using the below syntax.

    chef -i menu.json
    cat menu.json | chef
    chef < menu.json

Chef currently generate ten meal items of the category _bread_ and four of the
category _rice_. Currently only these to meal categories are supported. Chef
would output the results on stdout.  Below is a sample response.

    -----MENU-----
             aloo paratha
             methi paratha
             chapathi - rajma masala
             gobi paratha
             chapathi - aloo mutter
             chapathi - aloo sagu
             chapathi - colocasia dry
             chapathi - tomato gojju
             chapathi - lady finger gojju
             chapathi - dal fry
             white rice - khol khol sambar
             white rice - raddish sambar
             bisi bele bath
             white rice - dal fry
    
    -----GROCERY-LIST-----
            * ghee
            * carrot
            * beans
            * toor dal
            * raddish
            * khol khol
            * rice
            * sambar powder
            * tamarind
            * fenugreek seeds
            * hing
            * bisi bele bath masala
            * urad dal
            * onion
            * potatoes
            * bey leaves
            * peas
            * lady finger
            * wheat flour
            * cashewnut
            * refinedoil
            * curryleaves
            * mustardseeds
            * tomatoes
            * jeera
            * greenchilly
            * redchilly
            * ginger
            * corianderleaves
            * salt
            * methi
            * tomato
            * garlic
            * danyapowder
            * cardamom
            * redchillypowder
            * rajma
            * turmericpowder
            * gobi
            * coconut
            * onions
            * cloves
            * colocasia

It is possible output the grocery list and the menu on separate files. This is
done by providing chef the command line options -g and -m respectively. Invoking
chef as below would save the grocery list on groceryList.txt and the menu on
menu.txt respectively.

    chef -i menu.json -g groceryList.txt -m menu.txt

## Database structure
As mentioned in the previous section, the food database has three primary
sections. They will be discussed in detail here.

### Recipe Groups
Recipe groups is an array of Json objects. Each entry in the array is a recipe
group which is nothing but a logical grouping of ingredients. The value of the
_groupName_ attribute can be used while describing _Meal Items_ and _Sides_.
On doing this, the ingredients represented by the recipe group would be added
to the _Meal Item_ or _Side_. The main purpose of a recipe group is to capture
repeating ingredients and to simplify the description of the ingredients of a
recipe.  Below is a sample definition of valid recipe groups.

    "recipeGroups": [
       { "groupName":"seasoning", "ingredients": [ "curry leaves", "mustard seeds",
    "jeera", "green chilly", "red chilly", "turmeric powder", "coriander leaves", "refined oil" ] },
       { "groupName":"gingerGarlic", "ingredients": [ "ginger", "garlic" ] }
    ]

### Meal Items
_Meal Items_ are used to describe the main course items of a meal. They are
broadly classified into two categories, _bread_ and _rice_. These categories
are used in the list generation algorithm. Most attributes in the meal item
structure are self explanatory. The value of the _category_ attribute under the
_eatWith_ attribute is of special interest. It is this value that binds a meal
item to a side dish. If the _eatWith_ attribute is an empty json attribute,
it is assumed that the meal item needs no side dish. In that case the search
algorithm would not pair it with a side dish. Below is an example of a valid
meal item definition.

    "mealItems": [
      { "dishName": "aloo paratha","category": "bread", "eatWith": {}, 
    "recipeGroup": ["seasoning"], "ingredients": [ "wheat flour", "salt", "potatoes", "onion" ] },
      { "dishName": "ven pongal", "category": "rice", "eatWith": {"category":"sambar"},
    "ingredients": [ "rice", "moong dal", "ghee", "jeera", "pepper" ], "recipeGroup": ["seasoning"] }
    ]


### Sides
Side dishes are accompaniments to meal items. Most attributes again are self
explanatory. The array of strings referred to by category defines different tags
that can be used by meal items. A side can have more than one category.  Below is an example of a valid definition of sides.

    "sides": [
      { "dishName": "dal palak", "category" : ["withChapathi", "withRice" ], 
    "ingredients": [ "palak", "toor dal", "tomatoes", "tamarind" , "onion"], "recipeGroup": [ "seasoning" ] },
      { "dishName": "rajma masala", "category" : ["withChapathi", "withRice" ], "ingredients": 
    ["tomatoes", "rajma", "onion" ], "recipeGroup": ["seasoning", "spices", "gingerGarlic", "chillyDhanya"] }
    ]

## Open Items
The following features will be supported in future

   * Meal item categories should be dynamically definable instead of being restricted to _bread_ and _rice_
   * It should be possible to specify the number of meal items of a desired category to be generated via the command line
   * It should be possible to add and remove entries from the json database using the tool rather than having to edit it manually
