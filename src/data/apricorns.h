struct ApricornTree
{
    u8 minimum;
    u8 maximum;
    enum ApricornType apricornType;
};

const struct ApricornTree gApricornTrees[APRICORN_TREE_COUNT] =
{
    [APRICORN_TREE_NONE] =
    {
        .minimum = 1,
        .maximum = 1,
        .apricornType = APRICORN_RED,
    },
    [APRICORN_TREE_ROUTE102] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_RED,
    },
    [APRICORN_TREE_ROUTE103] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_BLUE,
    },
    [APRICORN_TREE_ROUTE104] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_YELLOW,
    },
    [APRICORN_TREE_ROUTE110] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_PINK,
    },
    [APRICORN_TREE_ROUTE111] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_BLACK,
    },
    [APRICORN_TREE_ROUTE112] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_RED,
    },
    [APRICORN_TREE_ROUTE114] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_YELLOW,
    },
    [APRICORN_TREE_ROUTE115] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_BLUE,
    },
    [APRICORN_TREE_ROUTE116] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_GREEN,
    },
    [APRICORN_TREE_ROUTE117] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_WHITE,
    },
    [APRICORN_TREE_ROUTE118] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_GREEN,
    },
    [APRICORN_TREE_ROUTE119] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_PINK,
    },
    [APRICORN_TREE_ROUTE120] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_WHITE,
    },
    [APRICORN_TREE_ROUTE121] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_BLACK,
    },
    [APRICORN_TREE_ROUTE123] =
    {
        .minimum = 2,
        .maximum = 4,
        .apricornType = APRICORN_RED,
    },
};
