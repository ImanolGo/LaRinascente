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


StarsManager::StarsManager(): Manager(), m_starsSize(20.0), m_currentStarInde(0), m_explosionInterval(0), m_explosionTime(2.0)
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
            ofPoint starPosition;
            
            if(parseStarLine(line,starPosition))
            {
                createStar(starPosition);
            }
            
        }
    }
    
}


void StarsManager::saveStarsPositions()
{
     string star_position_path = STARS_LIST_PATH + "StarsPositions.txt";
     ofFile starPosFile(star_position_path, ofFile::WriteOnly, true);
    
    for(auto star: m_stars)
    {
        ofPoint pos = star->getPosition();
        starPosFile << "{" << pos.x << ", " << pos.y << ", 0.0}" <<std::endl;
    }
    
    starPosFile.close();
    
    ofLogNotice() <<"StarsManager::saveStarsPositions -> saved Star positions to file " <<  star_position_path;
    
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
    auto fbo = AppManager::getInstance().getNoiseManager().getFbo();
    ofPixels pix;
    fbo.readToPixels(pix);
    
    this->setPixels(pix);
}

void StarsManager::setPixels(ofPixels& pixels)
{
    this->setStarColors(pixels);
    
}

void StarsManager::setStarColors(ofPixels& pixels)
{
    for(auto star: m_stars){
        star->setPixelColor(pixels);
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
    for(auto star: m_stars)
    {
        star->draw(width,height);
    }
}

void StarsManager::onSetStarsSize(float &value)
{
    m_starsSize = value;
    
    for(auto star: m_stars){
        star->setWidth(m_starsSize);
    }
}

void StarsManager::onSetExplosionsInterval(float &value)
{
    m_explosionInterval = value;
}

void StarsManager::onSetExplosionsTime(float &value)
{
    m_explosionTime = value;
}

void StarsManager::showChannels(bool _showChannels)
{
    for(auto star: m_stars)
    {
        star->showId(_showChannels);
    }
}

void StarsManager::onSetStarPosition(int& value)
{
    if(value<0 || value >= m_stars.size()){
        return;
    }
    
    m_currentStarInde = value;
}


void StarsManager::increaseCurrentX()
{
    if(m_currentStarInde<0 || m_currentStarInde >= m_stars.size()){
        return;
    }
    
    auto currentStar = m_stars[m_currentStarInde];
    auto position = currentStar->getPosition();
    position.x+=0.001;
    currentStar->setPosition(position);
}

void StarsManager::increaseCurrentY()
{
    if(m_currentStarInde<0 || m_currentStarInde >= m_stars.size()){
        return;
    }
    
    auto currentStar = m_stars[m_currentStarInde];
    auto position = currentStar->getPosition();
    position.y+=0.001;
    currentStar->setPosition(position);
}

void StarsManager::decreaseCurrentX()
{
    if(m_currentStarInde<0 || m_currentStarInde >= m_stars.size()){
        return;
    }
    
    auto currentStar = m_stars[m_currentStarInde];
    auto position = currentStar->getPosition();
    position.x-=0.001;
    currentStar->setPosition(position);
    
}

void StarsManager::decreaseCurrentY()
{
    if(m_currentStarInde<0 || m_currentStarInde >= m_stars.size()){
        return;
    }
    
    auto currentStar = m_stars[m_currentStarInde];
    auto position = currentStar->getPosition();
    position.y-=0.001;
    currentStar->setPosition(position);
}







