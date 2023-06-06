#ifndef GUARD_CRAFTING_H
#define GUARD_CRAFTING_H

enum
{
    RECIPE_POKE_BALL,
    RECIPE_GREAT_BALL,
    RECIPE_ULTRA_BALL,
    RECIPE_NET_BALL,
    RECIPE_NEST_BALL,
    RECIPE_DIVE_BALL,
    RECIPE_TIMER_BALL,
    RECIPE_REPEAT_BALL,
    RECIPE_LUXURY_BALL,
    RECIPES_COUNT,
};

#define MAX_RECIPE_INGREDIENTS 4

struct Recipe
{
    u16 result;
    u16 ingredients[MAX_RECIPE_INGREDIENTS];
    u8 ingredientQuantities[MAX_RECIPE_INGREDIENTS];
};

extern const struct Recipe gRecipes[];

bool8 IsRecipeUnlocked(u16 recipeIndex);
u16 GetMaxCraftingCount(u16 recipeIndex);

#endif // GUARD_CRAFTING_H
