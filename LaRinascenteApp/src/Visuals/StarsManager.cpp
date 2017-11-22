/*
 *  StarsManager.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */


#include "ofMain.h"

#include "StarsManager.h"
#include "AppManager.h"

const string StarsManager::STARS_LIST_PATH = "stars/";


StarsManager::StarsManager(): Manager(), m_starsSize(20.0)
{
	//Intentionally left empty
}


StarsManager::~StarsManager()
{
    this->saveStarsPositions();
    ofLogNotice() <<"StarsManager::Destructor" ;
}


void StarsManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupStars();
    
    ofLogNotice() <<"StarsManager::initialized" ;
    
}

void StarsManager::setupStars()
{
    this->readStarsPositions();
}


void StarsManager::addStar(const ofPoint& position)
{    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    ofRectangle windowRect(0,0,width,height);
    createStar(position);
//
//    if (!m_stars.empty()) {
//        m_stars.back()->normalize(windowRect);
//    }
    
    ofLogNotice() <<"StarsManager::addStar-> id = " <<  m_stars.back()->getId();
}

void StarsManager::deleteLastStar()
{
    if(!m_stars.empty()){
        int id = m_stars.back()->getId();
        m_stars.pop_back();

        ofLogNotice() <<"StarsManager::deleteLastStar-> id = " << id;
    }
}

void StarsManager::readStarsPositions()
{
    
    string star_position_path = STARS_LIST_PATH + "StarsPositions.txt";
    ofBuffer buffer = ofBufferFromFile(star_position_path);
    
    
    if(buffer.size())
    {
        for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it)
        {
            string line = *it;
            ofPoint StarPosition;
            
            if(parseStarLine(line,StarPosition))
            {
                createStar(StarPosition);
            }
            
        }
    }
    
}


void StarsManager::saveStarsPositions()
{
     string Star_position_path = STARS_LIST_PATH + "StarsPositions.txt";
     ofFile StarPosFile(Star_position_path, ofFile::WriteOnly, true);
    
    for(auto Star: m_stars)
    {
        ofPoint pos =Star->getPosition();
        StarPosFile << "{" << pos.x << ", " << pos.y << ", 0.0}" <<std::endl;
    }
    
    StarPosFile.close();
    
    ofLogNotice() <<"StarsManager::saveStarsPositions -> saved Star positions to file " <<  Star_position_path;
    
}


void StarsManager::createStar(const ofPoint& position)
{
    auto star = ofPtr<Star> (new Star ( position, m_stars.size() + 1) );
    star->setColor(ofColor::black);
    star->setWidth(m_starsSize);
    m_stars.push_back(star);

    
    ofLogNotice() <<"StarsManager::createStar -> id " << star->getId() << ", x = "  << star->getPosition().x << ", y = "  << star->getPosition().y;
}

bool StarsManager::parseStarLine(string& line, ofPoint& position)
{
    if(line.size() == 0){
        return false;
    }

    char chars[] = "{}";
    removeCharsFromString(line, chars);
    vector <string> strings = ofSplitString(line, ", " );
    
    position.x = ofToFloat(strings[0]);
    position.y = ofToFloat(strings[1]);
    position.z = ofToFloat(strings[2]);
    
    return true;
}

void StarsManager::removeCharsFromString( string &str, char* charsToRemove ) {
    for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
        str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
    }
}

void StarsManager::update()
{
    //
}

void StarsManager::setPixels(ofPixelsRef pixels)
{
    this->setStarColors(pixels);
    
}

void StarsManager::setStarColors(ofPixelsRef pixels)
{
    for(auto Star: m_stars){
        Star->setPixelColor(pixels);
    }
}


void StarsManager::draw()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    this->drawStars(width, height);
}

void StarsManager::draw(int width, int height)
{
    this->drawStars(width, height);
}

void StarsManager::drawStars(int width, int height)
{
    for(auto Star: m_stars)
    {
        Star->draw(width,height);
    }
}

void StarsManager::onSetStarsSize(float &value)
{
    m_starsSize = value;
    
    for(auto Star: m_stars){
        Star->setWidth(m_starsSize);
    }
}

void StarsManager::showChannels(bool _showChannels)
{
    for(auto Star: m_stars)
    {
        Star->showId(_showChannels);
    }
}









