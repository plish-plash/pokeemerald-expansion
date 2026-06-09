#include "crafting.h"

const struct CraftingRecipe gCraftingRecipes[] =
{
    [RECIPE_POKE_BALL] =
    {
        .category = RECIPE_CATEGORY_POKEBALLS,
        .output = ITEM_POKE_BALL,
        .outputCount = 1,
        .ingredients = {ITEM_RED_APRICORN, ITEM_NONE, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 0, 0, 0},
    },
    [RECIPE_POTION] =
    {
        .category = RECIPE_CATEGORY_MEDICINE,
        .output = ITEM_POTION,
        .outputCount = 1,
        .ingredients = {ITEM_ORAN_BERRY, ITEM_FRESH_WATER, ITEM_NONE, ITEM_NONE},
        .ingredientCounts = {1, 1, 0, 0},
    },
    [RECIPE_SUPER_POTION] =
    {
        .category = RECIPE_CATEGORY_MEDICINE,
        .output = ITEM_SUPER_POTION,
        .outputCount = 1,
        .ingredients = {ITEM_ORAN_BERRY, ITEM_FRESH_WATER, ITEM_ABSORB_BULB, ITEM_NONE},
        .ingredientCounts = {1, 1, 1, 0},
    }
};
