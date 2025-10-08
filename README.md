🔐 Secure User Authentication System in C

📘 Overview

This project is a secure user authentication system implemented in C, which allows users to register and log in safely using SHA-256 password hashing with salts.
It also integrates process handling (forking) for background login operations, password strength validation, and login attempt logging to ensure better security and accountability.
The program demonstrates essential concepts in system programming, file handling, cryptography, and process management using the C language.

⚙️ Features

🧾 1. User Registration

Users can create an account by entering a unique username and a strong password.

Passwords are validated for:

Minimum 8 characters

At least one uppercase letter

At least one lowercase letter

At least one number

At least one special character

For added security:

A random salt (16 characters) is generated.

The password + salt combination is hashed using SHA-256.

Username, salt, and hashed password are stored in users.txt.

🔐 2. User Login

Users can log in using their username and password.

The program reads the stored hash and salt, rehashes the entered password, and compares the results.

Supports up to 3 login attempts before locking out.

All login attempts (success or failure) are logged with timestamps in login_attempts.txt.

🧠 3. Secure Password Handling

Passwords are never stored in plain text.

SHA-256 hashing from OpenSSL ensures cryptographic security.

Random salt generation prevents dictionary and rainbow table attacks.

🧩 4. Background Process (Optional)

Users can choose to run the login process in the background.

Implemented using UNIX fork() and wait() system calls.

If the user selects background mode, the parent process continues execution while the child process handles login authentication.

🧾 5. Logging System

Every login attempt (success or failure) is recorded in a file login_attempts.txt with:

Timestamp

Username

Attempt status (SUCCESS / FAIL)

📁 File Structure
📦 Secure-Login-System
├── users.txt               # Stores username, salt, and hashed password
├── login_attempts.txt      # Records all login activities
├── main.c                  # Main source code file
└── README.md               # Project documentation

🧰 Dependencies

This program uses:

OpenSSL library for SHA-256 hashing

Standard C Libraries:

<stdio.h>, <string.h>, <stdlib.h>, <unistd.h>, <time.h>, <ctype.h>

<sys/types.h>, <sys/wait.h>, <openssl/sha.h>

🛠️ Installation of OpenSSL (if not installed)

For Linux / macOS:

sudo apt install libssl-dev


For Windows (MinGW / MSYS2):

pacman -S mingw-w64-x86_64-openssl

🖥️ Compilation & Execution
Step 1: Compile
gcc main.c -o secure_login -lcrypto

Step 2: Run
./secure_login

🧩 Usage Guide

Register a User

Choose option 1 in the menu.

Enter a username.

Enter a strong password (as per password rules).

Your credentials will be stored securely in users.txt.

Login

Choose option 2.

Select if you want to run in background (1 for yes, 0 for no).

Enter your username and password.

On success: “✅ Login successful!”

On failure: “❌ Login failed! Attempt X/3”

Exit

Choose option 3 to quit.

📄 Example Output
1. Register
2. Login
3. Exit
Choice: 1
Enter username: saksham
Enter password: Pass@123
✅ User registered successfully!

1. Register
2. Login
3. Exit
Choice: 2
Run login in background? (1 = yes, 0 = no): 0
Enter username: saksham
Enter password: Pass@123
✅ Login successful!

🧱 Core Concepts Demonstrated
Concept	Description
File Handling	Used to store and retrieve user credentials.
Hashing (SHA-256)	Ensures passwords are stored securely.
Salt Generation	Adds randomness to each password hash.
Process Management	Uses fork() and wait() for child process login.
Input Validation	Checks password strength before accepting.
Logging System	Tracks all login attempts with timestamps.
⚖️ Security Notes

Passwords are never stored in plain text.

Each password is salted and hashed to prevent offline attacks.

The program enforces strong password policies.

Login attempts are rate-limited to 3 tries per session.

🧑‍💻 Future Improvements

Add user deletion and password reset options.

Encrypt stored files for extra protection.

Introduce user lockout timers after failed attempts.

Implement multi-threaded login sessions.

Add admin dashboard to view login logs.

👨‍🏫 Author

Saksham Kamra
College Student | System Programmer | Security Enthusiast
📧 Contact: (optional – add your email or GitHub)
