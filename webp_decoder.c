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

    // Decode the malicious WebP image
    uint8_t *output;
    WebPDecoderConfig config;
    WebPInitDecoderConfig(&config);
    WebPGetFeatures(data, size, &config.input);
    output = WebPDecodeRGBA(data, size, NULL, NULL);
    free(data);
    free(output);
    return 0;
}
