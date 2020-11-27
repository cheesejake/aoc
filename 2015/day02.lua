readdata = function()
    local ret = ""
    for line in io.lines() do
        ret = ret .. line .. '\n'
    end
    return ret
end

part1 = function(t)
    local totalarea = 0
    for w in t:gmatch("(.-)\n") do
        local length = w:match("(.-)x")
        local width = w:match(".-x(.-)x")
        local height = w:match(".+x(.+)")
        local area1 = length * width
        local area2 = length * height
        local area3 = width * height
        local smallest = area1
        if area2 < smallest then smallest = area2 end
        if area3 < smallest then smallest = area3 end
        totalarea = totalarea + 2*area1 + 2*area2 + 2*area3 + smallest
    end
    return totalarea
end

part2 = function(t)
    local totallength = 0
    for w in t:gmatch("(.-)\n") do
        local length = w:match("(.-)x")
        local width = w:match(".-x(.-)x")
        local height = w:match(".+x(.+)")
        local per1 = 2*length + 2*width
        local per2 = 2*length + 2*height
        local per3 = 2*width + 2*height
        local smallest = per1
        if per2 < smallest then smallest = per2 end
        if per3 < smallest then smallest = per3 end
        totallength = totallength + smallest + length*width*height
    end
    return totallength
end

local data = readdata()
print("part1:", part1(data))
print("part2:", part2(data))
