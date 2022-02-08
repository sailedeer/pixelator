#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include <image.h>

#define CHANNELS_IN_IMAGE   0

#define NULL_PTR(addr)      (addr == NULL)

#define PXLT_NO_ERR         0
#define PXLT_ERR            1
#define PXLT_IO_ERR         (PXLT_ERR + 0)
#define PXLT_ARG_ERR        (PXLT_ERR + 1)

/*
 * Pixelates some image 'img' into AR preserving
 * 'pixels' given the value of 'ratio'. Places image in 'out',
 * and returns 0 on success, negative otherwise.
 *
 */
static int pixelate(image img, int ratio, image *out) {
    int x_incr, y_incr;
    int x_off, y_off;
    int x, y, c;

    if (NULL_PTR(out)) {
        return -(PXLT_ARG_ERR);
    }
    x_incr = img.w / ratio;
    y_incr = img.h / ratio;

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

    /* pixelation ratio */
    int ratio;

    /* original image attributes */
    image orig_img;

    /* pixelated image attributes */
    image p_img;

    /* status code from functions */
    int status;

    /* for measuring execution time */
    clock_t t;

    /* Check CLI arguments */
    if (argc != 4) {
        fprintf(stderr, "Usage: pixelate <input file> <ratio> <output file>");
        return EXIT_FAILURE;
    }

    /* be bad and naively assume that these args aren't malformed */
    /* TODO: don't be bad and naively assume that these args aren't malformed */
    strcpy(orig_filepath, argv[1]);
    ratio = atoi(argv[2]);
    strcpy(p_filepath, argv[3]);

    status = read_image(orig_filepath, CHANNELS_IN_IMAGE, &orig_img);
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
    status = pixelate(orig_img, ratio, &p_img);
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