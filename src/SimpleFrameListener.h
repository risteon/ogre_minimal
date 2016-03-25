/**
 * \author  risteon
 * \date    2016-03-25
 */

#ifndef OGRE_MINIMAL_SIMPLEFRAMELISTENER_H
#define OGRE_MINIMAL_SIMPLEFRAMELISTENER_H

// OGRE
#include <OGRE/OgreFrameListener.h>
#include <OIS/OIS.h>

/**
 * class SimpleFrameListener
 */
class SimpleFrameListener : public Ogre::FrameListener
{
public:
    SimpleFrameListener(OIS::Keyboard* keyboard, OIS::Mouse* mouse)
    {
      mKeyboard = keyboard;
      mMouse = mouse;
    }
    // This gets called before the next frame is beeing rendered.
    bool frameStarted(const Ogre::FrameEvent& evt)
    {
      //update the input devices
      mKeyboard->capture();
      mMouse->capture();

      //exit if key KC_ESCAPE pressed
      if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;

      return true;
    }
    // This gets called at the end of a frame.
    bool frameEnded(const Ogre::FrameEvent& evt)
    {
      return true;
    }

private:
    OIS::Keyboard* mKeyboard;
    OIS::Mouse* mMouse;
};

#endif //OGRE_MINIMAL_SIMPLEFRAMELISTENER_H
