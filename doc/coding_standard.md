Coding standard
===============
The coding standard used in this project will be laid out in this file.

Example
-------
```
class some_test
{
    uint32_t _test;
public:
    int calc() const
    {
        return 23;
    }
};
```

Indentation
-----------
Code shall be indented using real spaces. There shall be 4 spaces per identation level. No tabs shall be used.

Braces
------
All braces shall start on a new line.

Naming
------
Almost all naming is lower case and with underscores to seperate words. The only identifiers that shall be uppercase are constants (full uppercase) and template parameters (First letter capitalized). Private class variables shall start with an underscore.

Const
-----
As much shall be made constant as possible. This goes for class members as well as variables and parameters.
