require("Assets\\Scripts\\Zero\\ZeroState")

ZeroWalkState = {
    __index = ZeroState
}

ZeroWalkState['Owner'] = nil

function ZeroWalkState:OnEnter(owner)
    ZeroWalkState['Owner'] = owner
    ZeroWalkState['Owner']['MoveHorizontal'] = 0

    local animator = owner:GetAnimator()
    animator:SetActiveAnimation("ZeroWalk")
    animator:SetFPS(12)
end

function ZeroWalkState:OnProcessInput(inputState)
    local owner = ZeroWalkState['Owner']
    owner['MoveHorizontal'] = 0

    local animator = owner:GetAnimator()
    local keyboardState = inputState:GetKeyboard()
    if keyboardState:IsPressed(VIKeyCode.A) or keyboardState:IsPressed(VIKeyCode.LEFT) then
        animator:FlipHorizontal(true);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] - 1
    end

    if keyboardState:IsPressed(VIKeyCode.D) or keyboardState:IsPressed(VIKeyCode.RIGHT) then
        animator:FlipHorizontal(false);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] + 1
    end
end

function ZeroWalkState:OnUpdate(deltaTime)
    local owner = ZeroWalkState['Owner']
    local x, y, _ = owner:GetPosition();

    owner:SetPositionX(x + owner['MoveHorizontal'] * owner['Speed'] * deltaTime)
    owner:SetPositionY(y + owner['MoveVertical'] * owner['Speed'] * deltaTime)

    if owner['MoveHorizontal'] == 0 then
        return owner['IdleState']
    end
end

function ZeroWalkState:OnExit()

end

