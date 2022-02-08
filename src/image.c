#include <stdlib.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <image.h>

#define NULL_PTR(addr) (addr == NULL)

static inline int image_index(image img, int x, int y, int c) {
    return (img.size * c + img.w * y + x);
}

/* Clamps the given coordinates to be within the bounds the image */
static inline void clamp_coordinates(image img, int *x, int *y, int *c) {
    *x = *x < 0 ? 0 : ((*x >= img.w) ? img.w - 1 : *x);
    *y = *y < 0 ? 0 : ((*y >= img.h) ? img.h - 1 : *y);
    *c = *c < 0 ? 0 : ((*c >= img.c) ? img.c - 1 : *c);
}

uint8_t get_pixel(image img, int x, int y, int c) {
    clamp_coordinates(img, &x, &y, &c);
    return img.data[image_index(img, x, y, c)];
}

void set_pixel(image img, int x, int y, int c, uint8_t val) {
    clamp_coordinates(img, &x, &y, &c);
    img.data[image_index(img, x, y, c)] = val;
}

image make_image(int w, int h, int c) {
    image img = make_empty_image(w, h, c);
    img.data = calloc(w * h * c, sizeof(uint8_t));
    return img;
}

image make_empty_image(int w, int h, int c) {
    image img;
    img.w = w;
    img.h = h;
    img.c = c;
    img.size = w * h;
    img.length = w * h * c;
    img.data = NULL;
    return img;
}

image copy_image(image src) {
    image dest = make_image(src.w, src.h, src.c);
    memcpy(dest.data, src.data, src.length);
    return dest;
}

int read_image(const char *filepath, int force_channels, image *out) {
    uint8_t *data;
    int w, h, c;
    int i, j, k;

    if (NULL_PTR(out)) {
        return -(IMG_ARG_ERR);
    }

    data = stbi_load(filepath, &w, &h, &c, force_channels);
    if (!data) {
        return -(IMG_IO_ERR);
    }

    *out = make_image(w, h, c);
    for (k = 0; k < c; ++k){
        for (j = 0; j < h; ++j){
            for (i = 0; i < w; ++i){
                int dst_index = i + w*j + w*h*k;
                int src_index = k + c*i + c*w*j;
                out->data[dst_index] = data[src_index];
            }
        }
    }
    free(data);
    return IMG_NO_ERR;
}

int write_image(const char *filepath, image img) {
    int status;
    unsigned char *data = calloc(img.w*img.h*img.c, sizeof(char));
    int i,k;
    for(k = 0; k < img.c; ++k){
        for(i = 0; i < img.w*img.h; ++i){
            data[i*img.c+k] = img.data[i + k*img.w*img.h];
        }
    }
    if (stbi_write_jpg(filepath, img.w, img.h, img.c, data, 100)) {
        status = IMG_NO_ERR;
    } else {
        status = -(IMG_IO_ERR);
    }
    free(data);
    return status;
}

void free_image(image *img) {
    stbi_image_free(img->data);
}