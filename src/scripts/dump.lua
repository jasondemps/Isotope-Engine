local function scope_format(scope) 
  local str = ""
  for i = 1, scope do
    str = str .. "\t"
  end
  
  return str
end

local function print_type(item, scope)
      local scope_string = scope_format(scope)
        local t = type(item)
        if t == "string"
        or t == "number" then
                print (scope_string .. item)
        elseif t == "function" then
                print (scope_string .. "Function")
        elseif t == "table" then
                for k, v in pairs(item) do
                        io.stdout:write(scope_string .. ":")
                        print_type(k, scope + 1)
                        io.stdout:write(scope_string .. ":")
                        print_type(v, scope + 1) 
                end
        else
                print (scope_string .. "Unhandled type")
        end
end
 
function PrintGame()
        io.stdout:write( "Game:\n" )
        
        for k, v in pairs(Game) do
                print_type("Module: " .. k, 1)
                print_type(v, 1)
        end
end

PrintGame()