#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stdlib.h>
#include <memory>
#include "stb_image.h"
#include "stb_image_resize.h"

using namespace std;

// functions that resizes the image and returns pointer to buffer with
// the new pixels data
unsigned char *resize_image(const unsigned char *input_pixels, int input_width,
                            int input_height, int new_width, int *new_height, int channels)
{
    float ratio = (float)input_height / (float)input_width;
    *new_height = new_width * ratio;
    unsigned char *resize = new unsigned char[new_width * *new_height * channels];
    stbir_resize_uint8(input_pixels, input_width, input_height, 0, resize,
                       new_width, *new_height, 0, channels);
    return resize;
};

int main(int argc, char *argv[])
{

    int x, y, n;
    const char *fname = argv[1]; // choose image you want from terminal using command
                                 // ./a.out filename

    // sets width/height/channels number
    // and returns pointer to a buffer with pixels's data
    const unsigned char *data = stbi_load(fname, &x, &y, &n, 0);

    cout << "pixels by width :" << x << ".\n"
         << "pixels by height :" << y << ".\n"
         << "number of channels :" << n << "." << endl;

    int new_width, new_height;
    new_width = 80; // set the new width

    // resize the image depending on new width you want
    unsigned char *new_data = resize_image(data, x, y, new_width, &new_height, n);
    const char *ascii = "Ñ@#W$9876543210?!abc;:+=-,._ ";
    cout << "\n \n";
    cout << " YOUR ASCII ART IMAGE :) ==> " << endl;
    for (int i = 0; i <= new_width * new_height * n; i += n)
    {
        int brightness = (new_data[i] + new_data[i + 1] + new_data[i + 2]) / 3;
        cout << ascii[28 - (brightness / (255 / 28))];
        if ((i / n) % new_width == 0)
            cout << endl;
    }
}
