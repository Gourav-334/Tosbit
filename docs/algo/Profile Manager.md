# Profile Manager


## 0. Description:

- This documentation is regarding ***profile_manager.h*** & ***profile_manager.c***.
- Purpose of this library is to maintain the user credential data throughout the lifecycle of the program.


## 1. Profile Manager:

```c
void profile_manager();
```

- Check if user account exists or not.
- If not, then ask user to set up & create one.
- Ask him username & password (with re-authentication).
- If it matches, then show the welcome note.
- Else show error & again re-authenticate.
- If account exists, prompt asking password.
- If password matches, then welcome.
- Else keep asking until it doesn't match.

---