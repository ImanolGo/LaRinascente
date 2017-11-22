/*
 *  LaRinascenteApp.cpp
 *  LaRinascenteApp
 *
 *  Created by Imanol Gomez on 22/11/17.
 *
 */



#include "AppManager.h"

#include "LaRinascenteApp.h"

//--------------------------------------------------------------
void LaRinascenteApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void LaRinascenteApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void LaRinascenteApp::draw(){
    AppManager::getInstance().draw();
}

void LaRinascenteApp::exit()
{
    ofLogNotice() <<"LaRinascenteApp::exit";

}

//--------------------------------------------------------------
void LaRinascenteApp::keyPressed(int key){

}

//--------------------------------------------------------------
void LaRinascenteApp::keyReleased(int key){

}

//--------------------------------------------------------------
void LaRinascenteApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void LaRinascenteApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void LaRinascenteApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void LaRinascenteApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void LaRinascenteApp::windowResized(int w, int h){
    AppManager::getInstance().getLayoutManager().windowResized(w,h);


}

//--------------------------------------------------------------
void LaRinascenteApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void LaRinascenteApp::dragEvent(ofDragInfo dragInfo){

}
