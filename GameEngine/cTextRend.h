#pragma once
#include <string>
#include <map>
#include <vector>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H


enum eLanguage
{
	ENGLISH,
	JAPANESE,
	UKRAINAN,
	SPANISH,
	POLSKA,
};

enum eMenu
{
	MAIN,
	CONTROLS,
	SETTINGS,
	LANGUAGE,
	WIND_SIZE,
	ENEMY,
	ABOUT,
	CLOSE
};

class cTextRend {

public:
	cTextRend();
	bool init();
	GLboolean init_gl();
	GLboolean initfreetype();
	void RenderMenu(std::string filename, int &width, int &height);
	void renderText(const wchar_t *text, float x, float y, float sx, float sy);
	void drawText(unsigned int width, unsigned int height, const wchar_t *text, GLfloat yoffset);

	eMenu getState();
	void setState(eMenu menu);
	void setLang(eLanguage lang);


private:



	float mTimeWaitedSoFar;
	bool mStart;

	float mWidth;
	float mHeight;

	//Localization related
	eMenu mState;
	eLanguage mLang;


	GLuint mvertex_shader;                           
	GLuint mfragment_shader;                         
	GLuint mprogramm;                                
	GLuint mvao;                                     
	GLuint mdp_vbo;                                  
	GLint attribute_coord;                           
	GLint uniform_tex;                               
	GLint uniform_color;                             
	const char* mvs_text;                            
	const char* mfs_text;                            
	FT_Library mft;                                  
	FT_Face mface;                                      

	struct point
	{
		GLfloat x;
		GLfloat y;
		GLfloat s;
		GLfloat t;
	};
};