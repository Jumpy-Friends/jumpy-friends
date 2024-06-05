#include "player.hpp"

Player::Player(double worldSpeed) {
    this->worldSpeed = worldSpeed;
}

void Player::ImportModel(const std::string& path, const std::string& texturePath, float scale) {
    Model model = LoadModel(path.c_str());
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture(texturePath.c_str());
    model.transform = MatrixScale(scale, scale, scale);
    models.push_back(model);
    scales.push_back(scale);
}

void Player::SwitchModel() {
    if (!models.empty()) {
        currentModelIndex = (currentModelIndex + 1) % models.size();  // Switch to the next model
    }
}
void Player::Draw() {
    if (!models.empty()) {
        DrawModel(this->models[currentModelIndex], this->position, 1.0f, WHITE);
    }
}
void Player::Update() {
    // Add world movement
    this->position.z -= this->worldSpeed;

    if (this->jumpType == JumpType::None) return;

    if (this->position.y < 0.1) {
        this->position.y = 0.1;
        this->jumpType = JumpType::None;
        return;
    }

    if (this->jumpType == JumpType::Forward)
        this->position.z += 0.5f / (JUMP_SPEED / abs(gravity));
    else if (this->jumpType == JumpType::Left)
        this->position.x += 0.5f / (JUMP_SPEED / abs(gravity));
    else if (this->jumpType == JumpType::Right)
        this->position.x -= 0.5f / (JUMP_SPEED / abs(gravity));
    else if (this->jumpType == JumpType::Backward)
        this->position.z -= 0.5f / (JUMP_SPEED / abs(gravity));

    this->currentSpeed += gravity;
    this->position.y += currentSpeed;
}

void Player::followLog(float speed) {
    this->position.x -= speed;
}

void Player::JumpForward() {
    if (this->jumpType != JumpType::None) return;

    this->currentSpeed = JUMP_SPEED;
    this->jumpType = JumpType::Forward;
}

void Player::JumpLeft() {
    if (this->jumpType != JumpType::None) return;

    this->currentSpeed = JUMP_SPEED;
    this->jumpType = JumpType::Left;
}

void Player::JumpRight() {
    if (this->jumpType != JumpType::None) return;

    this->currentSpeed = JUMP_SPEED;
    this->jumpType = JumpType::Right;
}

void Player::JumpBackward() {
    if (this->jumpType != JumpType::None) return;

    this->currentSpeed = JUMP_SPEED;
    this->jumpType = JumpType::Backward;
}

void Player::resetPos() {
    this->position = Vector3{0, 0.1, 0};
}

BoundingBox Player::GetBoundingBox() const {
    Vector3 min = {this->position.x - 0.15f, this->position.y - 0.15f, this->position.z - 0.15f};
    Vector3 max = {this->position.x + 0.15f, this->position.y + 0.15f, this->position.z + 0.15f};
    return BoundingBox{min, max};
}