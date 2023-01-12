#include <stdio.h>
#include <stdlib.h>
#include <gd.h>

int main(int argc, char *argv[]) {
    FILE *in;
    gdImagePtr im, im_resized;
    int x, y, color;
    int width, height;
    int new_width, new_height;
    char *ascii = " ";

    if (argc < 4) {
        printf("Usage: %s <input_image> <width> <height>\n", argv[0]);
        return 1;
    }

    in = fopen(argv[1], "rb");
    if (in == NULL) {
        printf("Error: Unable to open input image %s\n", argv[1]);
        return 2;
    }

    im = gdImageCreateFromJpeg(in);
    if (im == NULL) {
        printf("Error: Unable to read input image %s\n", argv[1]);
        fclose(in);
        return 3;
    }

    width = gdImageSX(im);
    height = gdImageSY(im);

    new_width = atoi(argv[2]);
    new_height = atoi(argv[3]);

    if (new_width > width || new_height > height) {
        printf("Error: New width and height must be smaller than the original image\n");
        gdImageDestroy(im);
        fclose(in);
        return 5;
    }

    im_resized = gdImageCreateTrueColor(new_width, new_height);
    gdImageCopyResampled(im_resized, im, 0, 0, 0, 0, new_width, new_height, width, height);

    for (y = 0; y < new_height; y++) {
        for (x = 0; x < new_width; x++) {
            color = gdImageGetPixel(im_resized, x, y);
            printf("\033[48;2;%d;%d;%dm%s", gdImageRed(im_resized, color), gdImageGreen(im_resized, color), gdImageBlue(im_resized, color), ascii);
        }
        printf("\n");
    }

    gdImageDestroy(im);
    gdImageDestroy(im_resized);
    fclose(in);

    return 0;
}
