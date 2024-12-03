#include "Player.h"
#include "CreateItem.h"


Item* currentItem = playerInventory.getItem(0, 3);
int currentItemRow = 0;
int currentItemColumn = 3;

Player::Player(
	Vec3 pos_, Vec3 vel_, Vec3 accel_,
	float mass_,
	float radius_ = 0.0f,
	float orientation_ = 0.0f,
	float rotation_ = 0.0f,
	float angular_ = 0.0f
)
{
	pos = pos_;
	vel = vel_;
	accel = accel_;
	mass = mass_;
	radius = radius_;
	orientation = orientation_;
	rotation = rotation_;
	angular = angular_;

	image = nullptr;
}


bool Player::OnCreate()
{


    textureFile = "textures/PlayerFacingFrontIdle.png";//Placeholder image
    SetTextureFile(textureFile);
    texture = loadImage(textureFile);
    // Image Surface used for animations
    setImage(IMG_Load(textureFile));

    //hitbox.Subscribe(onCollisionTrigger);

    playerInventory.addItem(sword);
    playerInventory.addItem(armor);
    playerInventory.addItem(shield);
    playerInventory.addItem(potion);
    playerInventory.addItem(shoes);
    playerInventory.printInventory();

    healthBar = new HealthBar(10.0f, 200.0f, { 0, 255, 150, 255 });

    panel.OnCreate(renderer, Vec2(1920 / 40, 830 / 2 + 100), "textures/itemFrame.png", panelScaling);
    if (currentItem != nullptr)
        panel.AddIcon(currentItem->filePath, panelScaling);
    else
        panel.AddIcon("textures/emptySlot.png", panelScaling);

    for (int i = 0; i < 5; i++)
    {
        if (playerInventory.getItem(0, i) != nullptr)
        {
            // display
            space[i].OnCreate(renderer, Vec2(1920 / 4.0f + 50 * i + 5 * i, 700 * 0.9), "textures/itemFrame.png", 0.5);
            space[i].AddIcon(playerInventory.getItem(0, i)->filePath, 0.5);
        }
        else
        {
            // display
            space[i].OnCreate(renderer, Vec2(1920 / 4.0f + 50 * i + 5 * i, 700 * 0.9), "textures/itemFrame.png", 0.5);
            space[i].AddIcon("textures/emptySlot.png", 0.5);
        }
    }


    return true;
}

void Player::setupCollision()
{
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
	hitbox.OnCreate(size.x, size.y, scale);
	hitbox.Subscribe(
		[this](const TileFaces& collidedObject) {
			onCollisionEnter(collidedObject);
		});
}

void Player::Render()
{   
    // Calls body entity render
    renderEntity(scale);
    
}

void Player::RenderUI() {
    healthBar->Render(renderer, Vec2(1050, 650), 20); // Position, height 20px

    panel.Render();

    for (int i = 0; i < 5; i++)
    {
        space[i].Render();
    }
}

void Player::HandleEvents(const SDL_Event& event)
{

	switch (event.type) {
	case SDL_KEYDOWN:
		//event.key.repeat == 0 prevents weirdness with normalizing the velocity later on
		if (event.key.repeat == 0) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_W:
				vel.y = walkSpeedMax;
				changeTexture("textures/PlayerFacingBackWalk.png");
				break;

			case SDL_SCANCODE_S:
				vel.y = -walkSpeedMax;
				changeTexture("textures/PlayerFacingFrontWalk.png");
				break;
			case SDL_SCANCODE_D:
				vel.x = walkSpeedMax;
				changeTexture("textures/PlayerFacingRightWalk.png");
				break;

			case SDL_SCANCODE_A:
				vel.x = -walkSpeedMax;
				changeTexture("textures/PlayerFacingLeftWalk.png");
				break;
			}
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_W:
			if (vel.y >= 0) {

				vel.y = 0.0f;
				changeTexture("textures/PlayerFacingBackIdle.png");
			}
			break;

		case SDL_SCANCODE_S:
			if (vel.y <= 0) {

				vel.y = 0.0f;
				changeTexture("textures/PlayerFacingFrontIdle.png");
			}
			break;

		case SDL_SCANCODE_D:
			if (vel.x >= 0) {

				vel.x = 0.0f;
				changeTexture("textures/PlayerFacingRightIdle.png");
			}
			break;


		case SDL_SCANCODE_A:
			if (vel.x <= 0) {

				vel.x = 0.0f;
				changeTexture("textures/PlayerFacingLeftIdle.png");
			}
			break;

		}

		break;


		// Check to see item in inventory
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			int x, y;
			SDL_GetMouseState(&x, &y);
			TriggerOnAttack(Vec3(x, y, 0), dmgValue);
			break;



		}

	case SDL_MOUSEBUTTONUP:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			// if (item == potion), sword, etc

			changeTexture("textures/Sprite-0012.png");

			break;
		}

		break;
	}
    
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        // Press number to change your current item
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_1:
            currentItem = playerInventory.getItem(0, 0);
            currentItemColumn = 0;
            break;
        case SDL_SCANCODE_2:
            currentItem = playerInventory.getItem(0, 1);
            currentItemColumn = 1;
            break;
        case SDL_SCANCODE_3:
            currentItem = playerInventory.getItem(0, 2);
            currentItemColumn = 2;
            break;
        case SDL_SCANCODE_4:
            currentItem = playerInventory.getItem(0, 3);
            currentItemColumn = 3;
            break;
        case SDL_SCANCODE_5:
            currentItem = playerInventory.getItem(0, 4);
            currentItemColumn = 4;
            break;
        case SDL_SCANCODE_Z:
            playerInventory.removeItem(currentItemRow, currentItemColumn);
            currentItem = playerInventory.getItem(0, currentItemColumn);
            break;
        case SDL_SCANCODE_E:
            if (currentItem != nullptr && currentItem->itemName == "potion") {
                addPlayerHP(3);
                getPlayerHP();
                std::cout << "potion used" << std::endl;
                std::cout << getPlayerHP() << std::endl;
                break;
            }
        }

        setCurrentItem(currentItem);
        // Refresh the icon after item change
        refreshIcons();

        // more of a debug/feedback feature. 
/*		if (currentItem) {
            std::cout << "Selected item: " << currentItem->itemName << std::endl;
        }
        else {
            std::cout << "Selected slot is empty." << std::endl;
        }*/
    }

}



void Player::refreshIcons() {
    // Clear the current icon
    panel.ClearIcons();

    // Add the new icon based on the current item
    if (currentItem != nullptr) {
        // Add the current item's icon
        panel.AddIcon(currentItem->filePath, panelScaling);
    }
    else {
        // If no item, show an empty slot, which is just a plus icon
        panel.AddIcon("textures/emptySlot.png", panelScaling);
    }

    for (int i = 0; i < 5; i++) {
        space[i].ClearIcons();
        if (playerInventory.getItem(0, i) != nullptr) {
            // Add the current item's icon
            space[i].AddIcon(playerInventory.getItem(0, i)->filePath, 0.5f);
        }
        else {
            // If no item, show an empty slot, which is just a plus icon
            space[i].AddIcon("textures/emptySlot.png", 0.5f);
        }
    }
}

void Player::Update(float deltaTime)
{
	Body::Update(deltaTime);

	std::cout << invulTimer << std::endl;
	if (invulTimer > 0)
		invulTimer--;

	//std::cout << region->getFaces(Vec2(pos.x, pos.y), Vec2(vel.x, vel.y)).objectTag << std::endl;
	if (region != nullptr) {
		std::vector<TileFaces> tempFaces;
    //std::cout << invulTimer << std::endl;
		//tempFaces.push_back(region->getFaces(Vec2(pos.x, pos.y), Vec2(vel.x, vel.y)));
		permFaces = region->getFaces(Vec2(pos.x, pos.y), Vec2(vel.x, vel.y));

		hitbox.setObstacles(permFaces);
		//SDL_RenderDrawLine(renderer, 0, 0, 1, 1);
	}



	hitbox.CheckCollision(pos, vel);

	Body::Update(deltaTime);

	hitbox.CheckCollision(pos, vel);

	if (isWallBouncingX) {
		// Gradually reduce horizontal velocity
		if (fabs(vel.x) > 0.01f) {
			vel.x *= wallBounceDecay; // Apply damping
		}
		else {
			vel.x = 0; // Stop when velocity is small enough
		}
		if (vel.x == 0) {
			isWallBouncingX = false; // End bounce-back state
			// End bounce-back state
		}
	}
	else if (isWallBouncingY) {
		// Gradually reduce vertical velocity
		if (fabs(vel.y) > 0.01f) {
			vel.y *= wallBounceDecay; // Apply damping
		}
		else {
			vel.y = 0; // Stop when velocity is small enough
		}

		// Stop bounce-back when both velocities are zero
		if (vel.y == 0) {
			// End bounce-back state
			isWallBouncingY = false; // End bounce-back state
		}
		//else if (vel.x <= 0 && vel.y == 0) {
	}
	//}

	float currentHP = getPlayerHP();
    healthBar->UpdateHealth(currentHP);

	Body::Update(deltaTime);
}

void Player::takeDamage(float damage)
{
	if (isHoldingShield()) {
		damage = 0;
		healthpoints -= damage;
		return;
	}
	else {
		healthpoints -= damage;
		std::cout << "Damaged: " << healthpoints << endl;
		invulTimer = invulTimerMax;
	}
}


//
void Player::setFaces(std::vector<TileFaces> faces_)
{
	hitbox.setObstacles(faces_);
}


void Player::OnDestroy()
{
    // Change to Debug::Info after
    std::cout << ("Deleting player assets: ", __FILE__, __LINE__);
    //delete textureFile;
    //delete texture;

    delete healthBar;
    healthBar = nullptr;

    for (int i = 0; i < 5; i++) {
        space[i].OnDestroy();
    }
    panel.OnDestroy();
}


void Player::onCollisionEnter(const TileFaces& collidedObject)
{

	switch (collidedObject.objectTag)
	{
	case none:
		break;
	case wall:

		if (collidedObject.PointOne.y == collidedObject.PointTwo.y) {
			//
			if (abs(vel.y) != 0) {
				int direction = vel.y > 0 ? 1 : -1;

				if (isWallBouncingY == false)
					vel.y = -direction * 4.0f; // Reverse velocity to simulate bounce-back


				isWallBouncingY = true; // Trigger bounce-back state
			}
		}

		else if (collidedObject.PointOne.x == collidedObject.PointTwo.x) {
			// Vertical wall adjustment
			if (abs(vel.x) != 0) {

				int direction = vel.x > 0 ? 1 : -1;
				if (isWallBouncingX == false)
					vel.x = -direction * 4.0f; // Reverse velocity to simulate bounce-back

				isWallBouncingX = true;// Trigger bounce-back state

			}
		}
		break;

	case enemy:
		if (invulTimer <= 0)
		{
			invulTimer = invulTimerMax;
			std::cout << healthpoints << "\n";
			healthpoints -= 1;
		}
		break;

	case loot:

		break;

	default:
		break;
	}
}

void Player::TriggerOnAttack(Vec3 mousePos, float damage)
{
	if (onAttackCallBack)
		onAttackCallBack(mousePos, damage);

}
/*
bool Player::hasShoes() {
    for (int row = 0; row < 1; ++row) { // Single row
        for (int col = 0; col < 5; ++col) { // 5 columns
            Item* currentItem = playerInventory[row][col];
            if (currentItem != nullptr && currentItem->getName() == "Shoes") {
                return true; // Immediately exit the function if shoes are found
            }
        }
    }
    return false; // If the loop completes, no shoes were found
}
*/
bool Player::isHoldingShield() const {
	if (currentItem && currentItem->itemName == "shield") {
		return true;
	}
	return false;
}
