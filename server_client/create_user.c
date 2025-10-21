#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    if (argc != 3) return -1;

    char* user_name = argv[1];
    char* plain_pass = argv[2];
    char* salt = "EL";

    FILE* file = fopen("user_files.txt", "a");
    if (!file) {
        perror("Fail file open");
        return -1;
    }

    char* hash_pass = crypt(plain_pass, salt);
    if (!hash_pass) {
        perror("Crypt failed");
        fclose(file);
        return -1;
    }

    fprintf(file, "%s %s\n", user_name, hash_pass);
    fclose(file);

    printf("Success\n");
    return 0;
}