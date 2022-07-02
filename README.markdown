<h1 align="center"><i>✨ lua-smaz ✨ </i></h1>

<h3 align="center">The lua binding for <a href="https://github.com/antirez/smaz">smaz</a> </h3>

### usage
```lua
smaz = require("smaz")

data = "12341234"

encoded = smaz.compress(data, 100)
print(encoded)
print(smaz.decompress(encoded,100))
```