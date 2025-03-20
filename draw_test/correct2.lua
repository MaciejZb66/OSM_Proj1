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
print(".")

local in2 = io.open("mid.txt", "r")
local out2 = io.open("mid2.txt","w")
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
        out2:write("1")
    else
        out2:write("0")
    end
    if bites == 16 then
        bites = 0
        out2:write("\n")
    end
end
out2:flush()
io.close()
print(".")

local in3 = io.open("mid2.txt", "r")
local out3 = io.open("res2.txt","w")
io.input(in3)
local countline = 0
out3:write("const int Test[]  = {\n\t")
bites = 0
for line in io.lines() do
    bites = bites + 1
    local num = 16
    local sum = 0
    for c in line:gmatch '.' do
        num = num - 1
        if c == "1" then
           sum = 2^num + sum
        end
    end
    if bites == 15 and countline == 118 then
        out3:write("0x" .. string.format('%04x', sum) .. "\n")
    else
        out3:write("0x" .. string.format('%04x', sum) .. ", ")
        if bites == 15 then
            bites = 0
            countline = countline + 1
            out3:write("\n\t")
        end
    end
end
out3:write("}")
out3:flush()
io.close()
print("finished")