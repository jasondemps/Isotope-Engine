extensions = {
  audio = {
    ".mp3",
    ".wav"
  },

  level = {
  },
}

function Get_Extensions()
--[[
  exts = {}
  
  for i,v in pairs(extensions) do
    -- Should be within each type
    for i,_ in pairs(v) do
      -- Should be at the string lvl
      table.insert(exts, i)
    end
  end
  
  return exts
  ]]
  
  return extensions
end