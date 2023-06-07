#include "global.h"
#include "crafting.h"
#include "event_data.h"
#include "item.h"
#include "string_util.h"

#include "data/recipes.h"

bool8 IsRecipeUnlocked(u16 recipeIndex)
{
    return FlagGet(RECIPE_FLAGS_START + recipeIndex);
}

// This is a script special. Prefer using the "unlockrecipe" macro to calling this function.
void UnlockRecipe(void)
{
    u16 recipeIndex = VarGet(VAR_0x8000);
    FlagSet(RECIPE_FLAGS_START + recipeIndex);
    CopyItemName(gRecipes[recipeIndex].result, gStringVar2);
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
