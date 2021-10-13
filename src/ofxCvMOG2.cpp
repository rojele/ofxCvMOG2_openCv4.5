//
//  ofxCvMOG2.h
//
//  Created by enrico<naus3a>viola on 2/23/17.
//  updated by rojele on 11/10/21
//

#include "ofxCvMOG2.h"

ofxCvMOG2::ofxCvMOG2(){
    bShadow = true;
    bSMask = true;
    bSLMask = true;
    nMixtures = 3;
    ofxCvMOG2::mog2 = cv::createBackgroundSubtractorMOG2(500,16,true);//int     history = 500,double  varThreshold = 16,bool    detectShadows = true

    updateParams();

}

void ofxCvMOG2::enableShadowDetection(bool b){
    bShadow = b;
    if(bShadow){
        // CV_WRAP virtual void setDetectShadows(bool detectShadows) = 0;
        // cv::Ptr<cv::BackgroundSubtractor> mog2;

        mog2->setDetectShadows(true);
        //mog2->set("detectShadows",1);
    }else{
        bSMask = false;
        bSLMask= false;
    }

}

void ofxCvMOG2::setNumMixtures(int n){
    nMixtures = n;
    //mog2->set("nmixtures", nMixtures);
    mog2->setNMixtures(nMixtures);
}

void ofxCvMOG2::updateParams(){
    mog2->setNMixtures(nMixtures);
    if (bShadow)mog2->setDetectShadows(true);
    mog2->setVarThreshold(threshold);
}

void ofxCvMOG2::updateThreshold() {
    mog2->setVarThreshold(threshold);
}
void ofxCvMOG2::reset(){
    destroyMog2();
    mog2 = cv::createBackgroundSubtractorMOG2(500, 16, true);
    updateParams();
}

void ofxCvMOG2::update(cv::Mat frame){
    mog2->apply(frame, fgMask);
    if(bShadow){
        if(bSLMask){
            ofxCv::threshold(fgMask, shadowLessMask, threshold);
        }
        if(bSMask){
            cv::inRange(fgMask, cv::Scalar(1),cv::Scalar(250),shadowMask);
        }
    }
}