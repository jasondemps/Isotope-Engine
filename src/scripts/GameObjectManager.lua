--[[
      GameObjectManager.lua

      supposed to take all sorts of different things, shove them into an Object (game object),
      then add them to a List (big table holding bunches of objects)

      i'm not sure if the logic is good or if this will even work, lol. i mean, it makes sense to me,
      but as i've said, i don't really know lua and how it works that well.

      so, bear with me, i'll get it working eventually.
]]
--this is the list "class", it holds dem objects
List = List or {
  objects = {}
}
--makeID makes an id for easy tracking of game objects
local function makeID()
  id = id or 0
  id = id + 1

  return id
end
--object class, has some functions and sech
Object = {
  --ID stored for referencing
  ID = 0,
  sprite = 0,
  --this is for adding an object to the list, also generates a new sprite at the moment
  add = function()
    local o = Object
    o.ID = makeID()
    sprite = Game.graphics.NewSprite()
    List.objects[o.ID] = o;
  end,
  --finds an object within the list. this is the part that i'm not really sure if it'll work
  find = function(val)
    local o = Object

    o = List.objects[val]

    return o
  end,
  --in theory, this should get an object for use
  get = function()
    local o = Object

    o.add()

    return o
  end
}