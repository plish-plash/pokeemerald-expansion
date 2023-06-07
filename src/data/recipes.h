const struct Recipe gRecipes[] =
{
    [RECIPE_POKE_BALL] =
    {
        .result = ITEM_POKE_BALL,
        .ingredients = {ITEM_RED_APRICORN, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 0, 0, 0},
    },
    [RECIPE_GREAT_BALL] =
    {
        .result = ITEM_GREAT_BALL,
        .ingredients = {ITEM_RED_APRICORN, ITEM_ARMORITE_ORE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 1, 0, 0},
    },
    [RECIPE_ULTRA_BALL] =
    {
        .result = ITEM_ULTRA_BALL,
        .ingredients = {ITEM_RED_APRICORN, ITEM_DYNITE_ORE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 1, 0, 0},
    },
    [RECIPE_NET_BALL] =
    {
        .result = ITEM_NET_BALL,
        .ingredients = {ITEM_GREEN_APRICORN, ITEM_ARMORITE_ORE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 1, 0, 0},
    },
    [RECIPE_NEST_BALL] =
    {
        .result = ITEM_NEST_BALL,
        .ingredients = {ITEM_PINK_APRICORN, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 0, 0, 0},
    },
    [RECIPE_DIVE_BALL] =
    {
        .result = ITEM_DIVE_BALL,
        .ingredients = {ITEM_BLUE_APRICORN, ITEM_ARMORITE_ORE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 1, 0, 0},
    },
    [RECIPE_TIMER_BALL] =
    {
        .result = ITEM_TIMER_BALL,
        .ingredients = {ITEM_WHITE_APRICORN, ITEM_ARMORITE_ORE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 1, 0, 0},
    },
    [RECIPE_QUICK_BALL] =
    {
        .result = ITEM_QUICK_BALL,
        .ingredients = {ITEM_WHITE_APRICORN, ITEM_DYNITE_ORE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 1, 0, 0},
    },
    [RECIPE_REPEAT_BALL] =
    {
        .result = ITEM_REPEAT_BALL,
        .ingredients = {ITEM_PINK_APRICORN, ITEM_ARMORITE_ORE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 1, 0, 0},
    },
    [RECIPE_LUXURY_BALL] =
    {
        .result = ITEM_LUXURY_BALL,
        .ingredients = {ITEM_YELLOW_APRICORN, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 0, 0, 0},
    },
    [RECIPE_HEAVY_BALL] =
    {
        .result = ITEM_HEAVY_BALL,
        .ingredients = {ITEM_BLACK_APRICORN, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .ingredientQuantities = {1, 0, 0, 0},
    },
};