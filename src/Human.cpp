#include <Human.h>

Human::Human(double x, double y, sf::Texture *texture) : GameObject(x, y) {
	//texture.loadFromFile("human.png");
	sprite.setTexture(*texture);
	sf::IntRect textureRect;
	textureRect.top = 0;
	textureRect.left = 0;
	textureRect.width = 15;
	textureRect.height = 40;
	sprite.setTextureRect(textureRect);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	//sprite.setOrigin(10, 20);

	questSprite.setTexture(*texture);
	textureRect.top = 41;
	questSprite.setTextureRect(textureRect);
	questSprite.setOrigin(questSprite.getLocalBounds().width / 2, questSprite.getLocalBounds().height / 2);

	hoverboard.setTexture(*texture);
	textureRect.left = 16;
	hoverboard.setTextureRect(textureRect);
	hoverboard.setOrigin(hoverboard.getLocalBounds().width / 2, hoverboard.getLocalBounds().height / 2);

	mass = 0.01;
	velocity.x = velocity.y = 0;
	direction.x = direction.y = 0;
	force = 0;
	angle = 0;

	dir = 1;

	jump = false;

	state = 0;
	nextStateChange = 0;

	closestSpecial = -1;
	closestLocal = -1;

	sprite.setColor(sf::Color(Functions::randomInt(0, 255), Functions::randomInt(0, 255), Functions::randomInt(0, 255)));

	speed = 1;

	hasQuest = false;
	hasReturn = false;
	quest = std::unique_ptr<Quest>(new Quest(0, 0, 0, 0, 0));

	returnQuest = 0;

	buffer.loadFromFile("Source/resources/Audio/footstep.ogg");
	sound.setBuffer(buffer);
	sound.setPitch(2);
	sound.setVolume(25);

	onHoverboard = false;
	heightFromPlanet = 0;
	hoverDir = 1;
}

sf::Vector2<double> Human::getVelocity() {
	return velocity;
}

sf::Vector2<double> Human::getDirection() {
	return direction;
}

float Human::getMass() {
	return mass;
}

float Human::getForce() {
	return force;
}

int Human::getDir() {
	return dir;
}

void Human::addVelocity(double x, double y) {
	velocity.x += x;
	velocity.y += y;
}

void Human::setDirection(double x, double y) {
	direction.x = x;
	direction.y = y;
}

void Human::setForce(float f) {
	force = f;
}

void Human::resetVelocity() {
	velocity.x = velocity.y = 0;
}

void Human::setAngle(float a) {
	angle = a;
}

void Human::setDir(int d) {
	sf::IntRect tR = sprite.getTextureRect();
	if (dir == d) {
		if (clock.getElapsedTime().asSeconds() > 0.1 * speed && !onHoverboard) {
			tR.left = tR.left + 16;
			if (tR.left >= sprite.getTexture()->getSize().x)
				tR.left = 16;
			clock.restart();
		}
	} else {
		dir = d;
		tR.left = 0;
	}
	sprite.setTextureRect(tR);
}

void Human::setDirJump(int d) {
	dir = d;
	sf::IntRect tR = sprite.getTextureRect();
	tR.left = 16;
	sprite.setTextureRect(tR);
}

void Human::resetSprite() {
	if (clock.getElapsedTime().asSeconds() >= 0.05) {
		sf::IntRect tR = sprite.getTextureRect();
		tR.left = 0;
		sprite.setTextureRect(tR);
	}
}

void Human::setState(int s) {
	state = s;
}

int Human::getState() {
	return state;
}

void Human::setNextStateChange(int nSC) {
	nextStateChange = nSC;
}

int Human::getNextStateChange() {
	return nextStateChange;
}

void Human::setJump(bool j) {
	jump = j;
}

bool Human::getJump() {
	return jump;
}

void Human::setClosestSpecial(int cS) {
	closestSpecial = cS;
}

int Human::getClosestSpecial() {
	return closestSpecial;
}

void Human::setColour(sf::Color colour) {
	sprite.setColor(colour);
}

void Human::setSpeed(float speed) {
	this->speed = speed;
}

void Human::setQuest(int type, int item, int noItems, int destination, int reward) {
	hasQuest = true;
	quest->setType(type);
	quest->setItem(item);
	quest->setDestination(destination);
	quest->setReward(reward);
	quest->setNoItems(noItems);
}

bool Human::getHasQuest() {
	return hasQuest;
}

void Human::setHasQuest(bool hQ) {
	hasQuest = hQ;
}

std::unique_ptr<Quest> Human::getQuest() {
	std::unique_ptr<Quest> rQuest(new Quest(quest->getType(), quest->getItem(), quest->getNoItems(), quest->getDestination(), quest->getReward()));
	return rQuest;
}

float Human::getWidth() {
	return sprite.getGlobalBounds().width;
}

float Human::getHeight() {
	return sprite.getGlobalBounds().height;
}

int Human::getClosestLocal() {
	return closestLocal;
}

void Human::setClosestLocal(int l) {
	closestLocal = l;
}

bool Human::getHasReturn() {
	return hasReturn;
}

void Human::setHasReturn(bool hR) {
	hasReturn = hR;
}

int Human::getReturnQuest() {
	return returnQuest;
}

void Human::setReturnQuest(int rQ) {
	hasReturn = true;
	returnQuest = rQ;
}

void Human::playSound() {
	if (sound.getStatus() != sf::Sound::Playing && !onHoverboard) {
		sound.play();
	}
}

void Human::setOnHoverboard(bool b) {
	onHoverboard = b;
}

bool Human::getOnHoverboard() {
	return onHoverboard;
}

void Human::update() {
	// Apply Force
	float acceleration = getForce() / getMass();
	sf::Vector2<double> direction = getDirection();
	addVelocity(direction.x * acceleration, direction.y * acceleration);
	sf::Vector2<double> velocity = getVelocity();
	setOldX(getX());
	setOldY(getY());
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);

	if (hasQuest) {
		questSprite.setColor(sf::Color::Green);
	}
	if (hasReturn) {
		questSprite.setColor(sf::Color::Cyan);
	}

	if (speed == 1)
		sound.setPitch(2);
	else
		sound.setPitch(3);
}

void Human::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	// Hovering Animation
	if (!onHoverboard) {
		heightFromPlanet = 0;
	} else {
		if (heightFromPlanet < 0.5) {
			hoverDir = 1;
		}
		if (heightFromPlanet > 1) {
			hoverDir = -1;
		}
		heightFromPlanet += hoverDir * 0.01;
	}

	float xHeight = sin(angle * PI / 180) * heightFromPlanet;
	float yHeight = -cos(angle * PI / 180) * heightFromPlanet;

	sprite.setRotation(angle);
	if (onHoverboard && jump) {
		sprite.setRotation(angle + -dir * 15);
	}
	sprite.setScale((double)0.07 * dir / ppm, (double)0.07 / ppm);
	sprite.setPosition((double)(((double)screen.width / 2) + (getX() + xHeight - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() + yHeight - view.y) / (double)ppm - 20));
	window.draw(sprite);

	if (onHoverboard) {
		xHeight = sin(sprite.getRotation() * PI / 180 - dir * 0.2) * (heightFromPlanet - 20 * 0.07);
		yHeight = -cos(sprite.getRotation() * PI / 180 - dir * 0.2) * (heightFromPlanet - 20 * 0.07);

		hoverboard.setRotation(sprite.getRotation() - dir * 0.2);
		hoverboard.setScale(sprite.getScale());
		hoverboard.setPosition((double)(((double)screen.width / 2) + (getX() + xHeight - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() + yHeight - view.y) / (double)ppm - 20));
		window.draw(hoverboard);
	}

	if (hasQuest || hasReturn) {
		questSprite.setRotation(sprite.getRotation());
		questSprite.setScale(sprite.getScale().y, sprite.getScale().y);
		float questAngle = sprite.getRotation() * PI / 180;
		questSprite.setPosition(sprite.getPosition().x + sin(questAngle) * 40 * sprite.getScale().y, sprite.getPosition().y - cos(questAngle) * 40 * sprite.getScale().y);
		window.draw(questSprite);
	}
}