#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void dec(FILE* encrypted_data_file , FILE* key_file , FILE* decrypted_file)
{
    int enc_char;
    while ((enc_char = fgetc(encrypted_data_file)) != EOF)
    {
        int key_c = fgetc(key_file);
        int dec_c = enc_char ^ key_c;

        fputc(dec_c , decrypted_file);

    }

}

int main(int argc, char *argv[]) 
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <encrypted_file> <key>\n", argv[0]);
        return 1;
    }

    char *encrypted_data_file_name = argv[1];
    char *key_file_name = argv[2];

    FILE *encrypted_data_file = fopen(encrypted_data_file_name, "r");
    if (encrypted_data_file == NULL) 
    {
        perror("Failed to open encrypted file");
        return 1;
    }

    FILE *key_file = fopen(key_file_name, "r");
    if (key_file == NULL) 
    {
        perror("Failed to open encrypted file");
        fclose(encrypted_data_file);
        return 1;
    }

    FILE *decrypted_file = fopen("../artifacts/decrypted_file", "w");
    if (decrypted_file == NULL) 
    {
        perror("Failed to open key output file");
        fclose(encrypted_data_file);
        fclose(decrypted_file);
        return 1;
    }

    dec(encrypted_data_file, key_file, decrypted_file);

    fclose(encrypted_data_file);
    fclose(key_file);
    fclose(decrypted_file);

    return 0;
}