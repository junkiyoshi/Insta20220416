#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int v_span = 8;
	int u_span = 30;
	int R = 200;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	int r = 50;
	float noise_seed = ofRandom(1000);
	for (int v = 0; v <= 360; v += v_span) {

		int u_start = ofMap(ofNoise(noise_seed, cos(v * DEG_TO_RAD) * 0.5, sin(v * DEG_TO_RAD) * 0.5, ofGetFrameNum() * 0.015), 0, 1, -360, 360);
		int next_u = ofMap(ofNoise(noise_seed, cos((v + v_span * 0.9) * DEG_TO_RAD) * 0.5, sin((v + v_span * 0.9) * DEG_TO_RAD) * 0.5, ofGetFrameNum() * 0.015), 0, 1, -360, 360);
		for (int u = u_start; u < u_start + 360; u += u_span) {

			face.addVertex(this->make_point(R, r, u, v));
			face.addVertex(this->make_point(R, r, u + u_span, v));
			face.addVertex(this->make_point(R, r, next_u + u_span, v + v_span * 0.8));
			face.addVertex(this->make_point(R, r, next_u, v + v_span * 0.8));

			line.addVertex(this->make_point(R, r, u, v));
			line.addVertex(this->make_point(R, r, u + u_span, v));
			line.addVertex(this->make_point(R, r, next_u + u_span, v + v_span * 0.8));
			line.addVertex(this->make_point(R, r, next_u, v + v_span * 0.8));

			ofColor face_color;
			face_color.setHsb((int)ofMap(u, u_start, u_start + 360, 0, 512) % 255, 140, 255);
			ofColor line_color = ofColor(255);

			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);

			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);

			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
			line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
			line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);

			next_u += u_span;

		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// ���w�f�b�T������ �`���Ċy���ސ��w�����@P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v) * 2;
	auto z = r * sin(u) * 2;

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}