# SYNTAXES IN ORDER (v2.0.0)


## 1. Features

- B+ tree implementation
- File inspector


## 2. Commands

1. `SELECT tbl_name.($sno, name)`
2. `SELECT tbl_name.(@) WHERE (score>7.0 & sem=8)`
3. `SELECT tbl_name.($sno, name) WHERE (score>7.0 & sem=8)`
4. `UPDATE tbl_name.(salary=80000, rank=captain) WHERE (years>2 | medals>=1)`
5. `CLEAR CACHE ROOT`
6. `CLEAR CACHE DB db_name`
7. `CLEAR CACHE TABLE tbl_name`

---