#include "Constructions.h"
#include "Soldiers.h"

int Mine::money = 1000;
int Barracks::money = 2000;
int Warfactory::money = 3000;
int Base::money = 5000;

int Mine::delay = 10;
int Barracks::delay = 15;
int Warfactory::delay = 15;
int Base::delay = 100;

int Mine::max_hp = 1000;
int Barracks::max_hp = 1000;
int Warfactory::max_hp = 1200;
int Base::max_hp = 2000;

Barracks* Barracks::create(const string filename)
{
	Barracks* sprite = new Barracks();
	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->createdog = Sprite::create("dog.png");
		sprite->createsoldier = Sprite::create("soldier.png");
		sprite->createengineer = Sprite::create("engineer.png");
		sprite->init("Barracks", 1000, 4, Vec2(300, 300), false, false, 1, 100);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Menu* Barracks::createMenu()
{
	auto dogItem = MenuItemSprite::create(createdog, createdog, CC_CALLBACK_1(Barracks::CreateDogCallback, this));
	auto soldierItem = MenuItemSprite::create(createsoldier, createsoldier, CC_CALLBACK_1(Barracks::CreateSoldierCallback, this));
	auto engineerItem = MenuItemSprite::create(createengineer, createengineer, CC_CALLBACK_1(Barracks::CreateEngineerCallback, this));
	auto menu = Menu::create(dogItem, soldierItem, engineerItem, NULL);
	menu->setPosition(Vec2(100, 100));
	return menu;
}

Sprite* Barracks::getdog()
{
	return createdog;
}

Sprite* Barracks::getsolder()
{
	return createsoldier;
}

Sprite* Barracks::getengineer()
{
	return createengineer;
}

void Barracks::CreateDogCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Dog::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateDog(); }, nullptr);
	this->runAction(seq);
}

void Barracks::CreateSoldierCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Soldier::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateDog(); }, nullptr);
	this->runAction(seq);
}

void Barracks::CreateEngineerCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Engineer::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateDog(); }, nullptr);
	this->runAction(seq);
}

void Barracks::CreateDog()
{
	string filename = "dog.png";
	Dog* dog = Dog::create(filename);
	dog->init(100, false, false, Vec2(300, 300), Vec2(0, 0));
	dog->setPosition(Vec2(100,100));
	auto target = Director::getInstance()->getRunningScene();
	auto layer = target->getChildByTag(1);
	layer->addChild(dog, 2);
}

void Barracks::CreateSoldier()
{
	string filename = "soldier.png";
	Soldier* soldier = Soldier::create(filename);
	soldier->init(200, false, false, Vec2(300, 300), Vec2(0, 0));
	soldier->setPosition(Vec2(0, 0));
	auto target = Director::getInstance()->getRunningScene();
	auto layer = target->getChildByTag(1);
	layer->addChild(soldier, 2);
}

void Barracks::CreateEngineer()
{
	string filename = "engineer.png";
	Engineer* engineer = Engineer::create(filename);
	engineer->init(200, false, false, Vec2(300, 300), Vec2(0, 0));
	engineer->setPosition(Vec2(0, 0));
	auto target = Director::getInstance()->getRunningScene();
	auto layer = target->getChildByTag(1);
	layer->addChild(engineer, 2);
}

Warfactory* Warfactory::create(const string filename)
{
	Warfactory* sprite = new Warfactory();
	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->createtank = Sprite::create("tank.png");
		sprite->init("Warfactory", 1800, 4, Vec2(400, 400), false, false, 1, 100);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Sprite* Warfactory::gettank()
{
	return createtank;
}

Mine* Mine::create(const string filename)
{
	Mine* sprite = new Mine();
	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->createminingcar = Sprite::create("miningcar.png");
		sprite->init("Mine", 1600, 4, Vec2(150, 150), false, false, 1, 100);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Menu* Mine::createMenu()
{
	auto miningcarItem = MenuItemSprite::create(createminingcar, createminingcar, CC_CALLBACK_1(Mine::CreateMiningcarCallback, this));
	auto menu = Menu::create(miningcarItem, NULL);
	menu->setPosition(Vec2(100, 100));
	return menu;
}

Sprite* Mine::getminingcar()
{
	return createminingcar;
}

Menu* Base::createMenu()
{
	auto barracksItem = MenuItemSprite::create(createbarracks, createbarracks, CC_CALLBACK_1(Base::CreateBarracksCallback, this));
	auto mineItem = MenuItemSprite::create(createmine, createmine, CC_CALLBACK_1(Base::CreateMineCallback, this));
	auto warfactoryItem = MenuItemSprite::create(createwarfactory, createwarfactory, CC_CALLBACK_1(Base::CreateWarfactoryCallback, this));
	auto menu = Menu::create(barracksItem, mineItem, warfactoryItem, NULL);
	menu->setPosition(Vec2(100, 100));
	return menu;
}

void Base::CreateMineCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Mine::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateMine(); }, nullptr);
	this->runAction(seq);
}

void Base::CreateWarfactoryCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Warfactory::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateWarfactory(); }, nullptr);
	this->runAction(seq);
}

void Base::CreateBarracksCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Barracks::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateBarracks(); }, nullptr);
	this->runAction(seq);
}

void Base::CreateMine()
{
	string filename = "Mine.png";
	Mine* mine = Mine::create(filename);
	mine->init("Mine", 1600, 4, Vec2(150, 150), false, false, 1, 100);
	mine->setPosition(Vec2(100, 100));
	auto target = Director::getInstance()->getRunningScene();
	auto layer = target->getChildByTag(1);
	layer->addChild(mine, 2);
}

void Base::CreateBarracks()
{
	string filename = "Barracks.png";
	Barracks* barracks = Barracks::create(filename);
	barracks->init("Barracks", 1600, 4, Vec2(150, 150), false, false, 1, 100);
	barracks->setPosition(Vec2(100, 100));
	auto target = Director::getInstance()->getRunningScene();
	auto layer = target->getChildByTag(1);
	layer->addChild(barracks, 2);
}

void Base::CreateWarfactory()
{
	string filename = "Warfactory.png";
	Warfactory* warfactory = Warfactory::create(filename);
	warfactory->init("Warfactory", 1600, 4, Vec2(150, 150), false, false, 1, 100);
	warfactory->setPosition(Vec2(100, 200));
	auto target = Director::getInstance()->getRunningScene();
	auto layer = target->getChildByTag(1);
	layer->addChild(warfactory, 2);
}

Base* Base::create(const string filename)
{
	Base* sprite = new Base();
	if (sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->createbarracks = Sprite::create("Barracks.png");
		sprite->createwarfactory = Sprite::create("Warfactory.png");
		sprite->createmine = Sprite::create("Mine.png");
		sprite->init("Base", 5000, 8, Vec2(100, 100), false, false, 1, 100);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

Sprite* Base::getbarracks()
{
	return createbarracks;
}

Sprite* Base::getwarfactory()
{
	return createwarfactory;
}

Sprite* Base::getmine()
{
	return createmine;
}

void Warfactory::CreateTank()
{
	string filename = "tank.png";
	Tank* tank = Tank::create(filename);
	tank->init(200, false, false, Vec2(300, 300), Vec2(0, 0));
	tank->setPosition(Vec2(0, 0));
	auto target = Director::getInstance()->getRunningScene();
	auto layer = target->getChildByTag(1);
	layer->addChild(tank, 2);
}

void Warfactory::CreateTankCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Tank::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateTank(); }, nullptr);
	this->runAction(seq);
}

void Mine::CreateMiningcar()
{
	string filename = "miningcar.png";
	Miningcar* miningcar = Miningcar::create(filename);
	miningcar->init(200, false, false, Vec2(300, 300), Vec2(0, 0));
	miningcar->setPosition(Vec2(0, 0));
	auto target = Director::getInstance()->getRunningScene();
	auto layer = target->getChildByTag(1);
	layer->addChild(miningcar, 2);
}

void Mine::CreateMiningcarCallback(Ref* pSender)
{
	auto delay = DelayTime::create(Miningcar::delay);
	auto seq = Sequence::create(delay, [&] {this->CreateMiningcar(); }, nullptr);
	this->runAction(seq);
}

void Barracks::createBar(Barracks * a)
{
	Sprite *hpSprite = Sprite::create("hp-con.png");
	auto hp = ProgressTimer::create(hpSprite);
	hp->setType(ProgressTimer::Type::BAR);
	hp->setMidpoint(Point(0, 0));
	hp->setBarChangeRate(Point(1, 0));
	hp->setPosition(Vec2(32, 100));
	hp->setPercentage((a->gethp() / Barracks::max_hp) * 100);
}

void Warfactory::createBar(Warfactory * a)
{
	Sprite *hpSprite = Sprite::create("hp-con.png");
	auto hp = ProgressTimer::create(hpSprite);
	hp->setType(ProgressTimer::Type::BAR);
	hp->setMidpoint(Point(0, 0));
	hp->setBarChangeRate(Point(1, 0));
	hp->setPosition(Vec2(32, 100));
	hp->setPercentage((a->gethp() / Warfactory::max_hp) * 100);
}

void Mine::createBar(Mine * a)
{
	Sprite *hpSprite = Sprite::create("hp-con.png");
	auto hp = ProgressTimer::create(hpSprite);
	hp->setType(ProgressTimer::Type::BAR);
	hp->setMidpoint(Point(0, 0));
	hp->setBarChangeRate(Point(1, 0));
	hp->setPosition(Vec2(32, 100));
	hp->setPercentage((a->gethp() / Mine::max_hp) * 100);
}

void Base::createBar(Base * a)
{
	Sprite *hpSprite = Sprite::create("hp-con.png");
	auto hp = ProgressTimer::create(hpSprite);
	hp->setType(ProgressTimer::Type::BAR);
	hp->setMidpoint(Point(0, 0));
	hp->setBarChangeRate(Point(1, 0));
	hp->setPosition(Vec2(32, 100));
	hp->setPercentage((a->gethp() / Base::max_hp) * 100);
}
