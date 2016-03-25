/* 
---------------------------------------------------------------- 
This is a mini Ogre Application. It does nothing. 
by Mythma (mythma@126.com)
--------------------------
Eihort porting: stoneCold
---------------------------------------------------------------- 
*/ 
 
// OGRE
#include <OGRE/Ogre.h>

// own
#include "SimpleFrameListener.h"
#include "SimpleKeyListener.h"
#include "SimpleMouseListener.h"
#include "ObjectManager.h"

using namespace Ogre;
 
/// Initialize renderer
bool manualInitialize(const String& desiredRenderer)
{
  RenderSystem* renderSystem;
  bool ok = false;
  const RenderSystemList& renderers = Root::getSingleton().getAvailableRenderers();

  // See if the list is empty (no renderers available)
  if (renderers.empty())
    return false;

  for(RenderSystemList::const_iterator it = renderers.begin(); it != renderers.end(); it++)
  {
    RenderSystem* rs = (*it);
    if(rs->getName() == desiredRenderer)
    {
      ok = true;
      renderSystem = rs;
      break;
    }
  }

  if(!ok)
  {
    // We still don't have a renderer; pick
    // up the first one from the list
    renderSystem = renderers.front();
  }

  Root::getSingleton().setRenderSystem(renderSystem);

  // Manually set some configuration options (optional)
  renderSystem->setConfigOption("Video Mode", "640 x 480");

  return true;

}

////////////////////////////////////////////////////////////////////////// 
// main 
////////////////////////////////////////////////////////////////////////// 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
  //-----------------------------------------------------
  // 1 enter ogre
  //-----------------------------------------------------
  Root* root = new Root;

  //-----------------------------------------------------
  // 2 configure resource paths
  //-----------------------------------------------------
  // Load resource paths from config file

  // File format is:
  //  [ResourceGroupName]
  //  ArchiveType=Path
  //  .. repeat
  // For example:
  //  [General]
  //  FileSystem=media/
  //  Zip=packages/level1.zip

  ConfigFile cf;
  cf.load("resources.cfg");

  // Go through all sections & settings in the file
  ConfigFile::SectionIterator seci = cf.getSectionIterator();

  String secName, typeName, archName;
  while (seci.hasMoreElements())
  {
    secName = seci.peekNextKey();
    ConfigFile::SettingsMultiMap *settings = seci.getNext();
    ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i)
    {
      typeName = i->first;
      archName = i->second;
      ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    }
  }
  //-----------------------------------------------------
  // 3 Configures the application and creates the window
  //-----------------------------------------------------
  if(!root->showConfigDialog())
  {
    delete root;
    return false; // Exit the application on cancel
  }

  //if (!manualInitialize("OpenGL"))
  //  std::cout <<"meeeeh..." <<std::endl;

  RenderWindow* window = root->initialise(true, "Simple Ogre App");
  std::cout <<"test" <<std::endl;
  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  //-----------------------------------------------------
  // 4 Create the SceneManager
  //
  //        ST_GENERIC = octree
  //        ST_EXTERIOR_CLOSE = simple terrain
  //        ST_EXTERIOR_FAR = nature terrain (depreciated)
  //        ST_EXTERIOR_REAL_FAR = paging landscape
  //        ST_INTERIOR = Quake3 BSP
  //-----------------------------------------------------
  SceneManager* sceneMgr = root->createSceneManager(ST_GENERIC);

  //-----------------------------------------------------
  // 5 Create the camera
  //-----------------------------------------------------
  Camera* camera = sceneMgr->createCamera("SimpleCamera");

  //-----------------------------------------------------
  // 6 Create one viewport, entire window
  //-----------------------------------------------------
  Viewport* viewPort = window->addViewport(camera);

  //----------------------------------------------------
  // 7 add OIS input handling
  //----------------------------------------------------
  OIS::ParamList pl;
  size_t windowHnd = 0;
  std::ostringstream windowHndStr;

  //tell OIS about the Ogre window
  window->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

  //setup the manager, keyboard and mouse to handle input
  OIS::InputManager* inputManager = OIS::InputManager::createInputSystem(pl);
  OIS::Keyboard* keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
  OIS::Mouse*    mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

  //tell OIS about the window's dimensions
  unsigned int width, height, depth;
  int top, left;
  window->getMetrics(width, height, depth, left, top);
  const OIS::MouseState &ms = mouse->getMouseState();
  ms.width = width;
  ms.height = height;

  // everything is set up, now we listen for input and frames (replaces while loops)
  //key events
  SimpleKeyListener* keyListener = new SimpleKeyListener();
  keyboard->setEventCallback(keyListener);
  //mouse events
  SimpleMouseListener* mouseListener = new SimpleMouseListener();
  mouse->setEventCallback(mouseListener);
  //render events
  SimpleFrameListener* frameListener = new SimpleFrameListener(keyboard, mouse);
  root->addFrameListener(frameListener);

  //----------------------------------------------------
  // 8 start rendering
  //----------------------------------------------------
  root->startRendering(); // blocks until a frame listener returns false. eg from pressing escape in this example

  //----------------------------------------------------
  // 9 clean
  //----------------------------------------------------
  //OIS
  inputManager->destroyInputObject(mouse);
  mouse = nullptr;
  inputManager->destroyInputObject(keyboard);
  keyboard = nullptr;
  OIS::InputManager::destroyInputSystem(inputManager);
  inputManager = nullptr;

  //listeners
  delete frameListener;
  delete mouseListener;
  delete keyListener;
  //Ogre
  delete root;

  return 0;
}
