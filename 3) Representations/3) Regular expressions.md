# REGULAR EXPRESSIONS

> **<u>NOTE</u>:**
> - 3 types of states:
>   1. Accept state
>   2. Error state (dump state)
>   3. Incomplete state


## @ Comment @

$$ \_^*@\_^*(STRING)\_^*@\_^* $$

- $\_$ is space
- $(STRING)$ is Comment


## open db Office

$$ open\_\_^*db\_\_^*(STRING)\_^* $$

- $\_$ is space.
- $(STRING)$ is database name.


## show struct Table

$$ show\_\_^*struct\_\_^*(STRING)\_^* $$

- $\_$ is space.
- $(STRING)$ is table name.


## show all db

$$ show\_\_^*all\_\_^*db\_\_^* $$

- $\_$ is space.


## show all tables

$$ show\_\_^*all\_\_^*tables\_\_^* $$

- $\_$ is space.


## make table Desk[string name, int age]

$$ make\_\_^*table\_\_^*Desk\_^*[\_^*(STRING)\_^*] $$

- $\_$ is space.