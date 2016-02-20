
#pragma once

inline int ifloor( double doubval ){
    return ( doubval >= 0. ? (int)(doubval) : ((int)doubval)-1 );
}

inline long double dnearbyint( double doubval ){
    return ( doubval >= 0. ? (long)(doubval + 0.5) : (long)(doubval - 0.5) );
}
