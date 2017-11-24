/*
 *  GuiManager.h
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxDatGui.h"


//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application´s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    static const string GUI_SETTINGS_FILE_NAME;
    static const string GUI_SETTINGS_NAME;
    static const int GUI_WIDTH;
    
public:

    //! Constructor
    GuiManager();

    //! Destructor
    ~GuiManager();

    //! Set-up the gui
    void setup();
    
    //! update the gui
    void update();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    int getWidth() {return m_gui.getWidth();}
    
    int getHeight() {return m_gui.getHeight();}
    
    ofPoint  getPosition() {return m_gui.getPosition();}
    
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
    void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    void onToggleEvent(ofxDatGuiToggleEvent e);
    
    void onMatrixEvent(ofxDatGuiMatrixEvent e);
    
    void onSetFrameRate(int& value);
    
    void onNextStar();
    
    void onPreviousStar();
    
    void onColorModeChange(const string& colorModeName);
    
    void onColorModeChange(int colorModeIndex);
    
    void onColorChange(const string& colorPaletteName);
    
    void onColorChange(int colorIndex);
    
    void onResetColors();
    
private:
    
    void setupGuiParameters();
    
    void setupLayoutGui();
    
    void setupColorModeGui();
    
    void setupPaletteGui();
        
    void setupNoiseGui();
    
    void setupScenesGui();
    
    void drawRectangle();
    
    void drawGui();
    
    void setupGuiEvents();

private:
    
    ofxDatGui			m_gui;

    ofParameter<float>	m_guiFPS;
    ofParameter<int>    m_framerate;
    

    ofParameterGroup         m_parameters;
    
    ofParameter<float>       m_starSize;
    ofParameter<int>         m_currentStar;
    
    ofParameter<int>        m_noiseResolution;
    ofParameter<float>      m_noiseFrequency;
    ofParameter<float>      m_noiseSpeed;
    
    vector<ofColor>         m_colors;
   
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================


