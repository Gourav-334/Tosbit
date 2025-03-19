# REGULAR EXPRESSIONS

> **<u>NOTE</u>:**
> - 3 types of states:
>   1. Accept state
>   2. Error state (dump state)
>   3. Incomplete state
> - Regular expression reperentation:
>   - $\_$ represents a space.
>   - $\{comment\}$ represents a comment.
>   - $\{database\}$ represents a database.
>   - $\{table\}$ represents a table.
>   - $\{data\_ type\}$ represents a data type.
>   - $\{attribute\}$ represents a attribute.

## 1. `@ This is a comment! @`
$$ \_^*@\{comment\}@\_^* $$

## 2. `OPEN DB db_name`
$$ \_^*OPEN\_^+DB\_^+\{database\}\_^* $$

## 3. `SHOW STRUCT tbl_name`
$$ \_^*SHOW\_^+STRUCT\_^+\{table\}\_^* $$

## 4. `SHOW ALL DB`
$$ \_^*SHOW\_^+ALL\_^+DB\_^* $$

## 5. `SHOW ALL TABLES`
$$ \_^*SHOW\_^+ALL\_^+TABLES\_^* $$

## 6. `MAKE TABLE tbl_name(STRING name, INT age)`
$$ \_^*MAKE\_^+TABLE\_^+\{table\}\_^*((\_^*\{data\_ type\}\_^+\{attribute\}\_^*)+(,\_*\{data\_ type\}\_^+\{attribute\}\_^*)\_^*)\_^* $$

## 7. `MAKE DB db_name`
$$ \_^*MAKE\_^+DB\_^+\{database\}\_^* $$

## 8. `DELETE TABLE table_name`
$$ \_^*DELETE\_^+TABLE\_^+\{table\}\_^* $$

## 9. `DELETE DB db_name`
$$ \_^*DELETE\_^+DB\_^+\{database\}\_^* $$

## 10. `CLEAR TABLE table_name`
$$ \_^*CLEAR\_^+TABLE\_^+\{table\}\_^* $$

## 11. `CLEAR DB db_name`
$$ \_^*CLEAR\_^+DB\_^+\{database\}\_^* $$

## 12. `PUSH TO tbl_name(1, Yuvraj, 8.2)`
$$ \_^*PUSH\_^+TO\_^+\{table\}\_^*((\_^*\{attribute\}\_^*)+(,\_^*\{attribute\}\_^*)^*)\_^* $$

## 13. `SELECT tbl_name.(@)`
$$ \_^*SELECT\_^+\{table\}\_^*.\_^*(\_^*@\_^*)\_^* $$

## 14. `UPDATE tbl_name.(name=Gourav, age=21)`
$$ \_^*UPDATE\_^+\{table\}\_^*.\_^*((\_^*\{attribute\}\_^*=\_^*\{value\}\_^*)+(,\_^*\{attribute\}\_^*=\_^*\{value\}\_^*)^*)\_^* $$

---