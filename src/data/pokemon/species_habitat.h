const struct SpeciesHabitat gSpeciesHabitat[NUM_WILD_SPECIES] =
{
    [SPECIES_BULBASAUR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_IVYSAUR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_VENUSAUR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_CHARMANDER] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CHARMELEON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CHARIZARD] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SQUIRTLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_WARTORTLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_BLASTOISE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_CATERPIE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_METAPOD] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_BUTTERFREE] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_WEEDLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_KAKUNA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_BEEDRILL] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_PIDGEY] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_PIDGEOTTO] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_PIDGEOT] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_RATTATA] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_RATICATE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SPEAROW] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_FEAROW] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_EKANS] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ARBOK] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_PIKACHU] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_RAICHU] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SANDSHREW] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SANDSLASH] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_NIDORAN_F] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_NIDORINA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_NIDOQUEEN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_NIDORAN_M] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_NIDORINO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_NIDOKING] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CLEFAIRY] = {
        .flags = HABITAT_CAVE | HABITAT_DAY,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CLEFABLE] = {
        .flags = HABITAT_CAVE | HABITAT_DAY,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_VULPIX] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_NINETALES] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_JIGGLYPUFF] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_WIGGLYTUFF] = {
        .flags = HABITAT_CAVE | HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ZUBAT] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_GOLBAT] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_ODDISH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GLOOM] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_VILEPLUME] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_PARAS] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_PARASECT] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_VENONAT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_VENOMOTH] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_DIGLETT] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_DUGTRIO] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_MEOWTH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_PERSIAN] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_PSYDUCK] = {
        .flags = HABITAT_LAND | HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_GOLDUCK] = {
        .flags = HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_MANKEY] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_PRIMEAPE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_GROWLITHE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ARCANINE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_POLIWAG] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_POLIWHIRL] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_POLIWRATH] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_ABRA] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_KADABRA] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_ALAKAZAM] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_MACHOP] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_MACHOKE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_MACHAMP] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_BELLSPROUT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_WEEPINBELL] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_VICTREEBEL] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_TENTACOOL] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_TENTACRUEL] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_GEODUDE] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_GRAVELER] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_GOLEM] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_PONYTA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_RAPIDASH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SLOWPOKE] = {
        .flags = HABITAT_LAND | HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_SLOWBRO] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_MAGNEMITE] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_MAGNETON] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_FARFETCHD] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_DODUO] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_DODRIO] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SEEL] = {
        .flags = HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_DEWGONG] = {
        .flags = HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_GRIMER] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_MUK] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_SHELLDER] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_CLOYSTER] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_GASTLY] = {
        .flags = HABITAT_LAND | HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_HAUNTER] = {
        .flags = HABITAT_LAND | HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GENGAR] = {
        .flags = HABITAT_LAND | HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ONIX] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_DROWZEE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_HYPNO] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_KRABBY] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_KINGLER] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_VOLTORB] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_ELECTRODE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_EXEGGCUTE] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_EXEGGUTOR] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_CUBONE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_MAROWAK] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_HITMONLEE] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_HITMONCHAN] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_LICKITUNG] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_KOFFING] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_WEEZING] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_RHYHORN] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_RHYDON] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CHANSEY] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_TANGELA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_KANGASKHAN] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_HORSEA] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_SEADRA] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_GOLDEEN] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_SEAKING] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_STARYU] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_STARMIE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_MR_MIME] = {
        .flags = HABITAT_CAVE | HABITAT_DAY,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_SCYTHER] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_JYNX] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_ELECTABUZZ] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MAGMAR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_PINSIR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_TAUROS] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MAGIKARP] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_GYARADOS] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_LAPRAS] = {
        .flags = HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_DITTO] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_EEVEE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_VAPOREON] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_JOLTEON] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_FLAREON] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_PORYGON] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_OMANYTE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_OMASTAR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KABUTO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KABUTOPS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_AERODACTYL] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SNORLAX] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_ARTICUNO] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_ZAPDOS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MOLTRES] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_DRATINI] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_DRAGONAIR] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_DRAGONITE] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_MEWTWO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MEW] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CHIKORITA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_BAYLEEF] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MEGANIUM] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CYNDAQUIL] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_QUILAVA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TYPHLOSION] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TOTODILE] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_CROCONAW] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_FERALIGATR] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_SENTRET] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_FURRET] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_HOOTHOOT] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_NOCTOWL] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_LEDYBA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_LEDIAN] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SPINARAK] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_ARIADOS] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_CROBAT] = {
        .flags = 0,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_CHINCHOU] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_LANTURN] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_PICHU] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_CLEFFA] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_IGGLYBUFF] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_TOGEPI] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_TOGETIC] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_NATU] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_XATU] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_MAREEP] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_FLAAFFY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_AMPHAROS] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_BELLOSSOM] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MARILL] = {
        .flags = HABITAT_LAND | HABITAT_WATER | HABITAT_CAVE | HABITAT_DAY,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_AZUMARILL] = {
        .flags = HABITAT_LAND | HABITAT_WATER | HABITAT_DAY,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_SUDOWOODO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_POLITOED] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_HOPPIP] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SKIPLOOM] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_JUMPLUFF] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_AIPOM] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SUNKERN] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SUNFLORA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_YANMA] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_WOOPER] = {
        .flags = HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_QUAGSIRE] = {
        .flags = HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_ESPEON] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_UMBREON] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_MURKROW] = {
        .flags = HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SLOWKING] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_MISDREAVUS] = {
        .flags = HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_UNOWN] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_WOBBUFFET] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_GIRAFARIG] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_PINECO] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_FORRETRESS] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_DUNSPARCE] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_GLIGAR] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_STEELIX] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_SNUBBULL] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_GRANBULL] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_QWILFISH] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_SCIZOR] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SHUCKLE] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_HERACROSS] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_SNEASEL] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_TEDDIURSA] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_URSARING] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SLUGMA] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_MAGCARGO] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_SWINUB] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_PILOSWINE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_CORSOLA] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_REMORAID] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_OCTILLERY] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_DELIBIRD] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_MANTINE] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SKARMORY] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_HOUNDOUR] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_HOUNDOOM] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_KINGDRA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_PHANPY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_DONPHAN] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_PORYGON2] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_STANTLER] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SMEARGLE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_TYROGUE] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_HITMONTOP] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_SMOOCHUM] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_ELEKID] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MAGBY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_MILTANK] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_BLISSEY] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_RAIKOU] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ENTEI] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SUICUNE] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_LARVITAR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_PUPITAR] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TYRANITAR] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_LUGIA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HO_OH] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CELEBI] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_TREECKO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_GROVYLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SCEPTILE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_TORCHIC] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_COMBUSKEN] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_BLAZIKEN] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_MUDKIP] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_MARSHTOMP] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_SWAMPERT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_POOCHYENA] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MIGHTYENA] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ZIGZAGOON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_LINOONE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_WURMPLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SILCOON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_BEAUTIFLY] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_CASCOON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_DUSTOX] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_LOTAD] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_LOMBRE] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_LUDICOLO] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_SEEDOT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_NUZLEAF] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SHIFTRY] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_TAILLOW] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_SWELLOW] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_WINGULL] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_PELIPPER] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_RALTS] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_KIRLIA] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_GARDEVOIR] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_SURSKIT] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_MASQUERAIN] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_SHROOMISH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_BRELOOM] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SLAKOTH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_VIGOROTH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SLAKING] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_NINCADA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_NINJASK] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SHEDINJA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_WHISMUR] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_LOUDRED] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_EXPLOUD] = {
        .flags = 0,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_MAKUHITA] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_HARIYAMA] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_AZURILL] = {
        .flags = HABITAT_LAND | HABITAT_WATER | HABITAT_DAY,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_NOSEPASS] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_SKITTY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_DELCATTY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SABLEYE] = {
        .flags = HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MAWILE] = {
        .flags = HABITAT_CAVE | HABITAT_DAY,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_ARON] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_LAIRON] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_AGGRON] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_MEDITITE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_MEDICHAM] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_ELECTRIKE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MANECTRIC] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_PLUSLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MINUN] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_VOLBEAT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_ILLUMISE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_ROSELIA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GULPIN] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SWALOT] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CARVANHA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_SHARPEDO] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_WAILMER] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_WAILORD] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_NUMEL] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CAMERUPT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TORKOAL] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SPOINK] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_GRUMPIG] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_SPINDA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TRAPINCH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_VIBRAVA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_FLYGON] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_CACNEA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CACTURNE] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SWABLU] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_ALTARIA] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_ZANGOOSE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SEVIPER] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_LUNATONE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_SOLROCK] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_BARBOACH] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_WHISCASH] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_CORPHISH] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_CRAWDAUNT] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_BALTOY] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_CLAYDOL] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_LILEEP] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CRADILY] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ANORITH] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_ARMALDO] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_FEEBAS] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_MILOTIC] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_CASTFORM] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_KECLEON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_FOREST,
        .encounter = 0,
    },
    [SPECIES_SHUPPET] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_BANETTE] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_DUSKULL] = {
        .flags = HABITAT_LAND | HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DUSCLOPS] = {
        .flags = HABITAT_LAND | HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TROPIUS] = {
        .flags = 0,
        .biome = BIOME_FOREST,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_CHIMECHO] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_ABSOL] = {
        .flags = HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_WYNAUT] = {
        .flags = 0,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_SNORUNT] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_GLALIE] = {
        .flags = 0,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_SPHEAL] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_SEALEO] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_WALREIN] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_CLAMPERL] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_HUNTAIL] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_GOREBYSS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_RELICANTH] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_LUVDISC] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_BAGON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SHELGON] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SALAMENCE] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_BELDUM] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_METANG] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_METAGROSS] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_REGIROCK] = {
        .flags = 0,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_REGICE] = {
        .flags = 0,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_REGISTEEL] = {
        .flags = 0,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_LATIAS] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_LATIOS] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_KYOGRE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GROUDON] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_RAYQUAZA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_JIRACHI] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_DEOXYS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TURTWIG] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GROTLE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_TORTERRA] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CHIMCHAR] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_MONFERNO] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_INFERNAPE] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_PIPLUP] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PRINPLUP] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_EMPOLEON] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_STARLY] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_STARAVIA] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_STARAPTOR] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_BIDOOF] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_BIBAREL] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_KRICKETOT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_KRICKETUNE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SHINX] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_LUXIO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_LUXRAY] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BUDEW] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ROSERADE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CRANIDOS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_RAMPARDOS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SHIELDON] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BASTIODON] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BURMY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_WORMADAM] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MOTHIM] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_COMBEE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_VESPIQUEN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_PACHIRISU] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BUIZEL] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_FLOATZEL] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_CHERUBI] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CHERRIM] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SHELLOS] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GASTRODON] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_AMBIPOM] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_DRIFLOON] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_DRIFBLIM] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_BUNEARY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_LOPUNNY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_MISMAGIUS] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HONCHKROW] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_GLAMEOW] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_PURUGLY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_CHINGLING] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_STUNKY] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SKUNTANK] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BRONZOR] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_BRONZONG] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_BONSLY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MIME_JR] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_HAPPINY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_CHATOT] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_SPIRITOMB] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GIBLE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_GABITE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GARCHOMP] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MUNCHLAX] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_RIOLU] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_LUCARIO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HIPPOPOTAS] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_HIPPOWDON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SKORUPI] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_DRAPION] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CROAGUNK] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_TOXICROAK] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_CARNIVINE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_FINNEON] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_LUMINEON] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_MANTYKE] = {
        .flags = HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SNOVER] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_ABOMASNOW] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_WEAVILE] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_MAGNEZONE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_LICKILICKY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_RHYPERIOR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TANGROWTH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ELECTIVIRE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MAGMORTAR] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TOGEKISS] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_YANMEGA] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_LEAFEON] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GLACEON] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_GLISCOR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_MAMOSWINE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_PORYGON_Z] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_GALLADE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PROBOPASS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DUSKNOIR] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_FROSLASS] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_ROTOM] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_UXIE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MESPRIT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_AZELF] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DIALGA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PALKIA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HEATRAN] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_REGIGIGAS] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_GIRATINA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CRESSELIA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PHIONE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MANAPHY] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DARKRAI] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SHAYMIN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ARCEUS] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_VICTINI] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SNIVY] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SERVINE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SERPERIOR] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_TEPIG] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_PIGNITE] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_EMBOAR] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_OSHAWOTT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DEWOTT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SAMUROTT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PATRAT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_WATCHOG] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_LILLIPUP] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_HERDIER] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_STOUTLAND] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_PURRLOIN] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_LIEPARD] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PANSAGE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SIMISAGE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_PANSEAR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SIMISEAR] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_PANPOUR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SIMIPOUR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MUNNA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_MUSHARNA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_PIDOVE] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_TRANQUILL] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_UNFEZANT] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_BLITZLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ZEBSTRIKA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ROGGENROLA] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_BOLDORE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_GIGALITH] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_WOOBAT] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_SWOOBAT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DRILBUR] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_EXCADRILL] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_AUDINO] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_TIMBURR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_GURDURR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_CONKELDURR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TYMPOLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PALPITOAD] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SEISMITOAD] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_THROH] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_SAWK] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_SEWADDLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SWADLOON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_LEAVANNY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_VENIPEDE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_WHIRLIPEDE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SCOLIPEDE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_COTTONEE] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_WHIMSICOTT] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_PETILIL] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_LILLIGANT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_BASCULIN] = {
        .flags = HABITAT_LAND | HABITAT_WATER | HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_SANDILE] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KROKOROK] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KROOKODILE] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DARUMAKA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_DARMANITAN] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_MARACTUS] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_DWEBBLE] = {
        .flags = HABITAT_LAND | HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_CRUSTLE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SCRAGGY] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_SCRAFTY] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_SIGILYPH] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_YAMASK] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_COFAGRIGUS] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TIRTOUGA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CARRACOSTA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ARCHEN] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ARCHEOPS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TRUBBISH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GARBODOR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ZORUA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ZOROARK] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MINCCINO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_CINCCINO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_GOTHITA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_GOTHORITA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_GOTHITELLE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_SOLOSIS] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_DUOSION] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_REUNICLUS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_DUCKLETT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_SWANNA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_VANILLITE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_VANILLISH] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_VANILLUXE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_DEERLING] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SAWSBUCK] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_EMOLGA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_KARRABLAST] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ESCAVALIER] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_FOONGUS] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_AMOONGUSS] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_FRILLISH] = {
        .flags = HABITAT_WATER | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_JELLICENT] = {
        .flags = HABITAT_CAVE | HABITAT_NIGHT,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_ALOMOMOLA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_JOLTIK] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GALVANTULA] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_FERROSEED] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_FERROTHORN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_KLINK] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_KLANG] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_KLINKLANG] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_TYNAMO] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_EELEKTRIK] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_EELEKTROSS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ELGYEM] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_BEHEEYEM] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_LITWICK] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_LAMPENT] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CHANDELURE] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_AXEW] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_FRAXURE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HAXORUS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CUBCHOO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_BEARTIC] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_CRYOGONAL] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_SHELMET] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ACCELGOR] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_STUNFISK] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_MIENFOO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_MIENSHAO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_DRUDDIGON] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GOLETT] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GOLURK] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PAWNIARD] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_BISHARP] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_BOUFFALANT] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_RUFFLET] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_BRAVIARY] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_VULLABY] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_MANDIBUZZ] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_HEATMOR] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_DURANT] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TEMPERATE,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_DEINO] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ZWEILOUS] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HYDREIGON] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_LARVESTA] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_VOLCARONA] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_COBALION] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TERRAKION] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_VIRIZION] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_TORNADUS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_THUNDURUS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_RESHIRAM] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_ZEKROM] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_LANDORUS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KYUREM] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_KELDEO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MELOETTA] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_GENESECT] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CHESPIN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_QUILLADIN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CHESNAUGHT] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_FENNEKIN] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_BRAIXEN] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_DELPHOX] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_FROAKIE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_FROGADIER] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GRENINJA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BUNNELBY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_DIGGERSBY] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_FLETCHLING] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = HABITAT_ENCOUNTER_FLYING,
    },
    [SPECIES_FLETCHINDER] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TALONFLAME] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SCATTERBUG] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SPEWPA] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_VIVILLON] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_LITLEO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_PYROAR] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_FLABEBE] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_FLOETTE] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_FLORGES] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SKIDDO] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GOGOAT] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_PANCHAM] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_PANGORO] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_FURFROU] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_ESPURR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_MEOWSTIC] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HONEDGE] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_DOUBLADE] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_AEGISLASH] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SPRITZEE] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_AROMATISSE] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SWIRLIX] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SLURPUFF] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_INKAY] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_PSYCHIC,
    },
    [SPECIES_MALAMAR] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BINACLE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_CAVE,
        .encounter = HABITAT_ENCOUNTER_ROCK_SMASH,
    },
    [SPECIES_BARBARACLE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SKRELP] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_DRAGALGE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_CLAUNCHER] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_CLAWITZER] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FISHING,
    },
    [SPECIES_HELIOPTILE] = {
        .flags = HABITAT_LAND,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_HELIOLISK] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_TYRUNT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TYRANTRUM] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_AMAURA] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_AURORUS] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_SYLVEON] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HAWLUCHA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_FIGHTING,
    },
    [SPECIES_DEDENNE] = {
        .flags = HABITAT_LAND | HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CARBINK] = {
        .flags = HABITAT_CAVE | HABITAT_DAY,
        .biome = BIOME_CAVE,
        .encounter = 0,
    },
    [SPECIES_GOOMY] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SLIGGOO] = {
        .flags = HABITAT_LAND | HABITAT_WATER,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GOODRA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KLEFKI] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = HABITAT_ENCOUNTER_STEEL,
    },
    [SPECIES_PHANTUMP] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_TREVENANT] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_PUMPKABOO] = {
        .flags = HABITAT_LAND | HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GOURGEIST] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_BERGMITE] = {
        .flags = HABITAT_CAVE,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_AVALUGG] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_NOIBAT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_NOIVERN] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_XERNEAS] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_YVELTAL] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ZYGARDE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DIANCIE] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HOOPA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_VOLCANION] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_ROWLET] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_DARTRIX] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_DECIDUEYE] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_LITTEN] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TORRACAT] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_INCINEROAR] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_POPPLIO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BRIONNE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PRIMARINA] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PIKIPEK] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_TRUMBEAK] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_TOUCANNON] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_YUNGOOS] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_GUMSHOOS] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_GRUBBIN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CHARJABUG] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_VIKAVOLT] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CRABRAWLER] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CRABOMINABLE] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_ORICORIO] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CUTIEFLY] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_RIBOMBEE] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ROCKRUFF] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_LYCANROC] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_WISHIWASHI] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MAREANIE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TOXAPEX] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MUDBRAY] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MUDSDALE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DEWPIDER] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_ARAQUANID] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_FOMANTIS] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_LURANTIS] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_MORELULL] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SHIINOTIC] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SALANDIT] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SALAZZLE] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_STUFFUL] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_BEWEAR] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_BOUNSWEET] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_STEENEE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_TSAREENA] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_COMFEY] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ORANGURU] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_PASSIMIAN] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_WIMPOD] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_GOLISOPOD] = {
        .flags = 0,
        .biome = BIOME_SWAMP,
        .encounter = 0,
    },
    [SPECIES_SANDYGAST] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PALOSSAND] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PYUKUMUKU] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TYPE_NULL] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_SILVALLY] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_MINIOR] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KOMALA] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_TURTONATOR] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_TOGEDEMARU] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MIMIKYU] = {
        .flags = HABITAT_DAY | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BRUXISH] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DRAMPA] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_DHELMISE] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_JANGMO_O] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HAKAMO_O] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KOMMO_O] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TAPU_KOKO] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TAPU_LELE] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TAPU_BULU] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_TAPU_FINI] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_COSMOG] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_COSMOEM] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SOLGALEO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_LUNALA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_NIHILEGO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BUZZWOLE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_PHEROMOSA] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_XURKITREE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CELESTEELA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KARTANA] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_GUZZLORD] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_NECROZMA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MAGEARNA] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MARSHADOW] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_POIPOLE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_NAGANADEL] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_STAKATAKA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BLACEPHALON] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_ZERAORA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MELTAN] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MELMETAL] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GROOKEY] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_THWACKEY] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_RILLABOOM] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SCORBUNNY] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_RABOOT] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_CINDERACE] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_SOBBLE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DRIZZILE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_INTELEON] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SKWOVET] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_GREEDENT] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_ROOKIDEE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CORVISQUIRE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CORVIKNIGHT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BLIPBUG] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_DOTTLER] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ORBEETLE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_NICKIT] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_THIEVUL] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GOSSIFLEUR] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_ELDEGOSS] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_WOOLOO] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_DUBWOOL] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_CHEWTLE] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DREDNAW] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_YAMPER] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BOLTUND] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ROLYCOLY] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CARKOL] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_COALOSSAL] = {
        .flags = 0,
        .biome = BIOME_MOUNTAIN,
        .encounter = 0,
    },
    [SPECIES_APPLIN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_FLAPPLE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_APPLETUN] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_SILICOBRA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SANDACONDA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CRAMORANT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ARROKUDA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_BARRASKEWDA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TOXEL] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_TOXTRICITY] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SIZZLIPEDE] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CENTISKORCH] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_CLOBBOPUS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GRAPPLOCT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SINISTEA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_POLTEAGEIST] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HATENNA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HATTREM] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_HATTERENE] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_IMPIDIMP] = {
        .flags = HABITAT_DAY | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MORGREM] = {
        .flags = HABITAT_DAY | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GRIMMSNARL] = {
        .flags = HABITAT_DAY | HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_OBSTAGOON] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_PERRSERKER] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CURSOLA] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SIRFETCHD] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MR_RIME] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_RUNERIGUS] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_MILCERY] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ALCREMIE] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_FALINKS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_PINCURCHIN] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SNOM] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_FROSMOTH] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_STONJOURNER] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_EISCUE] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_INDEEDEE] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_MORPEKO] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CUFANT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_COPPERAJAH] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DRACOZOLT] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ARCTOZOLT] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_DRACOVISH] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ARCTOVISH] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_DURALUDON] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DREEPY] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DRAKLOAK] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_DRAGAPULT] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ZACIAN] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ZAMAZENTA] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ETERNATUS] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_KUBFU] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_URSHIFU] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ZARUDE] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_REGIELEKI] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_REGIDRAGO] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_GLASTRIER] = {
        .flags = 0,
        .biome = BIOME_TUNDRA,
        .encounter = 0,
    },
    [SPECIES_SPECTRIER] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_CALYREX] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_WYRDEER] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_KLEAVOR] = {
        .flags = 0,
        .biome = BIOME_TEMPERATE,
        .encounter = 0,
    },
    [SPECIES_URSALUNA] = {
        .flags = 0,
        .biome = BIOME_URBAN,
        .encounter = 0,
    },
    [SPECIES_BASCULEGION] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_SNEASLER] = {
        .flags = 0,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_OVERQWIL] = {
        .flags = HABITAT_NIGHT,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
    [SPECIES_ENAMORUS] = {
        .flags = HABITAT_DAY,
        .biome = BIOME_ANY,
        .encounter = 0,
    },
};
