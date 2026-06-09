#ifndef GUARD_EVEN_CRAFTING_H
#define GUARD_EVEN_CRAFTING_H
#include "global.h"
#include "constants/crafting.h"

#define MAX_RECIPE_INGREDIENTS 4

struct CraftingRecipe {
    enum RecipeCategory category;
    u16 output;
    u8 outputCount;
    u16 ingredients[MAX_RECIPE_INGREDIENTS];
    u8 ingredientCounts[MAX_RECIPE_INGREDIENTS];
};

extern const struct CraftingRecipe gCraftingRecipes[];

bool32 IsRecipeInCategory(enum Recipe recipe, enum RecipeCategory category);
u16 GetRecipeOutput(enum Recipe recipe);
const u8 *GetRecipeName(enum Recipe recipe);
u16 CanCraftRecipe(enum Recipe recipe);
void CraftRecipe(enum Recipe recipe, u16 quantity);

bool32 IsRecipeUnlocked(enum Recipe recipe);
void UnlockRecipe(enum Recipe recipe);

#endif
