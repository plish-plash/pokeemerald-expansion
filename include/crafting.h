#ifndef GUARD_CRAFTING_H
#define GUARD_CRAFTING_H

#include "constants/recipes.h"

#define MAX_RECIPE_INGREDIENTS 4

struct Recipe
{
    u16 result;
    u16 ingredients[MAX_RECIPE_INGREDIENTS];
    u8 ingredientQuantities[MAX_RECIPE_INGREDIENTS];
};

extern const struct Recipe gRecipes[];

bool8 IsRecipeUnlocked(u16 recipeIndex);
void UnlockRecipe(void);
u16 GetMaxCraftingCount(u16 recipeIndex);

#endif // GUARD_CRAFTING_H
