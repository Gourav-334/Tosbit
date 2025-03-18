# Profile Manager


## 0. Description:

- This documentation is regarding ***profile_manager.h*** & ***profile_manager.c***.
- Purpose of this library is to maintain the user credential data throughout the lifecycle of the program.


## 1. `profileManager()`:

```c
void profileManager();
```

1. Check if user account exists or not.
2. If not, then ask user to set up & create one.
3. Ask him username & password (with re-authentication).
4. If it matches, then show the welcome note.
5. Else show error & exit.
6. If account exists, prompt asking password.
7. If password matches, then welcome.
8. Else just exit.

---