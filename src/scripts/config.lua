-- Engine Flags
ContinueOnError = true -- This will try to re-evaluate if Lua incurs an error. Use this to never leave Lua from the engine! *Takes precedence over LoopEval!*
LoopEval = true -- Will loop evaluation indefinitely or until return code is not clean.

-- Package paths
package.path = Game.assets.sourceDir .. "scripts\\?.lua;" .. package.path

-- Entry Point
MainFile = "main.lua" -- Our main entry point into our lua code