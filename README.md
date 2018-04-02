# Sorted Array #

An implementation of a sortedarray container in C++.

## Usage ##

```c++
include "sortedarray.h"
```


Six lines tutorial on sorted arrays:

```c++
sortedarray<std::string> sarray(3, "ha"); // [ha, ha, ha]
sarray.clean();                           // []
sarray.insert("cruel"); 
sarray.insert("angel");
sarray.insert("thesis");
std::cout << sarray << std::endl;

/*
[***Unsorted array:]
cruel
angel
thesis
[***Sorted array:]
thesis
cruel
angel
*/                                   
```

You may pass an optional functor to the template to change the ordering criteria. Default is decreasing.