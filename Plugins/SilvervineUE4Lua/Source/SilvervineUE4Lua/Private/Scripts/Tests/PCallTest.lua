-- SilvervineUE4Lua / devCAT studio
-- Copyright 2016 - 2019. Nexon Korea Corporation. All rights reserved.


SUE4Lua.Log("# PCallTest")

SUE4Lua.Log("xpcall returns: ", xpcall(function() end, SUE4Lua.ErrorHandler))
SUE4Lua.Log("xpcall returns: ", xpcall(
    function (a, b, c)
        return a*2, b*2, c*2
    end, 
    SUE4Lua.ErrorHandler,
    1, 2, 3))