part1 = function(line)
    local x = 0
    local y = 0
    local deltax = 0 -- initially
    local deltay = 1 -- facing north
    for letter, size in string.gmatch(line, '([RL])(%d+)') do
        if letter == 'R' then
            if deltax == 0 then
                deltax = deltay
                deltay = 0
            else
                deltay = -deltax
                deltax = 0
            end
        else
            if deltay == 0 then
                deltay = deltax
                deltax = 0
            else
                deltax = -deltay
                deltay = 0
            end
        end
        x = x + size * deltax
        y = y + size * deltay
    end
    return math.abs(x) + math.abs(y)
end

part2 = function(line)
    local x = 0
    local y = 0
    local deltax = 0 -- initially
    local deltay = 1 -- facing north
    local visited = {}
    visited[x .. ':' .. y] = true
    for letter, size in string.gmatch(line, '([RL])(%d+)') do
        if letter == 'R' then
            if deltax == 0 then
                deltax = deltay
                deltay = 0
            else
                deltay = -deltax
                deltax = 0
            end
        else
            if deltay == 0 then
                deltay = deltax
                deltax = 0
            else
                deltax = -deltay
                deltay = 0
            end
        end
        for i = 1, size do
            x = x + deltax
            y = y + deltay
            if visited[x .. ':' .. y] then
                return math.abs(x) + math.abs(y) end
            visited[x .. ':' .. y] = true
        end
    end
    return nil
end

for line in io.lines() do
    print("day 1, part 1: ", part1(line))
    print("day 1, part 2: ", part2(line))
end
