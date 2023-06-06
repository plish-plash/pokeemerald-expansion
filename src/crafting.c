#include "global.h"
#include "crafting.h"
#include "item.h"

#include "data/recipes.h"

bool8 IsRecipeUnlocked(u16 recipeIndex)
{
    return TRUE;
}

u16 GetMaxCraftingCount(u16 recipeIndex)
{
    u8 i;
    u16 quantityInBag;
    u16 maxCrafts = 99;
    const struct Recipe *recipe = &gRecipes[recipeIndex];
    
    for (i = 0; i < MAX_RECIPE_INGREDIENTS; i++)
    {
        if (recipe->ingredients[i] == ITEM_NONE || recipe->ingredientQuantities[i] == 0) break;
        quantityInBag = CountTotalItemQuantityInBag(recipe->ingredients[i]);
        if (quantityInBag == 0) return 0;
        maxCrafts = min(maxCrafts, quantityInBag / recipe->ingredientQuantities[i]);
    }
    return maxCrafts;
}
