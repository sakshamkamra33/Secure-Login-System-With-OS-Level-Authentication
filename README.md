# 🔐 Secure User Authentication System in C

## 📘 Overview
A secure user authentication system implemented in **C**, allowing users to register and log in safely using **SHA-256 hashing with salts**.

This project demonstrates:
- Cryptography (SHA-256)
- File Handling
- Process Management (fork, wait)
- Input Validation
- Logging System

---

## ⚙️ Features

### 🧾 1. User Registration
- Unique username creation
- Strong password validation:
  - Minimum 8 characters
  - At least one uppercase letter
  - At least one lowercase letter
  - At least one number
  - At least one special character

**Security:**
- Random 16-character salt generated
- Password + salt hashed using SHA-256
- Stored in `users.txt`

---

### 🔐 2. User Login
- Username & password authentication
- Password rehashed using stored salt
- Maximum 3 login attempts
- Logs stored in `login_attempts.txt`

---

### 🧠 3. Secure Password Handling
- No plain-text passwords
- SHA-256 hashing using OpenSSL
- Salt prevents rainbow table attacks

---

### 🧩 4. Background Process (Optional)
- Login can run in background
- Uses:
  - `fork()`
  - `wait()`

---

### 🧾 5. Logging System
Each login attempt stores:
- Timestamp
- Username
- Status (SUCCESS / FAIL)

---

## 📁 Project Structure
```
Secure-Login-System/
│── users.txt
│── login_attempts.txt
│── main.c
│── README.md
```


---

## 🧰 Dependencies

- OpenSSL (for SHA-256)
- Standard C Libraries:
- stdio.h
- string.h
- stdlib.h
- unistd.h
- time.h
- ctype.h
- sys/types.h
- sys/wait.h
- openssl/sha.h

---

## 🛠️ Installation

### Linux / macOS
```bash
sudo apt install libssl-dev
```

Windows (MinGW / MSYS2)
```
pacman -S mingw-w64-x86_64-openssl
```

🖥️ Compilation & Execution

Compile
```
gcc main.c -o secure_login -lcrypto
```
Run
```
./secure_login
```

🧩 Usage
- Register
- Choose option 1
- Enter username
- Enter strong password
- User registered successfully
---
Login
- Choose option 2
- Select background mode (1/0)
- Enter credentials

Output:

- ✅ Login successful
- ❌ Login failed (max 3 attempts)
