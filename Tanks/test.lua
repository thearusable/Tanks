-- test lua --
-- function test --
LOG = function(text)
	print(text)
end

LOG(doTrzeciej(4))

-- table test --
table = {}
table[1] = "Lua taka piekna"
table[2] = "turbosmiesznosc"

-- objects test --
p = CreateObject()

function PrintObject(obj)
	print(GetObjectData(obj))
end

PrintObject(p)
DestroyObject(p)




