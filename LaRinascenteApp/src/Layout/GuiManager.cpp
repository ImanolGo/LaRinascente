/*
 *  GuiManager.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */

#include "ofMain.h"

#include "AppManager.h"

#include "GuiManager.h"
#include "GuiTheme.h"


const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "GUI";
const int GuiManager::GUI_WIDTH = 350;


GuiManager::GuiManager(): Manager(), m_showGui(true), m_recordToggle(NULL)
{
	//Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
	if(m_initialized)
		return;
    
    Manager::setup();


    this->setupGuiParameters();
    this->setupScenesGui();
    this->setupLayoutGui();
    this->setupColorModeGui();
    this->setupPaletteGui();
    this->setupNoiseGui();
    this->setupGuiEvents();
    this->loadGuiValues();
    
    AppManager::getInstance().getGuiManager().onColorModeChange("WARM");

    ofLogNotice() <<"GuiManager::initialized";
    
}

void GuiManager::setupGuiParameters()
{
    
    ofxDatGuiLog::quiet();
    
    m_gui.setPosition(ofxDatGuiAnchor::TOP_LEFT);
    //m_gui.setAssetPath(ofToDataPath("fonts/"));
    //m_gui.setAssetPath("../Resources/data/fonts/");
    m_gui.setTheme(new GuiTheme());
    
    
    int margin =  LayoutManager::MARGIN;
    m_gui.setAutoDraw(false);
    auto pos = m_gui.getPosition();
    m_gui.setPosition(pos.x + margin, pos.y + margin);
    m_gui.addHeader(GUI_SETTINGS_NAME, false);
    
    m_gui.addFRM();
    
    m_framerate.set("Framerate",  60, 5, 60);
    m_framerate.addListener(this, &GuiManager::onSetFrameRate);
    m_parameters.add(m_framerate);
    
    m_gui.addSlider(m_framerate);
    
    m_gui.addBreak();
}

void GuiManager::setupScenesGui()
{
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    vector<string> opts;
    
    for(int i = 0; i < sceneManager->getNumberScenes(); i++)
    {
        opts.push_back(sceneManager->getSceneName(i));
    }
    
    string label = "SCENES";
    
    m_gui.addDropdown(label, opts);
    auto menu = m_gui.getDropdown(label);
    menu->expand(); //let's have it open by default
    menu->setStripeColor(ofColor::pink);
    for (int i=0; i<menu->size(); i++) menu->getChildAt(i)->setStripeColor(ofColor::pink);
    m_gui.addBreak();
    
}

void GuiManager::setupLayoutGui()
{
    auto starsManager = &AppManager::getInstance().getStarsManager();
    
    m_starSize.set("Star Size",  20.0, 0.0, 100.0 );
    m_starSize.addListener(starsManager, &StarsManager::onSetStarsSize);
    m_parameters.add(m_starSize);
    
    m_explosionsInterval.set("Star Interval",  0.1, 0.0, 0.5 );
    m_explosionsInterval.addListener(starsManager, &StarsManager::onSetExplosionsInterval);
    m_parameters.add(m_explosionsInterval);
    
    m_explosionsTime.set("Star Time",  1.0, 0.0, 5.0 );
    m_explosionsTime.addListener(starsManager, &StarsManager::onSetExplosionsTime);
    m_parameters.add(m_explosionsTime);
    
    m_currentStar.set("Current Star",  0, 0, 94);
    m_currentStar.addListener(starsManager, &StarsManager::onSetStarPosition);
    m_parameters.add(m_currentStar);

    ofxDatGuiFolder* folder = m_gui.addFolder("LAYOUT", ofColor::white);
    m_recordToggle = folder->addToggle("RECORD");
    folder->addSlider(m_starSize);
    folder->addSlider(m_explosionsInterval);
    folder->addSlider(m_explosionsTime);
    //folder->addSlider(m_currentStar);
    folder->expand();
    m_gui.addBreak();
}


void GuiManager::setupColorModeGui()
{
    vector<string> opts;
    auto colorModeNames = AppManager::getInstance().getColorManager().getPaletteNames();
    for(auto colorMode: colorModeNames)
    {
        opts.push_back(colorMode);
    }
    
    string label = "COLOR MODE";
    
    m_gui.addDropdown(label, opts);
    auto menu = m_gui.getDropdown(label);
    menu->expand(); //let's have it open by default
    menu->setStripeColor(ofColor::greenYellow);
    for (int i=0; i<menu->size(); i++) menu->getChildAt(i)->setStripeColor(ofColor::greenYellow);
    m_gui.addBreak();
}

void GuiManager::setupPaletteGui()
{
    // add some color pickers to color our lines //
    ofxDatGuiFolder* f1 = m_gui.addFolder("PALETTE", ofColor::fromHex(0x2FA1D6));
    
    int numColors = AppManager::getInstance().getColorManager().getMaxNumberOfColors();
    for(int i = 0; i < numColors; i++)
    {
        auto color = AppManager::getInstance().getColorManager().getColor(i);
        ofColor c(color->r, color->g, color->b);
        string colorName = "COLOR " + ofToString(i);
        f1->addColorPicker(colorName);
    }
    f1->expand();
    m_gui.addBreak();
    
}

void GuiManager::setupNoiseGui()
{
    auto noiseManager = &AppManager::getInstance().getNoiseManager();
    
    m_noiseResolution.set("Noise Resolution",  64, 2, 256 );
    m_noiseResolution.addListener(noiseManager, &NoiseManager::onNoiseResolutionChange);
    m_parameters.add(m_noiseResolution);
    
    m_noiseFrequency.set("Noise Frequency",  0.4, 0.0, 4.0);
    m_noiseFrequency.addListener(noiseManager, &NoiseManager::onNoiseFrequencyChange);
    m_parameters.add(m_noiseFrequency);
    
    m_noiseSpeed.set("Noise Speed",  1.0, 0.001, 3);
    m_noiseSpeed.addListener(noiseManager, &NoiseManager::onNoiseSpeedChange);
    m_parameters.add(m_noiseSpeed);
    
    ofxDatGuiFolder* folder = m_gui.addFolder("NOISE", ofColor::white);
    folder->addSlider(m_noiseResolution);
    folder->addSlider(m_noiseFrequency);
    folder->addSlider(m_noiseSpeed);
    folder->expand();
    m_gui.addBreak();
}

void GuiManager::update()
{
    m_gui.update();
}


void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    this->drawRectangle();
    this->drawGui();
}


void GuiManager::drawGui()
{
    ofEnableAlphaBlending();
    m_gui.draw();
    ofDisableAlphaBlending();
}

void GuiManager::setupGuiEvents()
{
    m_gui.onDropdownEvent(this, &GuiManager::onDropdownEvent);
    m_gui.onColorPickerEvent(this, &GuiManager::onColorPickerEvent);
    m_gui.onButtonEvent(this, &GuiManager::onButtonEvent);
    m_gui.onToggleEvent(this, &GuiManager::onToggleEvent);
    m_gui.onMatrixEvent(this, &GuiManager::onMatrixEvent);
}


void GuiManager::saveGuiValues()
{
    ofXml xml;
    xml.serialize(m_parameters);
    xml.save(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    ofXml xml(GUI_SETTINGS_FILE_NAME);
    xml.deserialize(m_parameters);
}


void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}

void GuiManager::drawRectangle()
{
    int margin =  LayoutManager::MARGIN;
    ofPushStyle();
    ofSetColor(15);
    ofDrawRectangle( m_gui.getPosition().x - margin, 0, m_gui.getWidth() + 2*margin, ofGetHeight());
    ofPopStyle();
}

void GuiManager::onResetColors()
{
    int numColors = AppManager::getInstance().getColorManager().getMaxNumberOfColors();
    for(int i = 0; i < numColors; i++)
    {
        string colorName = "COLOR " + ofToString(i);
        m_gui.getColorPicker(colorName)->setVisible(false);
    }
    
    numColors = AppManager::getInstance().getColorManager().getNumberOfColors();
    for(int i = 0; i < numColors; i++)
    {
        auto color = AppManager::getInstance().getColorManager().getColor(i);
        ofColor c(color->r, color->g, color->b);
        string colorName = "COLOR " + ofToString(i);
        m_gui.getColorPicker(colorName)->setVisible(true);
        m_gui.getColorPicker(colorName)->setColor(c);
    }
}



void GuiManager::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "onDropdownEvent: " << e.target->getName() << " Selected" << endl;
    
    if(e.target->getName() == "SCENES")
    {
        AppManager::getInstance().getSceneManager().changeScene(e.child);
        m_gui.getDropdown(e.target->getName())->expand();
        m_gui.getDropdown(e.target->getName())->setLabel("SCENES:" + e.target->getLabel());
    }
    
    else if(e.target->getName() == "COLOR MODE")
    {
        AppManager::getInstance().getColorManager().changeColorPalette(e.target->getLabel());
        m_gui.getDropdown(e.target->getName())->expand();
        m_gui.getDropdown(e.target->getName())->setLabel("COLOR MODE: " + e.target->getLabel());
    }
}

void GuiManager::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    cout << "onColorPickerEvent: " << e.target->getName() << " Selected" << endl;
    
    if(e.target->getName() == "LIGHT")
    {
    }
    
}

void GuiManager::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "onButtonEvent: " << e.target->getName() << " Selected" << endl;
    
    if(e.target->getName() == "Autodiscovery")
    {
        //AppManager::getInstance().getUdpManager().sendAutodiscovery();
    }
}


void GuiManager::onToggleEvent(ofxDatGuiToggleEvent e)
{
    cout << "onToggleEvent: " << e.target->getName() << " Selected" << endl;
    
    if(e.target->getName() == "RECORD")
    {
        AppManager::getInstance().getImagesExportManager().onSetRecording(e.target->getChecked());
    }
}

void GuiManager::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    cout << "onMatrixEvent " << e.child << " : " << e.enabled << endl;
}

void GuiManager::onSetFrameRate(int& value)
{
    value = ofClamp(value, 0.0, 60);
    ofSetFrameRate(value);
}


void GuiManager::onNextStar()
{
    m_currentStar += 1;
    m_currentStar = ofClamp(m_currentStar, m_currentStar.getMin(), m_currentStar.getMax());
}

void GuiManager::onPreviousStar()
{
    m_currentStar -= 1;
    m_currentStar = ofClamp(m_currentStar, m_currentStar.getMin(), m_currentStar.getMax());
}

void GuiManager::onColorChange(const string& colorPaletteName)
{
    int index = AppManager::getInstance().getColorManager().getIndex(colorPaletteName);
    this->onColorChange(index);
}

void GuiManager::onColorChange(int colorIndex)
{
    string dropBoxName = "COLOR PALETTES";
    auto menu = m_gui.getDropdown(dropBoxName);
    menu->select(colorIndex);
    string label =  menu->getChildAt(colorIndex)->getLabel();
    menu->setLabel("PALETTE:" + label);
    AppManager::getInstance().getColorManager().changeColorPalette(colorIndex);
    
}

void GuiManager::onColorModeChange(const string &colorModeName)
{
    int index = AppManager::getInstance().getColorManager().getIndex(colorModeName);
    this->onColorModeChange(index);
}

void GuiManager::onColorModeChange(int colorModeIndex)
{
    if(colorModeIndex<0){
        return;
    }
    
    string dropBoxName = "COLOR MODE";
    auto menu = m_gui.getDropdown(dropBoxName);
    menu->select(colorModeIndex);
    string label =  menu->getChildAt(colorModeIndex)->getLabel();
    menu->setLabel(dropBoxName + ": " + label);
    AppManager::getInstance().getColorManager().changeColorPalette(label);
}

void GuiManager::toggleRecord()
{
    if(m_recordToggle!=NULL)
    {
        m_recordToggle->toggle();
        AppManager::getInstance().getImagesExportManager().onSetRecording(m_recordToggle->getChecked());
    }
}
    
    

