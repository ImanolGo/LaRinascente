/*
 *  ExplosionVisual.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 24/11/17.
 *
 */

#include "ExplosionVisual.h"

#include "AppManager.h"



ExplosionParticle::ExplosionParticle(const ofPoint& pos, float time): BasicVisual(pos,0,0), m_lifeTime(time), m_live(true), m_time(0), m_initSize(0.0)
{
    this->setup();
}


ExplosionParticle::~ExplosionParticle()
{
    //Intentionaly left empty
}


void ExplosionParticle::setup()
{
    float size = AppManager::getInstance().getSettingsManager().getAppWidth();
    
    m_time = 0;
   // m_initSize = 0 + ofNoise( ofGetElapsedTimef()/4)*20;
    m_initSize = 0 ;
    //m_lifeTime = 1 + ofNoise( ofGetElapsedTimef()/2)*2;
    m_lifeTime = m_lifeTime + ofRandom(-m_lifeTime/4,m_lifeTime/4);
    
    m_size = size + ofNoise( ofGetElapsedTimef()/2)*size*0.5 ;
   // m_color = ofColor::white;
    m_color = AppManager::getInstance().getColorManager().getRandomColor();
    
    m_image.setResource("EXPLOSION");
    m_image.setCentred(true);
}


void ExplosionParticle::update()
{
    double dt = ofGetLastFrameTime();
    
    m_time += ofGetLastFrameTime();
    
    m_width = ofMap(m_time, 0, m_lifeTime, m_initSize, m_size);
    float brightness = ofMap(m_time, 0, m_lifeTime, 200, 0, true);
    m_color.setBrightness(brightness);
    //m_color.a = brightness;
    
    //m_color.a = 50;
    
    m_image.setColor(m_color);
    m_image.setWidth(m_width,true);
    m_image.setPosition(m_position);
    if(m_time>=m_lifeTime){
        m_live = false;
    }
    
}

void ExplosionParticle::draw()
{
    //ofPushStyle();
    //ofEnableAlphaBlending();
    //ofSetColor(m_color);
    //ofCircle(m_position, m_width);
    m_image.draw();
    //ofDisableAlphaBlending();
    //ofPopStyle();
}



ExplosionVisual::ExplosionVisual(): m_elapsedTime(10000), m_newParticleTime(0.2), m_frequency(0.6), m_amplitude(1.0), m_speed(0.5)
{
    
}


ExplosionVisual::~ExplosionVisual()
{
    //Intentionaly left empty
}


void ExplosionVisual::setup(int width, int height)
{
    
    this->setupFbos(width, height);
    this->setupShaders();
}



void ExplosionVisual::setupFbos(int width, int height)
{
    m_fbo.allocate(width, height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
}

void ExplosionVisual::setupShaders()
{
    
    if(ofIsGLProgrammableRenderer()){
        m_shader.load("shaders/shadersGL3/LiquifyShader");
    }
    else{
        m_shader.load("shaders/shadersGL2/LiquifyShader");
        
    }
    
    m_frequency = 0.4;
    m_amplitude = 0.4;
    m_speed = 0.5;
}

void ExplosionVisual::update()
{
    this->updateParticles();
}


void ExplosionVisual::updateParticles()
{
//    auto hands = AppManager::getInstance().getHandsManager().getHands();
//    
//    for (auto hand : hands) {
//        ofPoint pos = hand;
//        pos.x *= m_fbo.getWidth();
//        pos.y *= m_fbo.getHeight();
//        this->addParticle(pos);
//    }
    
    for(ParticlesVector::iterator it = m_particles.begin(); it != m_particles.end();)
    {
        (*it)->update();
        
        if(!(*it)->isAlive()){
            it = m_particles.erase(it);
        }
        else{
            ++it;
        }
    }
    
    
}


void ExplosionVisual::draw()
{
    this->drawParticles();
    //this->drawWaterRipples();
}


void ExplosionVisual::drawParticles()
{
    
    //ofPushStyle();
    
    m_fbo.begin();
    
    //ofEnableAlphaBlending();
    ofClear(0,0,0);
    //ofRect(0,0,m_fbo.getWidth(),m_fbo.getHeight());
    //ofSetColor(255,255,255);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (auto particle: m_particles) {
        particle->draw();
    }
    
    //ofDisableAlphaBlending();
    // ofDisableBlendMode();
    m_fbo.end();
    
    // ofPopStyle();
    
    //Drawing to screen through the shader
    m_shader.begin();		//Enable the shader
    
    m_shader.setUniform1f("time", ofGetElapsedTimef());
   // m_shader.setUniformTexture("tex", m_fbo.getTextureReference(), 0);
    m_shader.setUniform1f("frequency", m_frequency);
    m_shader.setUniform1f("amplitude", m_amplitude);
    m_shader.setUniform1f("speed", m_speed);
    

   // float time = ofGetElapsedTimef();
    //m_shader.setUniform1f( "time", time );	//Passing float parameter "time" to shader
    //m_shader.setUniform1f( "amplitude", 0.21 );	//Passing float parameter "amplitude" to shader
    
    //Draw fbo image
    ofSetColor( 255, 255, 255 );
    m_fbo.draw( 0, 0 );
    
    m_shader.end();		//Disable the shader
    
}


void ExplosionVisual::addParticle(const ofPoint &pos, float time)
{
    m_elapsedTime += ofGetLastFrameTime();
    
    if (m_elapsedTime >= m_newParticleTime) {
        m_elapsedTime = 0.0;
        auto particle = ofPtr<ExplosionParticle> (new ExplosionParticle(pos,time));
        m_particles.push_back(particle);
    }
   
}

void ExplosionVisual::clear()
{
    m_particles.clear();
}
