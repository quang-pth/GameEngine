require("Assets\\Scripts\\Core")
require("Assets\\Scripts\\Zero\\ZeroIdleState")
require("Assets\\Scripts\\Zero\\ZeroWalkState")
require("Assets\\Scripts\\Zero\\ZeroSlideState")
require("Assets\\Scripts\\Zero\\ZeroBasicAttack1State")
require("Assets\\Scripts\\Zero\\ZeroBasicAttack2State")
require("Assets\\Scripts\\Zero\\ZeroBasicAttack3State")
require("Assets\\Scripts\\Zero\\ZeroJumpState")
require("Assets\\Scripts\\Zero\\ZeroFallingState")
require("Assets\\Scripts\\Zero\\ZeroTouchGroundState")

PlayerController = PlayerController or {}

setmetatable(PlayerController, {
    __index = VIScript
})

PlayerController['MoveHorizontal'] = 0
PlayerController['MoveVertical'] = 0
PlayerController['ActiveState'] = nil
PlayerController['PrevState'] = nil
PlayerController['WalkState'] = ZeroWalkState
PlayerController['IdleState'] = ZeroIdleState
PlayerController['SlideState'] = ZeroSlideState
PlayerController['BasicAttack1State'] = ZeroBasicAttack1State
PlayerController['BasicAttack2State'] = ZeroBasicAttack2State
PlayerController['BasicAttack3State'] = ZeroBasicAttack3State
PlayerController['JumpState'] = ZeroJumpState
PlayerController['FallingState'] = ZeroFallingState
PlayerController['TouchGroundState'] = ZeroTouchGroundState
PlayerController['IsReadyToSlide'] = true
PlayerController['SlideCooldownSeconds'] = -1.0
PlayerController['HaveTouchedGround'] = false

function PlayerController:OnStart()
    local idleAnimation = Animation.Create("ZeroIdle");
    idleAnimation:AddSprite("Assets/Sprite/Zero/idle/idle00.png")
	idleAnimation:AddSprite("Assets/Sprite/Zero/idle/idle01.png")
	idleAnimation:AddSprite("Assets/Sprite/Zero/idle/idle02.png")
	idleAnimation:AddSprite("Assets/Sprite/Zero/idle/idle03.png")
	idleAnimation:AddSprite("Assets/Sprite/Zero/idle/idle04.png")
	idleAnimation:AddSprite("Assets/Sprite/Zero/idle/idle05.png")

    local walkAnimation = Animation.Create("ZeroWalk");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk01.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk02.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk03.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk04.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk05.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk06.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk07.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk08.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk09.png");
	walkAnimation:AddSprite("Assets/Sprite/Zero/walk/walk10.png");

    local basicAttack1 = Animation.Create("ZeroBasicAttack1")
    basicAttack1:AddSprite("Assets/Sprite/Zero/basic_attack1/basic_attack1_00.png");
    basicAttack1:AddSprite("Assets/Sprite/Zero/basic_attack1/basic_attack1_01.png");
    basicAttack1:AddSprite("Assets/Sprite/Zero/basic_attack1/basic_attack1_02.png");
    basicAttack1:AddSprite("Assets/Sprite/Zero/basic_attack1/basic_attack1_03.png");
    basicAttack1:AddSprite("Assets/Sprite/Zero/basic_attack1/basic_attack1_04.png");
    basicAttack1:AddSprite("Assets/Sprite/Zero/basic_attack1/basic_attack1_05.png");
    basicAttack1:AddSprite("Assets/Sprite/Zero/basic_attack1/basic_attack1_06.png");
    basicAttack1:AddSprite("Assets/Sprite/Zero/basic_attack1/basic_attack1_07.png");
    basicAttack1:SetIsLoop(false)

    local basicAttack2 = Animation.Create("ZeroBasicAttack2")
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_00.png");
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_01.png");
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_02.png");
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_03.png");
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_04.png");
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_05.png");
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_06.png");
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_07.png");
    basicAttack2:AddSprite("Assets/Sprite/Zero/basic_attack2/basic_attack2_08.png");
    basicAttack2:SetIsLoop(false)

    local basicAttack3 = Animation.Create("ZeroBasicAttack3")
    -- basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_00.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_01.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_02.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_03.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_04.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_05.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_06.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_07.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_08.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_09.png");
    basicAttack3:AddSprite("Assets/Sprite/Zero/basic_attack3/basic_attack3_10.png");
    basicAttack3:SetIsLoop(false)
    
    local slideState = Animation.Create("ZeroSlide")
    slideState:AddSprite("Assets/Sprite/Zero/slide/slide00.png");
    slideState:AddSprite("Assets/Sprite/Zero/slide/slide01.png");
    slideState:AddSprite("Assets/Sprite/Zero/slide/slide02.png");
    slideState:AddSprite("Assets/Sprite/Zero/slide/slide03.png");
    slideState:AddSprite("Assets/Sprite/Zero/slide/slide04.png");
    slideState:AddSprite("Assets/Sprite/Zero/slide/slide05.png");
    slideState:AddSprite("Assets/Sprite/Zero/slide/slide06.png");
    slideState:SetIsLoop(false)

    local jumpState = Animation.Create("ZeroJump")
    jumpState:AddSprite("Assets/Sprite/Zero/jump/jump00.png");
    jumpState:AddSprite("Assets/Sprite/Zero/jump/jump01.png");
    jumpState:AddSprite("Assets/Sprite/Zero/jump/jump02.png");
    jumpState:AddSprite("Assets/Sprite/Zero/jump/jump03.png");
    jumpState:AddSprite("Assets/Sprite/Zero/jump/jump04.png");
    jumpState:AddSprite("Assets/Sprite/Zero/jump/jump05.png");
    jumpState:SetIsLoop(false)
    
    local fallingState = Animation.Create("ZeroFalling")
    fallingState:AddSprite("Assets/Sprite/Zero/jump/jump06.png");
    fallingState:AddSprite("Assets/Sprite/Zero/jump/jump07.png");
    fallingState:AddSprite("Assets/Sprite/Zero/jump/jump08.png");
    fallingState:AddSprite("Assets/Sprite/Zero/jump/jump09.png");
    fallingState:SetIsLoop(true)
    
    local touchGroundState = Animation.Create("ZeroTouchGround")
    touchGroundState:AddSprite("Assets/Sprite/Zero/jump/jump10.png");
    touchGroundState:AddSprite("Assets/Sprite/Zero/jump/jump11.png");
    touchGroundState:SetIsLoop(false)

    local animator = self:AddAnimator()
    animator:AddAnimation(idleAnimation)
    animator:AddAnimation(walkAnimation)
    animator:AddAnimation(basicAttack1)
    animator:AddAnimation(basicAttack2)
    animator:AddAnimation(basicAttack3)
    animator:AddAnimation(slideState)
    animator:AddAnimation(jumpState)
    animator:AddAnimation(fallingState)
    animator:AddAnimation(touchGroundState)
    animator:SetActiveAnimation(walkAnimation:GetName())
    animator:FlipVertical(false)

    self:SetPositionX(10.0)
    self:SetPositionY(15.0)

    local box2D = self:AddBox2D()
    box2D:SetWidth(0.5)
    box2D:SetHeight(1.25)
    
    local rigidBody = self:AddRigidBody()
    rigidBody:SetDensity(1.0)
    rigidBody:SetFriction(1.0)
    rigidBody:SetBodyType(VIPhysic.BodyType.DYNAMIC)
    rigidBody:SetGravityScale(1.0)
    rigidBody:SetLinearDamping(10.0)
    rigidBody:SetFixedRotation(true)

    self['ActiveState'] = ZeroIdleState
    self['ActiveState']:OnEnter(self)
end

function PlayerController:OnProcessInput(inputState)
    self['ActiveState']:OnProcessInput(inputState)

    -- local mouseState = inputState:GetMouse()
    -- if mouseState:IsPressed(VIMouseButton.BUTTON_LEFT) then
    --     self:SetPositionY(5.0)
    -- end
end

function PlayerController:OnUpdate(deltaTime)
    local box2D = self:GetBox2D()
    box2D:SetWidth(self:GetAnimator():GetWidth() * 0.01)
    box2D:SetHeight(self:GetAnimator():GetHeight() * 0.018)

    local nextState = self['ActiveState']:OnUpdate(deltaTime)
    if nextState ~= nil and nextState ~= self['ActiveState'] then
        self['PrevState'] = self['ActiveState']
        self['ActiveState']:OnExit()
        self['ActiveState'] = nextState
        self['ActiveState']:OnEnter(self)
    end

    if self['ActiveState'] ~= ZeroSlideState then
        self['SlideCooldownSeconds'] = self['SlideCooldownSeconds'] - deltaTime
    end
    if not self['IsReadyToSlide'] and self['SlideCooldownSeconds'] < 0.0 then
        self:ResetSlideCooldown()
        self['IsReadyToSlide'] = true
    end
end

function PlayerController:OnCollision(collision)
    self['ActiveState']:OnCollision(collision)
end

function PlayerController:OnMouseButtonPressed(button)
    self['ActiveState']:OnMouseButtonPressed(button)
end

function PlayerController:ResetSlideCooldown()
    self['SlideCooldownSeconds'] = 0.05
end