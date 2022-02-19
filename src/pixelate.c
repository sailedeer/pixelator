#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include <image.h>

#define USE_IMAGE_CHANNELS   0

#define NULL_PTR(addr)      (addr == NULL)

#define PXLT_NO_ERR         0
#define PXLT_ERR            1
#define PXLT_IO_ERR         (PXLT_ERR + 0)
#define PXLT_ARG_ERR        (PXLT_ERR + 1)

static int verify_args(int argc, char **argv) {
    char *end;

    if (argc < 5) {
        return 0;
    }

    if (strtol(argv[2], &end, 10) == 0 && *end == 0) {
        // no valid conversion
        return 0;
    }

    if (strtol(argv[3], &end, 10) == 0 && *end == 0) {
        // no valid conversion
        return 0;
    } 

    return 1;
}

/*
 *
 * Pixelates some image 'img' based on the requested x and y cells.
 * Places pixelated image in 'out'. Returns 0 on success,
 * negative otherwise.
 *
 */
static int pixelate(image img, int x_cells, int y_cells, int borders, image *out) {
    int x_incr, y_incr;
    int x_off, y_off;
    int x, y, c;

    if (NULL_PTR(out)) {
        return -(PXLT_ARG_ERR);
    }

    x_incr = img.w / x_cells;
    y_incr = img.h / y_cells;

    for (c = 0; c < img.c; c++) {
        for (y_off = 0; y_off < img.h; y_off += y_incr) {
            for (x_off = 0; x_off < img.w; x_off += x_incr) {
                int q_c = 0;
                for (y = y_off; y < (y_off + y_incr); y++) {
                    for (x = x_off; x < (x_off + x_incr); x++) {
                        uint8_t pixel = get_pixel(img, x, y, c);
                        q_c += pixel;
                    }
                }
                q_c /= (x_incr * y_incr);
                for (y = y_off; y < (y_off + y_incr); y++) {
                    for (x = x_off; x < (x_off + x_incr); x++) {
                        set_pixel(*out, x, y, c, q_c);
                    }
                }
                if (borders) {
                    // draw the border in the x-direction
                    if (y_off % 32 == 0) {
                        for (y = y_off - 2; y < (y_off + 2); y++) {
                            for (x = x_off; x < (x_off + x_incr); x++) {
                                if (!(y_off == 0) && !(y_off == (img.h - 1))) {
                                    set_pixel(*out, x, y, c, 0);
                                }
                            }
                        }
                    } else {
                        for (y = y_off - 1; y < (y_off + 1); y++) {
                            for (x = x_off; x < (x_off + x_incr); x++) {
                                if (!(y_off == 0) && !(y_off == (img.h - 1))) {
                                    set_pixel(*out, x, y, c, 0);
                                }
                            }
                        }
                    }

                    // draw the border in the y-direction
                    if (x_off % 32 == 0) {
                        for (y = y_off; y < (y_off + y_incr); y++) {
                            for (x = x_off - 2; x < (x_off + 2); x++) {
                                if (!(x_off == 0) && !(x_off == (img.w - 1))) {
                                    set_pixel(*out, x, y, c, 0);
                                }
                            }
                        }
                    } else {
                        for (y = y_off; y < (y_off + y_incr); y++) {
                            for (x = x_off - 1; x < (x_off + 1); x++) {
                                if (!(x_off == 0) && !(x_off == (img.w - 1))) {
                                    set_pixel(*out, x, y, c, 0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return PXLT_NO_ERR;
}

int main(int argc, char **argv) {
    /* stores the path to the image to be pixelated */
    char orig_filepath[FILENAME_MAX + 1];

    /* stores the output path of the pixelated image */
    char p_filepath[FILENAME_MAX + 1];

    /* number of x cells to generate */
    int x_cells;

    /* number of y cells to generate */
    int y_cells;

    /* flag which indicates whether or not we should draw cell borders */
    int borders;

    /* original image attributes */
    image orig_img;

    /* pixelated image attributes */
    image p_img;

    /* status code from functions */
    int status;

    /* for measuring execution time */
    clock_t t;

    /* Check CLI arguments */
    if (!verify_args(argc, argv)) {
        fprintf(stderr, "Usage: pixelate <input file> <x increment> <y increment> <output file> [--no-border]");
        return EXIT_FAILURE;
    }

    /* be bad and naively assume that these args aren't malformed */
    /* TODO: don't be bad and naively assume that these args aren't malformed */
    strcpy(orig_filepath, argv[1]);
    x_cells = atoi(argv[2]);
    y_cells = atoi(argv[3]);
    strcpy(p_filepath, argv[4]);
    if ((argc == 6) && (strcmp(argv[5], "--no-border") == 0)) {
        borders = 0;
    } else {
        borders = 1;
    }

    status = read_image(orig_filepath, USE_IMAGE_CHANNELS, &orig_img);
    if (status < 0) {
        fprintf(stderr, "Failed to load image from file.\n");
        return EXIT_FAILURE;
    }

    p_img = copy_image(orig_img);
    if (status < 0) {
        fprintf(stderr, "Failed to write image to file.\n");
        return EXIT_FAILURE;
    }

    printf("Pixelating image...\n");
    t = clock();
    status = pixelate(orig_img, x_cells, y_cells, borders, &p_img);
    t = clock() - t;
    if (status < 0) {
        fprintf(stderr, "Failed to pixelate image.\n");
        return EXIT_FAILURE;
    }
    printf("Pixelated %s in %lf seconds.\n", orig_filepath, ((double)t) / CLOCKS_PER_SEC);

    printf("Writing pixelated image to %s... ", p_filepath);
    status = write_image(p_filepath, p_img);
    if (status < 0) {
        fprintf(stderr, "Failed to write image to file.\n");
        return EXIT_FAILURE;
    }
    printf("Done!\n");
    free_image(&orig_img);
    free_image(&p_img);
    return EXIT_SUCCESS;
}