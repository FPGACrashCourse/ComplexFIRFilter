#ifndef CORDIC_H
#define CORDIC_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ap_fixed.h>

#define FIXED_BITS_M 32
#define FIXED_BITS_N 20

#define DEBUG_MODE

typedef ap_fixed<FIXED_BITS_M, FIXED_BITS_N> FIXED_POINT; //!< AP-Fixed datype for consistent calculation
// typedef float FIXED_POINT; //!< Placeholder datatype for vscode development ease.

#define MAX_DEPTH 64 //!< Maximum depth/precision of the CORDIC

static FIXED_POINT cordicPhase[MAX_DEPTH] = {0.78539816339744828000, 0.46364760900080609000, 0.24497866312686414000, 0.12435499454676144000, 0.06241880999595735000, 0.03123983343026827700, 0.01562372862047683100, 0.00781234106010111110, 0.00390623013196697180, 0.00195312251647881880, 0.00097656218955931946, 0.00048828121119489829, 0.00024414062014936177, 0.00012207031189367021, 0.00006103515617420877, 0.00003051757811552610, 0.00001525878906131576, 0.00000762939453110197, 0.00000381469726560650, 0.00000190734863281019, 0.00000095367431640596, 0.00000047683715820309, 0.00000023841857910156, 0.00000011920928955078, 0.00000005960464477539, 0.00000002980232238770, 0.00000001490116119385, 0.00000000745058059692, 0.00000000372529029846, 0.00000000186264514923, 0.00000000093132257462, 0.00000000046566128731, 0.00000000023283064365, 0.00000000011641532183, 0.00000000005820766091, 0.00000000002910383046, 0.00000000001455191523, 0.00000000000727595761, 0.00000000000363797881, 0.00000000000181898940, 0.00000000000090949470, 0.00000000000045474735, 0.00000000000022737368, 0.00000000000011368684, 0.00000000000005684342, 0.00000000000002842171, 0.00000000000001421085, 0.00000000000000710543, 0.00000000000000355271, 0.00000000000000177636, 0.00000000000000088818, 0.00000000000000044409, 0.00000000000000022204, 0.00000000000000011102, 0.00000000000000005551, 0.00000000000000002776, 0.00000000000000001388, 0.00000000000000000694, 0.00000000000000000347, 0.00000000000000000173, 0.00000000000000000087, 0.00000000000000000043, 0.00000000000000000022, 0.00000000000000000011};
const FIXED_POINT cordicGain[MAX_DEPTH] = { 1.0, 0.7071067811865476, 0.6324555320336759, 0.6135719910778963, 0.6088339125177524, 0.6076482562561682, 0.6073517701412959, 0.6072776440935250, 0.6072591122988928, 0.6072544793325624, 0.6072533210898752, 0.6072530315291342, 0.6072529591389448, 0.6072529410413971, 0.6072529365170102, 0.6072529353859135, 0.6072529351031395, 0.6072529350324458, 0.6072529350147724, 0.6072529350103540, 0.6072529350092495, 0.6072529350089730, 0.6072529350089042, 0.6072529350088871, 0.6072529350088828, 0.6072529350088814, 0.6072529350088810, 0.6072529350088809, 0.6072529350088809, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808, 0.6072529350088808}; //!< CORDIC gain coefficents for quick-access

#define NUM_ITERATIONS 32 //!< Number of iterations for the rotational computer

void cordic(FIXED_POINT cos, FIXED_POINT sin, FIXED_POINT *mag, FIXED_POINT *theta);

#endif // CORDIC_H