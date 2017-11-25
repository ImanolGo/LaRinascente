/*
 *  ColorManager.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 24/11/17.
 *
 */


#include "ofMain.h"
#include "AppManager.h"
#include "ColorManager.h"

ColorManager::ColorManager(): Manager(), m_maxNumberColors(0)
{
	//Intentionally left empty
}


ColorManager::~ColorManager()
{
    ofLogNotice() <<"ColorManager::Destructor";
}


void ColorManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"ColorManager::initialized";

	Manager::setup();

    this->setupColors();

}

void ColorManager::draw()
{
    //Empty
}


void ColorManager::setupColors()
{
    m_blackColor = shared_ptr<ofColor>(new ofColor(0,0,0));
    
    if(this->loadSettingsFile()){
        this->loadColorPalettes();
    }
}

bool ColorManager::loadSettingsFile()
{
    
    if(!m_xml.load(SettingsManager::APPLICATION_SETTINGS_FILE_NAME)){
        ofLogNotice() <<"ColorManager::loadSettingsFile-> unable to load file: " << SettingsManager::APPLICATION_SETTINGS_FILE_NAME ;
        return false;
    }
    
    ofLogNotice() <<"ColorManager::loadSettingsFile->  successfully loaded " << SettingsManager::APPLICATION_SETTINGS_FILE_NAME ;
    return true;
}

void ColorManager::loadColorPalettes()
{
    m_xml.setTo("//");
    
    string colorsSettingsPath = "//colors";
    if(m_xml.exists(colorsSettingsPath)) {
        
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;
        
        colorsSettingsPath = "//colors/palette[0]";
        
        m_xml.setTo(colorsSettingsPath);
        do
        {
            attributes =  m_xml.getAttributes();
            string paletteName = attributes["name"];
            ofLogNotice() <<"ColorManager::loadColorPalettes->  loading color palette: " << paletteName;
            
            m_paletteNames.push_back(paletteName);
            m_currentPaletteName = paletteName;
            
            // set our "current" color to the first one
            if(m_xml.setTo("color[0]"))
            {
                ColorPalette palette;
                
                // get each individual name and hex color
                do {
                    
                    attributes =  m_xml.getAttributes();
                    ofLogNotice() <<"ColorManager::loadColorPalettes->  loading color: " << attributes["name"];
                    
                    ofColor c = ofColor::fromHex(ofHexToInt(attributes["hex"]));
                    
                    shared_ptr<ofColor> color = shared_ptr<ofColor>(new ofColor(c.r, c.g, c.b));
                    palette.push_back(color);
                    //ofLogNotice() <<"ColorManager::loadColorPalettes->  loading color: hex = " << attributes["hex"] << ", hex int  = " << ofHexToInt(attributes["hex"]);
                    //ofLogNotice() <<"ColorManager::loadColorPalettes->  loading color: r = " << color->r << ", g = " <<  color->g << ", b = " <<  color->b;
                    
                }
                while(m_xml.setToSibling()); // go the next PT
                
                // go back up
                m_xml.setToParent();
                
                m_colorPalettes[paletteName] = palette;
                
                if(m_colorPalettes[paletteName].size() > m_maxNumberColors)
                {
                    m_maxNumberColors = m_colorPalettes[paletteName].size();
                }
            }
        }
        while(m_xml.setToSibling()); // go to the next node
        
        
        ofLogNotice() <<"ColorManager::loadColors->  successfully loaded the applications colors" ;
        return;
    }
    
    ofLogNotice() <<"ColorManager::loadColors->  path not found: " << colorsSettingsPath ;
}

bool ColorManager::changeColorPalette(string paletteName)
{
    if ( m_colorPalettes.find(paletteName) == m_colorPalettes.end() ) {
        // not found
        return false;
    } else {
        // found
        m_currentPaletteName = paletteName;
        ofLogNotice() <<"ColorManager::changeColorPalette -> Changed to palette: " << m_currentPaletteName;
        AppManager::getInstance().getGuiManager().onResetColors();
        this->initializeColorIndexList();
    
        return true;
    }
}

bool ColorManager::changeColorPalette(int paletteIndex)
{
    
    if(paletteIndex < 0 || paletteIndex >= m_paletteNames.size()){
        return false;
    }
    
    return changeColorPalette(m_paletteNames[paletteIndex]);
}


shared_ptr<ofColor> ColorManager::getColor(int colorIndex)
{
    if ( m_colorPalettes.find(m_currentPaletteName) == m_colorPalettes.end() ) {
        // not found
        return m_blackColor;
    }
    
    const ColorPalette& palette = m_colorPalettes.at(m_currentPaletteName);
    
    if(colorIndex < 0 || colorIndex >= palette.size()){
        return m_blackColor;
    }
    
    return palette[colorIndex];
}

int ColorManager::getNumberOfColors() const
{
    if ( m_colorPalettes.find(m_currentPaletteName) == m_colorPalettes.end() ) {
        // not found
        return 0;
    }
    
    const ColorPalette& palette = m_colorPalettes.at(m_currentPaletteName);
    return palette.size();
}

int ColorManager::getIndex(const string& colorPaletteName)
{
    for(int i = 0; i< m_paletteNames.size(); i++){
        if(m_paletteNames[i] == colorPaletteName){
            return i;
        }
    }
    
    return -1;
}

ofColor ColorManager::getRandomColor()
{
    int randomNum = (int) ofRandom(0,m_colorIndexList.size());
    int index =  m_colorIndexList[randomNum];
    m_colorIndexList.erase(m_colorIndexList.begin() + randomNum);
    auto color = this->getColor(index);
    
    if(m_colorIndexList.empty()){
        this->initializeColorIndexList();
    }
    
    return ofColor(color->r,color->g,color->b);
}

void ColorManager::initializeColorIndexList()
{
    m_colorIndexList.clear();
    
    int numColors =this->getNumberOfColors();
    for(int i=0; i< numColors; i++){
        m_colorIndexList.push_back(i);
    }
}



