-- Credit to orig posting for lua c++ integration example: https://gist.github.com/Youka/2a6e69584672f7cb0331
-- We're thankful for your help by creating this example!


local obj = MyObject(42)
print(obj:get())    -- 42
obj:set(-1.5)
print(obj:get())    -- -1.5
