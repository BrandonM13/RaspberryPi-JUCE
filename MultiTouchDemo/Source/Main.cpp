/*
  ==============================================================================

    This file contains the startup code for a PIP.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MultiTouchDemo.h"

class Application    : public juce::JUCEApplication
{
public:
    //==============================================================================
    Application() = default;

    const juce::String getApplicationName() override       { return "MultiTouchDemo"; }
    const juce::String getApplicationVersion() override    { return "1.0.0"; }

    void initialise (const juce::String&) override
    {
        mainWindow.reset (new MainWindow ("MultiTouchDemo", new MultiTouchDemo, *this));
    }

    void shutdown() override                         { mainWindow = nullptr; }

private:
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (const juce::String& name, juce::Component* c, JUCEApplication& a)
            : DocumentWindow (name, juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                                .findColour (ResizableWindow::backgroundColourId), 0),
              app (a)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (c, true);

            c->addToDesktop(1);
            juce::Desktop::getInstance().setKioskModeComponent(c);
            
            c->setMouseCursor(MouseCursor::NoCursor);

            c->setMouseCursor(MouseCursor::NoCursor);

            centreWithSize (getWidth(), getHeight());
        }

        void closeButtonPressed() override
        {
            app.systemRequestedQuit();
        }

    private:
        JUCEApplication& app;

        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
START_JUCE_APPLICATION (Application)
