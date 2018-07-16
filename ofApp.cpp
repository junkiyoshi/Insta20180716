#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(39);
	ofNoFill();
	ofSetLineWidth(2.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int x_index = -1; x_index <= 1; x_index++) {

		for (int y_index = -1; y_index <= 1; y_index++) {

			ofPoint location(x_index * 230, y_index * 230);

			ofPushMatrix();
			ofTranslate(location);

			for (int rect_len = 30; rect_len < 200; rect_len += 16) {

				ofColor color;
				color.setHsb(ofRandom(255), 200, 255);
				ofSetColor(color);

				int start_noise = ofNoise(location.x * 0.1, rect_len * 0.05, ofGetFrameNum() * 0.005) * 360;
				int end_noise = ofMap(ofNoise(location.y * 0.1, rect_len * 0.05, ofGetFrameNum() * 0.01), 0, 1, -90, 360);
				int start_deg = ofRandom(360) + start_noise;
				int end_deg = start_deg + end_noise;

				if (start_deg > end_deg) { continue; }

				ofBeginShape();
				for (int deg = start_deg; deg < end_deg; deg += 1) {

					ofVertex(this->make_rect_point(rect_len, deg));
				}
				ofEndShape();
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
ofPoint ofApp::make_rect_point(float len, int deg, int z) {

	int half_len = len * 0.5;
	int param = (deg + 45) / 90;
	ofPoint point;

	switch (param % 4) {

	case 0:

		return ofPoint(half_len, ofMap((deg + 45) % 90, 0, 89, -half_len, half_len), z);
	case 1:

		return  ofPoint(ofMap((deg + 45) % 90, 0, 89, half_len, -half_len), half_len, z);
	case 2:

		return ofPoint(-half_len, ofMap((deg + 45) % 90, 0, 89, half_len, -half_len), z);
	case 3:

		return ofPoint(ofMap((deg + 45) % 90, 0, 89, -half_len, half_len), -half_len, z);
	default:

		return ofPoint(0, 0, 0);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}