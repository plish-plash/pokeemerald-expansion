#include "global.h"
#include "event_data.h"
#include "random.h"
#include "pokedex.h"
#include "pokedex_reward.h"
#include "constants/items.h"

static const u16 sMajorRewardItems[] = {
    ITEM_ABILITY_CAPSULE,
    ITEM_ABILITY_PATCH,
};

static const u16 sRewardItems[] = {
    ITEM_LONELY_MINT,
    ITEM_ADAMANT_MINT,
    ITEM_NAUGHTY_MINT,
    ITEM_BRAVE_MINT,
    ITEM_BOLD_MINT,
    ITEM_IMPISH_MINT,
    ITEM_LAX_MINT,
    ITEM_RELAXED_MINT,
    ITEM_MODEST_MINT,
    ITEM_MILD_MINT,
    ITEM_RASH_MINT,
    ITEM_QUIET_MINT,
    ITEM_CALM_MINT,
    ITEM_GENTLE_MINT,
    ITEM_CAREFUL_MINT,
    ITEM_SASSY_MINT,
    ITEM_TIMID_MINT,
    ITEM_HASTY_MINT,
    ITEM_JOLLY_MINT,
    ITEM_NAIVE_MINT,
    ITEM_SERIOUS_MINT,
};

static u16 GetCaughtMonsCount(void)
{
    if (IsNationalPokedexEnabled())
        return GetNationalPokedexCount(FLAG_GET_CAUGHT);
    else
        return GetHoennPokedexCount(FLAG_GET_CAUGHT);
}

bool8 CheckHasPokedexReward(void)
{
    return GetCaughtMonsCount() > VarGet(VAR_POKEDEX_REWARD);
}

void ChoosePokedexReward(void)
{
    u8 i;
    if (VarGet(VAR_POKEDEX_REWARD) % 10 == 0)
    {
        i = Random() % ARRAY_COUNT(sMajorRewardItems);
        gSpecialVar_Result = sMajorRewardItems[i];
    }
    else
    {
        i = Random() % ARRAY_COUNT(sRewardItems);
        gSpecialVar_Result = sRewardItems[i];
    }
}
