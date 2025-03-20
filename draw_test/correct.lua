---@diagnostic disable: need-check-nil
local in1 = io.open("input.txt","r")
local outpos = io.open("mid.txt","w")
io.input(in1)
for line in io.lines() do
    for c in line:gmatch '.' do
        if c ~= "," then
            if c~= " " then
               outpos:write(c)
            end
        else
            outpos:write("\n")
        end
    end
end
outpos:flush()
io.close()

local in2 = io.open("mid.txt", "r")
local out2 = io.open("res.txt","w")
io.input(in2)
local bites = 0
for line in io.lines() do
    bites = bites + 1
    local num = 1
    local iszero = 0
    for c in line:gmatch '.' do
        if num > 2 then
            if c ~= "0" then
                iszero = iszero + 1
            end
        end
        num = num + 1
    end
    if iszero == 0 then
        out2:write("1, ")
    else
        out2:write("0, ")
    end
    if bites == 240 then
        bites = 0
        out2:write("\n")
    end
end
out2:flush()
io.close()
print("finished")