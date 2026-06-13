#include "crafting.h"

const struct CraftingRecipe gCraftingRecipes[] =
{
    // Pokeballs
    [RECIPE_LEVEL_BALL] =
    {
        .category = RECIPE_CATEGORY_POKEBALLS,
        .output = ITEM_LEVEL_BALL,
        .outputCount = 1,
        .ingredients = {ITEM_RED_APRICORN, ITEM_TUMBLESTONE, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },
    [RECIPE_LURE_BALL] =
    {
        .category = RECIPE_CATEGORY_POKEBALLS,
        .output = ITEM_LURE_BALL,
        .outputCount = 1,
        .ingredients = {ITEM_BLUE_APRICORN, ITEM_TUMBLESTONE, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },
    [RECIPE_MOON_BALL] =
    {
        .category = RECIPE_CATEGORY_POKEBALLS,
        .output = ITEM_MOON_BALL,
        .outputCount = 1,
        .ingredients = {ITEM_YELLOW_APRICORN, ITEM_TUMBLESTONE, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },
    [RECIPE_FRIEND_BALL] =
    {
        .category = RECIPE_CATEGORY_POKEBALLS,
        .output = ITEM_FRIEND_BALL,
        .outputCount = 1,
        .ingredients = {ITEM_GREEN_APRICORN, ITEM_TUMBLESTONE, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },
    [RECIPE_LOVE_BALL] =
    {
        .category = RECIPE_CATEGORY_POKEBALLS,
        .output = ITEM_LOVE_BALL,
        .outputCount = 1,
        .ingredients = {ITEM_PINK_APRICORN, ITEM_TUMBLESTONE, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },
    [RECIPE_FAST_BALL] =
    {
        .category = RECIPE_CATEGORY_POKEBALLS,
        .output = ITEM_FAST_BALL,
        .outputCount = 1,
        .ingredients = {ITEM_WHITE_APRICORN, ITEM_TUMBLESTONE, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },
    [RECIPE_HEAVY_BALL] =
    {
        .category = RECIPE_CATEGORY_POKEBALLS,
        .output = ITEM_HEAVY_BALL,
        .outputCount = 1,
        .ingredients = {ITEM_BLACK_APRICORN, ITEM_TUMBLESTONE, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },

    // Special
    [RECIPE_ABILITY_CAPSULE] =
    {
        .category = RECIPE_CATEGORY_SPECIAL,
        .output = ITEM_ABILITY_CAPSULE,
        .outputCount = 1,
        .ingredients = {ITEM_NUGGET, ITEM_COMET_SHARD, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },
    [RECIPE_ABILITY_PATCH] =
    {
        .category = RECIPE_CATEGORY_SPECIAL,
        .output = ITEM_ABILITY_PATCH,
        .outputCount = 1,
        .ingredients = {ITEM_BIG_NUGGET, ITEM_COMET_SHARD, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    }
};
