# REGULAR EXPRESSIONS

> **<u>NOTE</u>:**
> - 3 types of states:
>   1. Accept state
>   2. Error state (dump state)
>   3. Incomplete state


## @ Comment @

$$ \_*@\_*(STRING)\_*@\_* $$

- $(STRING)$ is Comment
- $\_$ is space

## open db Office

$$ open\_\_*db\_\_*(STRING)\_* $$

- $(STRING)$ is database name.
- $\_$ is space.
