#include "graphicsmodule.h"
#include "..\\system\\modulehandler.h"

namespace Graphics
{
  GraphicsModule::GraphicsModule(System::Log* logger, System::AssetManager* assetManager) : Module("graphics", this), logger(logger), assetManager(assetManager), window(Window(*logger)), currTechnique(nullptr), drawFactory(&assetManager)
  {
    window.Render = &GraphicsModule::Render;

    // Setup the current "default" technique, and place it into the hash map.
    techniques.insert(std::make_pair("default", currTechnique = new Technique(*assetManager, "default", "default")));
    // If more shaders, insert hurrrrr.
    
    // Bind Drawable stuff
    AddEntry("NewSprite", drawFactory.NewSprite);

    // Bind Uniform stuff
    AddEntry("BindUniform", GraphicsModule::BindUniform);

    PushEntries();
  }

  // Lua pseudo: BindUniform(uni string, table(number/vector/matrix))
  // {elements = #, 0 1 2 3 ...}
  int GraphicsModule::BindUniform(lua_State *l)
  {
    // Get the uniform name
    const char* uniformName = lua_tostring(l, 1);

    // Get the number of elements from the table
    
    lua_pushstring(l, "elements");
    lua_gettable(l, 2);
    int elem = lua_tointeger(l, -1);

    // Set up the array of elements expected
    lua_Number *elems = new lua_Number[elem];

    // Request each position from lua and store it.
    for (int i = 1; i <= elem; ++i)
    {
      lua_pushnumber(l, i);
      lua_gettable(l, 2);
      elems[i - 1] = lua_tonumber(l, -1);
    }

    Technique* currTech = System::ModuleHandler::Get().GetModule("graphics")->GetParentAs<GraphicsModule*>()->currTechnique;

    switch(elem)
    {
      // Vectors
    case 1:
      gl::Uniform1i(currTech->GetProgram(), *elems);
      break;
    case 2:
      gl::Uniform2fv(currTech->GetProgram(), elem, (const GLfloat *)elems);
      break;
    case 3:
      gl::Uniform3fv(currTech->GetProgram(), elem, (const GLfloat *)elems);
      break;
    case 4:
      gl::Uniform4fv(currTech->GetProgram(), elem, (const GLfloat *)elems);
      break;

      // Matrices
    case 9:
      gl::UniformMatrix3fv(currTech->GetProgram(), elem, gl::FALSE_, (const GLfloat *)elems);
      break;
    case 16:
      gl::UniformMatrix4fv(currTech->GetProgram(), elem, gl::FALSE_, (const GLfloat *)elems);
      break;
    default:
      System::ModuleHandler::Get().GetModule("graphics")->GetParentAs<GraphicsModule*>()->logger->PrintError("Uniform count is wrong!\n");
    }

    delete elems;

    return 0;
  }

  void GraphicsModule::Render()
  {
    GraphicsModule* gfxMod = System::ModuleHandler::Get().GetModule("graphics")->GetParentAs<GraphicsModule*>();
    
    // Make sure we activate the program before we try to render anything.
    gfxMod->currTechnique->Render();

    // Render what drawables we can.
    for (auto d : gfxMod->drawFactory.GetDrawables())
      if (d->GetVisible())
        d->Render();
  }

  DrawableFactory& GraphicsModule::GetDrawFact() { return drawFactory; }
  Window& GraphicsModule::GetWindow() { return window; }

  GraphicsModule::~GraphicsModule()
  {
    for (auto t : techniques)
      delete t.second;

    techniques.clear();
  }
}