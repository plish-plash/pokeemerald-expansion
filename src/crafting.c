#include "crafting.h"
#include "item.h"
#include "main.h"
#include "malloc.h"

#include "global.h"

#include "data/crafting_recipes.h"

bool32 IsRecipeInCategory(enum Recipe recipe, enum RecipeCategory category)
{
    return gCraftingRecipes[recipe].category == category;
}

u16 GetRecipeOutput(enum Recipe recipe)
{
    return gCraftingRecipes[recipe].output;
}

const u8 *GetRecipeName(enum Recipe recipe)
{
    return GetItemName(GetRecipeOutput(recipe));
}

u16 CanCraftRecipe(enum Recipe recipeNum)
{
    u8 i;
    u16 maxQuantity = MAX_BAG_ITEM_CAPACITY;
    const struct CraftingRecipe *recipe = &gCraftingRecipes[recipeNum];
    for (i = 0; i < MAX_RECIPE_INGREDIENTS; i++)
    {
        if (recipe->ingredients[i] == ITEM_NONE) break;
        maxQuantity = min(maxQuantity, CountTotalItemQuantityInBag(recipe->ingredients[i]) / recipe->ingredientCounts[i]);
    }
    return maxQuantity;
}

void CraftRecipe(enum Recipe recipeNum, u16 quantity)
{
    u8 i;
    const struct CraftingRecipe *recipe = &gCraftingRecipes[recipeNum];
    for (i = 0; i < MAX_RECIPE_INGREDIENTS; i++)
    {
        if (recipe->ingredients[i] == ITEM_NONE) break;
        RemoveBagItem(recipe->ingredients[i], recipe->ingredientCounts[i] * quantity);
    }
    AddBagItem(recipe->output, recipe->outputCount * quantity);
}

bool32 IsRecipeUnlocked(enum Recipe recipe)
{
    u32 index = recipe >> 5;
    u32 subIndex = 1u << (recipe & 0x1f);
    if (gSaveBlock1Ptr->unlockedRecipes[index] & subIndex)
        return TRUE;
    return FALSE;
}

void UnlockRecipe(enum Recipe recipe)
{
    u32 index = recipe >> 5;
    u32 subIndex = 1u << (recipe & 0x1f);
    gSaveBlock1Ptr->unlockedRecipes[index] |= subIndex;
}
