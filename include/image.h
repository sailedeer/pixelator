#include <stdint.h>

#ifndef _IMAGE_H
#define _IMAGE_H

#define IMG_NO_ERR      0
#define IMG_ERR         1
#define IMG_IO_ERR      (IMG_ERR + 0)
#define IMG_ARG_ERR     (IMG_ERR + 1)

#define R(p)            ((p & (0x000000FF)))
#define G(p)            ((p & (0x0000FF00)) >> 8)
#define B(p)            ((p & (0x00FF0000)) >> 16)

/*
 *
 * Encapsulates data about an image.
 * x: width of image in pixels (left to right)
 * y: height of image in pixels (top to bottom)
 * c: number of image channels
 * size: size in pixels of the image
 * length: size in bytes of in-ram image data
 * data: in-ram image data
 * 
 */
typedef struct image_st {
    int w;
    int h;
    int c;
    int size;
    int length;
    uint8_t *data;
} image;

/*
 *
 * Returns the value of the pixel at (x, y, c) in image 'img'.
 * 
 */
uint8_t get_pixel(image img, int x, int y, int c);

/*
 *
 * Sets the value of the pixel at (x, y, c) in image 'img' to val.
 * 
 */
void set_pixel(image img, int x, int y, int c, uint8_t val);

/*
 *
 * Create an image in memory with the given dimensions.
 *
 */
image make_image(int w, int h, int c);

/*
 *
 * Create an image with the given dimensions which has no associated heap data.
 *
 */
image make_empty_image(int w, int h, int c);

/*
 *
 * Copy the contents of image 'src' into 'dest'.
 * 
 */
image copy_image(image src);

/*
 *
 * Loads an on-disk image file at 'filepath' into memory.
 * Returns 0 on success, and places the image in 'out'.
 * Returns negative otherwise.
 * 
 */
int read_image(const char *filepath, int force_channels, image *out);

/*
 *
 * Writes an in-ram image to disk at 'filepath'.
 * Returns 0 on success and negative otherwise.
 * 
 */
int write_image(const char *filepath, image img);

/*
 *
 * Frees memory associated with image 'img'.
 * 
 */
void free_image(image *img);

#endif  // _IMAGE_H