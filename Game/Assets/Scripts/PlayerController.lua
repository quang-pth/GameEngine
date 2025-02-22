require("Assets\\Scripts\\Core")

PlayerController = PlayerController or {}

PlayerController['MoveHorizontal'] = 0
PlayerController['MoveVertical'] = 0
PlayerController['Speed'] = 5.0

function PlayerController:OnStart()
    print("PlayerController started")
end

function PlayerController:OnProcessInput(inputState)
    self['MoveHorizontal'] = 0
    self['MoveVertical'] = 0

    local keyboardState = inputState:GetKeyboard()
    local mouseInput = inputState:GetMouse()

    local animator = self:GetAnimator()
    if keyboardState:IsPressed(VIKeyCode.A) or keyboardState:IsPressed(VIKeyCode.LEFT) then
        animator:FlipX(true);
        self['MoveHorizontal'] = self['MoveHorizontal'] - 1
    end

    if keyboardState:IsPressed(VIKeyCode.D) or keyboardState:IsPressed(VIKeyCode.RIGHT) then
        animator:FlipX(false);
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
