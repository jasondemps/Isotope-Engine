require "GameObjectManager"

function lua_init()
  music = Game.audio.LoadStream("loopingSound1", .1)
  effect = Game.audio.LoadSound("soundEffect1")
  
  Game.audio.Play(music)
  Game.audio.Play(effect)
end

function lua_main()--args)
  --print (Game.core.testTable.teststring111)
  --print(Game.core.printnum())
  --Game.log.PrintError("THIS IS AN ERROR!")
  --Game.log.PrintDebug("Some Debuggannnzzzz")
  --print (Game.core.testNum)
  --print (Game.core)
  
  --print (Game.core.printnum())
  --Game.log.PrintDebug("L")
  --Game.log.PrintError("LOL HI")
--asdf
  --Game.log.PrintInfo( x )
	--x = Game.graphics.NewSprite()
  
  --[[
  for _,v in ipairs(array) do
    print(v)
  end
  
  for i, v in pairs(array) do
    print(i .. " " .. v)
  end
  
  ]]
  lua_init()
  
  playing = true
  
  keyString = "Left"
  keyrightString = "Right"
  
  while (playing) do
    -- Update Engine stuff each loop
    Game.engine.Update()
    
    if Game.keyboard.KeyDown(keyString) then
      print (keyString.." key is down!")
      Game.audio.Play(effect)
    end
    
    if Game.keyboard.KeyDown(keyrightString) then
      print (keyrightString.." key is down!")
      Game.audio.Play(effect)
    end
    
    if Game.keyboard.KeyPressed(keyString) then
      print (keyString.." Key is pressed!")
    end

    if Game.keyboard.KeyPressed(keyrightString) then
      print (keyString.." Key is pressed!")
    end

    if Game.keyboard.KeyUp(keyString) then
      print (keyString.." key is up!")
    end
    
    -- Get time and print'er
    --print (Game.engine.GetTicks())
    
    if not x then
      -- Pass vertices + indices + a tex?
      -- {Vertices}, {Indices}, "image"
      
      --[[
        x = Game.graphics.NewSprite(
          { 
            count = 3,
            {0, 0, -1}, -- Vertex
            {1, 1, -1}, -- Vertex
            {0, 1, -1}, -- Vertex
          },
          {
            count = 1,
            {0, 1, 2}, -- Index
          },
          "test.png" -- Texture
        )
      ]]
      --x = Game.graphics.NewSprite()
      x = Game.graphics.NewSprite()
      --x = Object.get(x)
      --Game.log.PrintInfo(x)
    end

    if not b then
      b = Object.get()
      print(b.ID)
    end

    if not c then
      c = Object.get()
      print(c.ID)
    end

    if not d then
      d = Object.get()
      print(d.ID)
    end

    if not e then
      e = Object.get()
      print(e.ID)
    end

    if not f then
      f = Object.get()
      for k, v in pairs(List.objects) do
        print(List.objects[v].ID)
      end
    end     
  end
  
  return 0
end