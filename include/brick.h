#ifndef _BRICK_H
#define _BRICK_H

#include <stdint.h>

#include <image.h>

#define NUM_BRICKS                      10

#define BRICK_BLACK                     0x00000000
#define BRICK_DARK_TURQ                 0x00008F9B
#define BRICK_DARK_BLUE                 0x000A3463
#define BRICK_MED_AZURE                 0x0036AEBF
#define BRICK_BRIGHT_GREEN              0x004B9F4A
#define BRICK_LIME                      0x00BBE90B
#define BRICK_TAN                       0x00E4CD9E
#define BRICK_BRIGHT_ORANGE             0x00F8BB3D
#define BRICK_ORANGE                    0x00FE8A18
#define BRICK_CORAL                     0x00FF698F
#define BRICK_WHITE                     0x00FFFFFF

#define BRICK_DARK_TURQ_R               R(BRICK_DARK_TURQ)
#define BRICK_DARK_BLUE_R               R(BRICK_DARK_BLUE)
#define BRICK_MED_AZURE_R               R(BRICK_MED_AZURE)
#define BRICK_BRIGHT_GREEN_R            R(BRICK_BRIGHT_GREEN)
#define BRICK_LIME_R                    R(BRICK_LIME)
#define BRICK_TAN_R                     R(BRICK_TAN)
#define BRICK_BRIGHT_ORANGE_R           R(BRICK_BRIGHT_ORANGE)
#define BRICK_ORANGE_R                  R(BRICK_ORANGE)
#define BRICK_CORAL_R                   R(BRICK_CORAL)

#define BRICK_DARK_TURQ_G               G(BRICK_DARK_TURQ)
#define BRICK_DARK_BLUE_G               G(BRICK_DARK_BLUE)
#define BRICK_MED_AZURE_G               G(BRICK_MED_AZURE)
#define BRICK_BRIGHT_GREEN_G            G(BRICK_BRIGHT_GREEN)
#define BRICK_LIME_G                    G(BRICK_LIME)
#define BRICK_TAN_G                     G(BRICK_TAN)
#define BRICK_BRIGHT_ORANGE_G           G(BRICK_BRIGHT_ORANGE)
#define BRICK_ORANGE_G                  G(BRICK_ORANGE)
#define BRICK_CORAL_G                   G(BRICK_CORAL)

#define BRICK_DARK_TURQ_B               B(BRICK_DARK_TURQ)
#define BRICK_DARK_BLUE_B               B(BRICK_DARK_BLUE)
#define BRICK_MED_AZURE_B               B(BRICK_MED_AZURE)
#define BRICK_BRIGHT_GREEN_B            B(BRICK_BRIGHT_GREEN)
#define BRICK_LIME_B                    B(BRICK_LIME)
#define BRICK_TAN_B                     B(BRICK_TAN)
#define BRICK_BRIGHT_ORANGE_B           B(BRICK_BRIGHT_ORANGE)
#define BRICK_ORANGE_B                  B(BRICK_ORANGE)
#define BRICK_CORAL_B                   B(BRICK_CORAL)

// #define BRICK_DTRQ_BLK_MID              (BRICK_DARK_TURQ / 2)
// #define BRICK_DBL_DTRQ_MID              ((BRICK_DARK_BLUE - BRICK_DARK_TURQ) / 2)
// #define BRICK_MAZR_DBL_MID              ((BRICK_MED_AZURE - BRICK_DARK_BLUE) / 2)
// #define BRICK_BGRN_MAZR_MID             ((BRICK_BRIGHT_GREEN - BRICK_MED_AZURE) / 2)
// #define BRICK_LIME_BGRN_MID             ((BRICK_LIME - BRICK_BRIGHT_GREEN) / 2)
// #define BRICK_TAN_LIME_MID              ((BRICK_TAN - BRICK_LIME) / 2)
// #define BRICK_BORNG_TAN_MID             ((BRICK_BRIGHT_ORANGE - BRICK_TAN) / 2)
// #define BRICK_ORNG_BORNG_MID            ((BRICK_ORANGE - BRICK_BRIGHT_ORANGE) / 2)
// #define BRICK_CORAL_ORNG_MID            ((BRICK_CORAL - BRICK_ORANGE) / 2)
// #define BRICK_WHITE_CORAL_MID           ((BRICK_WHITE - BRICK_CORAL) / 2)

#define BRICK_DARK_TURQ_BKT_IDX         0
#define BRICK_DARK_BLUE_BKT_IDX         1
#define BRICK_MED_AZURE_BKT_IDX         2
#define BRICK_BRIGHT_GREEN_BKT_IDX      3
#define BRICK_LIME_BKT_IDX              4
#define BRICK_TAN_BKT_IDX               5
#define BRICK_BRIGHT_ORANGE_BKT_IDX     6
#define BRICK_ORANGE_BKT_IDX            7
#define BRICK_CORAL_BKT_IDX             8
#define BRICK_WHITE_BKT_IDX             9

#endif // _BRICK_H