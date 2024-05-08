#pragma once
#include "GameObject.h"
#include <SDL_ttf.h>

class Text : public GameObject
{
private:
	//Font used for the text
	TTF_Font* font{ nullptr };
	//Colour of the text
	SDL_Color color{ 0, 0, 0 };
public:
	Text(SDL_Renderer* _rend, const std::string& _fontPath, int _fontSize) : GameObject(_rend) {
		font = TTF_OpenFont(_fontPath.c_str(), _fontSize);
	};
	~Text();
	//Changes color of text. Use value -1 to keep previous value
	void ChangeColor(int _r, int _g, int _b);
	//Changes the text
	void ChangeText(const std::string& _text);

	void Update() {}
};