readdata = function()
    local ret = ""
    local ch
    repeat
        ch = io.read(1)
        if ch then ret = ret .. ch end
    until ch == nil
    return ret
end

part1 = function(t)
    local floor = 0
    for i = 1, #t do
        local ch = t:sub(i, i)
        if ch == '(' then floor = floor + 1 end
        if ch == ')' then floor = floor - 1 end
    end
    return floor
end

part2 = function(t)
    local floor = 0
    local count = 0
    for i = 1, #t do
        count = count + 1
        local ch = t:sub(i, i)
        if ch == '(' then floor = floor + 1 end
        if ch == ')' then floor = floor - 1 end
        if floor == -1 then return count end
    end
    return -1
end

local data = readdata()
print("part1:", part1(data))
print("part2:", part2(data))
