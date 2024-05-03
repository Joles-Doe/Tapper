#pragma once
#include "GameObject.h"
#include <SDL_ttf.h>

class Text : public GameObject
{
private:
	TTF_Font* font{ nullptr };
	SDL_Color color{ 0, 0, 0 };
public:
	Text(SDL_Renderer* _rend, const std::string& _fontPath, int _fontSize) : GameObject(_rend) {
		font = TTF_OpenFont(_fontPath.c_str(), _fontSize);
	};
	//Changes color of text. Use value -1 to keep previous value
	void ChangeColor(int _r, int _g, int _b);

	void ChangeText(const std::string& _text);

	void Update() {}
	//void Draw();
};