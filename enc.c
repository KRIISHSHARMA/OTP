#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void enc(FILE *sec_file, FILE *enc_file, FILE *key_file) 
{
    int urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd < 0) 
    {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }

    int charc;
    while ((charc = fgetc(sec_file)) != EOF) 
    {
        unsigned char key;
        if (read(urandom_fd, &key, sizeof(key)) != sizeof(key)) 
        {
            perror("Failed to read random data");
            close(urandom_fd);
            exit(EXIT_FAILURE);
        }

        int enc_c = charc ^ key;

        fputc(key, key_file);   
        fputc(enc_c, enc_file); 
    }

    close(urandom_fd);
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *sec_file_name = argv[1];
    FILE *sec_file = fopen(sec_file_name, "r");
    if (sec_file == NULL) 
    {
        perror("Failed to open input file");
        return 1;
    }

    FILE *enc_file = fopen("../artifacts/enc_file", "w");
    if (enc_file == NULL) 
    {
        perror("Failed to open encrypted file");
        fclose(sec_file);
        return 1;
    }

    FILE *key_file = fopen("../artifacts/key.out", "w");
    if (key_file == NULL) 
    {
        perror("Failed to open key output file");
        fclose(sec_file);
        fclose(enc_file);
        return 1;
    }

    enc(sec_file, enc_file, key_file);

    fclose(sec_file);
    fclose(enc_file);
    fclose(key_file);

    return 0;
}
