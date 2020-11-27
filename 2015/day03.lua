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
    local x = 0
    local y = 0
    local visited = {}
    visited[x .. ':' .. y] = true
    local count = 1
    for i = 1, #t do
        local ch = t:sub(i, i)
        if ch == '^' then y = y + 1 end
        if ch == 'v' then y = y - 1 end
        if ch == '<' then x = x - 1 end
        if ch == '>' then x = x + 1 end
        if not visited[x .. ':' .. y] then
            visited[x .. ':' .. y] = true
            count = count + 1
        end
    end
    return count
end

part2 = function(t)
    local santax = 0
    local santay = 0
    local robotx = 0
    local roboty = 0
    local visited = {}
    visited[santax .. ':' .. santay] = true
    local count = 1
    for i = 1, #t, 2 do
        local ch
        ch = t:sub(i, i)
        if ch == '^' then santay = santay + 1 end
        if ch == 'v' then santay = santay - 1 end
        if ch == '<' then santax = santax - 1 end
        if ch == '>' then santax = santax + 1 end
        if not visited[santax .. ':' .. santay] then
            visited[santax .. ':' .. santay] = true
            count = count + 1
        end
        ch = t:sub(i + 1, i + 1)
        if ch == '^' then roboty = roboty + 1 end
        if ch == 'v' then roboty = roboty - 1 end
        if ch == '<' then robotx = robotx - 1 end
        if ch == '>' then robotx = robotx + 1 end
        if not visited[robotx .. ':' .. roboty] then
            visited[robotx .. ':' .. roboty] = true
            count = count + 1
        end
    end
    return count
end

local data = readdata()
print("part1:", part1(data))
print("part2:", part2(data))
