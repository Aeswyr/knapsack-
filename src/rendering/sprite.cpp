#include "knapsack/sprite.h"
#include "knapsack/text.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

#include <knapsack/internal/import.h>
#include <knapsack/internal/resource.h>

#include "knapsack/globals.h"
#include "knapsack/log.h"

static unsigned long long RenderTime;
static std::unordered_map<std::string, Texture*>  spriteMap;

Texture* getTexture(std::string name) {
	if (spriteMap.find(name) == spriteMap.end()) {
        out::log << out::err << name << " is not present in the sprite map" << out::endl;
        exit(1);
    }
	Texture* ptr = spriteMap[name];
	return ptr;
}

void imp::importSprite(std::string path) {
	/*
	imp::SpriteData data = imp::parseSprite(path);
	Texture* texture = new Texture(data.path);
	

	std::string name = data.name;

	SDL_Surface* surface = IMG_Load(data.path.c_str());
	if (surface == NULL) {
		flog::out << flog::err << "\tfailed to generate surface for image at " << data.path << "\n" << SDL_GetError() << flog::endl;
		return;
	}

	texture->sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (texture->sheet == NULL) {
		flog::out << flog::err << "\tfailed to generate texture for image at " << data.path << "\n" << SDL_GetError() << flog::endl;
		return;
	}
	SDL_FreeSurface(surface);

	texture->frames = data.frames;
	SDL_QueryTexture(texture->sheet, NULL, NULL, &(texture->w), &(texture->h));
	texture->w /= texture->frames;

	texture->clips = new SDL_Rect*[texture->frames];
	for (int i = 0; i < texture->frames; i++) {
		texture->clips[i] = new SDL_Rect{texture->w * i, 0, texture->w, texture->h};
	}

	SDL_DestroyTexture(texture->sheet);
	texture->sheet = nullptr;

	
	spriteMap[name] = texture;

	flog::out << "\tmapping texture at " << name << flog::endl;
	*/
}

Sprite::Sprite(std::string name) : texture(getTexture(name)), frame{0}, anim_time{ENGINE_TICK} {}

void  Sprite::render(Vector3 pos, float scalex, float scaley) {
	render(pos, 0, 0, texture->w, texture->h, scalex, scaley);
}

void  Sprite::render(Alignment* align, float scalex, float scaley) {
	render(align, 0, 0, scalex, scaley);
}

void  Sprite::render(Alignment* align, int xoff, int yoff, float scalex, float scaley) {
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture->frames;
		anim_time = RenderTime;
	}

	texture->ping();
}

void  Sprite::renderOnce(Alignment* align, int xoff, int yoff, float scalex, float scaley) {

	if (frame == texture->frames)
		return;

	if (RenderTime - anim_time >= animDelta) {
		frame++;
		if (frame == texture->frames)
			return;
		frame %= texture->frames;
		anim_time = RenderTime;
	}

	texture->ping();
}

void Sprite::render(Vector3 pos, int x0, int y0, int w, int h, float scalex, float scaley) {
	if (RenderTime - anim_time >= animDelta) {
		frame++;
		frame %= texture->frames;
		anim_time = RenderTime;
	}
	
	texture->ping();
}


void spr::update() {
	RenderTime = ENGINE_TICK;
}

void spr::clean() {
	for (auto iterator = spriteMap.begin(); iterator != spriteMap.end(); iterator++) {
		iterator->second->update();
	}
}


void Texture::lazyload() {
	/*
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		flog::out << flog::err << "error loading surface for sprite at " << path << flog::endl;
		return;
	}

	sheet = SDL_CreateTextureFromSurface(getRenderer(), surface);
	if (sheet == NULL) {
		flog::out << flog::err << "error generating texture for sprite at " << path << flog::endl;
		return;
	}
	SDL_FreeSurface(surface);
	flog::out << "lazyloaded sprite at " << path << flog::endl;
	*/
}

void Texture::update() {
	if(loaded) {
		loaded--;
		if (!loaded)
			unload();
	}
}

void Texture::unload() {

	out::log << "unloaded sprite at " << path << out::endl;
}

void Texture::ping() {
	if (!loaded) {
		lazyload();
	}
	loaded = 30;
}

Text::Text(std::string text, int size, Vector4 color) {
	update(text);
	update(size);
	update(color);
}

void Text::update(std::string text) {
	this->text = text;
	u_flag = true;
}

void Text::update(int size) {
	this->size = size;
	u_flag = true;
}

void Text::update(Vector4 color) {
	this->color = color;
	u_flag = true;
}

void Text::refresh() {
	if (u_flag)  {

		/*
		if (texture != nullptr)
			SDL_DestroyTexture(texture);
		u_flag = false;
		TTF_Font* font = TTF_OpenFont("./res/IndieFantasy.ttf", size);
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);

		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
		*/
	}
}

void Text::render(Vector3 pos, float scalex, float scaley){
	refresh();
	if (pos.x > GAME_WIDTH || pos.x + w < 0
		|| pos.y > GAME_HEIGHT || pos.y + h < 0)
		return;
}
void Text::render(Alignment* align, float scalex, float scaley){
	render(align, 0, 0);
}
void Text::render(Alignment* align, int xoff, int yoff, float scalex, float scaley) {
	refresh();
	if (align->pos.x - w/2 - xoff > GAME_WIDTH || align->pos.x - w/2 - xoff + w < 0
		|| align->pos.y - h/2 - yoff > GAME_HEIGHT || align->pos.y - h/2 - yoff + h < 0)
		return;

}

Text::~Text() {
	
}

void spr::flush() {

}

void spr::push() {

}

void spr::init() { 
	
}

Renderable::~Renderable() {

}

void render::drawRect(Vector3 pos, int w, int h, Vector4 color) {
	if (pos.x > GAME_WIDTH || pos.x + w < 0
		|| pos.y > GAME_HEIGHT || pos.y + h < 0)
		return;

}

void render::fillRect(Vector3 pos, int w, int h, Vector4 color) {
	if (pos.x > GAME_WIDTH || pos.x + w < 0
		|| pos.y > GAME_HEIGHT || pos.y + h < 0)
		return;

}

void render::outlineRect(Vector3 pos, int w, int h, Vector4 color1, Vector4 color2) {
	if (pos.x > GAME_WIDTH || pos.x + w < 0
		|| pos.y > GAME_HEIGHT || pos.y + h < 0)
		return;

}

void Sprite::setFrame(int f) {
	frame = f % texture->frames;
}

