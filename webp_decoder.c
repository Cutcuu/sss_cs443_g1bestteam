#include <webp/decode.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input.webp>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    uint8_t *data = malloc(size);
    fread(data, 1, size, file);
    fclose(file);

    // Decode WebP Image
    uint8_t *output;
    WebPDecoderConfig config;
    WebPInitDecoderConfig(&config);
    fprintf(stdout, "Attempting to decode image file "+argv[1]+"...");
    WebPGetFeatures(data, size, &config.input);
    output = WebPDecodeRGBA(data, size, NULL, NULL);
    fprintf(stdout, "Image successfully decoded!");
    free(data);
    free(output);
    return 0;
}
