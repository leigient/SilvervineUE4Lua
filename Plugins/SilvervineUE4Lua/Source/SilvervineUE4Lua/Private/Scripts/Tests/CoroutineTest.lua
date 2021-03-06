-- SilvervineUE4Lua / devCAT studio
-- Copyright 2016 - 2019. Nexon Korea Corporation. All rights reserved.


SUE4Lua.Log("# CoroutineTest")

local Co = coroutine.create(function (a, b, c)
    SUE4Lua.Log("We are in coroutine.")
    coroutine.yield()
    SUE4Lua.Log("resumed.")

    --local Nil
    --Nil:Foo()

    return a + b + c
end)

SUE4Lua.Log("coroutine returns: ", coroutine.resume(Co, 1, 2, 3))
SUE4Lua.Log("coroutine returns: ", coroutine.resume(Co))

