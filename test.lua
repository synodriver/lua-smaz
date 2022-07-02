smaz = require("smaz")

data = "12341234"

encoded = smaz.compress(data, 10)
print(encoded)
print(smaz.decompress(encoded))
