# PROFILE MANAGER STRUCTURE



## Old structure

```
func1()
{
    func2()
    {
        func3();
        {
            func4();
            {
                func5();
            }
        }
    }
}
```

- **Space complexity:** $O(cn)$
- $c$ is number of nested function layers.


## New structure
```
switch (function)
{
    case 1:
        func1(); case = x1;

    case 2:
        func2(); case = x2;
    
    case 3:
        func3(); case = x3;
    
    case 4:
        func4(); case = x4;

    case 5:
        func5(); case = x5;
}
```

- **Space complexity:** $O(n)$