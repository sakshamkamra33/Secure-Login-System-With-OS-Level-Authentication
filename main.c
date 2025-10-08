#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <sys/types.h>
#include <sys/wait.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define SALT_LEN 16
#define HASH_LEN 65
#define FILE_NAME "users.txt"
#define LOG_FILE "login_attempts.txt"
#define MAX_ATTEMPTS 3

// Hash password + salt
void hash_password(const char *password, const char *salt, char *output)
{
    char salted_password[PASSWORD_LEN + SALT_LEN];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)salted_password, strlen(salted_password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(output + (i * 2), "%02x", hash[i]);
    output[64] = '\0';
}

// Generate random salt
void generate_salt(char *salt, int length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length - 1; i++)
        salt[i] = charset[rand() % (sizeof(charset) - 1)];
    salt[length - 1] = '\0';
}

// Check password strength
int is_strong_password(const char *password)
{
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    if (strlen(password) < 8)
        return 0;

    for (int i = 0; password[i]; i++)
    {
        if (isupper(password[i]))
            has_upper = 1;
        else if (islower(password[i]))
            has_lower = 1;
        else if (isdigit(password[i]))
            has_digit = 1;
        else
            has_special = 1;
    }
    return has_upper && has_lower && has_digit && has_special;
}

// Register user
void register_user()
{
    char username[USERNAME_LEN], password[PASSWORD_LEN], password_hash[HASH_LEN], salt[SALT_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    while (1)
    {
        printf("Enter password: ");
        scanf("%49s", password);

        if (is_strong_password(password))
            break;
        else
            printf("❌ Password too weak! Must be 8+ chars with upper, lower, digit & special.\n");
    }

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, password_hash);

    FILE *file = fopen(FILE_NAME, "a");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s %s %s\n", username, salt, password_hash);
    fclose(file);

    printf("✅ User registered successfully!\n");
}

// Log login attempt
void log_attempt(const char *username, const char *status)
{
    FILE *log = fopen(LOG_FILE, "a");
    if (!log)
        return;

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strcspn(time_str, "\n")] = 0; // remove newline

    fprintf(log, "[%s] Username: %s -> %s\n", time_str, username, status);
    fclose(log);
}

// Login with child process and optional background
void login_user()
{
    char username[USERNAME_LEN], password[PASSWORD_LEN], entered_hash[HASH_LEN];
    char file_username[USERNAME_LEN], file_salt[SALT_LEN], file_hash[HASH_LEN];
    int choice;

    printf("Run login in background? (1 = yes, 0 = no): ");
    scanf("%d", &choice);

    pid_t pid = fork(); // create a new child process

    if (pid < 0)
    {
        printf("❌ Fork failed!\n");
        return;
    }
    else if (pid == 0)
    { // child process
        int attempts = 0, found = 0;

        while (attempts < MAX_ATTEMPTS)
        {
            printf("Enter username: ");
            scanf("%49s", username);
            printf("Enter password: ");
            scanf("%49s", password);

            FILE *file = fopen(FILE_NAME, "r");
            if (!file)
            {
                printf("No users registered yet!\n");
                exit(0);
            }

            found = 0;
            while (fscanf(file, "%49s %15s %64s", file_username, file_salt, file_hash) != EOF)
            {
                if (strcmp(file_username, username) == 0)
                {
                    hash_password(password, file_salt, entered_hash);
                    if (strcmp(file_hash, entered_hash) == 0)
                        found = 1;
                    break;
                }
            }
            fclose(file);

            if (found)
            {
                printf("✅ Login successful!\n");
                log_attempt(username, "SUCCESS");
                exit(0);
            }
            else
            {
                attempts++;
                printf("❌ Login failed! Attempt %d/%d\n", attempts, MAX_ATTEMPTS);
                log_attempt(username, "FAIL");
            }
        }

        printf("⚠ Maximum login attempts reached. Exiting login process.\n");
        exit(0);
    }
    else
    { // parent process
        if (!choice)
            wait(NULL); // wait only if not background
        else
            printf("🔹 Login session started in background (PID: %d)\n", pid);
    }
}

// Main menu
int main()
{
    int choice;
    srand(time(NULL));

    while (1)
    {
        printf("\n1. Register\n2. Login\n3. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Exiting...\n");
            break;
        }

        switch (choice)
        {
        case 1:
            register_user();
            break;
        case 2:
            login_user();
            break;
        case 3:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
}
