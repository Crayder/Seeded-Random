#define INITIAL_SEED 0xCAA938DB
#define IL_RMULT (1103515245)

static simplex_seed = INITIAL_SEED;

stock srandom(seed)
    simplex_seed = seed;

stock core_random(max)
{
    if(simplex_seed == INITIAL_SEED)
        simplex_seed = gettime();
    
    new lo, hi, ll, lh, hh, hl;
    new result;

    lo = simplex_seed    & 0xffff;
    hi = simplex_seed   >> 16;
    ll = lo * (IL_RMULT  & 0xffff);
    lh = lo * (IL_RMULT >> 16    );
    hl = hi * (IL_RMULT  & 0xffff);
    hh = hi * (IL_RMULT >> 16    );
    
    result = ((ll + 12345) >> 16) + lh + hl + (hh << 16);
    result &= ~(-2147483647);
    
    if (max != 0)
        result %= max;
    
    simplex_seed = simplex_seed * IL_RMULT + 12345;
    
    return result;
}

#if defined _ALS_random
    #undef random
#else
    #define _ALS_random
#endif

#define random core_random
