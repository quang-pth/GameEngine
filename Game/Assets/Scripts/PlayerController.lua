require("Assets\\Scripts\\Core")

PlayerController = PlayerController or {}

PlayerController['MoveHorizontal'] = 0
PlayerController['MoveVertical'] = 0
PlayerController['Speed'] = 5.0

function PlayerController:OnStart()
    print("PlayerController started")

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

    local animator = self:GetAnimator()
    animator:SetFPS(120)
    animator:AddAnimation(idleAnimation)
    animator:AddAnimation(walkAnimation)
    animator:SetActiveAnimation(walkAnimation:GetName())
    animator:FlipVertical(true)

    self:SetPositionX(10.0)
    self:SetPositionY(10.0)
end

function PlayerController:OnProcessInput(inputState)
    self['MoveHorizontal'] = 0
    self['MoveVertical'] = 0

    local keyboardState = inputState:GetKeyboard()
    local mouseInput = inputState:GetMouse()

    local animator = self:GetAnimator()
    if keyboardState:IsPressed(VIKeyCode.A) or keyboardState:IsPressed(VIKeyCode.LEFT) then
        animator:FlipHorizontal(true);
        self['MoveHorizontal'] = self['MoveHorizontal'] - 1
    end

    if keyboardState:IsPressed(VIKeyCode.D) or keyboardState:IsPressed(VIKeyCode.RIGHT) then
        animator:FlipHorizontal(false);
        self['MoveHorizontal'] = self['MoveHorizontal'] + 1
    end

    if keyboardState:IsPressed(VIKeyCode.S) or keyboardState:IsPressed(VIKeyCode.DOWN) then
        self['MoveVertical'] = self['MoveVertical'] + 1
    end

    if keyboardState:IsPressed(VIKeyCode.W) or keyboardState:IsPressed(VIKeyCode.UP) then
        self['MoveVertical'] = self['MoveVertical'] - 1
    end

    if self['MoveHorizontal'] == 0 then
        animator:SetActiveAnimation("ZeroIdle")
        animator:SetFPS(4)
    else
       animator:SetActiveAnimation("ZeroWalk")
       animator:SetFPS(12)
    end
end

function PlayerController:OnUpdate(deltaTime)
    local x, y, _ = self:GetPosition();

    self:SetPositionX(x + self['MoveHorizontal'] * self['Speed'] * deltaTime)
    self:SetPositionY(y + self['MoveVertical'] * self['Speed'] * deltaTime)
end
