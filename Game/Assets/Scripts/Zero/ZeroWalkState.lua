require("Assets\\Scripts\\Zero\\ZeroState")

ZeroWalkState = {}
setmetatable(ZeroWalkState, {
    __index = ZeroState
})

ZeroWalkState['Owner'] = nil
ZeroWalkState['Speed'] = 5.0
ZeroWalkState['TriggerSlide'] = false

function ZeroWalkState:OnEnter(owner)
    self['Owner'] = owner
    local animator = owner:GetAnimator()
    animator:SetActiveAnimation("ZeroWalk")
    animator:SetFPS(12)
    owner['IsReadyToSlide'] = false
end

function ZeroWalkState:OnProcessInput(inputState)
    local owner = self['Owner']
    owner['MoveHorizontal'] = 0
    self['TriggerSlide'] = false

    local animator = owner:GetAnimator()
    local keyboardState = inputState:GetKeyboard()
    if keyboardState:IsPressed(VIKeyCode.A) then
        animator:FlipHorizontal(true);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] - 1
    end
    
    if keyboardState:IsPressed(VIKeyCode.D) then
        animator:FlipHorizontal(false);
        owner['MoveHorizontal'] = owner['MoveHorizontal'] + 1
    end

    if keyboardState:IsPressed(VIKeyCode.LEFT_SHIFT) then
        owner:ResetSlideCooldown()
        self['TriggerSlide'] = true
    end
end

function ZeroWalkState:OnUpdate(deltaTime)
    local owner = self['Owner']

    if owner['MoveHorizontal'] == 0 then
        return owner['IdleState']
    end

    if owner['IsReadyToSlide'] and self['TriggerSlide'] then
        return owner['SlideState']
    end

    local x, y, _ = owner:GetPosition();
    owner:SetPositionX(x + owner['MoveHorizontal'] * self['Speed'] * deltaTime)
    owner:SetPositionY(y + owner['MoveVertical'] * self['Speed'] * deltaTime)
end

function ZeroWalkState:OnExit()

end

